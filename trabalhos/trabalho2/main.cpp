#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <algorithm>
#include <iomanip>

int main() {
    std::vector <std::tuple <double, int, int>> edges;
    std::vector <int> components;
    std::vector <int> number_of_vertexes_on_component;
    std::string delimiter = " ";
    std::string input_string;
    int input_iterator = 0;
    int a, b, i=0, n_a=0, n;
    double w, r=0.0;
    size_t pos = 0;
    std::string token;
    std::string teste;
    
    while (std::getline(std::cin, input_string)) {
        if (!input_string.compare("")) {
            break;
        } else if (input_iterator < 2 || input_iterator == 3) {
            input_iterator++;
        } else if (input_iterator == 2) {
            input_string.erase(0, 2);
            n = stoi(input_string);
            components.reserve(n);
            number_of_vertexes_on_component.reserve(n);
            input_iterator++;
        } else {
            i = 0;
            while ((pos = input_string.find(delimiter)) != std::string::npos) {
                token = input_string.substr(0, pos);
                if (i == 0) {
                    a = stoi(token);
                } else {
                    b = stoi(token);
                }

                input_string.erase(0, pos + delimiter.length());
                i++;
            }
            teste = input_string;
            w = std::stod(teste);
            edges.push_back({w, a, b});
            input_iterator++;
        }
    }

    
    for (i = 0; i < n; i++) {
        components[i] = i;
        number_of_vertexes_on_component[i] = 1;
    }

    std::sort(edges.begin(), edges.end());

    i = 0;
    
    while (n_a < n - 1) {
        a = std::get<1>(edges[i]);
        b = std::get<2>(edges[i]);
        w = std::get<0>(edges[i]);
        int ac = components[a-1];
        int bc = components[b-1];

        if (!(components[a - 1] == components[b - 1])) {
            r += w;
            if (number_of_vertexes_on_component[a - 1] <= number_of_vertexes_on_component[b - 1]) {
                for (int j = 0; j < n; ++j) {
                    if (components[j] == ac) {
                        components[j] = bc;
                    }
                }
                number_of_vertexes_on_component[b - 1] += number_of_vertexes_on_component[a - 1];
                number_of_vertexes_on_component[a - 1] = 0;
            } else {
                for (int j = 0; j < n; ++j) {
                    if (components[j] == bc) {
                        components[j] = ac;
                    }
                }
                number_of_vertexes_on_component[a - 1] += number_of_vertexes_on_component[b - 1];
                number_of_vertexes_on_component[b - 1] = 0;
            }
            n_a++;
        }
        i++;
    }

    std::cout << std::fixed;
    std::cout << std::setprecision(3);
    std::cout << r << std::endl;
}