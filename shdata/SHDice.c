/*
 * SHDice.c
 *
 *  Created on: 31 d�c. 2013
 *      Author: Emmanuel
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "shdata.h"

/**
 * \fn		InitDice
 * \brief	Initialize a dice with a given type
 *
 * \param	type	dice type (4 or 6 faces)
 *
 * \returns	pointer to SHDice
 */
SHDice* InitDice(SH_DICE_TYPE type) {
	SHDice* res = malloc(sizeof(SHDice));
	srand((unsigned)time(NULL));	// randomize

	res->type 	= type;
	res->value	= (type == SH_SIX_FACES) ? 6 : 4;	// set to maximum value

	return res;
}

/**
 * \fn		DestroyDice
 * \brief	Destroy a given dice from memory
 *
 * \param	dice	pointer to dice to destroy
 */
void DestroyDice(SHDice* dice) {
	free(dice);
}

/**
 * \fn		RollDice
 * \brief	Let's roll the dice !
 *
 * \param	dice	pointer to dice to roll
 *
 * \returns	result
 */
int RollDice(SHDice* dice) {
	int res = 0; // impossible so that could be used as an error checker

	switch(dice->type) {
	case SH_FOUR_FACES:
		res = RandomInt(4);
		break;
	case SH_SIX_FACES:
		res = RandomInt(6);
		break;
	default: //do nothing
		break;
	}

	dice->value = res;
	return res;
}

/**
 * \fn		RandomInt
 * \brief	Get a random number between 1 and n
 *
 * \param	n	maximum desired random integer
 */
int RandomInt(int n) {
	return (rand()%n) + 1;
}
