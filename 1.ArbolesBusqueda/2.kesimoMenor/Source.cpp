
// Alberto Bañegil

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <string>
#include "TreeSet_AVL.h"

using namespace std;

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
int resolver(Set<int> arbol, int k) {
    return arbol.kesimo(k);
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int n, k, nElems;
    Set<int> arbol;

    cin >> n;
    if (n == 0)
        return false;
    
    for (int i = 0; i < n; i++) {
        cin >> k;
        arbol.insert(k);
    }
    
    cin >> nElems;

    for (int i = 0; i < nElems; i++) {
        try {
            cin >> k;
            cout << arbol.kesimo(k) << "\n";
        }
        catch (EKesimoNoExiste) {
            cout << "??" << "\n";
        }
    }
    cout << "---" << "\n";

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
