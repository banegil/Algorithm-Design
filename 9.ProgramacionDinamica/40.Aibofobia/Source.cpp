
// Alberto Bañegil

#include <iostream>
#include <fstream>
#include "Matriz.h"
using namespace std;

int patin_rec(string const& patitos, int i, int j, Matriz<int>& patin) {
	int& res = patin[i][j];
	if (res == -1) {
		if (i > j) res = 0;
		else if (i == j) res = 0;
		else if (patitos[i] == patitos[j])
			res = patin_rec(patitos, i + 1, j - 1, patin);
		else
			res = min(patin_rec(patitos, i + 1, j, patin),
				patin_rec(patitos, i, j - 1, patin)) + 1;
	}
	return res;
}

string reconstruir(string const& patitos, Matriz<int> const& patin,
	int i, int j) {
	if (i > j) return {};
	if (i == j) return { patitos[i] };
	if (patitos[i] == patitos[j])
		return patitos[i] + reconstruir(patitos, patin, i + 1, j - 1) + patitos[j];
	else if (patin[i][j] == patin[i + 1][j] + 1)
		return patitos[i] + reconstruir(patitos, patin, i + 1, j) + patitos[i];
	else
		return patitos[j] + reconstruir(patitos, patin, i, j - 1) + patitos[j];
}

bool resuelveCaso() {
	string patitos;

	cin >> patitos;
	if (!cin)
		return false;

	int n = patitos.length();
	Matriz<int> patindromo(n, n, -1);

	cout << patin_rec(patitos, 0, n - 1, patindromo) << " ";
	cout << reconstruir(patitos, patindromo, 0, n - 1) << '\n';

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