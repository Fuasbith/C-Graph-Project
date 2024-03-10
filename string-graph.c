/* Name:                 Daniel Truong
 * UID:                  117842166
 * TerpConnect Login ID: dtruong4
 * Section Number:       0201
 *
 * I pledge on my honor that I have not given or received any unauthorized
 * assistance on this examination (or assignment).
 */

/* This program uses an adjacency list to create a string graph. 
   The functions create a new graph and adds vertices to it.
   Those vertices connect to each other but at the same time also 
   connect to edges. Each vertice has an edge_list that contains an x 
   amount of edges. Each edge will point to a vertex which represent
   a connection between the original vertice and the vertice the
   edge is pointing to.The edges also contain weight which these 
   functions are able to change and return.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "string-graph.h"

/* This function initializes the graph by initializing it's structure 
   parameters to their base values.
 */
void graph_init(String_graph *const graph) {
  graph -> head = NULL;
  graph -> total_edges = 0;
  graph -> total_vertices = 0;
}

/* This function adds vertex to the graph . If there are no vertexes
   this function will create the first vertex. If any of the parameters
   are null it returns 0. This function will create a new Vertex and add it
   as long as a duplicate does not already exist within the graph. It also
   orders the Vertexes in alphabetical order or whatever order strcmp does so.
   If the vertex is added successfully it returns 1.
 */
short add_vertex_to_graph(String_graph *const graph, 
			  const char new_vertex[]) {

  Vertex *curr = NULL, *prev = NULL, *temp_Vertex = NULL;

  if (graph == NULL || new_vertex == NULL)
    return 0;

  curr = graph->head;

  /* this chunk brings us to the alphabetically correct
     vertex position in the list
     or if the name already exists it returns 0
  */
  while (curr != NULL && strcmp(new_vertex, curr->name) >= 0) {
    if (strcmp(curr->name, new_vertex) == 0)
      return 0;
    prev = curr;
    curr = curr->next_vertex;
  }

  /* creates a new Vertex and places it at the 
     alphabetically correct position in the list
     or sets graph->head equal to temp vertex if the list is empty
  */
  temp_Vertex = malloc(sizeof(*temp_Vertex));
  if (temp_Vertex != NULL) {
    temp_Vertex->name = malloc(strlen(new_vertex) + 1);
    strcpy(temp_Vertex->name, new_vertex);
    if (prev == NULL) { /* when list empty or correct position is first */
      graph->head = temp_Vertex;
      temp_Vertex->next_vertex = curr;
      temp_Vertex->edge_list = NULL; /* for valgrind uninitialized error */
    }
    else { /*when anywhere but the beginning of the list */
      prev->next_vertex = temp_Vertex;
      temp_Vertex->next_vertex = curr;
      temp_Vertex->edge_list = NULL; /* for valgrind uninitialized error */
    }
    graph -> total_vertices += 1;
  }

  return 1;
}

/* This function returns 0 if graph is NULL. Otherwise it will just return
   the value of total_vertices which is incremented by the 
   add_vertex_to_graph function.
 */
short vertex_count(const String_graph *const graph) {

  if (graph == NULL)
    return 0;
  return graph->total_vertices;
}

/* Returns 1 if there exists a vertex with the same name as the
   parameter 'name' which means name is a vertice. 
   Returns 0 if name is not in the graph or graph is NULL
 */
short isa_vertex(const String_graph *const graph, const char name[]) {
  short result = 0;
  Vertex *curr = NULL;

  if (graph == NULL || name == NULL)
    result = 0;
  else {
    curr = graph->head;
    while (curr != NULL && result == 0) {
      if (strcmp(curr -> name, name) == 0)
	result = 1;
      curr = curr -> next_vertex;
    }
  }

  return result;
}

/* This function creates and returns an array of character pointers. 
   Enough space will have to be allocated for the amount of vertices in the 
   graph plus 1 because the last space will be NULL.
   Each index has a character pointer that has to point to a copy of the name 
   of the vertexes in the graph. If graph is NULL return NULL. 
   Otherwise return the array after it's been filled.
 */
