/*
 * _surface.c
 *
 *  Created on: 28 d�c. 2013
 *      Author: Emmanuel
 */

#include <stdlib.h>

#include "shclient.h"
#include "shdata.h"

// Double buffered hardware rendered surface
// cannot be used for screen (main renderer)
SHSurface* NewSurface(int width, int height, SHSurface* parent, int pos_x, int pos_y, int visible, int r, int g, int b, SHLogger* myLogger) {
	SHSurface* res = malloc(sizeof(SHSurface));
	SDL_Surface* res_surf = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, 32, 0, 0, 0, 0);
	SDL_Rect* res_pos = malloc(sizeof(SDL_Rect));
	res_pos->x = pos_x; res_pos->y = pos_y;

	if(res_surf == NULL) {
		flogf(myLogger, "Failed to set video mode : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	// Filling fields
	res->sdl_surf 	= res_surf;
	res->parent 	= parent;
	res->sdl_pos 	= res_pos;
	res->visible	= visible;
	res->r			= r;
	res->g			= g;
	res->b			= b;

	flogf(myLogger, "Surface created successfully at address 0x%p\r\n", res);
	return res;
}

/**
 * \fn		DestroySurface
 * \brief	Removes all fields of an SHSurface from memory
 *
 * \param	surface		pointer to surface to destroy
 * \param	myLogger	pointer to logging "device"
 */
void DestroySurface(SHSurface* surface, SHLogger* myLogger) {
	SDL_FreeSurface(surface->sdl_surf);
	free(surface->sdl_pos);
	flogf(myLogger, "Surface at address 0x%p destroyed successfully\r\n", surface);
}

/**
 * \fn		RenderSurface
 * \brief	Renders a surface when called in rendering loop
 *
 * \param	surface	pointer to surface to render
 * \param	parent_surface	TEMPORAIRE !!
 */
void RenderSurface(SHSurface* surface, SDL_Surface* parent_surface) {
	// blit etc ...
	SDL_FillRect(surface->sdl_surf, NULL, SDL_MapRGB(surface->sdl_surf->format,
			surface->r, surface->g, surface->b));

//	if((surface->parent != NULL) && (surface->visible != 0)) {
	if(surface->visible != 0) { // temporaire
//		SDL_BlitSurface(surface->sdl_surf, NULL, surface->parent->sdl_surf, surface->sdl_pos);
		SDL_BlitSurface(surface->sdl_surf, NULL, parent_surface, surface->sdl_pos);
	}
}

/**
 * \fn		SetVisible
 * \brief	Changes visible status
 *
 * \param	surface	pointer to surface to set visible or not
 * \param	visible	any integer value, 0 meaning false
 */
void SetVisible(SHSurface* surface, int visible) {
	surface->visible = visible;
}
