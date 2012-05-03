#ifndef SCGL_EDGE_H
#define SCGL_EDGE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "list.h"
#include "scgl_def.h"

/**
 * definiton of edge cost attribute type
 * it should be used whenever you want to manipulate edges cost
 */
typedef cost_type cost_type_t;

/**
 * a function for operate at attributes
 *
 * It can eg.:
 *  - sum values of all attributes and set edge cost field
 *  - free memory occupied by key and value
 *  - dump data to specified stream (data pointer)
 *
 * @param key	reference for key attribute
 * @param value	reference for value attribute
 * @param data reference for additional data or result storing
 *
 * @see scgl_edge_foreach_attribute()
 * @see scgl_edge_destroy()
 * @see scgl_edge_dump()
 */
typedef void (*attr_function)(char *key, void *value, void *data);

/** edge object */
struct scgl_edge {
	/** edge's sibling, created when edge is undirected */
	scgl_edge_t *sibling;
	/** edge cost, by default it's int type */
	cost_type_t cost;
	/** edge source vertex */
	scgl_vertex_t *from;
	/** list head which will be connected with vertex out list */
	list_head_t from_list;
	/** edge destination vertex */
	scgl_vertex_t *to;
	/** list head which will be connected with vertex in list */
	list_head_t to_list;
	/** list head which will be connected with graph edges list */
	list_head_t owner_list;
	/** user-purpose list of edge attributes (attr_t objects) */
	list_head_t attributes;
};

/**
 * create edge object, allocate and initialize memory
 *
 * @param from	edge source (vertex object)
 * @param to	edge destination (vertex object)
 * @param undirected 1 means that edge is undirected, 0 opposite
 * @param cost	edge cost
 * @param attr	table of attr objects, user-purpose attributes
 * @param attr_n	lenght of attributes table
 * @return	edge object for success, NULL for failure
 */
scgl_edge_t* scgl_edge_create(scgl_vertex_t *from, scgl_vertex_t *to, int undirected, cost_type_t cost, scgl_attr_t **attr, unsigned int attr_n);

/**
 * free memory occupied by edge object
 *
 * @param edge	edge object
 * @param fun   user function which will free memory occupied by attributes
 */
void scgl_edge_destroy(scgl_edge_t **edge, attr_function fun);

/**
 * return edge's cost
 *
 * @param edge  reference to edge object
 * @return  edge's cost, COST_MAX for failure
 */
cost_type_t scgl_edge_get_cost(const scgl_edge_t *edge);

/**
 * set edge's cost
 *
 * @param edge  reference to edge object
 * @param cost  new cost
 */
void scgl_edge_set_cost(scgl_edge_t *edge, const cost_type_t cost);

/**
 * return reference to one of edge's endpoint
 *
 * @param edge  reference to edge object
 * @param endpoint  0 - function returns 'from' vertex, 1 - function returns 'to' vertex
 * @return  reference to choosen vertex of NULL for failure
 */
scgl_vertex_t* scgl_edge_get_vertex(scgl_edge_t *edge, const unsigned int endpoint);

/**
 * modify edge 'from/to' attribute, function removes relation between edge and old vertex
 *
 * @param edge	edge object
 * @param vertex	vertex
 * @param endpoint	0 means edge is outgoing from vertex, 1 means edge incoming to vertex, doesn't matter when edge is undirected
 * @return 0 for success, -1 for failure
 */
int scgl_edge_set_vertex(scgl_edge_t *edge, scgl_vertex_t *vertex, const unsigned int endpoint);

/**
 * remove vertex from edge, function also modifies vertex (in/out attributes)
 * 
 * @param edge  edge object wich will be modified
 * @param vertex    vertex object which will be removed
 * @return  0 for success, -1 for failure
 */
int scgl_dedge_del_vertex(scgl_edge_t *edge, scgl_vertex_t *vertex);

/**
 * add new attribute to existing edge
 *
 * @param edge	edge object
 * @param key	unique key for indexing attribute
 * @param value	value to be added
 */
void scgl_edge_add_attribute(scgl_edge_t *edge, char *key, void *value);

/**
 * remove attribute from edge
 *
 * @param edge	edge object
 * @param key	unique key for locate attribute
 * @param fun   user function which will free memory occupied by edge's attributes
 */
void scgl_edge_del_attribute(scgl_edge_t *edge, const char *key, attr_function fun);

/**
 * get attribute's value for specified key
 *
 * @param edge	edge object
 * @param key	key corresponding to the requested value
 * @return	value for success, NULL for failure
 */
void* scgl_edge_get_attribute(scgl_edge_t *edge, const char *key);

/**
 * return an attribute at given position
 *
 * @param edge	edge object
 * @param i	[0, edges_attribute_count-1] position index of the element
 * @return	reference to attribute attr or NULL for failure
 *
 * @see scgl_edge_get_attributes_count()
 */
scgl_attr_t* scgl_edge_get_attribute_at(const scgl_edge_t *edge, unsigned int i);

/**
 * count edge's attributes
 *
 * @param edge  reference to edge object
 * @return number of attributes, -1 for failure
 */
int scgl_edge_get_attributes_count(const scgl_edge_t *edge);

/**
 * call fun function for every attribute of edge
 *
 * @param edge	edge object
 * @param fun	pointer to the called function
 * @param result reference to called function result
 */
void scgl_edge_foreach_attribute(scgl_edge_t *edge, attr_function fun, void *result);

/**
 * return if edge is undirected or not
 *
 * @param edge  reference to edge object
 * @return  1 means edge is udirected, 0 means directed, -1 for failure
 */
int scgl_edge_get_undirected(const scgl_edge_t* edge);

/**
 * make an edge undirected or directed
 *
 * @param edge  edge object
 * @param undirected  1 means that edge is undirected, 0 opposite
 */
void scgl_edge_set_undirected(scgl_edge_t *edge, const unsigned int undirected);

/**
 * print edge object to stream
 *
 * @param edge  edge object
 * @param fp    object containing information to control a stream
 * @param fun   function which will print attributes, last parameter (result), should be casted as FILE* type for fprintf - eg.:
 * void
 * edge_attribute_dump(char *key, void *value, void *fp) {
 *  if (fp != NULL)
 *      fprintf((FILE*)fp, "%s : %s \n", key, (char*)value);
 * }
 *
 * @see scgl_edge_foreach_attribute()
 */
void scgl_edge_dump(scgl_edge_t *edge, FILE *fp, attr_function fun);

#ifdef __cplusplus
}
#endif

#endif
