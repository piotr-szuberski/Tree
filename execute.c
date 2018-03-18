#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "consts.h"
#include "structs.h"

extern Tree* arrayDoubleExpansion(Tree *array, int *arraySize) {
    int i;
    int newArraySize = DOUBLE*(*arraySize);

    Tree *newArray = (Tree*) malloc(sizeof(Tree) * newArraySize);
    if (newArray == NULL) {
        printf("NO MEMORY\n");
        exit(1);
    }

    for (i = ZERO; i < *arraySize; ++i) {
        newArray[i] = array[i];
    }

    *arraySize = newArraySize;

    free(array);
    return newArray;
}

extern void execute(bool diagnose) {
    Tree *graph = (Tree*) malloc(sizeof(Tree) * START_ARRAY_LENGTH);
    Tree toAdd, inputNode;
    List leftBrotherPoint;
    int arrayLength = START_ARRAY_LENGTH;
    int counter = COUNTER_START;
    int inputValue, leftBrother, command;

    inputValue = leftBrother = command = NON_EXISTING_NODE;
    createNode(ZERO, FATHER_ZERO, &graph[ARRAY_ZERO]);

    while (readInput(&inputValue, &leftBrother, &command)) {
        inputNode = graph[inputValue];
        if (counter == arrayLength)
            graph = arrayDoubleExpansion(graph, &arrayLength);

        switch (command) {
            case ADD_NODE:
                createNode(counter, inputValue, &toAdd);
                graph[counter] = toAdd;
                counter++;
                addNode(&inputNode, &toAdd);
                break;
            case RIGHTMOST_CHILD:
                rightmostChild(inputNode->rightest);
                break;
            case DELETE_NODE:
                deleteNode(inputNode, &graph[inputNode->father]);
                graph[inputValue] = NULL;
                break;
            case DELETE_SUBTREE:
                deleteSubTree(inputNode, &graph[inputNode->father], graph);
                break;
            case SPLIT_NODE:
                createNode(counter, inputValue, &toAdd);
                graph[counter] = toAdd;
                counter++;
                leftBrotherPoint = graph[leftBrother]->himself;
                splitNode(&toAdd, &graph[toAdd->father], leftBrotherPoint);
                break;
        }

        if (diagnose) {
            countNodesDiag(graph);
        }

    }

    deleteTree(graph[ARRAY_ZERO], graph);
    free(graph);
}