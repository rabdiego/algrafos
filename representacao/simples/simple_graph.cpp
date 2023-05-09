#include <vector>
#include <map>

class Graph {
    private:
        unsigned long int n;
        std::map <int, std::vector <int>> vertexes;
    
    public:
        Graph() {
            this->n = 0;
        }

        unsigned long int getSize() {
            return this->n;
        }

        void addEdge(int a, int b) {
            if (this->vertexes.count(a) == 0) {
                this->vertexes[a] = std::vector <int>();
                this->n++;
            }
            
            if (this->vertexes.count(b) == 0) {
                this->vertexes[b] = std::vector <int>();
                this->n++;
            }
            
            this->vertexes[a].push_back(b);
            this->vertexes[b].push_back(a);
        }
};