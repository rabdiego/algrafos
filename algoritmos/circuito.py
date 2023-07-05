class Graph:
    def __init__(self, n):
        self.n = n
        self.edges = [[] for i in range(n)]
    
    def addEdge(self, a, b):
        self.edges[a-1].append(b)
    
    def getNeighbours(self, a):
        return self.edges[a-1]


input_string = ' '
input_iterator = 0
while True:
    input_string = input()
    if input_string == '':
        break
    elif input_iterator < 2 or input_iterator == 3:
        pass
    elif input_iterator == 2:
        n_vertexes = int(input_string[2])
        graph = Graph(n_vertexes)
    else:
        a, b = input_string.split(' ')
        a = int(a)
        b = int(b)
        graph.addEdge(a ,b)
    
    input_iterator += 1

def have_circuit(graph):
    def found_circuit(graph, state, u):
        state[u] = 0
        
        for v in graph.getNeighbours(u):
            if state[v] == 0:
                return state, True
            if state[v] == -1:
                state, found = found_circuit(graph, state, v)
                if found:
                    return state, True
        
        state[u] = 1
        return state, False
    
    state = [-1 for i in range(graph.n)]
    
    for o in range(graph.n):
        if state[o] == -1:
            state, found = found_circuit(graph, state, o)
            if found:
                return True
    
    return False

print(have_circuit(graph))