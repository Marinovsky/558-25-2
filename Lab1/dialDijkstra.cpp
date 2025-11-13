#include <iostream>
#include <vector>
#include <deque>
#include <cmath>
#include <limits>
#include <numeric>
using namespace std;

// Lê o grafo e já converte pesos double para int
void create_graph_converted(int &n, int &m, int &s, int &d,
                            vector<vector<pair<int, int>>> &graph, int &max_weight) {
    cin >> n >> m >> s >> d;
    graph.assign(n, vector<pair<int, int>>());
    max_weight = 0;

    for (int i = 0; i < m; i++) {
        int u, v;
        double w;
        cin >> u >> v >> w;
        int iw = static_cast<int>(round(w));
        graph[u].push_back({iw, v});
        graph[v].push_back({iw, u});
        if (iw > max_weight)
            max_weight = iw;
    }
}

double dijkstra_dial(int n, int source, int dest,
                     const vector<vector<pair<int, int>>> &graph,
                     int max_weight) {
    /*
    /////////////////////////
    Escreva o seu código aqui
    /////////////////////////
    */
}

int main() {
    int n, m, s, d, max_weight;
    vector<vector<pair<int, int>>> graph;
    create_graph_converted(n, m, s, d, graph, max_weight);

    double dist = dijkstra_dial(n, s, d, graph, max_weight);

    cout << dist;
    return 0;
}