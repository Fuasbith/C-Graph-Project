#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "string-graph.h"

/* CMSC 216, Spring 2023, Project #8
 * Public test 4 (public04.c)
 *
 * Tests calling free_vertex_name_list() on an array of dynamically
 * allocated strings, and calling graph_delete().  This test does not check
 * for memory leaks or correctness of the heap; it is only testing the
 * correct behavior of these functions.
 *
 * (c) Larry Herman, 2023.  You are allowed to use this code yourself, but
 * not to provide it to anyone else.
 */

int main(void) {
  String_graph graph;
  char *some_strings[]= {"koala", "giraffe", "parrot", "zebra", "hedgehog",
                         "hippopotamus", "rhinoceros", "dog", "elephant"};
  char **animals;
  int i;

  graph_init(&graph);

  /* first check free_vertex_name_list() */

  /* some_strings is not dynamically allocated so we can't call
   * free_vertex_name_list() on it; we will make a dynamically allocated copy of
   * what's in it to test the function with
   */
  animals= calloc(1 + NUM_ELTS(some_strings), sizeof(*animals));

  if (animals != NULL) {
    for (i= 0; i < NUM_ELTS(some_strings); i++) {
      animals[i]= malloc(strlen(some_strings[i]) + 1);
      if (animals[i] != NULL)
        strcpy(animals[i], some_strings[i]);
    }

    animals[i]= NULL;  /* ensure the last element is NULL */

    /* now release everything that was allocated */
    free_vertex_name_list(animals);
  }

  /* next check graph_delete(), using those same strings to create vertices
     in the graph */

  /* add some vertices */
  for (i= 0; i < NUM_ELTS(some_strings); i++)
    add_vertex_to_graph(&graph, some_strings[i]);

  /* check that the vertices were all added */
  assert(vertex_count(&graph) == NUM_ELTS(some_strings));

  /* now trash the whole thing */
  graph_delete(&graph);

  /* note that it's not valid to call vertex_count()- or any other
   * functions- on the graph at this point, not unless graph_init() is
   * called on it after graph_delete() was called.  But we will skip calling
   * graph_init() again because here we just care about memory leaks and
   * correctness of the heap
   */

  printf("I was sure that the assertions would all succeed!\n");

  return 0;
}
