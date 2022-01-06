
// Alberto Bañegil

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <deque>
#include "Digrafo.h"

using namespace std;

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
class Resuelve {
private:
    vector<bool> visitado;
    vector<bool> enCola;
    bool hayCiclo;
    bool fin;
    int cont;

    void dfs(const Digrafo& g, int entrada) {
        visitado[entrada] = true;
        enCola[entrada] = true;
        for (int i : g.ady(entrada)) {
            if (hayCiclo) return;
            else if (!visitado[i]) {
                cont++;
                dfs(g, i);
            }
            else if (enCola[i])
                hayCiclo = true;
        }
        enCola[entrada] = false;
    }

public:
    Resuelve(const Digrafo& g) : visitado(g.V(), false), enCola(g.V(), false), hayCiclo(false), cont(0), fin(false) {
        dfs(g, 0);
        if (cont == g.V() - 1)
            fin = true;
    }

    bool ciclo() {
        return hayCiclo;
    }

    bool final() {
        return fin;
    }
};

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int L, iSalto;
    char inst;

    cin >> L;
    if (!cin)
        return false;

    Digrafo d(L + 1);

    for (int i = 0; i < L; i++) {
        cin >> inst;
        if(inst == 'A')
            d.ponArista(i, i + 1);
        else if (inst == 'J') {
            cin >> iSalto;
            d.ponArista(i, iSalto - 1);
        }
        else if (inst == 'C') {
            cin >> iSalto;
            d.ponArista(i, i + 1);
            d.ponArista(i, iSalto - 1);
        }
    }

    Resuelve r(d);
    if (!r.final())
        cout << "NUNCA\n";
    else if (r.ciclo())
        cout << "A VECES\n";
    else
        cout << "SIEMPRE\n";

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
