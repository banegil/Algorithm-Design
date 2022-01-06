
// Alberto Bañegil

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

/*iterativa ascendente
void subsecuencia(string const& A, string const& B, vector<vector<int>>& matriz) {
	for (int i = 1; i < A.length(); i++) {
		for (int j = 1; j < B.length(); j++) {
			if (A[i - 1] == B[j - 1])
				matriz[i][j] = matriz[i - 1][j - 1] + 1;
			else
				matriz[i][j] = max(matriz[i - 1][j], matriz[i][j - 1]);
		}
	}
}
*/

int subsecuencia(string const& A, string const& B, vector<vector<int>>& matriz, int i, int j) {
	int& res = matriz[i][j];
	if (res == -1) {
		if (i == A.length() || j == B.length()) res = 0;
		else if (A[i] == B[j])
			res = subsecuencia(A, B, matriz, i + 1, j + 1) + 1;
		else
			res = max(subsecuencia(A, B, matriz, i + 1, j),
					  subsecuencia(A, B, matriz, i, j + 1));
	}
	return res;
}

string reconstruir_rec(string const& A, string const& B, vector<vector<int>>& matriz, int i, int j) {
	if (i == A.length() || j == B.length()) return "";
	if (A[i] == B[j])
		return A[i] + reconstruir_rec(A, B, matriz, i + 1, j + 1);
	else if (matriz[i][j] == matriz[i + 1][j])
		return reconstruir_rec(A, B, matriz, i + 1, j);
	else
		return reconstruir_rec(A, B, matriz, i, j + 1);
}

bool resuelveCaso() {
	string A, B;

	cin >> A >> B;
	if (!cin)
		return false;

	vector<vector<int>> matriz(A.length() + 1, vector<int>(B.length() + 1, -1));
	subsecuencia(A, B, matriz, 0, 0);

	cout << reconstruir_rec(A, B, matriz, 0, 0) << '\n';

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