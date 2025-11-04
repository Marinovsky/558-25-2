#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <cmath>
#include <limits>
#include <chrono>
#include <numeric>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

string get_input_file(int x)
{
    fs::create_directories("input");
    return "input/graph_" + to_string(x) + ".txt";
}

// Lê o grafo e já converte pesos double para int
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
    srand((unsigned)time(NULL));
    vector<double> tempos;

    for (int x = 1; x <= 15; x++)
    {
        int n, m, s, d, max_weight;
        vector<vector<pair<int, int>>> graph;
        create_graph_converted(x, n, m, s, d, graph, max_weight);

        auto start = chrono::high_resolution_clock::now();
        double dist = dijkstra_dial(n, s, d, graph, max_weight);
        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double> interval = end - start;
        cout << "Dijkstra Dial n=" << n << " m=" << m * s << " s=" << s << " d=" << d << " dist=" << dist << " time=" << interval.count() << "s\n";
        tempos.push_back(interval.count());
    }

    double media = accumulate(tempos.begin(), tempos.end(), 0.0) / tempos.size();
    cout << "Média: " << media << "s\n";
    return 0;
}