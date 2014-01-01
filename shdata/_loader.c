/*
 * _loader.c - data loader : creates hashtable from files arborescence
 *
 *  Created on: 26 d�c. 2013
 *      Author: Emmanuel
 */

// folders & files --> hashtables (using parser) --> arrays of structures (using loader and specific structures)

// use a tree structure
// before adding a node for a folder, determine the number of its children recursively
// if it is a file, no children !

#include "shdata.h"

// we do not load anything here but we just get the arborescence
// other functions will take care of loading : images in SDL_Surfaces and files in SHHashtables
SHNode* GetDataArborescence(char* root) {
	return NULL;
}
