#include <vector>
#include <map>
#include <tuple>

class Graph {
    public:
        unsigned long int n;
        std::map <int, std::vector <std::tuple <int, double>>> vertexes;
    
    public:
        Graph() {
            this->n = 0;
        }

        unsigned long int getSize() {
            return this->n;
        }

        void addEdge(int a, int b, double w) {
            if (this->vertexes.count(a) == 0) {
                this->vertexes[a] = std::vector <std::tuple <int, double>>();
                this->n++;
            }
                
            
            if (this->vertexes.count(b) == 0) {
                this->vertexes[b] = std::vector <std::tuple <int, double>>();
                this->n++;
            }
                
            
            this->vertexes[a].push_back({b, w});
            this->vertexes[b].push_back({a, w});
        }

        std::map <int, std::vector <std::tuple <int, double>>> getVertexes() {
            return this->vertexes;
        }
};
