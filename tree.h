#ifndef TREE_H
#define TREE_H

#include "consts.h"
#include "structs.h"

extern void createNode(int nodeNumber, int fatherNumber, Tree *new);

extern void addNode(Tree *father, Tree *toAdd);

extern void rightmostChild(List rightest);

extern void deleteNode(Tree child, Tree *father);

extern void deleteTree(Tree toUtilization, Tree *graph);

extern void deleteSubTree(Tree toUtilization, Tree *father, Tree *graph);

extern void splitNode(Tree *toAdd, Tree *father, List leftBrother);

#endif /*TREE_H*/
