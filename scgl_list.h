#ifndef SCGL_LIST_H
#define SCGL_LIST_H

#ifdef __cplusplus
extern "C" {
#endif

#include "list.h"
#include "scgl_def.h"

struct scgl_list {
	void *data;
	list_head_t list;
};

unsigned int scgl_list_count(list_head_t *head);
void scgl_list_add(list_head_t *head, void *data);
void scgl_list_delete(list_head_t *head, void *data);

#ifdef __cplusplus
}
#endif

#endif
