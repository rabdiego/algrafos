import queue

class Node:
    def __init__(self):
        self.key = 0
        self.next = None


class AdjacencyList:
    def __init__(self):
        self.head = []
        self.n = 0
    
    def set_n(self, n):
        self.n = n
        self.head = [[] for i in range(n)]
    
    def add_edge(self, a, b):
        self.head[a - 1].append(b)
        self.head[b - 1].append(a)
    
    def get_neighbours(self, a):
        return self.head[a - 1]
    
    def is_neighbour(self, a, b):
        is_neigh = False
        
        if b in self.head[a-1]:
            is_neigh = True
        
        return is_neigh
    
    def get_degree(self, a):
        return len(self.head[a - 1])
    
    def get_n(self):
        return self.n

def get_components(graph):
    n = graph.get_n()
    components = list()
    already_travelled = [0 for i in range(n)]
    search_queue = queue.Queue()
    
    for o in range(1, n+1):
        if already_travelled[o - 1] == 0:
            temp = list()
            temp.append(o)
            already_travelled[o - 1] = 1
            search_queue.put(o)
            
            while (search_queue.empty() == False):
                v = search_queue.get()
                for i in range(n):
                    if graph.is_neighbour(v, i+1) and already_travelled[i] == 0:
                        temp.append(i + 1)
                        search_queue.put(i + 1)
                        already_travelled[i] = 1
            
            components.append(temp)
    
    for i in range(len(components)):
        components[i].sort()
    
    return components

graph = AdjacencyList()
input_string = "test"
input_iterator = 0
n = None

while True:
    try:
        input_string = input()
    except EOFError:
        break
    if input_string == '':
        break
    elif input_iterator < 2 or input_iterator == 3:
        input_iterator += 1
    elif input_iterator == 2:
        n = int(input_string[2:])
        graph.set_n(n)
        input_iterator += 1
    else:
        a, b = input_string.split(' ')
        a = int(a)
        b = int(b)
        graph.add_edge(a, b)
        input_iterator += 1

components = get_components(graph)

for i in range(len(components)):
    if len(components[i]) > 0:
        print(f'{components[i][0]}', end='')
        for j in range(1, len(components[i])):
            print(f' {components[i][j]}', end='')
        print()

        