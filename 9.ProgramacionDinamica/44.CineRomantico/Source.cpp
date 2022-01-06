// Alberto Bañegil

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

int cine(vector<pair<int,int>>& peliculas, int N) {
	vector <int> v(1451, 0);

	for (int i = 1; i < N + 1; ++i)
		for (int j = 1450; j > 0; --j) 
			if (j >= peliculas[i - 1].first + peliculas[i - 1].second + 10)
				v[j] = max(v[j], v[peliculas[i - 1].first] + peliculas[i - 1].second);

	return v[1450];
}

bool resuelveCaso() {
	int N, horas, minutos, dur, ini;
	char c;

	cin >> N;
	if (N == 0)
		return false;

	vector<pair<int, int>> peliculas;
	for (int i = 0; i < N; ++i) {
		cin >> horas >> c >> minutos >> dur;
		ini = horas * 60 + minutos;
		peliculas.push_back({ ini, dur });
	}

	sort(peliculas.begin(), peliculas.end());
	cout << cine(peliculas, N) << '\n';

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