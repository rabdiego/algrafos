#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <stdlib.h>
#include <math.h>

typedef struct _node {
    int key;
    struct _node *next;
} Node;

class AdjacencyList {
    public:
        std::vector <int> *head;
        int n;
        
        void setN(int n) {
            this->n = n;
            this->head = (std::vector <int> *) malloc(sizeof(std::vector <int>) * n);
            for (int i = 0; i < n; i++)
                this->head[i] = std::vector <int>();
        }

        void addEdge(int a, int b) {
            (this->head[a - 1]).push_back(b);
            (this->head[b - 1]).push_back(a);
        }

        int * getNeighbours(int a) {
            return &((this->head[a - 1])[0]);
        }

        int isNeighbour(int a, int b) {
            int is_neighbour = 0;
            long unsigned int n_neighbours = (this->head[a - 1]).size();

            for (long unsigned int i = 0; i < n_neighbours; ++i) {
                if (*(&(this->head[a - 1][0]) + i) == b)
                    is_neighbour = 1;
            }

            return is_neighbour;
        }

        long unsigned int getDegree(int a) {
            return (this->head[a - 1]).size();
        }

        int getN() {
            return this->n;
        }
};

double *getDistance(AdjacencyList graph, int n, int o) {
    double *distance = (double *) malloc(sizeof(double) * n);
    std::queue <int> searchQueue;

    for (int i = 0; i < n; ++i)
        distance[i] = INFINITY;
    
    distance[o - 1] = 0.0;

    searchQueue.push(o);

    while (searchQueue.empty() == 0) {
        int u = searchQueue.front();
        searchQueue.pop();
        for (int i = 0; i < n; ++i) {
            if (graph.isNeighbour(u, (i+1)) && distance[i] == INFINITY) {
                distance[i] = distance[u - 1] + 1;
                searchQueue.push(i + 1);
            }
        }
    }

    return distance;
}

std::vector <int> *getComponents(AdjacencyList graph) {
    int componentIndex = 0;
    std::vector <int> *components = (std::vector <int> *) malloc(sizeof(std::vector <int>) * graph.getN());
    double *alreadyTravelled = (double *) malloc(sizeof(double) * graph.getN());

    for (int i = 0; i < graph.getN(); i++) {
        alreadyTravelled[i] = INFINITY;
        components[i] = std::vector <int>();
    }
    
    for (int i = 1; i <= graph.getN(); i++) {
        if (alreadyTravelled[i - 1] == INFINITY) {
            double *distance = (double *) malloc(sizeof(double) * graph.getN());
            distance = getDistance(graph, graph.getN(), i);

            for (int j = 0; j < graph.getN(); j++) {
                if (distance[j] != INFINITY) {
                    alreadyTravelled[j] = distance[j];
                    components[componentIndex].push_back(j + 1);
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
    std::vector <int> *components;

    while (std::getline(std::cin, input_string)) {
        if (!input_string.compare("")) {
            break;
        } else if (input_iterator < 2 || input_iterator == 3) {
            input_iterator++;
        } else if (input_iterator == 2) {
            input_string.erase(0, 2);
            n = stoi(input_string);
            graph.setN(n);
            components = (std::vector <int> *) malloc(sizeof(std::vector <int>) * n);
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
        components[i] = std::vector <int>();
    
    components = getComponents(graph);

    for (int i = 0; i < n; i++) {
        if (components[i].size() > 0) {
            std::cout << components[i][0];
            for (long unsigned int j = 1; j < components[i].size(); j++) {
                std::cout << " " << components[i][j];
            } std::cout << std::endl;
        }
    }
}