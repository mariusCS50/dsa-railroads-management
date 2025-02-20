/* GAIBU Marius - 315CB */
#include "railroads.h"

#define MAX_SIZE 100
#define max(a, b) a > b ? a : b
#define min(a, b) a < b ? a : b

// Read the wear degrees for the railroad in both directions
void read_sections_wear(FILE* fin, Railroad src_rail, Railroad dest_rail) {
    int num_sections = src_rail->num_sections;
    for (int i = 0; i < num_sections; i++) {
        fscanf(fin, "%f", &(src_rail->wear[i]));
        dest_rail->wear[num_sections - i - 1] = src_rail->wear[i];
    }
}

// Find the maximum wear degree among neighboring sections of a city
void vicinity_highest_wear(Railroad city_rail, float *max_wear) {
    while (city_rail != NULL) {
        *max_wear = max(*max_wear, city_rail->wear[0]);
        city_rail = city_rail->next;
    }
}

// Find the maximum wear degree next to a section
void find_highest_wear_degree(Graph *g, int src, Railroad rail, int section_id, float *max_wear) {
    if (rail->num_sections == 1) {
        // The section is between two cities that need to be checked
        vicinity_highest_wear(g->adj[src], max_wear);
        vicinity_highest_wear(g->adj[rail->dest], max_wear);
    } else if (section_id == 0) {
        // The section is between the source city and another section
        *max_wear = rail->wear[section_id + 1];
        vicinity_highest_wear(g->adj[src], max_wear);
    } else if (section_id == rail->num_sections - 1) {
        // The section is between the destination city and another section
        *max_wear = rail->wear[section_id - 1];
        vicinity_highest_wear(g->adj[rail->dest], max_wear);
    } else {
        // The section is between two other sections
        *max_wear = max(rail->wear[section_id - 1], rail->wear[section_id + 1]);
    }
}

// Process input data for a railroad with wear degrees
void process_railroad_with_wear(FILE* fin, Graph *g, Queue* q) {
    int num_sections = 0;
    char src[MAX_SIZE], dest[MAX_SIZE];
    fscanf(fin, "%s%s%d", src, dest, &num_sections);

    /*
        Check if the source and destination cities are in the graph;
        if not, add them to the list of cities
    */
    if (!listed_city(g, src)) {
        list_new_city(g, src);
    }
    if (!listed_city(g, dest)) {
        list_new_city(g, dest);
    }

    int src_idx = city_index(g, src);
    int dest_idx = city_index(g, dest);

    // Add the indices of source and destination cities to the priority queue
    push(q, src_idx, dest_idx);

    // Construct railroads from source->destination and destination->source
    Railroad src_rail = build_railroad_with_wear(dest_idx, num_sections);
    Railroad dest_rail = build_railroad_with_wear(src_idx, num_sections);

    read_sections_wear(fin, src_rail, dest_rail);

    // Insert the new railroads into the respective adjacency lists
    src_rail->next = g->adj[src_idx];
    g->adj[src_idx] = src_rail;

    dest_rail->next = g->adj[dest_idx];
    g->adj[dest_idx] = dest_rail;
}

// Calculate the new wear degrees based on the current wear degrees
void compute_new_wear_degrees(Graph *g) {
    for (int city_id = 0; city_id < g->num_cities; city_id++) {
        Railroad rail = g->adj[city_id];
        while (rail != NULL) {
            for (int i = 0; i < rail->num_sections; i++) {
                rail->new_wear[i] = 2 * rail->wear[i];
                // If the current wear degree is 0, search for the maximum neighboring degree
                if (rail->new_wear[i] == 0) {
                    find_highest_wear_degree(g, city_id, rail, i, &(rail->new_wear[i]));
                    rail->new_wear[i] = rail->new_wear[i] / 2;
                }
            }
            rail = rail->next;
        }
    }
}

// Update the current wear degrees with the newly calculated ones
void update_wear_degrees(Graph *g) {
    for (int city_id = 0; city_id < g->num_cities; city_id++) {
        Railroad rail = g->adj[city_id];
        while (rail != NULL) {
            for (int i = 0; i < rail->num_sections; i++) {
                rail->wear[i] = min(rail->new_wear[i], 100);
            }
            rail = rail->next;
        }
    }
}

/*
    Display the railroads per priority and their current wear degrees,
    along with indices of railroads that can be retained
*/
void railroads_wear_status(FILE* fout, Graph *g, Queue *q, float threshold) {
    int *rails_to_keep = NULL, num_rtk = 0, railroad_idx = 0;

    while (q->head != NULL) {
        railroad_idx++;
        int src = q->head->src;
        int dest = q->head->dest;

        Railroad rail = g->adj[src];
        while (rail->dest != dest) rail = rail->next;

        fprintf(fout, "%s %s %d ", g->cities[src], g->cities[dest], rail->num_sections);
        // Print the wear degrees and compute the average
        float avg_wear = 0;
        for (int i = 0; i < rail->num_sections; i++) {
            fprintf(fout, "%.2f ", rail->wear[i]);
            avg_wear += rail->wear[i] / (float)rail->num_sections;
        }
        // If the average is less than the wear threshold, save the index of the railroad
        if (avg_wear < threshold) {
            rails_to_keep = realloc(rails_to_keep, ++num_rtk * sizeof(int));
            rails_to_keep[num_rtk - 1] = railroad_idx;
        }
        fprintf(fout, "\n");
        pop(q);
    }

    // Print the indices of the railroads that can be retained
    for (int rail_idx = 0; rail_idx < num_rtk; rail_idx++) {
        fprintf(fout, "%d ", rails_to_keep[rail_idx]);
    }
    free(rails_to_keep);
}
