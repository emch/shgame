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

/********************************** _color **********************************/
// http://www.tayloredmktg.com/rgb/
typedef enum _stored_colors {
	SH_BLACK, SH_WHITE, SH_DARK_ORANGE, SH_NONE
} SH_STORED_COLOR;

typedef struct _color SHColor;

struct _color {
	int	r; int g; int b;
};

// Prototypes
SHColor* CreateColor(int, int, int);
void DestroyColor(SHColor*);
SHColor* GetColorData(SH_STORED_COLOR);
/***************************************************************************/

/********************************* _surface ********************************/
typedef struct _surface SHSurface;

struct _surface {
	SDL_Surface*	bck;		// background
	SHColor*		bck_color;
	int				border_width;
	SHColor*		border_color;
	SHSurface*		parent;		// if not null, sld_pos is defined relatively to the parent
	SDL_Rect*		sdl_pos;
	int				visible;
};

// Prototypes
SHSurface* NewSurface(int, int, SHSurface*, int, int, int, SH_STORED_COLOR, int, SH_STORED_COLOR, SHLogger*);
void DestroySurface(SHSurface*, SHLogger*);
void RenderSurface(SHSurface*, SDL_Surface*);
void SetVisible(SHSurface*, int);
/***************************************************************************/

// SHButton

#endif /* SHCLIENT_H_ */
