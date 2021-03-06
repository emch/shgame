/*
 * _loader.c - Used to load graphical content. For game content, use _loader.c from shdata.
 *
 *  Created on: 1 janv. 2014
 *      Author: Emmanuel
 */

#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "shclient.h"

/**
 * \fn		LoadImage
 * \brief	Load image into memory from a given location
 *
 * \param	folder		(relative) path to file without filename. e.g. : data/art/
 * \param	name		image name
 * \param	myLogger	let's log!
 */
SHImage* LoadImage(char* folder, char* name, SHLogger* myLogger) {
	char completePath[DATA_MAX_PATH_LENGTH] = "";
	SHImage* res = malloc(sizeof(SHImage));

	// Generate complete path
	strcpy(completePath, folder);
	strcat(completePath, name);

	// Filling SHImage fields
	strcpy(res->name, name);
	res->surface = IMG_Load(completePath);

	flogf(myLogger, "Image created at address 0x%p", res);
	return res;
}

/**
 * \fn		DestroyImage
 * \brief	Cleans an SHImage from memory
 *
 * \param	image	SHImage to clean
 * \param	myLogger	let's log!
 */
void DestroyImage(SHImage* image, SHLogger* myLogger) {
	SDL_FreeSurface(image->surface);
	flogf(myLogger, "Image at address 0x%p destroyed", image);
	free(image);
}

// TODO to develop !
SHImage** LoadImages(char* location, SHLogger* myLogger) {
	int nb_images = 5; // TODO how to get number of files in a given folder ?
	SHImage** res = malloc(nb_images*sizeof(SHImage*));



	return res;
}

SHImage* GetImageByName(SHImage** imglib, char* name) {
	return NULL;
}

/**
 * \fn		UnloadImages
 * \brief	Unload all images stored into a given SHImage* array
 *
 * \param	imglib		images "library"
 * \param	myLogger	let's log!
 */
void UnloadImages(SHImage** imglib, SHLogger* myLogger) {
	int i;
	int imglib_size = sizeof(imglib)/sizeof(SHImage*);

	for(i = 0; i < imglib_size; i++) {
		DestroyImage(imglib[i], myLogger);
	}
}

// LoadSurfaces() ? --> not sure
