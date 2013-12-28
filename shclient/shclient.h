/*
 * shclient.h
 *
 *  Created on: 28 d�c. 2013
 *      Author: Emmanuel
 */

#ifndef SHCLIENT_H_
#define SHCLIENT_H_

#include <SDL/SDL.h>

/********************************* _surface ********************************/
typedef struct _surface {
	SDL_Surface*	sdl_surf;
	SDL_Rect*		sdl_pos;
	SDL_Surface*	parent;		// if not null, sld_pos is defined relatively to the parent
	int				visible;
	int				r;
	int				g;
	int				b;
} SHSurface;

// Prototypes
SHSurface* NewSurface(SHSurface*);
void DestroySurface(SHSurface*);
void RenderSurface(SHSurface*);
void SetVisible(SHSurface*, int);
/***************************************************************************/

#endif /* SHCLIENT_H_ */