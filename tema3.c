/* GAIBU Marius - 315CB */
#include "railroads.h"

#define MAX_SIZE 100

// Funcția care realizează cerința 1
void check_railroads_wear_degree(FILE* fin, FILE* fout) {
    // Crearea grafului și a cozii de prioritate
    Graph *rail_graph = create_railroad_graph();
    Queue *rail_priority = create_queue();

    int num_rails = 0, years = 0;
    float threshold = 0;
    fscanf(fin, "%d\n%d\n%f\n", &num_rails, &years, &threshold);

    // Procesăm fiecare cale ferată cu grad de uzură
    while (num_rails--) {
        process_railroad_with_wear(fin, rail_graph, rail_priority);
    }

    // Calculăm și actualizăm gradele de uzură pe parcursul anilor
    while (years--) {
        compute_new_wear_degrees(rail_graph);
        update_wear_degrees(rail_graph);
    }

    // Afișează informațiile cerute despre căile ferate
    railroads_wear_status(fout, rail_graph, rail_priority, threshold);

    // Distrugerea grafului și a cozii de prioritate
    destroy_queue(rail_priority);
    destroy_railroad_graph(rail_graph);
}

// Funcția care realizează cerința 2
void keep_most_profitable_railroads(FILE* fin, FILE* fout) {
    // Crearea grafului și a cozii de prioritate
    Graph *rail_graph = create_railroad_graph();
    Queue *rail_priority = create_queue();

    char start_city[MAX_SIZE];
    int k_max_rails = 0, num_rails = 0;
    fscanf(fin, "%s\n%d\n%d\n", start_city, &k_max_rails, &num_rails);

    // Procesăm fiecare cale ferată cu cost
    while (num_rails--) {
        process_railroad_with_cost(fin, rail_graph, rail_priority);
    }

    /*
        Dacă numărul de căi ferate este mai mare ca num_cities - 1, atunci
        numărul de căi ferate pentru o profitabilitate maximă este însăși
        num_cities - 1
    */
    if (rail_graph->num_cities - 1 < k_max_rails) {
        k_max_rails = rail_graph->num_cities - 1;
    }

    // Alegem cele k_max_rails căi ferate cu o profitabilitate maximă
    choose_max_k_profitable_rails(rail_graph, start_city, k_max_rails);

    // Afișăm căile ferate alese
    show_railroads_to_keep(fout, rail_graph, rail_priority, k_max_rails);

    // Distrugerea grafului și a cozii de prioritate
    destroy_queue(rail_priority);
    destroy_railroad_graph(rail_graph);
}

int main(int argc, char *argv[]) {
    (void)argc;
    // Deschiderea fișierelor pentru I/O
    FILE* fin = fopen("tema3.in", "rt");
    FILE* fout = fopen("tema3.out", "wt");

    // Executăm cerința transmisă ca parametru
    int task_number = atoi(argv[1]);
    switch (task_number) {
        case 1: check_railroads_wear_degree(fin, fout); break;
        case 2: keep_most_profitable_railroads(fin, fout); break;
    }

    // Închiderea fișierelor pentru I/O
    fclose(fin);
    fclose(fout);
}
