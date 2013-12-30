#include "shclient.h"

SHColor* CreateColor(int r, int g, int b) {
	SHColor* res = malloc(sizeof(SHColor));
	res->r = r; res->g = g; res->b = b;
	return res;
}

void DestroyColor(SHColor* color) {
	free(color);
}

SHColor* GetColorData(SH_STORED_COLOR input) {
	SHColor* color = CreateColor(255, 255, 255);
	switch(input) {
	case SH_BLACK:
		color = CreateColor(0, 0, 0);
		break;
	case SH_DARK_ORANGE:
		color = CreateColor(255, 140, 0);
		break;
	default: // WHITE
		break;
	}
	return color;
}
