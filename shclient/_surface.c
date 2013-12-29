/*
 * _surface.c
 *
 *  Created on: 28 d�c. 2013
 *      Author: Emmanuel
 */

#include <stdlib.h>

#include "shclient.h"
#include "shdata.h"

/**
 * \fn		NewSurface
 * \brief	Creates a surface (detailed parameters)
 *
 * \param	width
 * \param	height
 * \param	parent			pointer to parent surface. Position is defined relatively to this parent if it exists
 * \param	pos_x
 * \param	pos_y
 * \param	visible
 * \param	bck_color
 * \param	border_width
 * \param	border_color
 * \param	myLogger
 *
 * \returns	pointer to created SHSurface
 */
SHSurface* NewSurface(int width, int height, SHSurface* parent, int pos_x, int pos_y, int visible,
		SH_STORED_COLOR bck_color, int border_width, SH_STORED_COLOR border_color, SHLogger* myLogger) {

	SHSurface* res = malloc(sizeof(SHSurface));
	SDL_Rect* res_pos = malloc(sizeof(SDL_Rect));
	res_pos->x = pos_x; res_pos->y = pos_y;
	SHColor* sh_bck_color = GetColorData(bck_color);
	SHColor* sh_border_color = GetColorData(border_color);

	SDL_Surface* res_surf = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, 32, 0, 0, 0, 0);

	// Checking if surface was correctly defined
	if(res_surf == NULL) {
		flogf(myLogger, "Failed to set video mode : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	// Filling fields
	res->bck 			= res_surf;
	res->bck_color		= sh_bck_color;
	res->parent 		= parent;
	res->sdl_pos 		= res_pos;
	res->visible		= visible;
	res->border_width 	= border_width;
	res->border_color	= sh_border_color;

	// Logging and sending back result
	flogf(myLogger, "Surface created at address 0x%p\r\n", res);
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
	SDL_FreeSurface(surface->bck);
	free(surface->bck_color);
	free(surface->border_color);
	free(surface->sdl_pos);
	flogf(myLogger, "Surface at address 0x%p destroyed\r\n", surface);
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
	SDL_FillRect(surface->bck, NULL, SDL_MapRGB(surface->bck->format,
			surface->bck_color->r, surface->bck_color->g, surface->bck_color->b));

//	if((surface->parent != NULL) && (surface->visible != 0)) {
	if(surface->visible != 0) { // temporaire
		SDL_BlitSurface(surface->bck, NULL, parent_surface, surface->sdl_pos);
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
