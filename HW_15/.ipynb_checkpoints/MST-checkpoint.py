class DSU:
    parent = None
    rank = None
    def __init__(self, n):
        self.parent = list(range(n))
        self.rank = [0] * n
        
    def find_set(self, v):
        if v == self.parent[v]:
            return v
        self.parent[v] = self.find_set(self.parent[v])
        return self.parent[v]
    
    def union_set(self, v1, v2):
        v1 = self.find_set(v1);
        v2 = self.find_set(v2);

        if v1 != v2:
            if self.rank[v1] < self.rank[v2]:
                v1, v2 = v2, v1
            self.parent[v2] = v1;
            if self.rank[v1] == self.rank[v2]:
                self.rank[v1] += 1;
                

def find_MST(n, m, edges):
    edges = sorted(edges, key=lambda x:x[0])

    d = DSU(n)
    MST_edges = []
    for i in range(m):
        w, e1, e2 = edges[i]
        if d.find_set(e1) != d.find_set(e2):
            MST_edges.append((w, e1, e2))
            d.union_set(e1, e2)
    
    return MST_edges