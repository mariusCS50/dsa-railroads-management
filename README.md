# TEMA 3 - SDA

Tema a fost destul de complexă, dar am reușit să o rezolv prin aplicarea principiilor de simplitate a codului, l-am separat pe unde era posibil și se cuvinea mai bine în diferite funcții pentru a fi mai ușor de înțeles. De asemenea am incllus comentarii înainte tuturor funcțiilor și înăuntrul celor mai complicate pentru a facilita citirea codului.

Codul a fost scris în totalitate de mine, fără a folosi bucăți de cod din alte surse. Am verificat și corectat stilul de cod folosind clang-tidy și cpplint.

README-ul nu are extensia .md fiincă checkerul nu alocă punctajul pe README în acest caz.

## queue.h

În acest header file am definit structurile și funcțiile pentru coada de prioritate a căilor ferate conform datelor de intrare, pentru a putea la final să afișez căile ferate în ordinea lor inițială, precum se cere și în condiție.

## queue.c

Aici sunt implementate funcțiile clasice pentru o coadă: crearea, inserarea, extragerea, distrugerea.

## railroads.h

Aici sunt declarate structurile pentru o cale ferată, și graful cu lista de adiacență. De asemenea sunt include funcțiile necesare pentru prelucrarea grafului de căi ferate și construirea căilor ferate, funcțiile necesare pentru executarea cerințelor 1 și 2, dar și funcții de verificarea și inserarea orașelor.

Am inclus comentarii înaintea fiecărui grup de funcții pentru a fi ușor de diferențiat.

## railroads_management.c

Aici sunt declarate funcțiile de prelucrare a grafului:
 - create_railroad_graph(),
 - build_railroad_with_wear(int dest, int cost),
 - build_railroad_with_cost(int dest, int cost),
 - destroy_railroad_graph(Graph *g),

dar și cele ce țin de verificarea și inserarea orașelor:
 - listed_city(Graph *g, char* city),
 - list_new_city(Graph *g, char* city),
 - city_index(Graph *g, char* city).

 Toate funcțiile includ comentarii pentru a explica desfășurarea codului.

## railroads_wear_degree.c

Acest fișier conține funcțiile necesare pentru ralizarea cerinței 1.

Din nou, codul este bogat în comentarii și consider că nu trebuie să explic în amănunte ce face fiecare funcție.

O să explic desfășurarea algoritmului pe pași:
1) procesăm calea ferată curentă cu grade de uzură, o construim, verificând totodată și prezența orașelor din graf, inserându-le dacă e nevoie.
De asemenea includem indicii căii ferate în coada de prioritate pentru ca la final șă le putem afișa în ordnea de intrare.
2) După citirea tuturor datelor începe algoritmul propriu-zis, care constă în două părți principale:
    1) calcularea gradelor noi de uzură după valorile gradelor vechi în new_wear.
    2) actualizarea gradelor curente de uzură din wear cu cele noi din new_wear.

Am optat pentru acest algoritm, fiindcă actualizarea directă a gradelor de uzură duce la cazuri nefavorabile, trebuie verificate dacă ele au fost deja schimbate, dacă da, trebuie prelucrată altfel secțiunea curentă, iar la cazurile cu gradul de uzură 0 este o bătaie mare de cap.

Este mult mai simplu să calculăm gradele noi de uzură într-o altă listă, și apoi să le actulizăm, ceea face algoritmul mult mai simplu și ușor de urmărit.

3) Afișăm căile ferate după ordinea din coada de prioritate cu gradele de uzură finale, iar la final afișăm indicii căilor ferate cu media gradelor de uzură mai mică ca limita de uzură.

## railroads_profitability.c

Acest fișier conține funcțiile necesare pentru ralizarea cerinței 2.

Din nou, codul este bogat în comentarii și nu voi explica amănunțit fiecare funcție, doar algoritmul.

Algoritmul este o combinație a algoritmului lui Prim și Dijkstra, modificarea constă în faptul că nu căutăm calea ferată de cost minim, ci calea ferată către orașul cel mai apropiat de orașul origine.

Procesarea datelor și afișarea sunt aproximativ lafel, doar că modificate pentru cerința 2, adică citim căi ferate cu cost în loc de grade de uzură, iar la final afișăm doar căile ferate alese.

Pașii algoritmului efectiv sunt:
1) Inițializăm doi vectori, unul pentru salvarea orașelor vizitate și celălalt pentru distanța minimă.
2) Includem orașul de start ca vizitat cu distanța 0.
3) Iterăm prin toate orașele vizitate și căutăm calea ferată către cel mai apropiat oraș de origine care nu este vizitat, deoarece trebuie să maximizăm numărul de orașe la care nu se modifică drumul minim, dar și cele care sunt mai apropiate de origine.
4) După găsirea căii ferate, setăm calea ferată ca aleasă și includem orașul destinație ca vizitat cu distanța minimă de la origine până la acesta.
5) Repetăm pașii 1 - 4 pentru a alege cele k maxime căi ferate cu profitabilitate maximă.

Acum, de ce funcționează algoritmul?

La început avea două funcții care realizau separat partea cu Dijkstra și cea cu Prim modificat, însă după mi-am dat seama că nu am nevoie de drumurile minime către toate orașele, doar către cele alese și vizitate, așa că am inclus partea Dijkstra într-o singură funcție.

Începând de la orașul origine, includem un oraș nou unul câte unul, actualizându-i distanța minimă.

De exemplu pentru primul test, Algoritmul începe de la Malmo cu distanța 0 și alege orașele în felul următor:
1) Copenhaga cu drumul minim 1, calea ferată Malmo - Copenhaga
2) Oslo cu drumul minim 2, calea ferată Copenhaga - Oslo
3) Stockhold cu drumul minim 3, calea ferată Malmo - Stockhold
4) Bergen cu drumul minim 6, calea ferată Copenhaga - Bergen

Dat fiind că căutăm nu calea ferată de cost minim, ci calea cu costul cem mai mic de la origine, în cazul testelor cu număr maxim egal de orașe, se vor alege cele mai apropiate.

## tema3.c

Acesta este programul main, care citește numărul cerinței din argvă1î și execută respectiv cerința 1 sau 2.

Aici am pus comentarii la aproape fiecare pas pentru fiecare cerință, de aceea nu mai explic ce face fiecare funcție, mai ales că ele sunt bazate pe funcțiile explicate anterior.