/*
 * main.c
 *
 *  Created on: 23 d�c. 2013
 *      Author: Emmanuel
 */

#include <stdlib.h>

#include "shdata.h"

int main(int argc, char *argv[]) {
	// Initialization
	SHLogger* myLogger = CreateLogger("shserver.log"); // logging device
	// loader
	// loading
	// starting TCP/IP handling and listening (threads)
	// first player sends the start command

	// Main loop and threads management
	// TODO command thread
	int i = 0;
	i = 45;
	flogf(myLogger,"i equals %d\n",i);
	flogf(myLogger,"blabla");

	// Garbage collector
	DestroyLogger(myLogger);

	// End of program
	return EXIT_SUCCESS;
}

