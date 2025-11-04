#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <limits>
#include <numeric>
#include <chrono>
#include <filesystem>
#include <algorithm>

using namespace std;
namespace fs = std::filesystem;

const double INF = numeric_limits<double>::infinity();

// Função para criar o caminho do arquivo
string get_input_file(int x) {
    fs::create_directories("input");
    return "input/graph_" + to_string(x) + ".txt";
}

// Função para ler o grafo
void create_graph(int x, int &n, int &m, int &s, int &d,
                  vector<vector<pair<double, int>>> &graph) {
    string file = get_input_file(x);
    ifstream f(file);
    if (!f.is_open()) {
        cerr << "Erro ao abrir arquivo " << file << endl;
        exit(1);
    }

    f >> n >> m >> s >> d;
    graph.assign(n, vector<pair<double, int>>());

    for (int i = 0; i < m; i++) {
        int u, v;
        double w; 
        f >> u >> v >> w;
        graph[u].push_back({w, v});
        graph[v].push_back({w, u});
    }
    f.close();
}

bool relax_dijkstra(
    vector<double>& dist_A, 
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<>>& heap_A, 
    const vector<double>& dist_B, 
    const priority_queue<pair<double, int>, vector<pair<double, int>>, greater<>>& heap_B,
    double& min_dist, 
    const vector<vector<pair<double, int>>>& graph) {
    /*
    /////////////////////////
    Escreva o seu código aqui
    /////////////////////////
    */
}

double dijkstra_bidirectional(int n, int source, int dest,
                              const vector<vector<pair<double, int>>> &graph) {
    if (source == dest) return 0.0;
    
    // Estruturas para busca a partir do source
    vector<double> dist_f(n, INF);
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<>> heap_f;
    dist_f[source] = 0.0;
    heap_f.push({0.0, source});
    
    // Estruturas para a busca a partir do destination
    vector<double> dist_b(n, INF);
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<>> heap_b;
    dist_b[dest] = 0.0;
    heap_b.push({0.0, dest});

    double min_dist = INF; 
    
    while (!heap_f.empty() && !heap_b.empty()) {
        if (min_dist <= heap_f.top().first + heap_b.top().first) {
            break; 
        }
        
        // relaxar heap com melhor prioridade
        if (heap_f.top().first < heap_b.top().first) {
             if (!relax_dijkstra(dist_f, heap_f, dist_b, heap_b, min_dist, graph)) break;
        } else {
             if (!relax_dijkstra(dist_b, heap_b, dist_f, heap_f, min_dist, graph)) break;
        }
    }

    return min_dist;
}

int main() {
    vector<double> tempos;

    for (int x = 1; x <= 15; x++) {
        int n, m, s, d;
        vector<vector<pair<double, int>>> graph;
        create_graph(x, n, m, s, d, graph);

        auto start = chrono::high_resolution_clock::now();
        double dist = dijkstra_bidirectional(n, s, d, graph);
        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double> interval = end - start;
        cout << "Dijkstra Bidirecional n=" << n << " m=" << m << " s=" << s << " d=" << d << " dist=" << dist << " time=" << interval.count() << "s\n";
        tempos.push_back(interval.count());
    }

    double media = accumulate(tempos.begin(), tempos.end(), 0.0) / tempos.size();
    cout << "Média: " << media << "s\n";
    return 0;
}