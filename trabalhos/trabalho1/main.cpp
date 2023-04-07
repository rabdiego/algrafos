#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct _node {
    int key;
    struct _node *next;
} Node;

class Queue {
    public:
        Node *head;

        Queue() {
            this->head = NULL;
        }

        int isEmpty() {
            if (this->head == NULL)
                return 1;
            return 0;
        }

        void enqueue(int key) {
            Node *newNode = (Node *) malloc(sizeof(Node));
            newNode->key = key;
            newNode->next = NULL;
            Node *a = NULL, *b = this->head;
            
            while (b != NULL) {
                a = b;
                b = b->next;
            }

            if (a != NULL) {
                a->next = newNode;
            } else {
                this->head = newNode;
            }
        }

        int dequeue() {
            Node *toFree = this->head;
            if (toFree == NULL)
                return -1;
            int return_value = toFree->key;
            this->head = toFree->next;
            free(toFree);
            return return_value;
        }
};

class DynamicArray {
    public:
        int *head;
        int max;
        int n;

        DynamicArray() {
            this->head = (int *) malloc(sizeof(int));
            this->max = 1;
            this->n = 0;
        }

        void append(int k) {
            *(this->head + this->n) = k;
            this->n++;

            if (this->n == this->max) {
                this->max *= 2;
                int *temp = (int *) malloc(sizeof(int) * this->max);
                int *toFree = this->head;

                for (int i = 0; i < this->n; i++) {
                    temp[i] = toFree[i];
                }

                this->head = temp;
                free(toFree);
            }
        }

        int getN() {
            return this->n;
        }
};

class AdjacencyList {
    public:
        DynamicArray *head;
        int n;
        
        AdjacencyList(int n) {
            this->n = n;
            this->head = (DynamicArray *) malloc(sizeof(DynamicArray) * n);
            for (int i = 0; i < n; i++)
                this->head[i] = DynamicArray();
        }

        void addEdge(int a, int b) {
            (this->head[a - 1]).append(b);
            (this->head[b - 1]).append(a);
        }

        int * getNeighbours(int a) {
            return (this->head[a - 1]).head;
        }

        int isNeighbour(int a, int b) {
            int is_neighbour = 0;
            int n_neighbours = (this->head[a - 1]).n;

            for (int i = 0; i < n_neighbours; ++i) {
                if (*(this->head[a - 1].head + i) == b)
                    is_neighbour = 1;
            }

            return is_neighbour;
        }

        int getDegree(int a) {
            return (this->head[a - 1]).n;
        }

        int getN() {
            return this->n;
        }
};

double *getDistance(AdjacencyList graph, int n, int o) {
    double *distance = (double *) malloc(sizeof(double) * n);
    Queue searchQueue;

    for (int i = 0; i < n; ++i)
        distance[i] = INFINITY;
    
    distance[o - 1] = 0.0;

    searchQueue.enqueue(o);

    while (searchQueue.isEmpty() == 0) {
        int u = searchQueue.dequeue() ;
        for (int i = 0; i < n; ++i) {
            if (graph.isNeighbour(u, (i+1)) && distance[i] == INFINITY) {
                distance[i] = distance[u - 1] + 1;
                searchQueue.enqueue(i + 1);
            }
        }
    }

    return distance;
}

DynamicArray *getComponents(AdjacencyList graph) {
    int componentIndex = 0;
    DynamicArray *components = (DynamicArray *) malloc(sizeof(DynamicArray) * graph.getN());
    double *alreadyTravelled = (double *) malloc(sizeof(double) * graph.getN());

    for (int i = 0; i < graph.getN(); i++)
        alreadyTravelled[i] = INFINITY;

    for (int i = 0; i < graph.getN(); i++)
        components[i] = DynamicArray();
    
    for (int i = 1; i <= graph.getN(); i++) {
        if (alreadyTravelled[i - 1] == INFINITY) {
            double *distance = (double *) malloc(sizeof(double) * graph.getN());
            distance = getDistance(graph, graph.getN(), i);

            for (int j = 0; j < graph.getN(); j++) {
                if (distance[j] != INFINITY) {
                    alreadyTravelled[j] = distance[j];
                    components[componentIndex].append(j + 1);
                }
            }

            componentIndex++;
        }
    }

    return components;
}

int main() {
    int n = 7;
    AdjacencyList graph(n);
    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    graph.addEdge(2, 4);
    graph.addEdge(3, 4);
    graph.addEdge(4, 5);
    graph.addEdge(6, 7);
    DynamicArray *teste = (DynamicArray *) malloc(sizeof(DynamicArray) * 7);
    for (int i = 0; i < 7; i++)
        teste[i] = DynamicArray();
    teste = getComponents(graph);
    printf("%d\n", *((teste)->head + 4));
}