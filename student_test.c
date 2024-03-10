#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "string-graph.h"
#include "compare-vertex-lists.h"
#include "memory-functions.h"

/* CMSC 216, Spring 2023, Project #8
 * Public test 9 (public09.c)
 *
 * Tests adding edges back to a vertex after all of its edges were removed
 * using remove_graph_edge(), and ensures that all memory was properly
 * released and there are no errors in the heap.
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

  #if !defined(ENABLE_VALGRIND)
  setup_memory_checking();
  #endif

  graph_init(&graph);

  /* add some vertices */
  add_vertex_to_graph(&graph, "apple");

  /* add some edges */
  create_graph_edge(&graph, "apple", "angle" , 10);
  create_graph_edge(&graph, "apple", "blueberry" , 10);
  create_graph_edge(&graph, "apple", "grape" , 10);
  create_graph_edge(&graph, "apple", "mid" , 10);
  create_graph_edge(&graph, "apple", "orange" , 10);
  create_graph_edge(&graph, "apple", "range" , 10);  

  /*  remove_vertex_from_graph(&graph, "angle");
      remove_vertex_from_graph(&graph, "orange");*/

  /* remove_graph_edge(&graph, "apple", "blueberry");
  remove_graph_edge(&graph, "apple", "grape");
  remove_graph_edge(&graph, "apple", "gross");
  remove_graph_edge(&graph, "apple", "grouch");*/

 graph_delete(&graph);

 #if !defined(ENABLE_VALGRIND)
  check_heap();
  #endif

  /* if this is the only thing printed the heap must be valid, and there
     must not have been any memory leaks */
  printf("I was sure that the assertions would all succeed!\n");

  return 0;
}
