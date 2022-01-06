// Alberto Bañegil

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;

const int INF = 1000000000;

void resolver(const int& N, const int& PMax, const int& PMin, vector<int> potencia, vector<int> coste)
{
	vector<vector<int>> bombillas(N + 1, vector<int>(PMax + 1, INF));

	for (int i = 0; i < N + 1; i++)
		bombillas[i][0] = 0;

	for (int i = 1; i <= N; i++){
		for (int j = 1; j <= PMax; j++){
			if (potencia[i] > j)
				bombillas[i][j] = bombillas[i - 1][j];
			else
				bombillas[i][j] = min(bombillas[i - 1][j], bombillas[i][j - potencia[i]] + coste[i]);
		}
	}

	int minimo = bombillas[N][PMin];
	int miniTemp = minimo;
	int pot = PMin;
	for (int i = PMin + 1; i <= PMax; i++)
	{
		minimo = min(minimo, bombillas[N][i]);
		if (minimo != miniTemp) {
			pot = i;
			miniTemp = minimo;
		}
	}

	if (minimo == INF)
		cout << "IMPOSIBLE\n";
	else
		cout << minimo << " " << pot << "\n";


}

bool resuelveCaso() {
	int N, PMax, PMin;

	cin >> N >> PMax >> PMin;
	if (!cin)
		return false;

	vector<int> potencia(N + 1, 0);
	for (int i = 1; i <= N; i++)
		cin >> potencia[i];

	vector<int> coste(N + 1, 0);
	for (int i = 1; i <= N; i++)
		cin >> coste[i];

	resolver(N, PMax, PMin, potencia, coste);

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