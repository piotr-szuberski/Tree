#ifndef STRUCTS_H
#define STRUCTS_H

struct Node;

typedef struct Node* Tree;

struct Cube;

typedef struct Cube* List;

struct Node {
    int number;
    int father;
    List rightest, leftest, himself;
};

struct Cube {
    Tree node;
    List next, prev;
};

struct Stack {
    int value;
    struct Stack *next;
};

typedef struct Stack StackT;

#endif /*STRUCTS_H*/
