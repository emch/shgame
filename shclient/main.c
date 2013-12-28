/*
 * main.c
 *
 *  Created on: 23 d�c. 2013
 *      Author: Emmanuel
 */

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

#include "shdata.h"
#include "params.h"

void loop(SDL_Surface*, SDL_Surface*, SDL_Surface*); // nombre variable de param�tres ?

// 2 threads : updates serveur et update graphiques

int main(int argc, char *argv[]) {
	// Initialization
	SHLogger* myLogger = CreateLogger("shclient.log"); // logging device

	SDL_Surface *screen = NULL, *board = NULL, *players = NULL;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) == -1)
    {
        flogf(myLogger, "Failed to initialize SDL : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // SDL started successfully
    flogf(myLogger,"SDL initialized\r\n");

    if((screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
    	flogf(myLogger, "Failed to set video mode : %s\n", SDL_GetError());
    	exit(EXIT_FAILURE);
    }

    flogf(myLogger,"Video mode set\r\n");
    SDL_WM_SetCaption("SHClient", NULL);

    if((board = SDL_CreateRGBSurface(SDL_SWSURFACE, BOARD_SURF_WIDTH, BOARD_SURF_HEIGHT, 32, 0, 0, 0, 0)) == NULL) {
    	flogf(myLogger, "Failed to initialize board surface : %s\n", SDL_GetError());
    	exit(EXIT_FAILURE);
    }
    flogf(myLogger,"Board surface initialized\r\n");

    players = SDL_CreateRGBSurface(SDL_SWSURFACE, PLYRLIST_SURF_WIDTH, PLYRLIST_SURF_HEIGHT, 32, 0, 0, 0, 0);
    // End of Initialization !!

    // Main loop
    loop(screen, board, players);

    // Garbage collector
    SDL_FreeSurface(board);
    SDL_FreeSurface(players);
    SDL_Quit();
    DestroyLogger(myLogger);

    // End of program
    return EXIT_SUCCESS;
}

// SDL update loop (main thread)
void loop(SDL_Surface* screen, SDL_Surface* board, SDL_Surface* players)
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
        SDL_FillRect(board, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
        SDL_Rect board_pos;
        board_pos.x = SCREEN_WIDTH - BOARD_SURF_WIDTH - PADDING;
        board_pos.y = PADDING;
        SDL_BlitSurface(board, NULL, screen, &board_pos);

        // Players list update
		SDL_FillRect(players, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
		SDL_Rect players_pos;
		players_pos.x = PADDING;
		players_pos.y = PADDING;
		SDL_BlitSurface(players, NULL, screen, &players_pos);

        // Flipping buffer
        SDL_Flip(screen);

        // Maximum FPS constraint
        SDL_Delay(1000/MAX_FPS);
    }
}