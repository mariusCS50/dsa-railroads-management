/* GAIBU Marius - 315CB */
#include "railroads.h"

#define MAX_SIZE 100
#define max(a, b) a > b ? a : b
#define min(a, b) a < b ? a : b

// Citește gradele de uzură pentru calea ferată în ambele sensuri
void read_sections_wear(FILE* fin, Railroad src_rail, Railroad dest_rail) {
    int num_sections = src_rail->num_sections;
    for (int i = 0; i < num_sections; i++) {
        fscanf(fin, "%f", &(src_rail->wear[i]));
        dest_rail->wear[num_sections - i - 1] = src_rail->wear[i];
    }
}

// Caută gradul maxim de uzură din secțiunile vecine ale unui oraș
void vicinity_highest_wear(Railroad city_rail, float *max_wear) {
    while (city_rail != NULL) {
        *max_wear = max(*max_wear, city_rail->wear[0]);
        city_rail = city_rail->next;
    }
}

// Găsește gradul maxim de uzură de lângă o secțiune
void find_highest_wear_degree(Graph *g, int src, Railroad rail, int section_id, float *max_wear) {
    if (rail->num_sections == 1) {
        // Secțiunea este între două orașe care trebuie verificate
        vicinity_highest_wear(g->adj[src], max_wear);
        vicinity_highest_wear(g->adj[rail->dest], max_wear);
    } else if (section_id == 0) {
        // Secțiunea este între orasul sursă și o altă secțiune
        *max_wear = rail->wear[section_id + 1];
        vicinity_highest_wear(g->adj[src], max_wear);
    } else if (section_id == rail->num_sections - 1) {
        // Secțiunea este între orasul destinație și o altă secțiune
        *max_wear = rail->wear[section_id - 1];
        vicinity_highest_wear(g->adj[rail->dest], max_wear);
    } else {
        // Secțiunea este între alte două secțiuni
        *max_wear = max(rail->wear[section_id - 1], rail->wear[section_id + 1]);
    }
}

// Procesează datele de intrare pentru o cale ferată cu grade de uzură
void process_railroad_with_wear(FILE* fin, Graph *g, Queue* q) {
    int num_sections = 0;
    char src[MAX_SIZE], dest[MAX_SIZE];
    fscanf(fin, "%s%s%d", src, dest, &num_sections);

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
    Railroad src_rail = build_railroad_with_wear(dest_idx, num_sections);
    Railroad dest_rail = build_railroad_with_wear(src_idx, num_sections);

    read_sections_wear(fin, src_rail, dest_rail);

    // Inserăm noile căi ferate în listele de adiacență respective fiecăreia
    src_rail->next = g->adj[src_idx];
    g->adj[src_idx] = src_rail;

    dest_rail->next = g->adj[dest_idx];
    g->adj[dest_idx] = dest_rail;
}

// Calculează gradele noi de uzură pe baza gradelor curente
void compute_new_wear_degrees(Graph *g) {
    for (int city_id = 0; city_id < g->num_cities; city_id++) {
        Railroad rail = g->adj[city_id];
        while (rail != NULL) {
            for (int i = 0; i < rail->num_sections; i++) {
                rail->new_wear[i] = 2 * rail->wear[i];
                // Dacă gradul de uzură curent este 0, căutăm gradul maxim vecin
                if (rail->new_wear[i] == 0) {
                    find_highest_wear_degree(g, city_id, rail, i, &(rail->new_wear[i]));
                    rail->new_wear[i] = rail->new_wear[i] / 2;
                }
            }
            rail = rail->next;
        }
    }
}

// Actualizează gradele curente de uzură cu cele noi calculate
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
    Afișează după prioritate căile ferate și gradele lor curente de uzură,
    împreună cu indicii căilor care pot fi păstrate
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
        // Afișăm gradele de uzură și le adăugăm la medie
        float avg_wear = 0;
        for (int i = 0; i < rail->num_sections; i++) {
            fprintf(fout, "%.2f ", rail->wear[i]);
            avg_wear += rail->wear[i] / (float)rail->num_sections;
        }
        // Dacă media este mai mică decât limita de uzură, salvăm indicele căii
        if (avg_wear < threshold) {
            rails_to_keep = realloc(rails_to_keep, ++num_rtk * sizeof(int));
            rails_to_keep[num_rtk - 1] = railroad_idx;
        }
        fprintf(fout, "\n");
        pop(q);
    }

    // Afișăm indicii căilor care pot fi păstrate
    for (int rail_idx = 0; rail_idx < num_rtk; rail_idx++) {
        fprintf(fout, "%d ", rails_to_keep[rail_idx]);
    }
    free(rails_to_keep);
}
