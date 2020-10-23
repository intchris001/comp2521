// Implementation of the Queue ADT using a circular array

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Queue.h"

#define DEFAULT_SIZE 16 // DO NOT change this line

// DO NOT modify this struct
struct queue {
	Item *items;
	int size;
	int capacity;
	int frontIndex;
};

/**
 * Creates a new empty queue
 */
Queue QueueNew(void) {
	Queue q = malloc(sizeof(*q));
	if (q == NULL) {
		fprintf(stderr, "couldn't allocate Queue");
		exit(EXIT_FAILURE);
	}
	
	q->items = malloc(DEFAULT_SIZE * sizeof(Item));
	if (q->items == NULL) {
		fprintf(stderr, "couldn't allocate Queue");
		exit(EXIT_FAILURE);
	}
	
	q->size = 0;
	q->capacity = DEFAULT_SIZE;
	q->frontIndex = 0;
	return q;
}

/**
 * Frees all resources associated with the given queue
 */
void QueueFree(Queue q) {
	free(q->items);
	free(q);
}

/**
 * Adds an item to the end of the queue
 */
void QueueEnqueue(Queue q, Item it) {
	//if queue q is empty ,so we just need add element to the  struct queue q'sfrontindex postion
    //and size plus 1
    if (q->size == 0) {
        q->items[q->frontIndex] = it;
        q->size ++;
        return;
    }
    //then we need backindex to enqueue ,then we need to calculate backindex by size and frontindex 
    int backIndex = (q->frontIndex + (q->size -1))%(q->capacity);
    //case 1:if q not full
    if (q->size < q->capacity){
    //return te the top of queue
        if ((backIndex+1) >= q->capacity) {
            q->items[(backIndex+1)%q->capacity] = it; 
            q->size ++;
        }
    // not return 
        else if ((backIndex+1) < q->capacity){
            q->items[(backIndex+1)] = it; 
            q->size++;
        }
    }
    //case 2:q is full ,then need to extend item size and capacity of q
    else {
        q->items = realloc(q->items, (q->capacity * 2) * sizeof(Item));
        if (q->frontIndex > backIndex) {
           
            for (int i = (q->capacity - 1); i >= q->frontIndex; i--) {
                q->items[i + q->capacity] = q->items[i];
            }
        }
    
        q->items[backIndex + 1] = it;
        q->size++;
        q->capacity *= 2;
        
    }
}

/**
 * Removes an item from the front of the queue and returns it
 * Assumes that the queue is not empty
 */
Item QueueDequeue(Queue q) {
	Item front = q->items[q->frontIndex];
	q->frontIndex = (q->frontIndex + 1)%q->capacity;
    q->size--;
    
    return front;
}

/**
 * Gets the item at the front of the queue without removing it
 * Assumes that the queue is not empty
 */
Item QueueFront(Queue q) {
	assert(q->size > 0);
	
	return q->items[q->frontIndex];
}

/**
 * Gets the size of the given queue
 */
int QueueSize(Queue q) {
	return q->size;
}

/**
 * Returns true if the queue is empty, and false otherwise
 */
bool QueueIsEmpty(Queue q) {
	return q->size == 0;
}

/**
 * Prints the queue to the given file with items space-separated
 */
void QueueDump(Queue q, FILE *fp) {
	for (int i = q->frontIndex, j = 0; j < q->size; i = (i + 1) % q->capacity, j++) {
		fprintf(fp, "%d ", q->items[i]);
	}
	fprintf(fp, "\n");
}

