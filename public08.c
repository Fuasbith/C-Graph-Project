#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "string-graph.h"
#include "memory-functions.h"

/* CMSC 216, Spring 2023, Project #8
 * Public test 8 (public08.c)
 *
 * Tests calling free_vertex_name_list() on an array of dynamically
 * allocated strings, and calling graph_delete(), and ensures that all
 * memory was properly released and there are no errors in the heap.  This
 * test is the same as public04.c other than for checking the correctness of
 * the heap.
 *
 * In order to run valgrind on this test, note the following:
 *
 * 1. This test should have NO memory leaks, so do NOT use the valgrind option
 *    --leak-check=no.  (If valgrind reports any memory leaks you need to fix
 *    your code to eliminate them.)
 *
 * 2. As the project assignment explains, valgrind does not work with our
 *    memory checking functions, so to use valgrind with this test, add the
 *    options -g and -D ENABLE_VALGRIND to compilation commands and rebuild
 *    things, as described in Appendix B of the project assignment.
 *
 * (c) Larry Herman, 2023.  You are allowed to use this code yourself, but
 * not to provide it to anyone else.
 */

int main(void) {
  String_graph graph;
  char *some_strings[]= {"koala", "giraffe", "parrot", "zebra", "hedgehog",
                         "hippopotamus", "rhinoceros", "dog", "frog"};
  char **animals;
  int i;

  #if !defined(ENABLE_VALGRIND)
  setup_memory_checking();
  #endif

  graph_init(&graph);

  /* first check free_vertex_name_list() */

  /* some_strings is not dynamically allocated so we can't call
   * free_vertex_name_list() on it; we will make a dynamically allocated
   * copy of what's in it to test the function with
   */
  animals= calloc(1 + NUM_ELTS(some_strings), sizeof(*animals));

  if (animals != NULL) {
    for (i= 0; i < NUM_ELTS(some_strings); i++) {
      animals[i]= malloc(strlen(some_strings[i]) + 1);
      if (animals[i] != NULL)
        strcpy(animals[i], some_strings[i]);
    }

    /* ensure the last element is NULL */
    animals[i]= NULL;

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
     functions- on the graph at this point, not unless graph_init() is
     called on it first, which we will skip doing because here we just care
     about memory leaks and correctness of the heap */

  #if !defined(ENABLE_VALGRIND)
  check_heap();
  #endif

  /* if this is the only thing printed the heap must be valid, and there
     must not have been any memory leaks */
  printf("I was sure that the assertions would all succeed!\n");

  return 0;
}
