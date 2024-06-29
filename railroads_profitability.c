/* GAIBU Marius - 315CB */
#include "railroads.h"

#define MAX_SIZE 100

// Selectează păstrarea căii ferate dintre orașele sursă și destinație
void choose_rail(Graph *g, int src, int dest) {
    Railroad rail = g->adj[src];
    while (rail->dest != dest) rail = rail->next;
    rail->keep_rail = 1;
}

// Procesează datele de intrare pentru o cale ferată cu cost
void process_railroad_with_cost(FILE* fin, Graph *g, Queue* q) {
    int cost = 0;
    char src[MAX_SIZE], dest[MAX_SIZE];
    fscanf(fin, "%s%s%d", src, dest, &cost);

    /*
        Verificăm dacă orașele sursă și destinație au fost introduse în graf, în
        caz contrar sunt adăugate la lista de orașe
    */
    if (!listed_city(g, src)) {
        list_new_city(g, src);
    }
    if (!listed_city(g, dest)) {
        list_new_city(g, dest);
    }

    int src_idx = city_index(g, src);
    int dest_idx = city_index(g, dest);

    // Adăugăm indicii orașelor sursă și destinație în coada de prioritate
    push(q, src_idx, dest_idx);

    // Construim căile ferate sursă->destinație și destinație->sursă
    Railroad src_rail = build_railroad_with_cost(dest_idx, cost);
    Railroad dest_rail = build_railroad_with_cost(src_idx, cost);

    // Inserăm noile căi ferate în listele de adiacență respective fiecăreia
    src_rail->next = g->adj[src_idx];
    g->adj[src_idx] = src_rail;

    dest_rail->next = g->adj[dest_idx];
    g->adj[dest_idx] = dest_rail;
}

// Alege maxim k căi ferate pentru o profitabilitate maximă
void choose_max_k_profitable_rails(Graph *g, char *start_city, int k_max_rails) {
    int *distances = (int *)malloc(g->num_cities * sizeof(int));
    int *visited = (int *)calloc(g->num_cities, sizeof(int));

    for (int city = 0; city < g->num_cities; city++) {
        distances[city] = INT_MAX;
    }

    // Începem căutarea cu orașul origine cu costul 0
    distances[city_index(g, start_city)] = 0;
    visited[city_index(g, start_city)] = 1;

    for (int num_rail = 0; num_rail < k_max_rails; num_rail++) {
        Railroad rail = NULL;
        int src = 0, dest = 0, cost = INT_MAX;

        /*
            Iterăm prin toate orașele vizitate și căutăm calea ferată către cel
            mai apropiat oraș de origine care nu este vizitat
        */
        for (int city = 0; city < g->num_cities; city++) {
            if (visited[city]) {
                rail = g->adj[city];
                while (rail != NULL) {
                    if (!visited[rail->dest] && distances[city] + rail->num_sections < cost) {
                        src = city;
                        dest = rail->dest;
                        cost = distances[city] + rail->num_sections;
                    }
                    rail = rail->next;
                }
            }
        }

        // Alegem calea ferată dintre orașele sursă și destinație
        choose_rail(g, src, dest);
        choose_rail(g, dest, src);

        // Setăm orașul ales ca vizitat și îi salvăm costul minim
        distances[dest] = cost;
        visited[dest] = 1;
    }
    free(distances);
    free(visited);
}

// Afișăm căile ferate care au fost selectate
void show_railroads_to_keep(FILE *fout, Graph *g, Queue *q, int k_max_rails) {
    fprintf(fout, "%d\n", k_max_rails);

    while (q->head != NULL) {
        int src = q->head->src;
        int dest = q->head->dest;

        Railroad rail = g->adj[src];
        while (rail->dest != dest) rail = rail->next;

        if (rail->keep_rail) {
            fprintf(fout, "%s %s\n", g->cities[src], g->cities[dest]);
        }
        pop(q);
    }
}
