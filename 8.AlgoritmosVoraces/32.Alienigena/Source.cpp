
// Alberto Bañegil 

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
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

//Vamos recorriedno de C hasta F(izquierda a derecha), la variable fin = C al principio, pero va creciendo 
bool resuelveCaso() {
	int C, F, N, ci, fi, min = 0, i = 0, fin;
	bool imposible;

	cin >> C >> F >> N;
	if (C == 0 && F == 0 && N == 0)
		return false;

	PriorityQueue<limites, ordenador> pq;
	for (int i = 0; i < N; i++) {
		cin >> ci >> fi;
		pq.push({ ci, fi });
	}

	fin = C;
	imposible = false;
	stack<limites> pila;

	while (i < N && !imposible && fin < F) {
		limites l = pq.top(); pq.pop();
		if (l.w > fin && !pila.empty()) {
			if (pila.top().w <= fin) {
				min++;
				fin = pila.top().e;
				pila.pop();
			}
			else
				imposible = true;
		}

		if (l.w <= fin && fin < F && (pila.empty() || l.e >= pila.top().e)) 
				pila.push(l);
		++i;
	}

	if (!pila.empty() && fin < F) {
		if (pila.top().w <= fin) {
			min++;
			fin = pila.top().e;
			pila.pop();
		}
		else 
			imposible = true;
	}

	if (fin < F)
		imposible = true;

	if (imposible) 
		cout << "Imposible";
	else
		cout << min;
	cout << '\n';

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
