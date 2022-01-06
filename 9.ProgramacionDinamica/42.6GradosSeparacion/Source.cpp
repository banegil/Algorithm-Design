// Alberto Bañegil

#include <iostream>
#include <fstream>
#include <unordered_map>
#include "Matriz.h"
using namespace std;

const int INFINITO = 1000000000;

void grados(Matriz<int>& G) {
	int n = G.numfils() - 1;

	for (int k = 1; k <= n; ++k) 
		for (int i = 1; i <= n; ++i) 
			for (int j = 1; j <= n; ++j) 
				G[i][j] = min(G[i][j], G[i][k] + G[k][j]);

}

bool resuelveCaso() {
	int P, R;

	cin >> P >> R;
	if (!cin) 
		return false;

	Matriz<int> tabla(P + 1, P + 1, INFINITO);

	for (int d = 1; d <= P; d++) 
		tabla[d][d] = 0;

	string n1, n2;
	unordered_map<string, int> mapa;
	int cont = 1;

	for (int i = 0; i < R; ++i) {
		string p1, p2;
		cin >> p1 >> p2;

		if (mapa[p1] == 0) {
			mapa[p1] = cont;
			++cont;
		}
		if (mapa[p2] == 0) {
			mapa[p2] = cont;
			++cont;
		}

		tabla[mapa[p1]][mapa[p2]] = 1;
		tabla[mapa[p2]][mapa[p1]] = 1;
	}

	grados(tabla);

	int grado = 0;
	for (int i = 1; i <= P; i++)
		for (int j = i + 1; j <= P; j++)
				grado = max(grado, tabla[i][j]);

	if (grado == INFINITO)
		cout << "DESCONECTADA";
	else 
		cout << grado;
	cout << "\n";

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