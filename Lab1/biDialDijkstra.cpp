#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <string>
#include <limits>
#include <numeric>
#include <chrono>
#include <filesystem>
#include <cmath>
#include <algorithm>

using namespace std;
namespace fs = std::filesystem;
const int INF = numeric_limits<int>::max();

string get_input_file(int x) {
    fs::create_directories("input");
    return "input/graph_" + to_string(x) + ".txt";
}

void create_graph_converted(int x, int &n, int &m, int &s, int &d,
                            vector<vector<pair<int, int>>> &graph, int &max_weight) {
    string file = get_input_file(x);
    ifstream f(file);
    if (!f) {
        cerr << "Erro ao abrir arquivo: " << file << endl;
        exit(1);
    }

    f >> n >> m >> s >> d;
    graph.assign(n, vector<pair<int, int>>());
    max_weight = 0;

    for (int i = 0; i < m; i++) {
        int u, v;
        double w; 
        f >> u >> v >> w;
        int iw = static_cast<int>(round(w));
        graph[u].push_back({iw, v});
        graph[v].push_back({iw, u});

        if (iw > max_weight)
            max_weight = iw;
    }
    f.close();
}

bool relax_dial(
    vector<int>& dist_A, 
    vector<deque<int>>& buckets_A, 
    const vector<int>& dist_B, 
    int& idx_A,
    int& min_dist, 
    const vector<vector<pair<int, int>>>& graph,
    int max_weight) {
    /*
    /////////////////////////
    Escreva o seu código aqui
    /////////////////////////
    */
}

int bidirectional_dijkstra_dial(int n, int source, int dest,
                                 const vector<vector<pair<int, int>>> &graph,
                                 int max_weight) {
    if (source == dest) return 0;

    // Estruturas para busca a partir do source
    vector<int> dist_f(n, INF);
    vector<deque<int>> buckets_f(max_weight + 1); 
    dist_f[source] = 0;
    buckets_f[0].push_back(source);

    // Estruturas para a busca a partir do destination
    vector<int> dist_b(n, INF);
    vector<deque<int>> buckets_b(max_weight + 1); 
    dist_b[dest] = 0;
    buckets_b[0].push_back(dest);
    
    int min_dist = INF; 
    int idx_f = 0;
    int idx_b = 0;

    // Alterna as buscas. O algoritmo para quando min_dist <= idx_f + idx_b.
    while (min_dist > idx_f + idx_b) {
        
        // Expande a busca que está na menor fronteira
        if (idx_f <= idx_b) {
            if (!relax_dial(dist_f, buckets_f, dist_b, idx_f, min_dist, graph, max_weight)) break;
        } else {
            if (!relax_dial(dist_b, buckets_b, dist_f, idx_b, min_dist, graph, max_weight)) break;
        }
    }

    return min_dist;
}

int main() {
    vector<double> tempos;

    for (int x = 1; x <= 15; x++) {
        int n, m, s, d, max_weight;
        vector<vector<pair<int, int>>> graph;
        create_graph_converted(x, n, m, s, d, graph, max_weight);

        auto start = chrono::high_resolution_clock::now();
        int dist = bidirectional_dijkstra_dial(n, s, d, graph, max_weight);
        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double> interval = end - start;
        cout << "Dial Bidirecional n=" << n << " m=" << m << " s=" << s << " d=" << d << " dist=" << dist << " time=" << interval.count() << "s\n";
        tempos.push_back(interval.count());
    }

    double media = accumulate(tempos.begin(), tempos.end(), 0.0) / tempos.size();
    cout << "Média: " << media << "s\n";
    return 0;
}