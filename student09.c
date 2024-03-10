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
  char *vertices_to_add[]= {"horse", "cow", "chicken", "turkey", "lamb",
                            "goat", "donkey", "goose", "mule"};
  char *from[]= {"cow", "cow", "cow", "cow",
                 "lamb", "lamb", "lamb", "lamb", "lamb", "lamb",
                 "mule", "mule", "mule",
                 "donkey", "donkey", "donkey", "donkey",
                 "turkey",
                 "goose",
                 "horse", "horse",
                 "chicken", "chicken", "chicken", "chicken",
                 "goat", "goat", "goat", "goat", "goat"};
  char *to[]= {"lamb", "turkey", "chicken", "goat",
               "mule", "turkey", "goat", "horse", "lamb", "chicken",
               "goose", "mule", "chicken",
               "turkey", "horse", "goat", "cow",
               "horse",
               "turkey", 
               "goose", "chicken", 
               "lamb", "cow", "horse", "mule",
               "cow", "goose", "turkey", "horse", "mule"};
  const int costs[]= {9, 3, 4, 10, 15, 3, 18, 7, 5, 21, 1, 12, 5, 30, 17,
                      14, 8, 29, 15, 27, 3, 1, 5, 1, 6, 8, 15, 26, 10, 9};
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

  /* check donkey's neighbors */
  assert(neighbor_count(&graph, "donkey") == 4);

  /* now remove all of them */
  remove_graph_edge(&graph, "donkey", "turkey");
  remove_graph_edge(&graph, "donkey", "horse");
  remove_graph_edge(&graph, "donkey", "goat");
  remove_graph_edge(&graph, "donkey", "cow");

  /* check its neighbors again */
  assert(neighbor_count(&graph, "donkey") == 0);

  /* now add some new edges to donkey */
  create_graph_edge(&graph, "donkey", "lamb", 100);
  create_graph_edge(&graph, "donkey", "mule", 200);
  create_graph_edge(&graph, "donkey", "chicken", 300);

  /* check its neighbors again */
  assert(neighbor_count(&graph, "donkey") == 3);

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
