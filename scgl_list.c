#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scgl_list.h"
#include "scgl_def.h"

unsigned int
scgl_list_count(list_head_t *head) {
	unsigned int i=0;
	list_head_t *j;
	list_for_each(j, head) {
		++i;
	}
	return i;
}

void
scgl_list_add(list_head_t *head, void *data) {
	scgl_list_t *tmp = (scgl_list_t*) malloc(sizeof(scgl_list_t));
	INIT_LIST_HEAD(&tmp->list);
	tmp->data = data;
	list_add(&tmp->list, head);
}

void
scgl_list_delete(list_head_t *head, void *data) {
	list_head_t *i, *j;
	scgl_list_t *tmp;
	list_for_each_safe(i, j, head) {
		tmp = list_entry(i, scgl_list_t, list);
		if (tmp->data == data) {
			list_del(i);
			free(tmp);
			break;
		}
	}
}