char **get_vertex_list(const String_graph *const graph) {
  char **arr = NULL;
  Vertex *curr = NULL;
  int i;
  
  if (graph == NULL)
    return NULL;

  curr = graph->head;
  arr = malloc((vertex_count(graph) + 1) * sizeof(char*));

  for (i = 0; i < vertex_count(graph); i++) {
    arr[i] = malloc(strlen(curr->name) + 1);
    strcpy(arr[i], curr->name);
    curr = curr-> next_vertex;
  }
  arr[i] = NULL;

  return arr;
}

/* This function creates an edge between a source and destination vertex. 
   An edge has a weight as well as a vertex it points to. 
   If the vertexes in the parameter do not exist, make them and 
   then create the edge. 
   If any of the pointer parameters are NULL or weight is negative 
   then return 0. 
   If the edge is successfully added then return 1.
   Makes the edge list in alphabetical order for each vertex
 */
short create_graph_edge(String_graph *const graph, const char source[],
                        const char dest[], int weight) {
  Vertex *curr = NULL;
  Edge *temp = NULL, *prev_temp = NULL, *new_edge = NULL;
  Vertex *dest_vertex = NULL;
  if (graph == NULL || source == NULL || dest == NULL ||  weight < 0)
    return 0;

  /*adds the vertexes to the graph if they don't exist */
  if (isa_vertex(graph, source) == 0)
    add_vertex_to_graph(graph, source);
  if (isa_vertex(graph, dest) == 0)
    add_vertex_to_graph(graph, dest);

  /*find destination vertex */
  dest_vertex = graph->head;
  while (dest_vertex != NULL && strcmp(dest_vertex->name, dest) != 0) {
    dest_vertex = dest_vertex->next_vertex;
  }

  curr = graph->head;
  /*iterate to let curr find where source is in the list */
  while (curr != NULL && strcmp(curr->name, source) != 0) {
    curr = curr->next_vertex;
  }

  temp = curr -> edge_list;
  /*iterate through the source vertex's edge_list to let temp 
    find the right dest.
    Do so alphabetically so the edge list is created in alphabetical order.

    If dest edge exists: prev_temp will be on the dest and temp will be 
    1 edge ahead
    If dest edge no exists: prev_temp & temp surrounds the area new_edge
    will be in
  */
  while (temp != NULL && strcmp(dest, temp->destination->name) >= 0) {  
    prev_temp = temp;
    temp = temp->next_edge;
  }
  

   /*if source to dest edge already exist change weight */
  if (prev_temp != NULL && strcmp(prev_temp->destination->name, dest) == 0) {
    prev_temp->weight = weight;
  }
  else { /*if we're here the edge doesn't exist so make the edge*/
    /* you also got to allocate space for it */
    new_edge = malloc(sizeof(*new_edge));
    new_edge-> weight = weight;
    new_edge-> destination = dest_vertex;
    /*if this is the first edge for that vertex */
    if (curr->edge_list == NULL) {
      curr->edge_list = new_edge;
      curr->edge_list->next_edge = NULL; /*for Valgrind uninitialized error */
    }
    else { /*if this isn't the first edge for that vertex*/
      new_edge->next_edge = temp;
       /*when the new edge is not alphabetically the smallest*/
      if (prev_temp != NULL)
	prev_temp->next_edge = new_edge;
      /*when new edge is alphabetically lowest, make it head of the edgelist*/
      else { 
	curr->edge_list = new_edge;
      }
    }
    graph->total_edges++;
  }

  return 1;
}

/* This function finds the edge that goes from source to destination and 
   returns that edge's weight. If any of the parameters are null, 
   the source or destination do not exist as edges, or the edge itself 
   does not exist return -1.
 */
