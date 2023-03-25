#include <stdio.h>

int countOne(int *array, int n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (*(array + i) == 1) {
            count++;
        }
    }
    return count;
}

int isStar(int *graph, int n) {
    /*
    Temos uma variável index para guardar o indice que aparece o candidato a nó central
    Uma variável count para verificar se só existe um nó central
    E uma variável boolean para dizer se o grafo é ou não estrela
    
    Primeiro, procuramos o nó central, e após isso checamos se existe exatamente um nó desse tipo.
    
    Depois, verificamos em cada nó exceto o central se ele possui nenhuma ligação a outro nó, além do central.
    */
    int index, count = 0;
    int boolean = 1;
    
    for (int i = 0; i < n; i++) {
        if (countOne((graph + i*n), n) == n -1) {
            index = i;
            count++;
        } else if (countOne(graph + i*n, n) > 1) {
            boolean = 0;
        }
    }
    
    if (count != 1)
        boolean = 0;
    
    return boolean;
}

int main() {
    int graph[5][5] = {
        {0, 1, 0, 0, 0},
        {1, 0, 1, 1, 1},
        {0, 1, 0, 0, 0},
        {0, 1, 0, 0, 0},
        {0, 1, 0, 0, 0}
    };
    printf("%d\n", isStar(&graph[0][0], 5));
    return 0;
}