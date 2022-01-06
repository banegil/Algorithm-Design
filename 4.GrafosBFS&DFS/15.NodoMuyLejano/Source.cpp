
// Alberto Bañegil

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include "Grafo.h"  

using namespace std;

class Solucion {
    int vertAlzanzables;
    vector<bool> visitados;
    vector<int> ttl;

    void bfs(Grafo const& g, int nodoIni, int TTL) {
        queue<int> q;
        visitados[nodoIni] = true;
        q.push(nodoIni);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (int w : g.ady(v)) {
                if (!visitados[w] && ttl[v] < TTL) {
                    visitados[w] = true;
                    ttl[w] = ttl[v] + 1;
                    q.push(w);
                    vertAlzanzables++;
                }
            }
        }
    }

    public:
        Solucion(const Grafo& g, int nodoIni, int TTL, int K) : vertAlzanzables(1), visitados(g.V(), false), ttl(g.V(), 0) {
            bfs(g, nodoIni, TTL);
        }

        int vA() {
            return vertAlzanzables;
        }
};

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int N, C, v1, v2, K, nodoIni, TTL;

    cin >> N >> C;
    if (!cin)
        return false;

    Grafo g(N);

    for (int i = 0; i < C; i++) {
        cin >> v1 >> v2;
        g.ponArista(v1 - 1, v2 - 1);
    }

    cin >> K;
    for (int i = 0; i < K; i++) {
        cin >> nodoIni >> TTL;
        Solucion s(g, nodoIni - 1, TTL, K);
        cout << g.V() - s.vA() << '\n';
    }

    cout << "---\n";

    return true;
}


int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}