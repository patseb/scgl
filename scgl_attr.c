#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scgl_attr.h"

scgl_attr_t*
scgl_attr_create(char *key, void *value) {
	scgl_attr_t *p;

	p = (scgl_attr_t*) malloc(sizeof(scgl_attr_t));
	INIT_LIST_HEAD(&p->list);
	p->key = key;
	p->value = value;

	return p;
}

void
scgl_attr_destroy(scgl_attr_t **attr, attr_function fun) {
	if (attr != NULL && *attr != NULL) {
		if (fun != NULL)
			(*fun)((*attr)->key, (*attr)->value, NULL);
		list_del(&(*attr)->list);
		(*attr)->key = NULL;
		(*attr)->value = NULL;
		free(*attr);
		*attr = NULL;
	}
}

char*
scgl_attr_get_key(const scgl_attr_t* attr) {
	if (attr != NULL)
		return attr->key;
	else
		return NULL;
}

void*
scgl_attr_get_value(const scgl_attr_t* attr) {
	if (attr != NULL)
		return attr->value;
	else
		return NULL;
}

int
scgl_attr_comparator(const void *a, const void *b) {
	const scgl_attr_t *p1, *p2;

	if (a == NULL && b == NULL)
		return 0;
	else if (a == NULL)
		return -1;
	else if (b == NULL)
		return 1;

	p1 = (const scgl_attr_t*) a;
	p2 = (const scgl_attr_t*) b;

	if (p1->key == NULL && p2->key == NULL)
		return 0;
	else if (p1->key == NULL)
		return -1;
	else if (p2->key == NULL)
		return 1;

	return strcmp(p1->key, p2->key)*(-1);
}
