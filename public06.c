#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "string-graph.h"
#include "memory-functions.h"

/* CMSC 216, Spring 2023, Project #8
 * Public test 6 (public06.c)
 *
 * Tests calling remove_graph_edge() and ensures that the edges are properly
 * removed, and ensures that all memory was properly released and there are
 * no errors in the heap.  This test is the same as public02.c other than
 * for checking the correctness of the heap.
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
                            "giraffe", "elephant", "dog", "hedgehog"};
  char *from[]= {"dog", "elephant", "hedgehog", "hedgehog", "hedgehog",
                 "hedgehog", "parrot", "panda", "giraffe", "snake", "snake"};
  char *to[]= {"elephant", "dog", "dog", "salamander", "koala", "snake",
               "koala", "salamander", "elephant", "salamander", "parrot"};
  const int costs[]= {2, 5, 9, 8, 7, 3, 1, 2, 10, 6, 12};
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

  /* check hedgehog's neighbors */
  assert(neighbor_count(&graph, "hedgehog") == 4);

  /* now remove two of them */
  remove_graph_edge(&graph, "hedgehog", "koala");
  remove_graph_edge(&graph, "hedgehog", "salamander");

  /* check its neighbors again */
  assert(neighbor_count(&graph, "hedgehog") == 2);
  assert(get_graph_edge_weight(&graph, "hedgehog", "dog") == 9);
  assert(get_graph_edge_weight(&graph, "hedgehog", "snake") == 3);

  /* now clean up after ourselves */
  graph_delete(&graph);

  #if !defined(ENABLE_VALGRIND)
  check_heap();
  #endif

  /* if this is the only thing printed the heap must be valid, and there
     must not have been any memory leaks */
  printf("I was sure that the assertions would all succeed!\n");

  return 0;
}
