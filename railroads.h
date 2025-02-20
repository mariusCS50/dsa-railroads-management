/* GAIBU Marius - 315CB */
#include "queue.h"

// Structure that represents a railroad
typedef struct railroad {
    int dest;
    int num_sections;
    float *new_wear;
    float *wear;
    int keep_rail;
    struct railroad *next;
} Rail, *Railroad;

// Structure that represents the railroad graph
typedef struct graph {
    int num_cities;
    char **cities;
    Railroad *adj;
} Graph;


// Functions related to the railroad graph
Graph* create_railroad_graph();
Railroad build_railroad_with_wear(int dest, int num_sections);
Railroad build_railroad_with_cost(int dest, int cost);
void destroy_railroad_graph(Graph *g);

// Functions for checking the existence of a railroad in the graph
int listed_city(Graph *g, char* city);
void list_new_city(Graph *g, char* city);
int city_index(Graph *g, char* city);

// Functions for processing the wear degrees
void process_railroad_with_wear(FILE* fin, Graph *g, Queue* q);
void compute_new_wear_degrees(Graph *g);
void update_wear_degrees(Graph *g);
void railroads_wear_status(FILE* fout, Graph *g, Queue *q, float threshold);

// Functions for processing the graph's profitability
void process_railroad_with_cost(FILE* fin, Graph *g, Queue *q);
void choose_max_k_profitable_rails(Graph *g, char* start_city, int k_max_rails);
void show_railroads_to_keep(FILE* fout, Graph *g, Queue *q, int k_max_rails);
