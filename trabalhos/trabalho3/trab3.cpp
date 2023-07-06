#include <vector>
#include <map>
#include <tuple>
#include <algorithm>
#include <queue>
#include <math.h>
#include <iterator>
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
            auto iterator = std::find_if(this->vertexes[a].begin(), this->vertexes[a].end(), [&b](const std::tuple<int, double>& e) {return std::get<0>(e) == b;});
            
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

        void changeWeight(int a, int b, double w)
        {
            auto iterator = std::find_if(this->vertexes[a].begin(), this->vertexes[a].end(), [&b](const std::tuple<int, double>& e) {return std::get<0>(e) == b;});

            int index = (int) (iterator - this->vertexes[a].begin());

            this->vertexes[a].at(index) = {b, w};
        }
};

template <typename T>
void printVector(std::vector <T> vector)
{
    for (int i = 0; i < vector.size(); ++i)
    {
        std::cout << vector[i] << ' ';
    }
    std::cout << std::endl;
}

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
                residual_graph.addEdge(node, i, 0);
            }
        }
    }

    return residual_graph;
}

std::tuple <std::vector <int>, double> breath_first_search(Graph graph, int o, int t)
{
    int n = graph.getN();
    std::vector <std::vector <int>> distances;
    std::vector <std::vector <double>> costs;
    std::queue <int> queue;
    bool visited[n];

    for (int i = 0 ; i < n; ++i)
    {
        visited[i] = false;
    }

    distances.reserve(n);
    costs.reserve(n);
    queue.push(o);

    visited[o - 1] = true;

    while (!queue.empty())
    {
        int v = queue.front();
        queue.pop();

        for (int i = 0; i < graph.getNeighbours(v).size(); ++i)
        { 
            if (visited[std::get<0>(graph.getNeighbours(v).at(i)) - 1] == false)
            {
                std::vector <int> temp;
                std::vector <double> temp2;

                std::copy(distances[v - 1].begin(), distances[v - 1].end(), back_inserter(temp));
                std::copy(costs[v - 1].begin(), costs[v - 1].end(), back_inserter(temp2));

                temp.push_back(std::get<0>(graph.getNeighbours(v).at(i)));
                temp2.push_back(std::get<1>(graph.getNeighbours(v).at(i)));
                queue.push(std::get<0>(graph.getNeighbours(v).at(i)));
                visited[std::get<0>(graph.getNeighbours(v).at(i)) - 1] = true;
                

                std::copy(temp.begin(), temp.end(), back_inserter(distances[std::get<0>(graph.getNeighbours(v).at(i)) - 1]));
                std::copy(temp2.begin(), temp2.end(), back_inserter(costs[std::get<0>(graph.getNeighbours(v).at(i)) - 1]));
            }
        }
    }
    
    return {distances[t - 1], *min_element(costs[t - 1].begin(), costs[t - 1].end())};
}

double getMaxFlux(Graph graph, int s, int t)
{
    Graph residual_graph = graph;
    std::tuple <std::vector <int>, int> augmenting_path;
    std::vector <int> exists;
    
    while (1)
    {
        residual_graph = create_residual_graph(residual_graph);
        augmenting_path = breath_first_search(residual_graph, s, t);
        exists = std::get<0>(augmenting_path);

        if (exists.size() <= 0)
        {
            break;
        }
    }
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

    std::tuple <std::vector <int>, double> asd = breath_first_search(graph, 1, 3);

    std::cout << std::get<1>(asd) << std::endl;
}