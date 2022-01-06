
// Alberto Bañegil

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <string>
#include "bintree.h"

using namespace std;

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
bool esAVL(bintree<int> arbol, int& altura, int& maxim, int& minim) {
    int izAlt, derAlt, izMaxim, izMinim, derMaxim , derMinim;
    bool izAVL, derAVL;

    if (arbol.empty()) {
        altura = maxim = 0;
        minim = 10000000;
        return 1;
    }

    izAVL = esAVL(arbol.left(), izAlt, izMaxim, izMinim);
    derAVL = esAVL(arbol.right(), derAlt, derMaxim, derMinim);

    altura = max(izAlt, derAlt) + 1;
    maxim = max(max(izMaxim, derMaxim), arbol.root());
    minim = min(min(izMinim, derMinim), arbol.root());

    if (abs(izAlt - derAlt) >= 2)
        return 0;
    else
        return izAVL && derAVL && (arbol.root() > izMaxim && arbol.root() < derMinim);
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int altura, max, min;
    auto arbol = leerArbol(-1);

    // escribir solución
    if (esAVL(arbol, altura, max, min))
        cout << "SI" << "\n";
    else
        cout << "NO" << "\n";
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
