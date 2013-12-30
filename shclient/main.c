/*
 * main.c
 *
 *  Created on: 23 d�c. 2013
 *      Author: Emmanuel
 */

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "shclient.h"
#include "shdata.h"
#include "params.h"

void GameLoop(SDL_Surface*, SHSurface**); // nombre variable de param�tres ?

// 2 threads : updates serveur et update graphiques

int main(int argc, char *argv[]) {
	// Initialization
	int surfRenderCmpt = 0;
	SHLogger* myLogger = CreateLogger("shclient.log"); 	// logging device

	char gameLoggerFilename [40];
	sprintf(gameLoggerFilename, "gamelog_%02d-%02d-%04d_%02d-%02d-%02d.txt",
			myLogger->now.tm_mon+1, myLogger->now.tm_mday, myLogger->now.tm_year+1900,
			myLogger->now.tm_hour, myLogger->now.tm_min, myLogger->now.tm_sec);
	SHLogger* gameLogger = CreateLogger(gameLoggerFilename);	// game logger

	SDL_Surface *screen = NULL;
	SHSurface *players = NULL, *board = NULL, *gamelog = NULL, *items = NULL, *dice = NULL;
	//*msgbox = NULL, *curr_card = NULL;
	// load a background image for msgbox and curr_card (transparency) ?

	// Initializing SDL
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) == -1) {
        flogf(myLogger, "Failed to initialize SDL : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_WM_SetCaption("SHClient", NULL);

    // SDL started successfully
    flogf(myLogger,"SDL initialized\r\n");

    // Creating rendering surface
    if((screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
    	flogf(myLogger, "Failed to set video mode : %s\n", SDL_GetError());
    	exit(EXIT_FAILURE);
    }
    flogf(myLogger,"Video mode set\r\n");

    // Creating surfaces (to be rendered through screen surface)
    board 	= NewSurface(BOARD_SURF_WIDTH, BOARD_SURF_HEIGHT, NULL,
    		SCREEN_WIDTH - BOARD_SURF_WIDTH - PADDING, PADDING, 1,
    		SH_WHITE, -1, 0, SH_NONE, myLogger); // no border here (image will be loaded)
    players = NewSurface(PLYRLIST_SURF_WIDTH, PLYRLIST_SURF_HEIGHT, NULL,
    		PADDING, PADDING, 1,
    		SH_BURLYWOOD, BORDER_WIDTH, 1, SH_BURLYWOOD, myLogger);
    gamelog = NewSurface(GAMELOG_SURF_WIDTH, GAMELOG_SURF_HEIGHT, NULL,
    		SCREEN_WIDTH - GAMELOG_SURF_WIDTH - PADDING, SCREEN_HEIGHT - GAMELOG_SURF_HEIGHT - PADDING, 1,
    		SH_IVORY, BORDER_WIDTH, 1, SH_IVORY, myLogger);
    items	= NewSurface(ITEMS_SURF_WIDTH, ITEMS_SURF_HEIGHT, NULL,
    		PADDING, SCREEN_HEIGHT - GAMELOG_SURF_HEIGHT - PADDING, 1,
    		SH_BURLYWOOD, BORDER_WIDTH, 1, SH_BURLYWOOD, myLogger);
    dice	= NewSurface(DICE_SURF_WIDTH, DICE_SURF_HEIGHT, NULL,
    		2*PADDING + ITEMS_SURF_WIDTH, SCREEN_HEIGHT - GAMELOG_SURF_HEIGHT - PADDING, 1,
    		SH_YELLOW_GREEN, BORDER_WIDTH, 1, SH_YELLOW_GREEN, myLogger);
    // Stacking all surfaces to be rendered
    SHSurface *surfaces [5] = {board, players, gamelog, items, dice};
    // End of Initialization !!

    // Main loop
    GameLoop(screen, surfaces);

    // Garbage collector
    // idem
    for(surfRenderCmpt = 0; surfRenderCmpt < 5; surfRenderCmpt++) {
    	DestroySurface(surfaces[surfRenderCmpt], myLogger);
	}
    SDL_Quit();

    // Last but not least, destroy logger !
    flogf(myLogger, "Client closed\r\n");
    DestroyLogger(gameLogger); DestroyLogger(myLogger);

    // End of program
    return EXIT_SUCCESS;
}

// SDL update loop (main thread)
void GameLoop(SDL_Surface* screen, SHSurface** surfaces)
{
    int done = 0, surfRenderCmpt = 0;
    SDL_Event event;

    // detection de clic et de la SDL_surface cliqu�e (bouton, ...)
    while (!done)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                done = 1;
                break;
        }

        // Screen update
//        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 200, 200, 200));
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));

        // Board update
        for(surfRenderCmpt = 0; surfRenderCmpt < 5; surfRenderCmpt++) {
        	RenderSurface(surfaces[surfRenderCmpt], screen);
        }

        // Flipping buffer
        SDL_Flip(screen);

        // Maximum FPS constraint
        SDL_Delay(1000/MAX_FPS);
    }
}

// plan a ConnectLoop, ErrorLoop, ...
