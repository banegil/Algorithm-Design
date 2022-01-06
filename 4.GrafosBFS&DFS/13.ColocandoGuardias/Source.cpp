
// Alberto Bañegil

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema
#define DOMJUDGE
#include <iostream>
#include <fstream>
#include "Grafo.h"  

using namespace std;

class ColocarGuardias
{
public:
    ColocarGuardias(const Grafo& g) : visitados(g.V(), false), negros(g.V(), false), blancos(g.V(), false) {
        for (int i = 0; i < g.V(); i++) {

            if (!visitados[i]) {

                int negro = 0;
                int blanco = 0;

                dfs(g, i, false, negro, blanco);
                if (negro >= blanco)
                    guardias += blanco;
                else
                    guardias += negro;
            }
        }
    };

    bool getEsPosible() {
        return esPosible;
    }

    int getGuardias() {
        return guardias;
    }

private:
    vector<bool> visitados;
    vector<bool> negros;
    vector<bool> blancos;
    int guardias = 0;
    bool esPosible = true;

    void dfs(const Grafo& g, int origen, bool vieneNegro, int& negrosColocados, int& blancosColocados) {
        visitados[origen] = true;

        if (vieneNegro) {
            blancos[origen] = true;
            blancosColocados++;
        }
        else {
            negros[origen] = true;
            negrosColocados++;
        }

        for (int w : g.ady(origen)) {

            if (visitados[w] && blancos[w] == vieneNegro)
                esPosible = false;
            else if (!visitados[w]) {
                dfs(g, w, !vieneNegro, negrosColocados, blancosColocados);
            }
        }
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
        grafo.ponArista(v1 - 1, v2 - 1);
    }

    ColocarGuardias guardias(grafo);

    if (guardias.getEsPosible()) {
        cout << guardias.getGuardias() << "\n";
    }
    else
        cout << "IMPOSIBLE \n";
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