// Copyright (C) 2019  Alberto Di Biase


#include "queue.h"

Node *newEmptyQueue() {
    Node *start = (Node *)malloc(sizeof(Node));
    start->next = NULL;
    return start;
};

Node *appendQueue(Node* queue, void* value) {
    /** Add element to the end of the list */
    Node *last = _lastNode(queue);
    Node *item = (Node *)malloc(sizeof(Node));
    item->next = NULL;
    last->next = item;
    item->value = value;
    return queue;
}

Node * popQueue(Node* queue) {
    /** Remove last element of the list */
    Node *curr = queue;
    Node *prev = queue;
    while (curr->next)
    {
        prev = curr;
        curr = curr->next;
    }
    free(curr->value);
    free(curr);
    prev->next = NULL;

    return prev;

}

Node *pushQueue(Node* queue, void* value) {
    /** Add element to the start of the list */
    Node *new = (Node *)malloc(sizeof(Node));
    new->next = queue;
    new->value = value;
    return new;

}

Node *shiftQueue(Node* queue) {
    /** Remove first element of the list */
    Node *new_first = queue->next;
    free(queue->value);
    free(queue);
    return new_first;
}

void freeQueue(Node* queue) {
    /** Free memory */
    // Node *queue = queue;
    if (! queue->next) {
        free(queue->value);
        return;
    }
    do {
        free(queue->value);
        free(queue);
        queue = queue->next;
    } while (queue->next);
    // free(queue->value);
    // free(queue);
}

unsigned int lengthQueue(Node* queue) {
    /** Returns the length of the list */
    int i = 0;
    while(queue->next) {
        queue = queue->next;
        i++;
    }
    return i+1;
}
void *nthElementQueue(Node *queue, unsigned int n) {
    /** Returns the nth element */
    Node *n_node = _nthNode(queue, n);
    return n_node->value;

}

Node *_nthNode(Node *queue, unsigned int n) {
    /* Returns the nth node */
    for (int i = 0; i < n; i++)
    {
        queue = queue->next;
    }
    return queue;
}

Node *_lastNode(Node *queue) {
    /** Returns the last node */

    while(queue->next) {
        queue = queue->next;
    }
    return queue;
}

void *firstElementQueue(Node* queue) {
    /** Returns the first element of the list */
    return queue->value;
}

void *lastElementQueue(Node* queue) {
    /** Returns the last element of the list */
    Node *node = _lastNode(queue);
    return node->value;
}

void dispList(Node* queue) {
    /** Prints the values of the list */
    printf("[");
    Node *curr = queue;
    while (curr->next) {
        printf("%d, ", *(int *)curr->value);
        curr = curr->next;
    }
    printf("%d", *(int *)curr->value);
    printf("]\n");

}