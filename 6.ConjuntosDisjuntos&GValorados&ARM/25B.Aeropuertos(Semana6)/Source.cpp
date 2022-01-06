
// Alberto Bañegil

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include "GrafoValorado.h"
#include "PriorityQueue.h"
#include "ConjuntosDisjuntos.h"

using namespace std;

class ARM_Kruskal {
    int coste;
    int numA;
    vector<Arista<int>> _ARM;

public:
    ARM_Kruskal(GrafoValorado<int> g, int costeAeropuerto) : coste(0){
        ConjuntosDisjuntos cjtos(g.V());
        PriorityQueue<Arista<int>> pq(g.aristas());

        while (!pq.empty()) {
            auto a = pq.top(); pq.pop();
            int v = a.uno(), w = a.otro(v);
            if (!cjtos.unidos(v, w) && a.valor() < costeAeropuerto) {
                cjtos.unir(v, w);
                _ARM.push_back(a);
                coste += a.valor();
                if (_ARM.size() == g.V() - 1)
                    break;
            }
        }
        numA = cjtos.num_cjtos();
        coste += costeAeropuerto * numA;
    }

    int numAeropuertos() {
        return numA;
    }

    int costeTotal() {
        return coste;
    }
};

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int N, M, costeAeropuerto, v1, v2, costeCarretera;

    cin >> N >> M >> costeAeropuerto;
    if (!cin)
        return false;

    GrafoValorado<int> g(N);

    for (int i = 0; i < M; i++) {
        cin >> v1 >> v2 >> costeCarretera;
        g.ponArista(Arista<int>(v1 - 1, v2 - 1, costeCarretera));
    }

    ARM_Kruskal s(g, costeAeropuerto);

    cout << s.costeTotal() << " " << s.numAeropuertos() << '\n';

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
