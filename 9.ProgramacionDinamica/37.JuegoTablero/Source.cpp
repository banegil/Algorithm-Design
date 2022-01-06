// Alberto Bañegil

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta


int juegoTablero(vector<vector<int>>& tablero, int& colIni, const int& N) {

    for (int i = 1; i <= N; ++i) 
        for (int j = 1; j <= N; ++j)
            tablero[i][j] = max(tablero[i - 1][j - 1], max(tablero[i - 1][j], tablero[i - 1][j + 1])) + tablero[i][j];

    int sumaTotal = tablero[N][0];

    for (int i = 1; i <= N; ++i) 
        if (sumaTotal < tablero[N][i]) {
            sumaTotal = tablero[N][i];
            colIni = i;
        }

    return sumaTotal;
}


bool resuelveCaso() {
    int N, col = 0;
    cin >> N;

    if (!cin) return false;

    vector<vector<int>> mat(N + 1, vector<int>(N + 2));
    for (int i = 1; i <= N; ++i) 
        for (int n = 1; n <= N; ++n)
            cin >> mat[i][n];

    cout << juegoTablero(mat, col, N) << " ";
    cout << col << '\n';

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