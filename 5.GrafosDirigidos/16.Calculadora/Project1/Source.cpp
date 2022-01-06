
// Fabrizio Alcaraz Escobar

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

//#define DOMJUDGE

#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

const int NUMEROMAX = 10000;

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
class Resuelve {
private:
    vector<bool> visitado;
    vector<int> distancia;

    void calcular(int entrada, int salida) {
        queue<int> cola;
        bool encontrado = false;

        visitado[entrada] = true;
        distancia[entrada] = 0;
        cola.push(entrada);
        if (entrada == salida) encontrado = true;
        while (!encontrado) {                          
            int nodoActual = cola.front();
            cola.pop();
            int ady[3];

            ady[0] = (nodoActual * 2) % NUMEROMAX;
            ady[1] = (nodoActual / 3) % NUMEROMAX;
            ady[2] = (nodoActual + 1) % NUMEROMAX;

            for (int i = 0; i < 3; i++) {
                if (!visitado[ady[i]]) {
                    if (ady[i] == salida) encontrado = true;
                    else cola.push(ady[i]);
                    visitado[ady[i]] = true;
                    distancia[ady[i]] = distancia[nodoActual] + 1;
                }
            }
        }
    }
public:
    Resuelve(int entrada, int salida) : visitado(NUMEROMAX, false), distancia(NUMEROMAX) {
        calcular(entrada, salida);
    }

    int getDistancia(int salida) const {
        return distancia[salida];
    }

};

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    int inicio, fin;

    cin >> inicio >> fin;

    if (!std::cin)  // fin de la entrada
        return false;

    Resuelve res(inicio, fin);

    cout << res.getDistancia(fin) << "\n";


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
