// Alberto Bañegil

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

const int INF = 1000000000;

struct Objeto {
	int profundidad;
	int cantidadOro;
};

int cazaTesoros(vector<Objeto> const& v, int i, int j, vector<vector<int>>& M) {
	if (M[i][j] != -1) // subproblema ya resuelto
		return M[i][j];
	if (i == 0 || j == 0)
		M[i][j] = 0;
	else if (v[i - 1].profundidad * 3 > j)
		M[i][j] = cazaTesoros(v, i - 1, j, M);
	else
		M[i][j] = max(cazaTesoros(v, i - 1, j, M),
		              cazaTesoros(v, i - 1, j - v[i - 1].profundidad * 3, M)
				      + v[i - 1].cantidadOro);

	return M[i][j];
}

bool resuelveCaso() {
	int T, N;

	cin >> T >> N;
	if (!cin)
		return false;

	vector<Objeto> v(N);
	for (int i = 0; i < N; i++)
		cin >> v[i].profundidad >> v[i].cantidadOro;

	vector<vector<int>> M(N + 1, vector<int>(T + 1, -1));
	cout << cazaTesoros(v, N, T, M) << '\n';

	int i = N, j = T, cont = 0;
	vector<bool> sol = vector<bool>(N, false);
	while (i > 0 && j > 0) {
		if (M[i][j] != M[i - 1][j]) {
			sol[i - 1] = true;
			j = j - v[i - 1].profundidad * 3;
			cont++;
		}
		--i;
	}

	cout << cont << '\n';
	for (int i = 0; i < N; i++)
		if (sol[i])
			cout << v[i].profundidad << " " << v[i].cantidadOro << '\n';
	cout << "---\n";

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