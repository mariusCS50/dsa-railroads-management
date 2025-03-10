/* GAIBU Marius - 315CB */
#include "railroads.h"

// Create the railroad graph
Graph* create_railroad_graph() {
	Graph *g = (Graph*)malloc(sizeof(Graph));
	g->num_cities = 0;
	g->cities = NULL;
	g->adj = NULL;
	return g;
}

// Create a railroad with sections and wear degree
Railroad build_railroad_with_wear(int dest, int num_sections) {
	Railroad rail = (Railroad)malloc(sizeof(Rail));

	rail->dest = dest;
	rail->num_sections = num_sections;
	rail->new_wear = (float*)malloc(num_sections * sizeof(float));
	rail->wear = (float*)malloc(num_sections * sizeof(float));

	return rail;
}

// Create a railroad with the cost between cities
Railroad build_railroad_with_cost(int dest, int cost) {
	Railroad rail = (Railroad)malloc(sizeof(Rail));

	rail->dest = dest;
	rail->num_sections = cost;  // numărul de secțiuni reprezintă costul
	rail->keep_rail = 0;

	// la această cerință nu folosim grade de uzură
	rail->new_wear = NULL;
	rail->wear = NULL;

	return rail;
}

// Destroy the railroad graph
void destroy_railroad_graph(Graph *g) {
	for (int city_id = 0; city_id < g->num_cities; city_id++) {
		Railroad rail = g->adj[city_id];

		while (rail != NULL) {
			Railroad aux = rail;
			rail = rail->next;
			if (aux->wear != NULL) {
				free(aux->new_wear);
				free(aux->wear);
			}
			free(aux);
		}
		free(g->cities[city_id]);
	}
	free(g->cities);
	free(g->adj);
	free(g);
}

// Check if a city is already present and encoded in the graph
int listed_city(Graph *g, char* city) {
	for (int i = 0; i < g->num_cities; i++) {
		if (strcmp(g->cities[i], city) == 0) {
			return 1;
		}
	}
	return 0;
}

// Add a new city to the graph, assigning it its corresponding index
void list_new_city(Graph *g, char* city) {
	g->num_cities++;

	g->adj = realloc(g->adj, g->num_cities * sizeof(Railroad));
	g->cities = realloc(g->cities, g->num_cities * sizeof(char *));
	g->cities[g->num_cities - 1] = (char *)calloc(strlen(city) + 1, sizeof(char));

	g->adj[g->num_cities - 1] = NULL;
	snprintf(g->cities[g->num_cities - 1], strlen(city) + 1, "%s", city);
}

// Return the index of a city in the graph
int city_index(Graph *g, char* city) {
	for (int i = 0; i < g->num_cities; i++) {
		if (strcmp(g->cities[i], city) == 0) {
			return i;
		}
	}
	return -1;
}
