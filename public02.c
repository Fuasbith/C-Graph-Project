#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "string-graph.h"

/* CMSC 216, Spring 2023, Project #8
 * Public test 2 (public02.c)
 *
 * Tests calling remove_graph_edge() and ensures that the edges are properly
 * removed.  This test does not check for memory leaks or correctness of the
 * heap; it is only testing the correct behavior of the function.
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
  int costs[]= {2, 5, 9, 8, 7, 3, 1, 2, 10, 6, 12};
  int i;

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

  printf("I was sure that the assertions would all succeed!\n");

  return 0;
}
