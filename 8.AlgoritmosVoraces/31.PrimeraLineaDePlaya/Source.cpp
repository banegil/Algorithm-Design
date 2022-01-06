
// Alberto Bañegil 

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include "PriorityQueue.h"
using namespace std;

struct limites {
    int w;
    int e;
};

struct ordenador {
	bool operator()(const limites& a, const limites& b) {
		return a.w < b.w || (b.w == a.w && a.e < b.e);
	}
};

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	int N, W, E, fin, cont = 1;

	cin >> N;
	if (N == 0)
		return false;

	PriorityQueue<limites, ordenador> pq;
	for (int i = 0; i < N; i++) {
		cin >> W >> E;
		pq.push({ W, E });
	}

	fin = pq.top().e; pq.pop();

	for (int i = 1; i < N; i++) {
		limites l = pq.top(); pq.pop();

		if (fin > l.w) 
			fin = min(fin, l.e);
		else {
			fin = l.e;
			cont++;
		}
	}

	cout << cont << '\n';

	return true;

}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
