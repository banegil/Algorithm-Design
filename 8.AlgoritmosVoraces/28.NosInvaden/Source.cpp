
// Alberto Bañegil 

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include "PriorityQueue.h"
using namespace std;


// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int n, enemigos, soldados, max = 0;

    cin >> n;
    if (!cin)
        return false;

    PriorityQueue<int> colaEnemigos, cola;

    for (int i = 0; i < n; i++) {
        cin >> enemigos;
        colaEnemigos.push(enemigos);
    }

    for (int i = 0; i < n; i++) {
        cin >> soldados;
        cola.push(soldados);
    }

    enemigos = colaEnemigos.top(); colaEnemigos.pop();
    soldados = cola.top(); cola.pop();
    for (int i = 1; i < n; i++) {
        if (soldados >= enemigos) {
            enemigos = colaEnemigos.top(); colaEnemigos.pop();
            max++;
        }
        soldados = cola.top(); cola.pop();
    }

    if (soldados >= enemigos) max++;

    cout << max << '\n';

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
