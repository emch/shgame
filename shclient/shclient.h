/*
 * shclient.h
 *
 *  Created on: 28 d�c. 2013
 *      Author: Emmanuel
 */

#ifndef SHCLIENT_H_
#define SHCLIENT_H_

#include <SDL/SDL.h>

#include "shdata.h"

/********************************* _surface ********************************/
typedef struct _surface SHSurface;

struct _surface {
	SDL_Surface*	sdl_surf;
	SHSurface*		parent;		// if not null, sld_pos is defined relatively to the parent
	SDL_Rect*		sdl_pos;
	int				visible;
	int				r;
	int				g;
	int				b;
};

// Prototypes
SHSurface* NewSurface(int, int, SHSurface*, int, int, int, int, int, int, SHLogger*);
void DestroySurface(SHSurface*, SHLogger*);
void RenderSurface(SHSurface*, SDL_Surface*);
void SetVisible(SHSurface*, int);
/***************************************************************************/

// SHButton

#endif /* SHCLIENT_H_ */
