#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <random>
#include <ctime>
#include <cstdlib>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

// Cria pasta e retorna caminho do arquivo
string get_input_file(int x) {
    fs::create_directories("input");
    return "input/graph_" + to_string(x) + ".txt";
}

// Sorteia inteiro diferente de "exclude"
int rand_exclude(int n, int exclude) {
    int r = rand() % n;
    while (r == exclude)
        r = rand() % n;
    return r;
}

// Função para gerar peso real aleatório no intervalo [min_val, max_val]
double rand_weight(double min_val, double max_val, mt19937 &gen) {
    uniform_real_distribution<double> dist(min_val, max_val);
    return dist(gen);
}

// Gera grafo direcionado simétrico com pesos iguais em (u,v) e (v,u)
void generate_connected_graph(int n, int m, double c, int x) {
    random_device rd;
    mt19937 g(rd());

    set<pair<int,int>> edges;
    int count = 0;

    string file = get_input_file(x);
    ofstream f(file);

    // vértices inicial e final
    int s = rand() % n;
    int d = rand_exclude(n, s);
    f << n << " " << m << " " << s << " " << d << "\n";
    cout << "Generating Graph " << x << ", n=" << n << " m=" << m << " s=" << s << " d=" << d << "\n";

    // spanning tree garante que o grafo é conexo
    for (int u = 1; u < n; u++) {
        int v = rand() % u;
        double w = rand_weight(100.0, c, g);
        f << u << " " << v << " " << w << "\n";
        edges.insert({u, v});
        count += 1;
    }

    // arestas extras
    while (count < m) {
        int u = rand() % n;
        int v = rand() % n;
        if (u != v && !edges.count({u, v})) {
            double w = rand_weight(100.0, c, g);
            f << u << " " << v << " " << w << "\n";
            edges.insert({u, v});
            count += 1;
        }
    }

    f.close();
}

int main() {
    srand(time(NULL));
    for (int i = 1; i <= 15; i++) {
        int n = 50000 + rand() % 50000; // Número grande de vertices pra fazer dial valer a pena
        int m = ((5 * n) + rand() % (5 * n));
        double c = 500.0; // Máximo custo pequeno se não dial perde efeito
        generate_connected_graph(n, m, c, i);
    }
    return 0;
}