short get_graph_edge_weight(const String_graph *const graph,
                            const char source[], const char dest[]) {
  short value;
  Vertex *curr;
  Edge *temp;

  /* null check*/
  if (graph == NULL || source == NULL || dest == NULL ||
      isa_vertex(graph, source) == 0 || isa_vertex(graph, dest) == 0)
    return -1;

  curr = graph->head;
  /*iterate to let curr find where source is in the list */
  while (curr != NULL && strcmp(curr->name, source) != 0) {
    curr = curr->next_vertex;
  }
  
  temp = curr -> edge_list;
  /*iterate through the source vertex's edge_list
    to let temp find the right dest */
  while (temp != NULL && strcmp(temp->destination->name, dest) != 0) {
    temp = temp->next_edge;
  }
  
   /*if temp doesn't equal NULL then an edge has been found */
  if (temp != NULL) {
    value = temp->weight;
  }
  else { /*the edge doesn't exist and return -1 */
    value = -1;
  }

  return value;
}

/* This function finds the vertex given in the parameter and returns the
   amount of outgoing edges it posseses. If either parameter is 
   null return -1. 
 */
short neighbor_count(const String_graph *const graph, const char vertex[]) {
  short result = 0;
  Vertex *curr = NULL;
  Edge *temp = NULL;
  if (graph == NULL || vertex == NULL || isa_vertex(graph, vertex) == 0)
    return -1;

  curr = graph->head;
  /*iterate to let curr find where vertex is in the list */
  while (curr != NULL && strcmp(curr->name, vertex) != 0) {
    curr = curr->next_vertex;
  }

  temp = curr -> edge_list;
  /*iterate through vertex's edge_list to count amount of edges */
  while (temp != NULL) {
    temp = temp->next_edge;
    result++;
  }

  return result;
}













/*************************************
 *           Start of                *
 *           Project 8               *
 *************************************/












/*
  If names is null don't do anything. Otherwise this function takes an
  array of character pointers and frees each index of the array.
  At the end the array names is also freed.
*/
void free_vertex_name_list(char **const names) {
  int array_size = 0;

  if (names != NULL) {
    /*free each index in the array*/
    while (names[array_size] != NULL) {
      free(names[array_size]);
      array_size++;
    }

    free(names); /*free the entire names array after freeing its indexes */
  }
}

/*
  If graph is NULL or the vertex isn't in the graph return NULL. Otherwise
  this function creates and returns a dynamically allocated array of
  character pointers. The pointers in each index point to a copy of the names 
  of the neighbors that vertex possess. Each index should be dynamically 
  allocated as well. The names put into the array should be done so in
  alphabetical order. The array should have 1 extra space for a NULL 
  at the end after all the neighbor names have been added.
*/
char **get_neighbor_names(const String_graph *const graph, 
			  const char vertex[]) {
  Vertex *curr_vertex = NULL;
  Edge *curr_edge = NULL;
  char **new_array = NULL;
  int array_size = neighbor_count(graph, vertex), i;


  if (graph == NULL || isa_vertex(graph, vertex) == 0)
    return NULL;

  curr_vertex = graph->head;
  /*Dynamically allocate memory for new_array
    Add 1 for the instruction mandated NULL at the end of new_array*/
  new_array =  malloc((array_size + 1) * sizeof(char*));

  /*iterate to let curr_vertex find where vertex is in the list */
  while (curr_vertex != NULL && strcmp(curr_vertex->name, vertex) != 0) {
    curr_vertex = curr_vertex->next_vertex;
  }

  curr_edge = curr_vertex->edge_list;
  /*fill & dynamically allocate new_array with pointers to copies
    of neighbor vertice names*/
  for (i = 0; i < array_size; i++) { 
    /* plus 1 for the Null char a string needs */ 
    new_array[i] = malloc(strlen(curr_edge->destination->name) + 1);
    strcpy(new_array[i], curr_edge->destination->name);
    curr_edge = curr_edge->next_edge;
  }
  new_array[i] = NULL;

  return new_array;
}

