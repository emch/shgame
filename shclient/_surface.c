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
 * \param	border_radius
 * \param	border_color
 * \param	myLogger
 *
 * \returns	pointer to created SHSurface
 */
SHSurface* NewSurface(int width, int height, SHSurface* parent, int pos_x, int pos_y, int visible,
		SH_STORED_COLOR bck_color,
		int border_width, SH_STORED_COLOR border_color,
		SHLogger* myLogger) {

	int bckWidth = width, bckHeight = height;

	SHSurface* res = malloc(sizeof(SHSurface));
	SHColor* sh_bck_color = GetColorData(bck_color);
	SHColor* sh_border_color = GetColorData(border_color);

	SDL_Rect* res_pos = malloc(sizeof(SDL_Rect));
	SDL_Surface *res_bck = NULL;
	SDL_Surface *res_border_tc = NULL, *res_border_ml = NULL, *res_border_mr = NULL, *res_border_bc = NULL;
	//*res_border_tl = NULL,

	if(border_width <= 0) { // no border
		res_bck = SDL_CreateRGBSurface(SDL_HWSURFACE, bckWidth, bckHeight, 32, 0, 0, 0, 0);
		res_pos->x = pos_x; res_pos->y = pos_y;
	} else {
		bckWidth -= 2*border_width; bckHeight -= 2*border_width;
		res_bck = SDL_CreateRGBSurface(SDL_HWSURFACE, bckWidth, bckHeight, 32, 0, 0, 0, 0);

		// Move background center at the right position
		res_pos->x = pos_x + border_width; res_pos->y = pos_y + border_width;

		// Create other surfaces (rounded corners especially !)
		res_border_tc = SDL_CreateRGBSurface(SDL_HWSURFACE, bckWidth, border_width, 32, 0, 0, 0, 0);
		res_border_ml = SDL_CreateRGBSurface(SDL_HWSURFACE, border_width, bckHeight, 32, 0, 0, 0, 0);
		res_border_mr = SDL_CreateRGBSurface(SDL_HWSURFACE, border_width, bckHeight, 32, 0, 0, 0, 0);
		res_border_bc = SDL_CreateRGBSurface(SDL_HWSURFACE, bckWidth, border_width, 32, 0, 0, 0, 0);

		// border radius equals border_width !
	}

	// Checking if surface was correctly defined
	if(res_bck == NULL) {
		flogf(myLogger, "Failed to create SDL surface : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	// Filling fields
	res->bck 			= res_bck;
	res->bck_color		= sh_bck_color;

	res->border_width 	= border_width;
	res->border_color	= sh_border_color;

	res->border_tc		= res_border_tc;
	res->border_ml		= res_border_ml;
	res->border_mr		= res_border_mr;
	res->border_bc		= res_border_bc;

	res->parent 		= parent;
	res->sdl_pos 		= res_pos;
	res->visible		= visible;

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

//	SDL_FreeSurface(surface->border_tl);
	SDL_FreeSurface(surface->border_tc);
//	SDL_FreeSurface(surface->border_tr);
	SDL_FreeSurface(surface->border_ml);
	SDL_FreeSurface(surface->border_mr);
//	SDL_FreeSurface(surface->border_bl);
	SDL_FreeSurface(surface->border_bc);
//	SDL_FreeSurface(surface->border_br);

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
	// Temporary SDL_Rect for positionning border
	SDL_Rect pos;
	pos.x = surface->sdl_pos->x; pos.y = surface->sdl_pos->y;

	// Background
	SDL_FillRect(surface->bck, NULL, SDL_MapRGB(surface->bck->format,
			surface->bck_color->r, surface->bck_color->g, surface->bck_color->b));

	// if((surface->parent != NULL) && (surface->visible != 0)) {
	if(surface->visible != 0) { // temporaire
		SDL_BlitSurface(surface->bck, NULL, parent_surface, surface->sdl_pos);

		// Border
		if(surface->border_width > 0) {
			// Border (problem here !!)
			SDL_FillRect(surface->border_tc, NULL, SDL_MapRGB(surface->border_tc->format,
					surface->border_color->r, surface->border_color->g, surface->border_color->b));
			SDL_FillRect(surface->border_ml, NULL, SDL_MapRGB(surface->border_ml->format,
					surface->border_color->r, surface->border_color->g, surface->border_color->b));
			SDL_FillRect(surface->border_mr, NULL, SDL_MapRGB(surface->border_mr->format,
					surface->border_color->r, surface->border_color->g, surface->border_color->b));
			SDL_FillRect(surface->border_bc, NULL, SDL_MapRGB(surface->border_bc->format,
					surface->border_color->r, surface->border_color->g, surface->border_color->b));

			// Blitting border
			pos.y -= surface->border_width;
			SDL_BlitSurface(surface->border_tc, NULL, parent_surface, &pos);
			pos.x -= surface->border_width; pos.y += surface->border_width;
			SDL_BlitSurface(surface->border_ml, NULL, parent_surface, &pos);
			pos.x += surface->border_width + surface->bck->w;
			SDL_BlitSurface(surface->border_mr, NULL, parent_surface, &pos);
			pos.x -= surface->bck->w; pos.y += surface->bck->h;
			SDL_BlitSurface(surface->border_bc, NULL, parent_surface, &pos);
		}
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
