#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "consts.h"
#include "structs.h"

/* The function copies the array and creates an extended one */
extern Tree* arrayDoubleExpansion(Tree *array, int *arraySize) {
    int i;
    int newArraySize = 2 * (*arraySize);

    Tree *newArray = (Tree*) malloc(sizeof(Tree) * newArraySize);
    if (newArray == NULL) {
        printf("NO MEMORY\n");
        exit(1);
    }

    for (i = 0; i < *arraySize; ++i) {
        newArray[i] = array[i];
    }

    *arraySize = newArraySize;

    free(array);
    return newArray;
}

/* The most important function that links all others - reads the input
 * and interpretes it
 */
extern void execute(bool diagnose) {
    Tree *graph = (Tree*) malloc(sizeof(Tree));
    Tree toAdd, inputNode;
    List leftBrotherPoint;
    int arrayLength = 1;
    int counter = 1;
    int inputValue, leftBrother, command;

    inputValue = leftBrother = command = -1;
    createNode(0, -1, &graph[0]);

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

    deleteTree(graph[0], graph);
    free(graph);
}