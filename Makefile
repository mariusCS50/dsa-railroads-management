build: queue.c railroads_management.c railroads_wear_degree.c railroads_profitability.c tema3.c
	gcc queue.c railroads_management.c railroads_wear_degree.c railroads_profitability.c tema3.c -Wall -Werror -Wextra -std=c99 -o tema3

clean:
	rm -f tema3