/*
  If graph is NULL return 0. If the source or destination vertex does
  not exist in the graph return 0. If the edge between source and dest
  doesn't exist return 0. Otherwise this graph removes the edge
  between the 2 and frees the memory from the removed edge. If
  the edge is successfully removed return 1.
*/
int remove_graph_edge(String_graph *const graph, const char source[],
                      const char dest[]) {
  Vertex *curr_vertex = NULL;
  Edge *curr_edge = NULL;
  Edge *prev_edge = NULL;

  /*Null check, vertex existence check, edge existence check*/
  if (graph == NULL || isa_vertex(graph, source) == 0 || 
      isa_vertex(graph, dest) == 0 || 
      get_graph_edge_weight(graph, source, dest) == -1)
    return 0;

  curr_vertex = graph->head;

  /*finds the source vertex in the graph and points curr_vertex to it*/
  while (curr_vertex != NULL && strcmp(curr_vertex->name, source) != 0) {
    curr_vertex = curr_vertex->next_vertex;
  }

  /*find the edge to dest; change what the previous edge points to; 
    free the edge that has nothing pointing to it*/

  curr_edge = curr_vertex->edge_list;
  /*curr_edge should end up at the edge that points to dest 
    and prev_edge is 1 edge behind it*/
  while (curr_edge != NULL && 
	 strcmp(curr_edge->destination->name, dest) != 0) {
    prev_edge = curr_edge;
    curr_edge = curr_edge->next_edge;
  }

  /*if the edge to remove is the first edge for the vertice
   make the next edge become the edge_list*/
  if (prev_edge == NULL) {
    curr_vertex->edge_list = curr_edge->next_edge;
    (graph->total_edges)--;
  }
  else {
  /*if the edge to remove is not the first edge*/
  prev_edge->next_edge = curr_edge->next_edge;
  (graph->total_edges)--;
  }

  free(curr_edge);

  return 1;
}

/*If the graph is NULL return 0. If vertex doesn't exist return 0. Otherwise
  remove the vertex as well as any outgoing and incoming edges. Return 1 
  if the vertex is removed successfully.
*/
int remove_vertex_from_graph(String_graph *const graph, const char vertex[])
{
  Vertex *curr_vertex = NULL;
  Vertex *prev_vertex = NULL;
  char **arr = NULL;
  int i;

  if (graph == NULL || isa_vertex(graph, vertex) == 0)
    return 0;

  /*first free the edges and then the vertex itself*/

  /*loop through the graphs's vertice list
    remove and free all incoming edges to vertex*/
  curr_vertex = graph->head;
  while (curr_vertex != NULL) {
    remove_graph_edge(graph, curr_vertex->name, vertex);
    curr_vertex = curr_vertex->next_vertex;
  }

  /*obtain the location of vertex in the list*/
  curr_vertex = graph-> head;
  while (curr_vertex != NULL && strcmp(curr_vertex->name, vertex) != 0) {
    prev_vertex = curr_vertex;
    curr_vertex = curr_vertex->next_vertex;
  }

  arr = get_neighbor_names(graph, vertex);
  /*remove and free all outgoing edges from vertex*/
  for (i = 0; i < neighbor_count(graph, vertex); i++) {
    remove_graph_edge(graph, vertex, arr[i]);
  }
  free_vertex_name_list(arr);

  /*gets rid of the last edge, the edge_list, from vertex*/
  free(curr_vertex->edge_list);

  /*what if the vertex removed is the head vertex*/
  if (strcmp(graph->head->name, vertex) == 0) {
    /*make the graph head point to the next vertex*/
    graph->head = curr_vertex->next_vertex;
  }
  else {
  /*what if the vertex removed is any other vertex*/
    prev_vertex->next_vertex = curr_vertex->next_vertex;
  }

  free(curr_vertex->name);
  free(curr_vertex);
  (graph->total_vertices)--;

  return 1;
}

/*
  If graph is NULL do nothing. This function should deallocate
  all dynamically-allocated memory in the graph. So when this
  function is done running, the graph data structure that graph pointed
  to effectively no longer exists in memory
*/
void graph_delete(String_graph *const graph) {
  char **arr = NULL;
  int i = 0;
  int vertex_amount;

  if (graph != NULL) {
    arr = get_vertex_list(graph);
    vertex_amount = graph->total_vertices;
    /*
      Loop until all vertices have been nixed
      Continuously removes each vertex until the graph is empty
    */
    while(vertex_amount != 0) {
      remove_vertex_from_graph(graph, arr[i]);
      vertex_amount--;
      i++;
    }
    free_vertex_name_list(arr);
  }
}
