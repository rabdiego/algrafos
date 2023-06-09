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

        void addWeight(int a, int b, double w)
        {
            int i = 0;
            for (const auto &neighbour : this->vertexes[a])
            {
                if (std::get<0>(neighbour) == b)
                {
                    this->vertexes[a].at(i) = {b, std::get<1>(this->vertexes[a].at(i)) + w};
                    break;
                }
                i++;
            }
        }

        double getWeight(int a, int b)
        {
            int i = 0;
            for (const auto &neighbour : this->vertexes[a])
            {
                if (std::get<0>(neighbour) == b)
                {
                    return std::get<1>(neighbour);
                }
                i++;
            }

            return -1;
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
    int n = g.getN();
    Graph residual_graph = g;

    for (int i = 1; i <= n; ++i)
    {
        const auto& neighbours = g.getNeighbours(i);

        for (const auto& neighbour : neighbours)
        {
            int node = std::get<0>(neighbour);

            if (std::get<0>(g.isNeighbour(node, i)) == 0)
            {
                residual_graph.addEdge(node, i, 0);
            }
        }
    }

    return residual_graph;
}

std::tuple<std::vector<int>, double> breath_first_search(Graph graph, int o, int t)
{
    int n = graph.getN();
    std::vector<std::vector<int>> distances(n);
    std::vector<std::vector<double>> costs(n);
    std::queue<int> queue;
    std::vector<int> error_vector;
    bool visited[n];

    for (int i = 0; i < n; ++i)
    {
        visited[i] = false;
    }

    queue.push(o);
    visited[o - 1] = true;

    const auto& neighbours = graph.getNeighbours(o);

    while (!queue.empty())
    {
        int v = queue.front();
        queue.pop();

        const auto& v_neighbours = graph.getNeighbours(v);

        for (const auto& neighbour : v_neighbours)
        {
            int node = std::get<0>(neighbour) - 1;
            double weight = std::get<1>(neighbour);

            if (!visited[node] && weight > 0)
            {
                distances[node] = distances[v - 1];
                costs[node] = costs[v - 1];
                distances[node].push_back(node + 1);
                costs[node].push_back(weight);
                queue.push(node + 1);
                visited[node] = true;
            }
        }
    }

    if (visited[t - 1])
    {
        return {distances[t - 1], *min_element(costs[t - 1].begin(), costs[t - 1].end())};
    }
    else
    {
        return {error_vector, 0.0};
    }
}

double getMaxFlux(Graph graph, int s, int t)
{
    Graph residual_graph = create_residual_graph(graph);
    std::vector<int> augmenting_path = std::get<0>(breath_first_search(residual_graph, s, t));
    augmenting_path.insert(augmenting_path.begin(), 1);

    int next;
    double result = 0.0;
    double bottleneck;

    while (true)
    {
        bottleneck = std::get<1>(breath_first_search(residual_graph, s, t));

        if (bottleneck == 0)
        {
            break;
        }
        else
        {
            next = s;
            for (const auto& node : augmenting_path)
            {
                residual_graph.addWeight(next, node, -bottleneck);
                residual_graph.addWeight(node, next, bottleneck);
                next = node;
            }
            result += bottleneck;
        }

        augmenting_path = std::get<0>(breath_first_search(residual_graph, s, t));
        augmenting_path.insert(augmenting_path.begin(), 1);
    }

    return result;
}

int main()
{
    std::string delimiter = " ";
    std::string input_string;
    int input_iterator = 0;
    int a, b, i=0, n;
    double w;
    size_t pos = 0;
    std::string token;
    std::string teste;
    Graph graph, residual_graph;

    while (std::getline(std::cin, input_string)) 
    {
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

    for (int i = 2; i <= n; ++i)
    {
        std::cout << i << " " << getMaxFlux(graph, 1, i) << std::endl;
    }
}