/*
 * main.c
 *
 *  Created on: 23 d�c. 2013
 *      Author: Emmanuel
 */

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

#include "shclient.h"
#include "shdata.h"
#include "params.h"

void loop(SDL_Surface*, SHSurface*, SHSurface*); // nombre variable de param�tres ?

// 2 threads : updates serveur et update graphiques

int main(int argc, char *argv[]) {
	// Initialization
	SHLogger* myLogger = CreateLogger("shclient.log"); // logging device

	SDL_Surface *screen = NULL;
	SHSurface *players = NULL, *board = NULL; //, *items = NULL, *chat = NULL, *msgbox = NULL;

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
    		SCREEN_WIDTH - BOARD_SURF_WIDTH - PADDING, PADDING, 1, 255, 255, 255, myLogger);
    players = NewSurface(PLYRLIST_SURF_WIDTH, PLYRLIST_SURF_HEIGHT, NULL,
    		PADDING, PADDING, 1, 255, 255, 255, myLogger);
    // End of Initialization !!

    // Main loop
    // to be improved (array of SHSurface pointers ?)
    loop(screen, board, players);

    // Garbage collector
    // idem
    DestroySurface(board, myLogger);
    DestroySurface(players, myLogger);
    SDL_Quit();

    // Last but not least, destroy logger !
    flogf(myLogger, "Client closed successfully\r\n");
    DestroyLogger(myLogger);

    // End of program
    return EXIT_SUCCESS;
}

// SDL update loop (main thread)
void loop(SDL_Surface* screen, SHSurface* board, SHSurface* players)
{
    int done = 0;
    SDL_Event event;

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
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 100, 100, 100));

        // Board update
        RenderSurface(board, screen);
        RenderSurface(players, screen);

        // Flipping buffer
        SDL_Flip(screen);

        // Maximum FPS constraint
        SDL_Delay(1000/MAX_FPS);
    }
}
