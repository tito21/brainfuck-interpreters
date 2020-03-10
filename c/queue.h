#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Nodes {
    void *value;
    struct Node *next;

} Node;
/** Node: represents an element and a pointer to the next element in the list.
 * The queue argument in all this function (and the one returned) always points
 * to the first element.
 *
 * */

Node *newEmptyQueue();

Node *appendQueue(Node* queue, void* value);
/** Add element to the end of the list */

Node *popQueue(Node* queue);
/** Remove last element of the list */

Node *pushQueue(Node* queue, void* value);
/** Add element to the start of the list */

Node *shiftQueue(Node* queue);
/** Remove first element of the list */

void freeQueue(Node* queue);
/** Free memory */

unsigned int lengthQueue(Node* queue);
/** Returns the length of the list */

void *nthElementQueue(Node *queue, unsigned int n);
/** Returns the nth element */

Node *_nthNode(Node *queue, unsigned int n);
/** Returns the nth node */

Node *_lastNode(Node *queue);
/** Returns the last node */

void *firstElementQueue(Node* queue);
/** Returns the first element of the list */

void *lastElementQueue(Node* queue);
/** Returns the last element of the list */

void dispList(Node* queue);
/** Prints the values of the list */


#endif
