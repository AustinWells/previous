/*
 *          File: queue.c
 *        Author: Robert I. Pitts <rip@cs.bu.edu>
 * Last Modified: March 9, 2000
 *         Topic: Queue - Array Implementation
 * ----------------------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
/*
 * Constants
 * ---------
 * MAX_QUEUE_SIZE = Largest number of items queue can hold.
 */

#define MAX_QUEUE_SIZE  100

/*
 * struct queueCDT gives the implementation of a queue.
 * It holds the information that we need for each queue.
 */

typedef struct queueCDT {
  queueElementT contents[MAX_QUEUE_SIZE];
  int front;
  int count;
} queueCDT;

queueADT QueueCreate(void)
{
  queueADT queue;

  queue = (queueADT)malloc(sizeof(queueCDT));

  if (queue == NULL) {
    fprintf(stderr, "Insufficient Memory for new Queue.\n");
    exit(ERROR_MEMORY);  /* Exit program, returning error code. */
  }

  queue->front = 0;
  queue->count = 0;

  return queue;
}

void QueueDestroy(queueADT queue)
{
  free(queue);
}

void QueueEnter(queueADT queue, queueElementT element)
{
  int newElementIndex;

  if (queue->count >= MAX_QUEUE_SIZE) {
	return;
  }

  /*
   * Calculate index at which to put
   * next element.
   */
  newElementIndex = (queue->front + queue->count)
                    % MAX_QUEUE_SIZE;
  queue->contents[newElementIndex] = element;
  queue->count++;
}

int QueuePeek(queueADT queue)
{
return queue->count;
}

queueElementT QueueDelete(queueADT queue)
{
  queueElementT oldElement;

  if (queue->count <= 0) {
	return NULL;
  }

  /* Save the element so we can return it. */
  oldElement = queue->contents[queue->front];

  /*
   * Advance the index of the front,
   * making sure it wraps around the
   * array properly.
   */
  queue->front++;
  queue->front %= MAX_QUEUE_SIZE;

  queue->count--;

  return oldElement;
}

inline int QueueIsEmpty(queueADT queue)
{
  return queue->count <= 0;
}

inline int QueueIsFull(queueADT queue)
{
  return queue->count >= MAX_QUEUE_SIZE;
}
