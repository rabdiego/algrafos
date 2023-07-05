edges = list()

input_string = ' '
input_iterator = 0
n_vertexes = 0  # Número de vértices do grafo (lembre que em uma AGM, todos os vértices são preservados)
result = 0.0

while True:
    input_string = input()
    if input_string == '':
        break
    elif input_iterator < 2 or input_iterator == 3:
        pass
    elif input_iterator == 2:
        n_vertexes = int(input_string[2])
        components = [i for i in range(n_vertexes)]
        number_of_vertexes_on_component = [1 for i in range(n_vertexes)]
    else:
        a, b, w = input_string.split(' ')
        a = int(a)
        b = int(b)
        w = float(w)
        
        edges.append((a, b, w))
    input_iterator += 1

edges.sort(key = lambda tup: tup[2])  # Ordenando a lista de tuplas que representam o grafo (Lista de Adjacências)

idx = 0  # Índice para acessar as arestas em ordem crescente
n_edges = 0  # Número de arestas da AGM

while n_edges < n_vertexes - 1:
    # Coletando as informações da aresta
    a = edges[idx][0]
    b = edges[idx][1]
    w = edges[idx][2]
    
    # Salvando o componente principal em uma variável
    # O componente principal é o representante do sub-grafo que está sendo criado
    a_component = components[a-1]
    b_component = components[b-1]
    
    # Checando para não haver ciclos
    if components[a - 1] != components[b -1]:
        result += w
        if number_of_vertexes_on_component[a - 1] <= number_of_vertexes_on_component[b - 1]:
            for j in range(n_vertexes):
                if components[j] == a_component:
                    components[j] = b_component
            number_of_vertexes_on_component[b - 1] += number_of_vertexes_on_component[a - 1]
            number_of_vertexes_on_component[a - 1] = 0
        else:
            for j in range(n_vertexes):
                if components[j] == b_component:
                    components[j] = a_component
            number_of_vertexes_on_component[a - 1] += number_of_vertexes_on_component[b - 1]
            number_of_vertexes_on_component[b - 1] = 0
        n_edges += 1
    
    idx += 1

print(result)

