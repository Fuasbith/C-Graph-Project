#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "string-graph.h"
#include "compare-vertex-lists.h"

/* CMSC 216, Spring 2023, Project #8
 * Public test 1 (public01.c)
 *
 * Tests calling get_neighbor_names().  This test does not check for memory
 * leaks or correctness of the heap; it is only testing the correct behavior
 * of the function.
 *
 * In order to run valgrind on this test note that it will unavoidably have
 * memory leaks, since it does not call graph_delete() as the last
 * operation.  So when running valgrind on this test, add the valgrind
 * option --leak-check=no to turn off checking for memory leaks.  Then fix
 * any *other* errors that valgrind identifies (other than memory leaks).
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

  printf("I was sure that the assertions would all succeed!\n");

  return 0;
}
