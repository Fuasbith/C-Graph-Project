#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "string-graph.h"
#include "compare-vertex-lists.h"

/* CMSC 216, Spring 2023, Project #8
 * Public test 3 (public03.c)
 *
 * Tests calling remove_vertex_from_graph() and ensures that the vertices
 * are properly removed.  This test does not check for memory leaks or
 * correctness of the heap; it is only testing the correct behavior of the
 * function.
 *
 * (c) Larry Herman, 2023.  You are allowed to use this code yourself, but
 * not to provide it to anyone else.
 */

int main(void) {
  String_graph graph;
  char *vertices_to_add[]= {"koala", "quokka", "parrot", "zebra", "hedgehog",
                            "dog", "elephant"};
  char *expected_results[]= {"dog", "elephant", "hedgehog", "quokka",
                             "zebra", NULL};
  char **names;
  int i;

  graph_init(&graph);

  /* add some vertices */
  for (i= 0; i < NUM_ELTS(vertices_to_add); i++)
    add_vertex_to_graph(&graph, vertices_to_add[i]);

  /* now remove two of them */
  remove_vertex_from_graph(&graph, "koala");
  remove_vertex_from_graph(&graph, "parrot");

  names= get_vertex_list(&graph);

  /* check the vertices against the results that we expect to be returned */
  compare_vertex_lists(names, expected_results);

  printf("I was sure that the assertions would all succeed!\n");

  return 0;
}
