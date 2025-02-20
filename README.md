# DSA Railroads Management

This project implements a command-line tool in C for managing and analyzing railroad networks. It was developed as a university homework assignment and focuses on two main requirements:

- **Task 1:** Simulate railroad wear over several years using wear degrees per railroad section.
- **Task 2:** Determine the most profitable subset of railroads starting from a given city.

## Features

- **Railroad Wear Simulation:**
  Reads a railroad network with multiple sections per link, computes new wear degrees over successive years, and identifies railroads with average wear below a provided threshold.
  - Uses [railroads_wear_degree.c](railroads_wear_degree.c) for processing and updating wear values.

- **Profitability Analysis:**
  Calculates costs for each railroad (interpreting the number of sections as cost) and selects the most profitable connections using a modified minimum spanning tree approach.
  - Implemented in [railroads_profitability.c](railroads_profitability.c).

- **Graph and Queue Structures:**
  Maintains the network using an adjacency list for cities and railroads.
  - Graph management is in [railroads_management.c](railroads_management.c) and [railroads.h](railroads.h).
  - A custom queue for processing railroads is provided in [queue.c](queue.c) and [queue.h](queue.h).

- **Automated Testing Support:**
  Input files (in `input/`), reference outputs (in `ref/`), and output directories (in `output/`) are structured to support automated testing via the provided [run_tests.sh](run_tests.sh) script.

## Project Structure

- **Input Files:**
  Located in the `input/` directory with subfolders for each task (e.g. `cerinta1/` and `cerinta2/`).

- **Reference Outputs:**
  Stored in the `ref/` directory, these files are used by the testing script to verify program correctness.

- **Source Code:**
  - `tema3.c` – Main program that parses the task parameter and invokes the corresponding requirement function.
  - `railroads.h` – Declarations for the railroad graph and associated functions.
  - `railroads_management.c` – Functions for creating and destroying the graph, and city management.
  - `railroads_wear_degree.c` – Implements wear degree simulation, updating, and output for Cerința 1.
  - `railroads_profitability.c` – Implements processing of railroad costs and selection of the most profitable subset for Cerința 2.
  - `queue.c` and `queue.h` – Implementation of a queue used for processing railroads.

- **Makefile:**
  Provides targets to build the project and clean build artifacts.

- **Test Script:**
  [run_tests.sh](run_tests.sh) – Automates execution of both requirements and validates the outputs against reference files.

## Building the Project

The project uses a Makefile to compile the source files. To build the executable, run:

```sh
make build
```

The command compiles [`queue.c`](queue.c ), [`railroads_management.c`](railroads_management.c ), [`railroads_wear_degree.c`](railroads_wear_degree.c ), [`railroads_profitability.c`](railroads_profitability.c ), and [`tema3.c`](tema3.c ) into the [`tema3`](tema3 ) executable.

## Running the Program

The built executable accepts a task parameter:

- **Task 1:** Railroad wear simulation
  ```sh
  ./tema3 1
  ```

- **Task 2:** Railroad profitability selection
  ```sh
  ./tema3 2
  ```

Input should be provided in a file named [`tema3.in`](tema3.in ) and the output will be written to [`tema3.out`](tema3.out ).

## Implementation Details

- **Graph Representation:**
  Cities are stored as a dynamic array of strings, and railroads are maintained as linked lists in an adjacency list.
  See [`railroads_management.c`](railroads_management.c ) and [`railroads.h`](railroads.h ).

- **Wear Degree Updates:**
  For each railroad, new wear degrees are calculated based on the current degree, and then updated with a cap of 100.
  More details in [`railroads_wear_degree.c`](railroads_wear_degree.c ).

- **Profitability Analysis:**
  Uses a greedy approach similar to Prim's algorithm to choose a fixed number of railroads for maximum profitability starting from a given city.
  Check [`railroads_profitability.c`](railroads_profitability.c ).

- **Queue Operations:**
  A simple linked-list based queue implementation is provided for managing processing order.
  Refer to [`queue.c`](queue.c ) and [`queue.h`](queue.h ).

## Testing

The provided [`run_tests.sh`](run_tests.sh ) script copies input files, runs the executable, and diffs [`tema3.out`](tema3.out ) with reference outputs. To run tests, simply execute:

```sh
./run_tests.sh
```

This script also invokes Valgrind to check for memory leaks.