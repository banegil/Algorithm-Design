
// Alberto Bañegil

#include <iostream>
#include <fstream>
#include "Matriz.h"
using namespace std;

const int INFINITO = 1000000000;

void Floyd(Matriz<int>& C, int n) {
	for (int k = 0; k <= n; ++k)
		for (int i = n - 1; i > 0; --i)
			for (int j = i + 1; j <= n; ++j) 
				C[i][j] = min(C[i][j], C[i][k] + C[k][j]);
}


bool resuelveCaso() {
	int n;

	cin >> n;
	if (!cin)
		return false;

	Matriz<int> G(n + 1, n + 1, INFINITO);

	for (int i = 1; i <= n; i++)
		for (int j = i + 1; j <= n; j++)
			cin >> G[i][j];

	for (int i = 0; i <= n; i++) 
		G[i][i] = 0;

	Floyd(G, n);

	for (int i = 1; i < n; i++) {
		for (int j = i + 1; j <= n; j++)
			cout << G[i][j] << " ";
		cout << '\n';
	}

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