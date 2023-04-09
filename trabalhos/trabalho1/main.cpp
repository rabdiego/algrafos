#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>
#include <stdlib.h>

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

std::vector <int> *getComponents(AdjacencyList graph) {
    int n = graph.getN(), componentIndex = 0;
    std::vector <int> *components = (std::vector <int> *) malloc(sizeof(std::vector <int>) * n);
    int *alreadyTravelled = (int *) malloc(sizeof(int) * n);
    std::queue <int> searchQueue;

    for (int i = 0; i < n; ++i)
        alreadyTravelled[i] = 0;
    
    for (int o = 1; o <= n; ++o) {
        if (alreadyTravelled[o - 1] == 0) {
            components[componentIndex].push_back(o);
            alreadyTravelled[o - 1] = 1;
            searchQueue.push(o);

            while (!searchQueue.empty()) {
                int v = searchQueue.front();
                searchQueue.pop();
                for (int i = 0; i < n; ++i) {
                    if (graph.isNeighbour(v, (i + 1)) && alreadyTravelled[i] == 0) {
                        components[componentIndex].push_back(i + 1);
                        searchQueue.push(i + 1);
                        alreadyTravelled[i] = 1;
                    }
                }
            }

            componentIndex++;
        }
    }

    for (int i = 0; i < componentIndex; ++i)
        std::sort(components[i].begin(), components[i].end());

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