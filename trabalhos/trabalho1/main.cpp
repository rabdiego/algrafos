#include <iostream>
#include <string>
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

        void printArray() {
            if (this->max > 0) {
                printf("%d", *(this->head));
                for (int i = 1; i < this->n; ++i) {
                    printf(" %d", *(this->head + i));
                } printf("\n");
            }   
        }
};

class AdjacencyList {
    public:
        DynamicArray *head;
        int n;
        
        void setN(int n) {
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
    AdjacencyList graph;
    std::string input_string;
    int input_iterator = 0;
    int n;
    DynamicArray *components;

    while (std::getline(std::cin, input_string)) {
        if (!input_string.compare("")) {
            break;
        } else if (input_iterator < 2 || input_iterator == 3) {
            input_iterator++;
        } else if (input_iterator == 2) {
            input_string.erase(0, 2);
            n = stoi(input_string);
            graph.setN(n);
            components = (DynamicArray *) malloc(sizeof(DynamicArray) * n);
            input_iterator++;
        } else {
            std::string delimiter = " ";
            int a, b;
            a = stoi(input_string.substr(0, input_string.find(delimiter)));
            b = stoi(input_string.substr(input_string.find(delimiter)));
            graph.addEdge(a, b);
            input_iterator++;
        }
    }

    for (int i = 0; i < n; i++)
        components[i] = DynamicArray();
    
    components = getComponents(graph);

    for (int i = 0; i < n; i++) {
        if (components[i].max > 1)
            components[i].printArray();
    }
}