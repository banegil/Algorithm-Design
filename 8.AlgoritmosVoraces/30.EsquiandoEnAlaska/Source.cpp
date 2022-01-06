
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
    int n, altura, ski, maximo = 0;

    cin >> n;
    if (n == 0)
        return false;

    PriorityQueue<int> alturas;
    PriorityQueue<int> skis;

    for (int i = 0; i < n; i++) {
        cin >> altura;
        alturas.push(altura);
    }

    for (int i = 0; i < n; i++) {
        cin >> ski;
        skis.push(ski);
    }

    for (int i = 0; i < n; i++) {
        altura = alturas.top(); alturas.pop();
        ski = skis.top(); skis.pop();
        
        maximo += abs(ski - altura);
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
