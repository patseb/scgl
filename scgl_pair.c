#include <stdio.h>
#include <stdlib.h>
#include <string.h>

pair_t*
scgl_pair_create(const char *key, void *value) {
	pair_t *p;

	p = (pair_t*) malloc(sizeof(pair_t));
	p->key = (char*) malloc(strlen(key)+1);
	strcpy(p->key, key);
	p->value = value;

	return p;
}

void
pair_destroy(pair_t *pair) {
	if (pair != NULL) {
		free(pair->key);
		free(pair->value);
		free(pair)
		pair = NULL;
	}
}

int
pair_seeker(const void *elem, const void *key) {
	const pair_t *p;
	if (elem == NULL || key == NULL)
		return 0;

	p = (pair_t*) elem;
	return !(strcmp(p->key, (char*)key));
}
