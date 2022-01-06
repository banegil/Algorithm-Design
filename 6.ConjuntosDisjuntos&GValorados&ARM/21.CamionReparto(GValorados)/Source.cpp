
// Alberto Bañegil

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include "GrafoValorado.h"

using namespace std;

class Solucion {
    vector<bool> visitado;
    bool posible;

    void dfs(GrafoValorado<int> g, int origen, int destino, int anchuraC) {
        visitado[origen] = true;
        if (origen == destino) posible = true;
        else {
            for (auto a : g.ady(origen)) {
                int w = a.otro(origen);
                if (a.valor() >= anchuraC && !visitado[w])
                    dfs(g, w, destino, anchuraC);
            }
        }
    }

public:
    Solucion(GrafoValorado<int> g, int V, int origen, int destino, int anchura) : visitado(V, false), posible(false) {
        dfs(g, origen, destino, anchura);
    }

    bool esPosible() {
        return posible;
    }
};

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int V, E, v1, v2, anchura, K;

    cin >> V;
    if (!cin)
        return false;

    cin >> E;

    GrafoValorado<int> g(V);
    for (int i = 0; i < E; i++) {
        cin >> v1 >> v2 >> anchura;
        g.ponArista(Arista<int>(v1 - 1, v2 - 1, anchura));
    }

    cin >> K;
    for (int i = 0; i < K; i++) {
        cin >> v1 >> v2 >> anchura;
        Solucion s(g, V, v1 - 1, v2 - 1, anchura);
        if (s.esPosible())
            cout << "SI\n";
        else
            cout << "NO\n";
    }

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
