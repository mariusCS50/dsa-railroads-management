/* GAIBU Marius - 315CB */
#include "railroads.h"

#define MAX_SIZE 100

// Function that performs requirement 1
void check_railroads_wear_degree(FILE* fin, FILE* fout) {
    // Create the graph and the priority queue
    Graph *rail_graph = create_railroad_graph();
    Queue *rail_priority = create_queue();

    int num_rails = 0, years = 0;
    float threshold = 0;
    fscanf(fin, "%d\n%d\n%f\n", &num_rails, &years, &threshold);

    // Process each railroad with a wear degree
    while (num_rails--) {
        process_railroad_with_wear(fin, rail_graph, rail_priority);
    }

    // Compute and update wear degrees over the years
    while (years--) {
        compute_new_wear_degrees(rail_graph);
        update_wear_degrees(rail_graph);
    }

    // Display the required information about railroads
    railroads_wear_status(fout, rail_graph, rail_priority, threshold);

    // Destroy the graph and the priority queue
    destroy_queue(rail_priority);
    destroy_railroad_graph(rail_graph);
}

// Function that performs requirement 2
void keep_most_profitable_railroads(FILE* fin, FILE* fout) {
    // Create the graph and the priority queue
    Graph *rail_graph = create_railroad_graph();
    Queue *rail_priority = create_queue();

    char start_city[MAX_SIZE];
    int k_max_rails = 0, num_rails = 0;
    fscanf(fin, "%s\n%d\n%d\n", start_city, &k_max_rails, &num_rails);

    // Process each railroad with cost
    while (num_rails--) {
        process_railroad_with_cost(fin, rail_graph, rail_priority);
    }

    /*
        If the number of railroads is greater than num_cities - 1, then
        the maximum number of railroads for maximum profitability is num_cities - 1
    */
    if (rail_graph->num_cities - 1 < k_max_rails) {
        k_max_rails = rail_graph->num_cities - 1;
    }

    // Select the k_max_rails railroads with maximum profitability
    choose_max_k_profitable_rails(rail_graph, start_city, k_max_rails);

    // Display the selected railroads
    show_railroads_to_keep(fout, rail_graph, rail_priority, k_max_rails);

    // Destroy the graph and the priority queue
    destroy_queue(rail_priority);
    destroy_railroad_graph(rail_graph);
}

int main(int argc, char *argv[]) {
    (void)argc;
    // Open the I/O files
    FILE* fin = fopen("tema3.in", "rt");
    FILE* fout = fopen("tema3.out", "wt");

    // Execute the requirement passed as a parameter
    int task_number = atoi(argv[1]);
    switch (task_number) {
        case 1: check_railroads_wear_degree(fin, fout); break;
        case 2: keep_most_profitable_railroads(fin, fout); break;
    }

    // Close the I/O files
    fclose(fin);
    fclose(fout);
}
