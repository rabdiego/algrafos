#include <vector>
#include <map>
#include <tuple>
#include <algorithm>
#include <iostream>

class Graph
{
    public:
        int n;
        std::map <int, std::vector <std::tuple <int, double>>> vertexes;
    
    public:
        void setN(int n)
        {
            this->n = n;

            for (int i = 0; i < n; ++i)
            {
                this->vertexes[i] = std::vector <std::tuple <int, double>>();
            }
        }

        int getSize()
        {
            return this->n;
        }

        void addEdge(int a, int b, double w)
        {   
            this->vertexes[a].push_back({b, w});
        }

        int getN()
        {
            return this->n;
        }

        std::map <int, std::vector <std::tuple <int, double>>> getVertexes()
        {
            return this->vertexes;

        }

        std::vector <std:: tuple <int, double>> getNeighbours(int a)
        {
            return this->vertexes[a];
        }

        std::tuple <int, double> isNeighbour(int a, int b)
        {
            auto iterator = std::find_if(this->vertexes[a].begin(), this->vertexes[a].end(), [](const std::tuple<int, double>& e) {return std::get<0>(e) == 0;});
            
            int index = (int) (iterator - this->vertexes[a].begin());
            
            if (iterator != this->vertexes[a].end())
            {
                return this->vertexes[a].at(index);
            }
            else
            {
                std::tuple <int, double> error_tuple = {-1, -1.0};
                return error_tuple;
            }
        }

        int getEdgesNumber()
        {
            int size = 0;

            for (int i = 0; i < this->n; ++i)
            {
                size += this->vertexes[i].size();
            }

            return size;
        }

        void printEdges()
        {
            for (int i = 1; i <= this->n; ++i)
            {
                std::cout << "Vertex " << i << std::endl << std::endl;

                for (auto &neighbour : this->getNeighbours(i))
                {
                    int node = std::get<0>(neighbour);
                    double weight = std::get<1>(neighbour);

                    std::cout << i << ' ' << node << ' ' << weight << std::endl;
                }
                
                std::cout << std::endl;
            }
        }
};

Graph create_residual_graph(Graph g)
{
    Graph residual_graph = g;
    unsigned long int n = g.getN();

    for (int i = 1; i <= n; ++i)
    {
        for (auto &neighbour : g.getNeighbours(i))
        {
            int node = std::get<0>(neighbour);
            double weight = std::get<1>(neighbour);

            std::tuple <int, double> checker = g.isNeighbour(node, i);
            
            if (std::get<0>(checker) == -1)
            {
                residual_graph.addEdge(node, i, -weight);
            }
        }
    }

    return residual_graph;
}

int main()
{
    std::string delimiter = " ";
    std::string input_string;
    int input_iterator = 0;
    int a, b, i=0, n_a=0, n;
    double w, r=0.0;
    size_t pos = 0;
    std::string token;
    std::string teste;
    Graph graph, residual_graph;

    while (std::getline(std::cin, input_string)) {
        if (!input_string.compare(""))
        {
            break;
        }
        else if (input_iterator < 2 || input_iterator == 3)
        {
            input_iterator++;
        }
        else if (input_iterator == 2)
        {
            input_string.erase(0, 2);
            n = stoi(input_string);
            graph.setN(n);
            input_iterator++;
        }
        else
        {
            i = 0;
            while ((pos = input_string.find(delimiter)) != std::string::npos)
            {
                token = input_string.substr(0, pos);

                if (i == 0)
                {
                    a = stoi(token);
                }
                else
                {
                    b = stoi(token);
                }

                input_string.erase(0, pos + delimiter.length());
                i++;
            }
            teste = input_string;
            w = std::stod(teste);
            graph.addEdge(a, b, w);
            input_iterator++;
        }
    }


    /*
    Início do algorítmo
    */

    residual_graph = create_residual_graph(graph);
}