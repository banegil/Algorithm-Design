
// Alberto Bañegil

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <string>
#include "priorityQueue.h"

using namespace std;

struct usuario {
    int atendido;
    int id;
    int periodo;
};

struct ordenadorUsuarios {          
    bool operator()(const usuario& a, const usuario& b) {
        return a.atendido < b.atendido || (b.atendido == a.atendido && a.id < b.id);
    }
};

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    PriorityQueue<usuario, ordenadorUsuarios> cola;
    int n, id, periodo, k;
    cin >> n;
    if (n == 0)
        return false;

    for (int i = 0; i < n; ++i) {                   
        cin >> id >> periodo;
        cola.push({ periodo,id,periodo });          
    }

    cin >> k;

    for (int i = 0; i < k; ++i) {
        usuario usuarioActual = cola.top();       
        cola.pop();                               
        cout << usuarioActual.id << "\n";
        usuarioActual.atendido += usuarioActual.periodo;
        cola.push(usuarioActual);               
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

    while(resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
