#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

class DSU {
public:
    DSU(int n);
    ~DSU();
    void union_set(int v1, int v2);
    int find_set(int v);
private:
    void make_set(int v);
    int *parent;
    int *rank;
};
DSU::DSU(int n) {
    parent = new int[n];
    rank = new int[n];

    for (int i = 0; i < n; i++)
        make_set(i);
}
DSU::~DSU() {
    delete[] parent;
    delete[] rank;
}
void DSU::make_set(int v) {
    parent[v] = v;
    rank[v] = 0;
}
int DSU::find_set(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}
void DSU::union_set(int v1, int v2) {
    v1 = find_set(v1);
    v2 = find_set(v2);

    if (v1 != v2) {
        if (rank[v1] < rank[v2]) {
            int tmp = v1;
            v1 = v2;
            v2 = tmp;
        }
        parent[v2] = v1;
        if (rank[v1] == rank[v2])
            rank[v1] += 1;
    }
}

int main() {

    std::vector <std::pair<int, std::pair<int, int> > > edges;
    int n = 0;
    int m = 0;

    std::cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int e1 = 0;
        int e2 = 0;
        int w = 0;
        std::cin >> e1 >> e2 >> w;
        edges.push_back(std::make_pair(w, std::make_pair(e1 - 1, e2 - 1)));
    }
    std::sort(edges.begin(), edges.end());

    int cost = 0;

    DSU dsu(n);

    for (int i = 0; i < m; i++) {
        int e1 = edges[i].second.first;
        int e2 = edges[i].second.second;
        int w = edges[i].first;
        if (dsu.find_set(e1) != dsu.find_set(e2)) {
            cost += w;
            dsu.union_set(e1, e2);
        }
    }

    std::cout << cost << std::endl;

    return 0;
}