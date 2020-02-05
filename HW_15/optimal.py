import itertools
import numpy as np

def find_optimal(n, edges, start = 0):
    graph = np.array([9999.9]*n*n).reshape(n, n)
    for w, e1, e2 in edges:
        graph[e1, e2] = graph[e2, e1] = w

    vertex_to_visit = [el for el in range(n) if el != start]
    
    optimal = (99999999.9, [])
    
    for perm in itertools.permutations(vertex_to_visit):
        perm = [start] + list(perm) + [start]
        w = sum([graph[el[0], el[1]] for el in list(zip(perm, perm[1:]))])
        if w < optimal[0]:
            optimal = (w, perm)
            
    return optimal