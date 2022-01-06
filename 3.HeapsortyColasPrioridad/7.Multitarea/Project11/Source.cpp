
// Alberto Bañegil

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <string>
#include "priorityQueue.h"

using namespace std;

struct tarea {
    int inf;
    int sup;
    int per;
};

struct ordenadorUsuarios {
    bool operator()(const tarea& a, const tarea& b) {
        return a.inf < b.inf || (b.inf == a.inf && a.sup < b.sup);
    }
};


bool resuelveCaso()
{
    PriorityQueue<tarea, ordenadorUsuarios> cola;
    int n, m, t, inf, sup, per;
    bool solapan = 0;
    tarea aux;

    cin >> n >> m >> t;
    if (!cin)
        return false;

    for (int i = 0; i < n; ++i) {
        cin >> inf >> sup;
        cola.push({ inf, sup, 0 });
    }

    for (int i = 0; i < m; ++i) {
        cin >> inf >> sup >> per;
        cola.push({ inf, sup, per });
    }

    int i = 0;
    aux = cola.top();
    cola.pop();

    while (!solapan && !cola.empty() && cola.top().inf < t && i <= t) {
        solapan = aux.sup > cola.top().inf;
        
        if (i == aux.sup) {
            if (aux.per > 0)
                cola.push({ aux.inf + aux.per, aux.sup + aux.per, aux.per });
            aux = cola.top();
            cola.pop();  
        }
        i++;
    }

    if (solapan)
        cout << "SI" << "\n";
    else
        cout << "NO" << "\n";

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
