/*
 * _surface.c
 *
 *  Created on: 28 déc. 2013
 *      Author: Emmanuel
 */

#include <stdlib.h>

#include "shclient.h"

SHSurface* NewSurface(SHSurface* parent) {
	return NULL;
}

/**
 * \fn		DestroySurface
 * \brief	Removes all fields of an SHSurface from memory
 *
 * \param	surface	pointer to surface to destroy
 */
void DestroySurface(SHSurface* surface) {
	SDL_FreeSurface(surface->sdl_surf);
	free(surface->sdl_pos);
}

/**
 * \fn		RenderSurface
 * \brief	Renders a surface when called in rendering loop
 *
 * \param	surface	pointer to surface to render
 */
void RenderSurface(SHSurface* surface) {
	// blit etc ...
	SDL_FillRect(surface->sdl_surf, NULL, SDL_MapRGB(surface->sdl_surf->format, 255, 255, 255));

	if((surface->parent != NULL) && (surface->visible != 0)) {
		SDL_BlitSurface(surface->sdl_surf, NULL, surface->parent, surface->sdl_pos);
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
