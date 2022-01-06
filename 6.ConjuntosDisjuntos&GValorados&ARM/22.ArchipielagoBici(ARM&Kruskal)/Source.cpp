
// Alberto Bañegil

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include "GrafoValorado.h"
#include "ConjuntosDisjuntos.h"
#include "PriorityQueue.h"

using namespace std;

template <typename Valor>
class ARM_Kruskal {
private:
    vector<Arista<Valor>> _ARM;
    Valor coste;
    int islas;

public:
    Valor costeARM() const {
        return coste;
    }

    vector<Arista<Valor>> const& ARM() const {
        return _ARM;
    }

    int numIslas() {
        return islas;
    }

    ARM_Kruskal(GrafoValorado<Valor> const& g) : coste(0), islas(0) {
        PriorityQueue<Arista<Valor>> pq(g.aristas());
        ConjuntosDisjuntos cjtos(g.V());

        while (!pq.empty()) {
            auto a = pq.top(); pq.pop();
            int v = a.uno(), w = a.otro(v);
            if (!cjtos.unidos(v, w)) {
                islas++;
                cjtos.unir(v, w);
                _ARM.push_back(a); coste += a.valor();
                if (_ARM.size() == g.V() - 1) break;
            }
        }
    }
};

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int I, P, i1, i2, p;

    cin >> I >> P;
    if (!cin)
        return false;

    GrafoValorado<int> g(I);

    for (int i = 0; i < P; i++) {
        cin >> i1 >> i2 >> p;
        g.ponArista(Arista<int>(i1 - 1, i2 - 1, p));
    }

    ARM_Kruskal<int> arm(g);

    if(arm.numIslas() + 1 == I)
        cout << arm.costeARM() << '\n';
    else
        cout << "No hay puentes suficientes\n";

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
