#if !defined(DATASTRUCTURE_H)
#define DATASTRUCTURE_H
struct vertex;

typedef struct edge {
  unsigned int weight;
  struct vertex *destination;
  struct edge *next_edge;
} Edge;

typedef struct vertex {
  char *name;
  Edge *edge_list;
  struct vertex *next_vertex;
} Vertex;

typedef struct graph {
  Vertex *head;
  int total_vertices;
  int total_edges;
} String_graph;

#endif
