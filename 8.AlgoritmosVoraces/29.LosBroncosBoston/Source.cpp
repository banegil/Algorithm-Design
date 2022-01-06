
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
    int n, rivales, broncos, maximo = 0;

    cin >> n;
    if (n == 0)
        return false;

    PriorityQueue<int> colaEnemigos;
    PriorityQueue<int, greater<int>> cola;

    for (int i = 0; i < n; i++) {
        cin >> rivales;
        colaEnemigos.push(rivales);
    }

    for (int i = 0; i < n; i++) {
        cin >> broncos;
        cola.push(broncos);
    }

    for (int i = 0; i < n; i++) {
        rivales = colaEnemigos.top(); colaEnemigos.pop();
        broncos = cola.top(); cola.pop();
        
        maximo += max(0, broncos - rivales);
    }

    cout << maximo << '\n';

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
