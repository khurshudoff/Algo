import numpy as np

def return_way(n, MST, start=0):
    def dfs(el):
        used[el] = 1
        way.append(el)
        for v, w in enumerate(graph[el]):
            if w == 0:
                continue
            if not used[v]:
                used[v] = 1
                dfs(v)
                way.append(el)
            

    graph = np.array([0.0] *n*n).reshape(n, n)
    for w, v1, v2 in MST:
        graph[v1, v2] = w
        graph[v2, v1] = w

    used = [0] * n
    way = []

    dfs(start)
    
    w = sum([graph[el[0], el[1]] for el in list(zip(way, way[1:]))])
    
    return w, way