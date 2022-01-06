
// Alberto Bañegil

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <deque>

#include "Digrafo.h"  // propios o los de las estructuras de datos de clase

using namespace std;

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
class Resuelve {
private :
    deque<int> camino;
    vector<bool> visitado;
    vector<bool> enCola;
    bool hayCiclo;

    void recorre(const Digrafo& g, int entrada) {
        visitado[entrada] = true;
        enCola[entrada] = true;
        for (int i : g.ady(entrada)) {
            if (hayCiclo) return;
            else if (!visitado[i]) {
                recorre(g, i);
            }
            else if (enCola[i]) hayCiclo = true;
        }
        camino.push_front(entrada);
        enCola[entrada] = false;
    }

public:
    Resuelve(const Digrafo& g) :  visitado(g.V(), false), enCola(g.V(), false), hayCiclo(false) {
        for (int i = 0; i < g.V(); i++) {
            if (!visitado[i]) recorre(g, i);
        }
    }

    bool existeCiclo()const {
        return hayCiclo;
    }

    void escribeCamino()const {
        for (int i : camino) {
            cout << i + 1 << " ";
        }
    }

};

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
   
    int n, m, a, b;
   
    cin >> n >> m;
   if (!std::cin)  // fin de la entrada
      return false;
   Digrafo grafo(n);

   for (int i = 0; i < m; i++) {
       cin >> a >> b;
       grafo.ponArista(a - 1, b - 1);
   }

   Resuelve caso(grafo);

   if (caso.existeCiclo()) cout << "Imposible";
   else caso.escribeCamino();

   cout << "\n";
   
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
