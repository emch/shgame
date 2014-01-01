//
///************************************ _tree **********************************/
//typedef enum _filetype {
//	SH_FOLDER, SH_IMAGE, SH_TEXTFILE
//} SH_FILETYPE;
//
//typedef struct _node SHNode;
//
///**
// * \struct 	_node
// * \brief	Used to store data in a tree structure. In our case, nodes with children are folders
// * 			and leaves are files.
// */
//struct _node {
//	char		name[FOLDERNAME_MAXLEN];
//
//	SH_FILETYPE	filetype;
//
//	int			nb_children;
//	int			nb_max_children;
//	SHNode**	children;
//};
//
//// Prototype
//SHNode* NewNode(char*, int);
//SHNode* NewLeaf(char*, SH_FILETYPE);
//void AddChild(SHNode*, SHNode*);
//void DestroyNode(SHNode*);
//// tree search
///*****************************************************************************/
///*
// * _tree.c
// *
// *  Created on: 1 janv. 2014
// *      Author: Emmanuel
// */
//
//#include <stdlib.h>
//#include <string.h>
//
//#include "shdata.h"
//
//// INUTILE ??
///**
// * \fn		NewNode
// * \brief	Creates a new node representing a folder
// *
// * \param	name		folder name
// * \param	nb_children	number of files in the folder
// *
// * \returns	pointer to SHNode
// */
//SHNode* NewNode(char* name, int nb_max_children) {
//	SHNode* res = malloc(sizeof(SHNode));
//
//	// Fields
//	strcpy(res->name, name);
//
//	res->filetype 		= SH_FOLDER;
//
//	res->nb_children	= 0; // will be increased on child addition
//	res->nb_children	= nb_max_children;
//	res->children		= malloc(nb_max_children*sizeof(SHNode));
//
//	return res;
//}
//
///**
// * \fn		NewLeaf
// * \brief	Creates a new node representing a file
// *
// * \param	name		file name
// * \param	filetype	file type (for casting)
// *
// * \returns	pointer to SHNode
// */
//SHNode* NewLeaf(char* name, SH_FILETYPE filetype) {
//	SHNode* res = malloc(sizeof(SHNode));
//
//	// Fields
//	strcpy(res->name, name);
//
//	res->filetype 			= filetype;
//
//	res->nb_children		= 0;
//	res->nb_max_children	= 0;
//	res->children			= NULL;
//
//	return res;
//}
//
//// child needs to be in memory (used NewNode)
//void AddChild(SHNode* node, SHNode* child) {
//	if(node->nb_children < node->nb_max_children) {
//		node->children[node->nb_children] = child;
//		node->nb_children++;
//	}
//}
//
//// destroys child and all subchildren
//void RemoveChild(SHNode* node, char* child_name) {
////	DestroyNode(node->children[i]) where i has been identified using child_name
//}
//
//int GetChildId(SHNode* node, char* child_name) {
//	return 0;
//}
//
///**
// * \fn		DestroyNode
// * \brief	Destroy node and children recursively
// *
// * \param	node	node to destroy
// */
//void DestroyNode(SHNode* node) {
//	int i;
//	for(i = 0; i < node->nb_children; i++) {
//		DestroyNode(node->children[i]);
//	}
//	free(node->children);
//	free(node);
//}
