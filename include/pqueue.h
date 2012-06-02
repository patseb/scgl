#ifndef PQUEUE_H
#define PQUEUE_H

/**
 * function which will compare data/priority in queue
 *
 * @param data1 reference for data
 * @param data2 reference for data
 * @return 0 if datas are the same, negative if data1 has smaller priority, positive if data1 has greater priority
 *
 */
typedef int (*queue_cmp)(const void *data1, const void *data2);

/**
 * function which will replace data1 with data2 and free data1 memory
 *
 * @param data1 reference for old data
 * @param data2 reference for new data
 */
typedef void (*queue_swp)(void **data1, void **data2);

/* priority queue object */
struct pqueue {
	/* actual size of heap */
	size_t size;
	/* amount of allocated memory */
	size_t capacity;
	/* an array of (void*), the actual max-heap */
	void **data;
	/* a pointer to a comparator function */
	queue_cmp cmp;
};

typedef struct pqueue pqueue_t;

/**
 * function allocates memory for new queue
 *
 * @param zrobić to po mojemu
 * @return reference to new priority queue, or NULL for failure
 *
 */
pqueue_t* pqueue_create(int (*cmp)(const void *d1, const void *d2), size_t capacity);

/**
 * free memory occupied by queue and set reference to NULL
 *
 * @param queue reference to queue object
 */
void pqueue_destroy(pqueue_t **queue);

/**
 * add an element inside into the queue
 *
 * @param quque reference to queue object
 * @param data  reference to user data to be added
 */
void pqueue_enqueue(pqueue_t *queue, const void *data);

/**
 * removes the element with the greatest priority from queue
 *
 * @param queue reference to queue object
 * @return user data wich has greatest priority
 */
void* pqueue_dequeue(pqueue_t *queue);

/**
 * replace data pointed by compare function into new one
 *
 * @param queue reference to queue object
 * @param old_data  reference to old data which is inside the queue
 * @param new_data  reference to new data which will be inserted
 * @param cmp   reference to function which will compare data
 * @param swp   reference to function which will replace data
 *
 * @see queue_cmp()
 * @see queue_swp()
 */
void pqueue_replace_data(pqueue_t *queue, void *old_data, void *new_data, queue_cmp cmp, queue_swp swp);

#endif
