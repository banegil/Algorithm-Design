
// Alberto Bañegil

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema
#define DOMJUDGE
#include <iostream>
#include <fstream>
#include "Grafo.h"  

using namespace std;

void recorreEnProfundidad(int& visitados, Grafo const& g, int inicio, vector<bool>& marcados) {
	visitados++;
	marcados[inicio] = true;
	for (int elem : g.ady(inicio))
		if (!marcados[elem]) recorreEnProfundidad(visitados, g, elem, marcados);
}


void resuelveCaso() {
	int n, m, v1, v2;
	cin >> n >> m;
	Grafo g(n + 1);
	for (int i = 0; i < m; ++i) {
		cin >> v1 >> v2;
		g.ponArista(v1, v2);
	}
	vector <bool> marcados(n + 1, false);
	int maxAmigos = 0, visitados;
	for (int i = 1; i <= n; ++i) {
		visitados = 0;
		recorreEnProfundidad(visitados, g, i, marcados);
		if (visitados > maxAmigos) maxAmigos = visitados;
	}
	cout << maxAmigos << '\n';
}

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}