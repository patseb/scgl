#ifndef SCGL_EDGE_H
#define SCGL_EDGE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "simclist.h"
#include "scgl_def.h"

/**
 * a function for operate at attributes
 *
 * Attribute function will be called by foreach attribute loop at specified edge.
 * It can eg. sum values of all attributes and set edge cost field.
 *
 * @param key	reference for key attribute
 * @param value	reference for value attribute
 * @param result reference for result storing
 *
 * @see scgl_edge_foreach_attribute()
 */
typedef void (*attr_foreach_function)(char *key, void *value, void *result);

/**
 * a function for free occupied memory by attribute values
 *
 * Attribute function will be called by foreach attribute loop at specified edge.
 * Attribute key will be free by scgl_edge_destroy() function.
 *
 * @param key	reference for key attribute
 * @param value	reference for value attribute
 *
 * @see scgl_edge_destroy()
 */
typedef void (*attr_free_function)(char *key, void *value);

struct scgl_edge {
	/* edge identifier */
	char *id;
	/* 0 - edge is undirected, edge is 1 directed */
	int is_directed;
	/* edge cost, by default it's int type */
	cost_type_t cost;
	/* edge source vertex */
	scgl_vertex_t *from;
	/* edge destination vertex */
	scgl_vertex_t *to;
	/* pointer to graph object which contains that edge */
	scgl_graph_t *owner;
	/* user-purpose list of edge attributes (pair_t objects) */
	list_t *attributes;
	/* user function which free attribute value memory */
	attr_free_function attr_free_fun;
};

/**
 * create edge object, allocate and initialize memory
 *
 * @param id	unique edge identifier
 * @param from	edge source (vertex object)
 * @param to	edge destination (vertex object)
 * @param is_directed 1 means that edge is directed, 0 opposite
 * @param cost	edge cost
 * @param attr	table of pair objects, user-purpose attributes
 * @param attr_n	lenght of attributes table
 * @return	edge object for success, NULL for failure
 */
scgl_edge_t* scgl_edge_create(char *id, scgl_vertex_t *from, scgl_vertex_t *to, int is_directed, cost_type_t cost, scgl_pair_t **attr, unsigned int attr_n);

/**
 * free memory occupied by edge object
 *
 * @param edge	edge object
 */
void scgl_edge_destroy(scgl_edge_t **edge);

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
void scgl_edge_add_attribute(scgl_edge_t *edge, const char *key, void *value);

/**
 * remove attribute from edge
 *
 * @param edge	edge object
 * @param key	unique key for locate attribute
 */
void scgl_edge_del_attribute(scgl_edge_t *edge, const char *key);

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
 * @return	reference to attribute pair or NULL for failure
 *
 * @see scgl_edge_get_attributes_count()
 */
scgl_pair_t* scgl_edge_get_attribute_at(const scgl_edge_t *edge, unsigned int i);

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
void scgl_edge_foreach_attribute(scgl_edge_t *edge, attr_foreach_function fun, void *result);

/**
 * register function which will free memory for edge attributes
 *
 * @param edge	edge object
 * @param fun	pointer to the function
 */
void scgl_edge_attr_free_function(scgl_edge_t *edge, attr_free_function fun);

/**
 * set is_directed attribute in specified edge object
 * 
 * @param edge  edge object
 * @param directed  1 means that edge is directed, 0 opposite
 */
void scgl_edge_set_is_directed(scgl_edge_t *edge, const unsigned int directed);

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
 * @see scgl_edge_foreach_attribute
 */
void scgl_edge_dump(scgl_edge_t *edge, FILE *fp, attr_foreach_function fun);

/* internal functions section */
int scgl_edge_seeker(const void *elem, const void *key);
int scgl_edge_comparator(const void *a, const void *b);

#ifdef __cplusplus
}
#endif

#endif
