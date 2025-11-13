#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <limits>
#include <numeric>
using namespace std;

// Função para ler o grafo do arquivo e trasnformar em uma lista de adjacência
void create_graph(int &n, int &m, int &s, int &d, vector<vector<pair<double,int>>> &graph) {
    cin >> n >> m >> s >> d;
    graph.assign(n, vector<pair<double,int>>());

    for (int i = 0; i < m; i++) {
        int u, v;
        double w;
        cin >> u >> v >> w;
        graph[u].push_back({w, v});
        graph[v].push_back({w, u});
    }
}

double dijkstra(int n, int source, int dest, const vector<vector<pair<double,int>>> &graph) {
    /*
    /////////////////////////
    Escreva o seu código aqui
    /////////////////////////
    */
}

int main() {
    int n, m, s, d;
    vector<vector<pair<double,int>>> graph;
    create_graph(n, m, s, d, graph);

    double dist = dijkstra(n, s, d, graph);

    cout << dist;
    return 0;
}