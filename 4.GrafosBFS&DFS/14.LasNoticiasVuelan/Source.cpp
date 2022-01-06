
// Alberto Bañegil

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema
#include <iostream>
#include <fstream>
#include <vector>
#include "Grafo.h"  

using namespace std;

class Solucion {
    vector<bool> marcados;
    vector<int> compConx;
    vector<int> v;

    int dfs(const Grafo& g, int origen, int cc) {
        int nV = 1;
        for (int ad : g.ady(origen)) {
            if (!marcados[ad]) {
                marcados[ad] = true;
                v[ad] = cc;
                nV += dfs(g, ad, cc);
            }
        }

        return nV;
    }

    public:
        Solucion(const Grafo& g, int n) : marcados(n, false), compConx(n), v(n) {
            int cc = 0;
            for (int i = 0; i < g.V(); i++) {
                if (!marcados[i]) {
                    marcados[i] = true;
                    v[i] = cc;
                    compConx[cc] = dfs(g, i, cc);
                    cc++;
                }
            }
        }

        vector<int> componenteConexas() {
            return compConx;
        }

        vector<int> vertices() {
            return v;
        }
};

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int N, M, users, v1, v2;

    cin >> N >> M;
    if (!cin)
        return false;

    Grafo g(N);

    // Leo datos
    for (int i = 0; i < M; i++) {
        cin >> users;
        if (users != 0) cin >> v1;

        for (int j = 1; j < users; j++) {
            cin >> v2;
            g.ponArista(v1 - 1, v2 - 1);
            v1 = v2;
        }
    }

    // Resuelvo problema
    Solucion s(g, N);
    
    vector<int> cc = s.componenteConexas();

    for (int vertice : s.vertices()) {
        int j = 0;
        while (j != vertice)
            j++;
        cout << cc[j] << ' ';
    }

    cout << '\n';

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