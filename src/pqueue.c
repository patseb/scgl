#include<stdio.h>
#include<stdlib.h>

#include "pqueue.h"

#define LEFT(x) (2 * (x) + 1)
#define RIGHT(x) (2 * (x) + 2)
#define PARENT(x) ((x-1) / 2)

void pqueue_heapify(pqueue_t *queue, size_t idx);

pqueue_t*
pqueue_create(queue_cmp fun, size_t capacity) {
	pqueue_t *res = NULL;

	if (fun == NULL)
		return NULL;
	res = (pqueue_t*) malloc(sizeof(*res));
	if (res == NULL)
		return NULL;
	res->cmp = fun;
	res->data = malloc(capacity * sizeof(*(res->data)));
	if (res->data == NULL)
		return NULL;
	res->size = 0;
	res->capacity = capacity;
	return res;
}

void
pqueue_destroy(pqueue_t **queue) {
	if (queue != NULL && *queue != NULL) {
		free((*queue)->data);
		free(*queue);
		*queue = NULL;
	}
}

void
pqueue_enqueue(pqueue_t *queue, const void *data) {
	size_t i;
	void *tmp = NULL;
	if (queue == NULL || queue->size >= queue->capacity)
		return;
	/* adds element last */
	queue->data[queue->size] = (void*)data;
	i = queue->size;
	queue->size++;

	/* the new element is swapped with its parent as long as its precedence is higher */
	while(i > 0 && queue->cmp(queue->data[i], queue->data[PARENT(i)]) > 0) {
		tmp = queue->data[i];
		queue->data[i] = queue->data[PARENT(i)];
		queue->data[PARENT(i)] = tmp;
		i = PARENT(i);
	}
}

void*
pqueue_dequeue(pqueue_t *queue) {
	void *data = NULL;
	if (queue == NULL || queue->size < 1)
		return NULL;
	data = queue->data[0];
	queue->data[0] = queue->data[queue->size-1];
	queue->size--;
	/* restore heap property */
	pqueue_heapify(queue, 0);
	return (data);
}

void
pqueue_heapify(pqueue_t *queue, size_t idx) {
	/* left index, right index, largest */
	void *tmp = NULL;
	size_t l_idx, r_idx, lrg_idx;

	if (queue == NULL)
		return;

	l_idx = LEFT(idx);
	r_idx = RIGHT(idx);

	/* left child exists, compare left child with its parent */
	if (l_idx < queue->size && queue->cmp(queue->data[l_idx], queue->data[idx]) > 0) {
		lrg_idx = l_idx;
	} else {
		lrg_idx = idx;
	}
 
	/* right child exists, compare right child with the largest element */
	if (r_idx < queue->size && queue->cmp(queue->data[r_idx], queue->data[lrg_idx]) > 0) {
		lrg_idx = r_idx;
	}
 
	/* at this point largest element was determined */
	if (lrg_idx != idx) {
		/* swap between the index at the largest element */
		tmp = queue->data[lrg_idx];
		queue->data[lrg_idx] = queue->data[idx];
		queue->data[idx] = tmp;
		/* heapify again */
		pqueue_heapify(queue, lrg_idx);
	}
}

void
pqueue_replace_data(pqueue_t *queue, void *old_data, void *new_data, queue_cmp cmp, queue_swp swp) {
	size_t i;
	for(i=0; i<queue->size; ++i) {
		if ((*cmp)(queue->data[i], old_data)) {
			(*swp)(&queue->data[i], &new_data);
			pqueue_heapify(queue, 0);
			break;
		}
	}
}
