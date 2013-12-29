/*
 * _logger.c
 *
 *  Created on: 26 d�c. 2013
 *      Author: Emmanuel
 */

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "shdata.h"

/**
 * \fn		CreateLogger
 * \brief	Creates a logging file in executable directory
 *
 * \param	output_name	desired output file name
 * \returns	pointer to logging "device"
 */
SHLogger* CreateLogger(char* output_name) {
	SHLogger* mylogger = malloc(sizeof(SHLogger));
	FILE* myfile = fopen(output_name, "w");

	strcpy(mylogger->filename, output_name); // TODO check properties considering size
	mylogger->file = myfile;
	time(&mylogger->timestamp);
	mylogger->now = *localtime(&mylogger->timestamp);

	// Some basic information
//	fprintf(mylogger->file, "%s\r\n", "SHServer Logging File");
//	fprintf(mylogger->file, "Generated on %02d-%02d-%04d",
//			mylogger->now.tm_mon+1, mylogger->now.tm_mday, mylogger->now.tm_year+1900);
//	fprintf(mylogger->file, " at %02d:%02d:%02d\r\n\r\n",
//			mylogger->now.tm_hour, mylogger->now.tm_min, mylogger->now.tm_sec);
	// End of Basic information

	return mylogger;
}

/**
 * \fn		DestroyLogger
 * \brief	Eliminates logger from memory
 *
 * \param	mylogger	pointer to logging "device"
 */
void DestroyLogger(SHLogger* mylogger) {
	fclose(mylogger->file); // in case this was not done before
	free(mylogger);
}

/**
 * \fn		flogf
 * \brief	Logs content to the logfile
 *
 * \param	logger		pointer to logger
 * \param	format		works on fprintf same basis
 * \returns	interger	error checking
 */
void flogf(SHLogger* mylogger, char* format, ...) {
	va_list arg;
	va_start(arg, format);

	// Update time variables
	time(&mylogger->timestamp);
	mylogger->now = *localtime(&mylogger->timestamp);

	fprintf(mylogger->file, "[%02d:%02d:%02d] ",
			mylogger->now.tm_hour, mylogger->now.tm_min, mylogger->now.tm_sec);

	vfprintf(mylogger->file, format, arg);
	va_end(arg);
}
