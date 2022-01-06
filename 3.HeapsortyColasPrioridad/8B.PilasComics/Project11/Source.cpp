//ALberto Bañegil Diaz

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema


//#define DOMJUDGE

#include <iostream>
#include <fstream>
#include <string>
#include <stack>

#include "PriorityQueue.h"  // propios o los de las estructuras de datos de clase

using namespace std;

struct comic {
    int comic;
    int pila;
};

struct ordenadorPilas {              // Lo usaremos para indicar que ordenaremos de menor a mayor
    bool operator()(const comic& a, const comic& b) {
        return a.comic < b.comic || (b.comic == a.comic && a.pila < b.pila);
    }
};

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...

// El problema tiene un coste logarítmico (O(NlogN + KlogN)), donde N es el número de usuarios registrados y K los envíos que se realizarán

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    PriorityQueue<comic, ordenadorPilas> cola;
    int n, k, elem, menor = 100000000;

    cin >> n;
    if (!cin)
        return false;

    //Leo entrada
    vector<stack<int>> pilas(n);
    for (int i = 0; i < n; i++) {
        cin >> k;
        for (int j = 0; j < k; j++) {
            cin >> elem;
            menor = min(elem, menor);
            pilas[i].push(elem);
        }
    }

    //Resuelvo ejercicio
    for (int i = 0; i < pilas.size(); i++) {
        cola.push( { pilas[i].top(), i } );
        pilas[i].pop();
    }

    int pila, i = 1;
    while (cola.top().comic != menor) {
        pila = cola.top().pila;
        cola.pop();
        if (!pilas[pila].empty()) {
            cola.push({ pilas[pila].top(), pila });
            pilas[pila].pop();
        }
        i++;
    }

    cout << i << "\n";

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