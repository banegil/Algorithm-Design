
// Alberto Bañegil 

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <queue>
#include <climits>

#include "DigrafoValorado.h" 
#include "IndexPQ.h"

using namespace std;

const int INF = INT_MAX;

class Solucion {
    int ratonesExitosos;
    vector<int> dist;
    IndexPQ<int> pq;

    void dijkstra(DigrafoValorado<int> const& dg, int origen) {
        dist[origen] = 0;
        pq.push(origen, 0);

        auto gi = dg.inverso();
        while (!pq.empty()) {
            int v = pq.top().elem;
            pq.pop();
            for (auto a : gi.ady(v)) {
                int v = a.desde();
                int w = a.hasta();
                if (dist[w] > dist[v] + a.valor()) {
                    dist[w] = dist[v] + a.valor();
                    pq.update(w, dist[w]);
                }
            }
        }
    }

    void ratones(int tiempo, int salida) {
        for(int i = 0; i < dist.size(); i++)
            if (i != salida && dist[i] <= tiempo)
                ratonesExitosos++;
    }

public:
    Solucion(DigrafoValorado<int> dg, int salida, int tiempo) : ratonesExitosos(0), dist(dg.V(), INF), pq(dg.V()) {
        dijkstra(dg, salida);
        ratones(tiempo, salida);
    }

    int ratEx() {
        return ratonesExitosos;
    }
};


// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int N, S, T, P, v1, v2, valor;

    cin >> N >> S >> T >> P;
    if (!cin)
        return false;

    DigrafoValorado<int> dg(N);
    
    for (int i = 0; i < P; i++) {
        cin >> v1 >> v2 >> valor;
        dg.ponArista({ v1 - 1, v2 - 1, valor });
    }

    Solucion s(dg, S - 1, T);
    cout << s.ratEx() << '\n';

    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
