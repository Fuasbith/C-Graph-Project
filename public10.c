#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "string-graph.h"
#include "compare-vertex-lists.h"
#include "memory-functions.h"

/* CMSC 216, Spring 2023, Project #8
 * Public test 10 (public10.c)
 *
 * Tests adding vertices back to a graph after all vertices were removed
 * using remove_vertex_from_graph(), and ensures that all memory was
 * properly released and there are no errors in the heap.
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
  char *vertices[]= {"koala", "quokka", "parrot", "zebra", "hedgehog", "dog",
                     "frog"};
  char *expected_results[]= {"blobfish", "naked mole rat",
                             "pink fairy armadillo", "star-nosed mole"};
  char **names;
  int i;

  #if !defined(ENABLE_VALGRIND)
  setup_memory_checking();
  #endif

  graph_init(&graph);

  /* add some vertices */
  for (i= 0; i < NUM_ELTS(vertices); i++)
    add_vertex_to_graph(&graph, vertices[i]);

  /* check them */
  assert(vertex_count(&graph) == 7);

  /* now remove all of them */
  for (i= 0; i < NUM_ELTS(vertices); i++)
    remove_vertex_from_graph(&graph, vertices[i]);

  /* check them again */
  assert(vertex_count(&graph) == 0);

  /* add a few more (these are all real animals...) */
  add_vertex_to_graph(&graph, "star-nosed mole");
  add_vertex_to_graph(&graph, "blobfish");
  add_vertex_to_graph(&graph, "pink fairy armadillo");
  add_vertex_to_graph(&graph, "naked mole rat");

  names= get_vertex_list(&graph);

  /* check the vertices against the results that we expect to be returned */
  compare_vertex_lists(names, expected_results);

  /* now clean up after ourselves */
  free_vertex_name_list(names);
  graph_delete(&graph);

  #if !defined(ENABLE_VALGRIND)
  check_heap();
  #endif

  /* if this is the only thing printed the heap must be valid, and there
     must not have been any memory leaks */
  printf("I was sure that the assertions would all succeed!\n");

  return 0;
}
