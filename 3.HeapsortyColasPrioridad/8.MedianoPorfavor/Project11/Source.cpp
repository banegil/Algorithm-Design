
// Alberto Bañegil Diaz

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

// El problema se resuelve con la utilización de una clase ColaMedianas, en la que se almacenan dos colas de prioridades, una de máximos, en la que colocaremos los elementos más pequeños, 
//y otra de mínimos, en la que irán los elementos más grandes.

//#define DOMJUDGE

#include <iostream>
#include <fstream>
#include <string>
#include "priorityQueue.h"

using namespace std;
class ColaMedianas {
public:
    void insertar(int x) {
        if ((colaMenores.empty() && (colaMayores.empty() || x < colaMayores.top())) || (!colaMenores.empty() && x < colaMenores.top())) {
            colaMenores.push(x);
            tamMenores++;
            if (tamMenores - tamMayores > 1) {
                colaMayores.push(colaMenores.top());
                colaMenores.pop();
                tamMayores++;
                tamMenores--;
            }
        }
        else {
            colaMayores.push(x);
            tamMayores++;
            if (tamMayores - tamMenores > 1) {
                colaMenores.push(colaMayores.top());
                colaMayores.pop();
                tamMenores++;
                tamMayores--;
            }
        }
    };
    bool vacia() const {
        return tamMayores == 0 && tamMenores == 0;
    };
    int mediana() const {
        int tamTotal = tamMenores + tamMayores;
        if (tamTotal % 2 == 0) {
            return colaMenores.top();
        }
        else if (tamMayores > tamMenores) return colaMayores.top();
        else return colaMenores.top();
    };
    void quitarMediana() {
        int tamTotal = tamMenores + tamMayores;
        if (tamTotal % 2 == 0) {
            colaMenores.pop();
            tamMenores--;
        }
        else if (tamMayores > tamMenores) {
            colaMayores.pop();
            tamMayores--;
        }
        else if (tamMayores < tamMenores) {
            colaMenores.pop();
            tamMenores--;
        }
    };

private:
    PriorityQueue<int> colaMayores;
    PriorityQueue<int, greater<int>> colaMenores;
    int tamMenores = 0;
    int tamMayores = 0;
};
// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    int n, evento;
    ColaMedianas colaClientes;
    bool ok = 1;
    cin >> n;
    if (!std::cin)  // fin de la entrada
        return false;

    for (int i = 0; i < n; i++) {
        cin >> evento;
        if (evento != 0) {
            colaClientes.insertar(evento);
        }
        else {
            if (!colaClientes.vacia()) {
                if (ok) ok = 0;
                else cout << ' ';
                cout << colaClientes.mediana();
                colaClientes.quitarMediana();
            }
            else {
                if (ok) ok = 0;
                else cout << ' ';
                cout << "ECSA";
            }
        }
    }
    cout << "\n";
    // escribir sol

    return true;
}

int main() {
    // ajustes para que cin extraiga directamente de un fichero


    while (resuelveCaso());

    // para dejar todo como estaba al principio
    return 0;
}
