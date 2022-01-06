
// Alberto Bañegil

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <string>
#include "priorityQueue.h"

using namespace std;

class ColaUrgencias {
    struct usuario {
        int orden;
        string nombre;
        int gravedad;
    };

    struct ordenadorUsuarios {
        bool operator()(const usuario& a, const usuario& b) {
            return a.gravedad > b.gravedad || (b.gravedad == a.gravedad && a.orden < b.orden);
        }
    };

    PriorityQueue<usuario, ordenadorUsuarios> cola;
    int cont;
public:
    ColaUrgencias() : cont(0) {}

    void ingresarPaciente(string nombre, int gravedad) {
        cola.push({cont++, nombre, gravedad});
    }

    string nombrePrimero() const {
        return cola.top().nombre;
    }

    void atenderPaciente() {
        cola.pop();
    }
};


bool resuelveCaso()
{
    ColaUrgencias cola;
    string evento, nombre;
    int n, gravedad;

    cin >> n;
    if (n == 0)
        return false;

    for (int i = 0; i < n; ++i) {
        cin >> evento;

        if (evento == "I") {
            cin >> nombre >> gravedad;
            cola.ingresarPaciente(nombre, gravedad);
        }
        else {
            cout << cola.nombrePrimero() << "\n";
            cola.atenderPaciente();
        }
    }

    cout << "---\n";

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
