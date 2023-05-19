#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>
#include <stdlib.h>

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

        std::vector <int> getNeighbours(int a) {
            return this->head[a - 1];
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

std::vector <std::vector <int>> getComponents(AdjacencyList graph) {
    int n = graph.getN();
    std::vector <std::vector <int>> components;
    int *alreadyTravelled = (int *) malloc(sizeof(int) * n);
    std::queue <int> searchQueue;

    for (int i = 0; i < n; ++i)
        alreadyTravelled[i] = 0;
    
    for (int o = 1; o <= n; ++o) {
        if (alreadyTravelled[o - 1] == 0) {
            std::vector <int> temp;
            temp.push_back(o);
            alreadyTravelled[o - 1] = 1;
            searchQueue.push(o);

            while (!searchQueue.empty()) {
                int v = searchQueue.front();
                searchQueue.pop();
                for (long unsigned int i = 0; i < graph.getNeighbours(v).size(); i++) {
                    if (alreadyTravelled[graph.getNeighbours(v)[i] - 1] == 0) {
                        temp.push_back(graph.getNeighbours(v)[i]);
                        searchQueue.push(graph.getNeighbours(v)[i]);
                        alreadyTravelled[graph.getNeighbours(v)[i] - 1] = 1;
                    }
                    
                }
            }

            components.push_back(std::move(temp));
        }
    }

    for (long unsigned int i = 0; i < components.size(); ++i)
        std::sort(components[i].begin(), components[i].end());

    return components;
}

int main() {
    AdjacencyList graph;
    std::string input_string;
    int input_iterator = 0;
    int n;
    std::vector <std::vector <int>> components;

    while (std::getline(std::cin, input_string)) {
        if (!input_string.compare("")) {
            break;
        } else if (input_iterator < 2 || input_iterator == 3) {
            input_iterator++;
        } else if (input_iterator == 2) {
            input_string.erase(0, 2);
            n = stoi(input_string);
            graph.setN(n);
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
    
    components = getComponents(graph);

    for (long unsigned int i = 0; i < components.size(); i++) {
        if (components[i].size() > 0) {
            std::cout << components[i][0];
            for (long unsigned int j = 1; j < components[i].size(); j++) {
                std::cout << " " << components[i][j];
            } std::cout << std::endl;
        }
    }
}