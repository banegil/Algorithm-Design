
// Alberto Bañegil

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema
#define DOMJUDGE
#include <iostream>
#include <fstream>
#include "Grafo.h"  

using namespace std;

class Solucion {
private:
    vector<bool> visitados;
    vector<int> anteriores;
    bool grafoCorrecto = true;

    void solucionar(const Grafo& g, int origen, int& verticesVisitados) {
        visitados[origen] = true;
        for (int w : g.ady(origen)) {
            if (visitados[w] && (anteriores[origen] != w)) {
                grafoCorrecto = false;
            }
            else if (!visitados[w]) {
                verticesVisitados++;
                anteriores[w] = origen;
                solucionar(g, w, verticesVisitados);
            }
        }
    }

public:
    Solucion(const Grafo& g) : visitados(g.V(), false), anteriores(g.V()) {
        int verticesVisitados = 1;
        solucionar(g, 0, verticesVisitados);
        if (verticesVisitados < g.V())  grafoCorrecto = false;
    }

    bool esCorrecto() {
        return grafoCorrecto;
    }
};

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int v, a, v1, v2;
    cin >> v;
    if (!std::cin) 
        return false;
    Grafo grafo(v);

    cin >> a;

    for (int i = 0; i < a; i++) {
        cin >> v1 >> v2;
        grafo.ponArista(v1, v2);
    }

    Solucion sol(grafo);

    if (sol.esCorrecto()) cout << "SI\n";
    else cout << "NO\n";


    return true;
}

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}