/**
 * Vector implementation.
 *
 * - Implement each of the functions to create a working growable array (vector).
 * - Do not change any of the structs
 * - When submitting, You should not have any 'printf' statements in your vector 
 *   functions.
 *
 * IMPORTANT: The initial capacity and the vector's growth factor should be 
 * expressed in terms of the configuration constants in vect.h
 */
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "vect.h"

/** Main data structure for the vector. */
struct vect {
  char **data;             /* Array containing the actual data. */
  unsigned int size;       /* Number of items currently in the vector. */
  unsigned int capacity;   /* Maximum number of items the vector can hold before growing. */
};

/** Construct a new empty vector. */
vect_t *vect_new() {
  vect_t *v = malloc(sizeof(*v));
  assert(v != NULL);
  v->size = 0;
  v->capacity = VECT_INITIAL_CAPACITY;
  v->data = calloc(v->capacity, sizeof(*v->data));
  assert(v->data != NULL);
  return v;
}

/** Delete the vector, freeing all memory it occupies. */
void vect_delete(vect_t *v) {
  if (v == NULL) return;
  for (unsigned int i = 0; i < v->size; i++) free(v->data[i]);
  free(v->data);
  free(v);
}

/** Get the element at the given index. */
const char *vect_get(vect_t *v, unsigned int idx) {
  assert(v != NULL);
  assert(idx < v->size);

  return v->data[idx];
}

/** Get a copy of the element at the given index. The caller is responsible
 *  for freeing the memory occupied by the copy. */
char *vect_get_copy(vect_t *v, unsigned int idx) {
  assert(v != NULL);
  assert(idx < v->size);

  const char *original = vect_get(v, idx);
  char *copy = malloc(strlen(original) + 1);
  assert(copy != NULL);
  strcpy(copy, original);
  return copy;
}
/** Set the element at the given index. */
void vect_set(vect_t *v, unsigned int idx, const char *elt) {
  assert(v != NULL);
  assert(idx < v->size);

  assert(elt != NULL);
  /* Copy first, since elt might point into the element being replaced. */
  char *copy = malloc(strlen(elt) + 1);
  assert(copy != NULL);
  strcpy(copy, elt);
  free(v->data[idx]);
  v->data[idx] = copy;
}

/** Add an element to the back of the vector. */
void vect_add(vect_t *v, const char *elt) {
  assert(v != NULL);

  assert(elt != NULL);
  /* Copy before realloc, in case elt points into the vector itself. */
  char *copy = malloc(strlen(elt) + 1);
  assert(copy != NULL);
  strcpy(copy, elt);
  if (v->size == v->capacity) {
    assert(v->capacity <= VECT_MAX_CAPACITY / VECT_GROWTH_FACTOR);
    unsigned int next = v->capacity * VECT_GROWTH_FACTOR;
    char **data = realloc(v->data, (size_t)next * sizeof(*v->data));
    assert(data != NULL);
    v->data = data;
    v->capacity = next;
  }
  v->data[v->size++] = copy;
}

/** Remove the last element from the vector. */
void vect_remove_last(vect_t *v) {
  assert(v != NULL);

  assert(v->size > 0);
  free(v->data[--v->size]);
  v->data[v->size] = NULL;
}

/** The number of items currently in the vector. */
unsigned int vect_size(vect_t *v) {
  assert(v != NULL);

  return v->size;
}

/** The maximum number of items the vector can hold before it has to grow. */
unsigned int vect_current_capacity(vect_t *v) {
  assert(v != NULL);

  return v->capacity;
}
