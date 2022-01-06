
// Alberto Bañegil

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <limits>


using namespace std;
#include "GrafoValorado.h"
#include "IndexPQ.h"

class CaminoMin {
	vector<int> distancia;
	IndexPQ<int> cola;
	vector<int> distancias;

	void dijkstra(GrafoValorado<int> const& g, int s) {
		distancia[s] = 0;
		cola.push(s, 0);
		distancias[s] = 1;

		while (!cola.empty()) {
			int v = cola.top().elem;
			cola.pop();
			for (Arista<int> w : g.ady(v)) {
				int origen = w.uno();
				int destino = w.otro(v);

				if (distancia[destino] > distancia[origen] + w.valor()) {
					distancia[destino] = distancia[origen] + w.valor();
					cola.update(destino, distancia[destino]);
					distancias[destino] = distancias[origen];
				}
				else {
					if (distancia[destino] == distancia[origen] + w.valor()) {
						distancias[destino] += distancias[origen];
					}
				}
			}
		}
	}
public:
	CaminoMin(GrafoValorado<int> const& g, int origen) : distancia(g.V(), numeric_limits<int>::max()), cola(g.V()), distancias(g.V()) {
		dijkstra(g, origen);
	}

	int dameCaminos() {
		return distancias[distancias.size() - 1];
	}
};
// resuelve un caso de prueba
void resuelveCaso(int const& N, int const& C) {
	int a1, a2, valor;

	GrafoValorado<int> grafo(N);

	for (int i = 0; i < C; i++) {
		cin >> a1 >> a2 >> valor;
		Arista<int> arista(a1 - 1, a2 - 1, valor);
		grafo.ponArista(arista);
	}

	CaminoMin sol(grafo, 0);
	int cam = sol.dameCaminos();
	cout << cam << endl;
}



int main() {
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	int N, C;
	cin >> N >> C;
	while (!cin.fail()) {
		resuelveCaso(N, C);
		cin >> N >> C;
	}

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("pause");
#endif
	return 0;
}