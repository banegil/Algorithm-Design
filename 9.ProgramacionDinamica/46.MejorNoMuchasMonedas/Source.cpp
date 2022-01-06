
// Alberto Bañegil

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int INTMAX = 1000000000;

void monedas_pd(vector<pair<int, int>>& v, vector<int>& monedas, int& N, int& C) {
	for (int i = 1; i <= N; i++) {
		for (int j = C; j >= 0; j--) {
			int aux = INTMAX;
			for (int k = 0; k <= v[i].second && k * v[i].first <= j; k++) 
				if (monedas[j - k * v[i].first] != INTMAX)
					aux = min(aux, monedas[j - k * v[i].first] + k);
			monedas[j] = aux;
		}
	}
}

bool resuelveCaso() {
	int N, valor, C;

	cin >> N;

	if (!cin)
		return false;

	vector<pair<int, int>> v;
	v.push_back({ 0, 0 });

	for (int i = 1; i <= N; i++) {
		cin >> valor;
		v.push_back({ valor, 0 });
	}

	for (int i = 1; i <= N; i++) 
		cin >> v[i].second;

	cin >> C;

	vector<int> monedas(C + 1);
	for (int j = 1; j < C + 1; j++) 
		monedas[j] = INTMAX;

	monedas_pd(v, monedas, N, C);

	if (monedas[C] == INTMAX)
		cout << "NO\n";
	else
		cout << "SI " << monedas[C] << '\n';

	return true;
}

int main() {
#ifndef DOMJUDGE
    ifstream in("casos.txt");
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
    while (resuelveCaso());
#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}