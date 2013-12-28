/*
 * _hashtable.c
 *
 *  Created on: 26 d�c. 2013
 *      Author: Emmanuel
 */

// folder = array of hashtables
// file in folder = hashtable
// hence : hashtable with varying number of parameters (but constant once created)

// pr�voir une fonction qui renvoie la valeur d'un �l�ment dans le bon type

#include <stdlib.h>
#include <string.h>

#include "shdata.h"

/**
 * \fn		NewHashtableElement
 * \brief	Create a new hashtable element and assign it to an existing hashtable.
 *
 * \inputs	parent		pointer to hashtable
 * 			key			key string (gives access to value)
 *			value_type
 *			value		stored value
 *			next		pointer to next hashtable elements (can be chosen NULL)
 *
 * \return	pointer to SHHashtableElt
 */
SHHashtableElt* NewHashtableElement(SHHashtable* parent, char* key, SH_RAW_TYPE value_type, char* value, SHHashtableElt* next) {
	SHHashtableElt* res = malloc(sizeof(SHHashtableElt));

	// Create copy of key in memory
	char* loc_key = malloc(sizeof(key)); strcpy(key, loc_key);

	// Create copy of value in memory
	char* loc_val = malloc(sizeof(value)); strcpy(value, loc_val);

	// Assign fields
	res->id			= -1;
	res->parent 	= parent;
	res->key 		= &loc_key;
	res->value_type = value_type;
	res->value		= &loc_val;
	res->next		= next;

	return res;
}

/**
 * \fn		DestroyHashtableElement
 * \brief	Free memory of all allocated variables
 *
 * \inputs	element		pointer to hashtable element to destroy
 */
void DestroyHashtableElement(SHHashtableElt* element) {
	free(element->key);
	free(element->value);
	free(element);
}

/**
 * \fn		NewHashtable
 * \brief	Create new hashtable
 *
 * \inputs	name
 * 			type
 *
 * \returns	pointer to SHHashtable
 */
SHHashtable* NewHashtable(char* name) {
	SHHashtable* res = malloc(sizeof(SHHashtable));

	// Create copy of name in memory
	char* loc_name = malloc(sizeof(name)); strcpy(name, loc_name);

	// Assign fields
	res->name 		= &loc_name;
	res->first 		= NULL;
	res->last		= NULL;
	res->nb_elts 	= 0;

	return res;
}

/**
 * \fn		DestroyHashtable
 * \brief	Clear a given hashtable (and all subitems) from memory
 *
 * \inputs	table	pointer to hashtable to destroy
 */
void DestroyHashtable(SHHashtable* table) {
	// Destroying hashtable elements
	SHHashtableElt* current;
	SHHashtableElt* next;
	current = table->first;
	while(current != NULL) {
		next = current->next;
		DestroyHashtableElement(current);
		current = next;
	}

	// Destroying other fields and finally hashtable
	free(table->name);
	free(table);
}

/**
 * \fn		AppendHashtableElement
 * \brief	Appends an hashtable element to the end of an hashtable
 *
 * \inputs	table	pointer to hashtable to consider
 * 			element	pointer to element to append
 */
void AppendHashtableElement(SHHashtable* table, SHHashtableElt* element) {
	if(table->nb_elts == 0) {
		table->first 		= element;
		table->last 		= element;
	} else {
		table->last->next	= element;
		table->last			= element;
	}
	table->last->id		= table->nb_elts;
	table->last->next 	= NULL;	// delete any unwanted link !
	table->nb_elts += 1;
}

/**
 * \fn		GetHashtableElementByKey
 * \brief	Returns an hashtable element of an hashtable given its key.
 *
 * \inputs	table	pointer to given hashtable
 * 			key		pointer to expected key
 * \returns	pointer to SHHashtableElt, NULL if not found
 */
SHHashtableElt* GetHashtableElementByKey(SHHashtable* table, char* key) {
	SHHashtableElt* current = table->first;
	while((current != NULL) && !strcmp(key, *current->key))
		current = current->next;
	return current;
}

/**
 * \fn		GetHashtableElementIntValue
 * \brief	Get value when an integer one is awaited
 *
 * \inputs	element	pointer to hashtable element
 * \return	integer
 */
int GetHashtableElementIntValue(SHHashtableElt* element) {
	switch(element->value_type) {
	case STRING:
		return -1;
		break;
	case INT:
		return (int)&element->value; // TODO : corriger --> char* to int !!
		break;
	default:
		return -1;
	}
}

/**
 * \fn		GetHashtableElementStringValue
 * \brief	Get value when an integer one is awaited
 *
 * \inputs	element	pointer to hashtable element
 * \return	pointer to array of char (string)
 */
char* GetHashtableElementStringValue(SHHashtableElt* element) {
	switch(element->value_type) {
	case STRING:
		return (char*)&element->value;
		break;
	case INT:
		return "";
		break;
	default:
		return "";
	}
}
