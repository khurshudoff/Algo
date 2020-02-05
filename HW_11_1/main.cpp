#include <iostream>
#include <vector>
#include <queue>
#include <utility>

class Graph {
public:
    explicit Graph(int n);
    void add_edge(int from, int to);
    int min_cycle();
private:
    int pseudo_bfs(int from);
    int vertex_amm = 0;
    std::vector<std::vector<int> > graph;
};


Graph::Graph(int n) {
    vertex_amm = n;
    for (int i = 0; i < n; i++) {
        std::vector<int> v;
        graph.push_back(v);
    }
}

void Graph::add_edge(int from, int to) {
    graph[from].push_back(to);
    graph[to].push_back(from);
}

int Graph::pseudo_bfs(int from) {
    std::queue<std::pair<int, std::pair<int, int> > > q;  // <vertex, where_from>
    q.push(std::make_pair(from, std::make_pair(-1, 0)));

    int depth_arr[vertex_amm];
    for (int i = 0; i < vertex_amm; i++) depth_arr[i] = -1;
    depth_arr[from] = 0;

    while (!q.empty()) {
        auto[cur_vertex, tmp1] = q.front();
        auto[where_from, cur_depth] = tmp1;
        q.pop();

        for (auto el : graph[cur_vertex]) {
            if (el == where_from) {
                continue;
            }
            if (el == from) {
                return cur_depth - depth_arr[from] + 1;
            }
            depth_arr[el] = cur_depth + 1;
            q.push(std::make_pair(el, std::make_pair(cur_vertex, cur_depth+1)));
        }
    }
    return -1;
}

int Graph::min_cycle() {
    int min_cycle_len = -1;
    for (int i = 0; i < vertex_amm; i++) {
        int cur_cycle_len = pseudo_bfs(i);
        if (min_cycle_len == -1) {
            min_cycle_len = cur_cycle_len;
        } else {
            if (cur_cycle_len != -1 && cur_cycle_len < min_cycle_len) {
                min_cycle_len = cur_cycle_len;
            }
        }
    }
    return min_cycle_len;
}

int main() {
    int n = 0;
    int m = 0;
    std::cin >> n >> m;
    Graph g(n);

    for (int i = 0; i < m; i++) {
        int e1 = -1;
        int e2 = -1;
        std::cin >> e1 >> e2;
        g.add_edge(e1, e2);
    }

    std::cout << g.min_cycle();

    return 0;
}
