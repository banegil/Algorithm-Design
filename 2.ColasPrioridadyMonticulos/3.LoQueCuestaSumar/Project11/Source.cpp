
// Alberto Bañegil

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <string>
#include "priorityQueue.h"

using namespace std;

bool resuelveCaso()
{

    PriorityQueue<long long int> sumandos;
    int n;
    long long int  sumando, costeTotal = 0;

    cin >> n;
    if (n == 0)
        return false;

    for (int i = 0; i < n; i++) {           
        cin >> sumando;
        sumandos.push(sumando);	
    }

    while (!sumandos.empty() && sumandos.size() > 1) {	
        sumando = sumandos.top();		
        sumandos.pop();
        sumando += sumandos.top(); 
        sumandos.pop();          
        costeTotal += sumando;
        sumandos.push(sumando);
    }

    cout << costeTotal << "\n";

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
