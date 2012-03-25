#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scgl_pair.h"

scgl_pair_t*
scgl_pair_create(const char *key, void *value) {
	scgl_pair_t *p;

	p = (scgl_pair_t*) malloc(sizeof(scgl_pair_t));
	p->key = (char*) malloc(strlen(key)+1);
	strcpy(p->key, key);
	p->value = value;

	return p;
}

void
scgl_pair_destroy(scgl_pair_t *pair, attr_free_function fun) {
	if (pair != NULL) {
		if (fun != NULL)
			(*fun)(pair->key, pair->value);
		free(pair->key);
		pair->key = NULL;
		free(pair);
		pair = NULL;
	}
}

int
scgl_pair_seeker(const void *elem, const void *key) {
	const scgl_pair_t *p;
	if (elem == NULL || key == NULL)
		return 0;

	p = (scgl_pair_t*) elem;
	return !(strcmp(p->key, (char*)key));
}

int
scgl_pair_comparator(const void *a, const void *b) {
	const scgl_pair_t *p1, *p2;

	if (a == NULL && b == NULL)
		return 0;
	else if (a == NULL)
		return -1;
	else if (b == NULL)
		return 1;

	p1 = (const scgl_pair_t*) a;
	p2 = (const scgl_pair_t*) b;

	if (p1->key == NULL && p2->key == NULL)
		return 0;
	else if (p1->key == NULL)
		return -1;
	else if (p2->key == NULL)
		return 1;

	return strcmp(p1->key, p2->key)*(-1);
}
