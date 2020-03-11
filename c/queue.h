#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>

/** Node: represents an element and a pointer to the next element in the list.
 * The queue argument in all this function (and the one returned) always points
 * to the first element.
 *
 * */
typedef struct {
    void *value;
    struct Node *next;

} Node;


Node *newEmptyQueue();

/** Add element to the end of the list */
Node *appendQueue(Node* queue, void* value);

/** Remove last element of the list */
Node *popQueue(Node* queue);

/** Add element to the start of the list */
Node *pushQueue(Node* queue, void* value);

/** Remove first element of the list */
Node *shiftQueue(Node* queue);

/** Free memory */
void freeQueue(Node* queue);

/** Returns the length of the list */
unsigned int lengthQueue(Node* queue);

/** Returns the nth element */
void *nthElementQueue(Node *queue, unsigned int n);

/** Returns the nth node */
Node *_nthNode(Node *queue, unsigned int n);

/** Returns the last node */
Node *_lastNode(Node *queue);

/** Returns the first element of the list */
void *firstElementQueue(Node* queue);

/** Returns the last element of the list */
void *lastElementQueue(Node* queue);

/** Prints the values of the list */
void dispList(Node* queue);


#endif
