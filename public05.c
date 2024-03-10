#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "string-graph.h"
#include "compare-vertex-lists.h"
#include "memory-functions.h"

/* CMSC 216, Spring 2023, Project #8
 * Public test 5 (public05.c)
 *
 * Tests calling get_neighbor_names(), and ensures that all memory was
 * properly released and there are no errors in the heap.  This test is the
 * same as public01.c other than for checking the correctness of the heap.
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
  char *vertices_to_add[]= {"koala", "parrot", "snake", "salamander",
                            "giraffe", "frog", "dog", "hippopotamus"};
  char *from[]= {"dog", "frog", "hippopotamus", "hippopotamus",
                 "hippopotamus", "parrot", "panda", "giraffe", "snake",
                 "snake"};
  char *to[]= {"frog", "dog", "dog", "salamander", "koala", "koala",
               "salamander", "frog", "salamander", "parrot"};
  const int costs[]= {2, 5, 9, 8, 7, 3, 1, 2, 10, 6};
  char *expected_results[]= {"dog", "koala", "salamander", NULL};
  char **names;
  int i;

  #if !defined(ENABLE_VALGRIND)
  setup_memory_checking();
  #endif

  graph_init(&graph);

  /* add some vertices */
  for (i= 0; i < NUM_ELTS(vertices_to_add); i++)
    add_vertex_to_graph(&graph, vertices_to_add[i]);

  /* add some edges */
  for (i= 0; i < NUM_ELTS(from); i++)
    create_graph_edge(&graph, from[i], to[i], costs[i]);

  names= get_neighbor_names(&graph, "hippopotamus");

  /* check the neighbors against the results that we expect to be returned */
  assert(compare_vertex_lists(names, expected_results));

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
