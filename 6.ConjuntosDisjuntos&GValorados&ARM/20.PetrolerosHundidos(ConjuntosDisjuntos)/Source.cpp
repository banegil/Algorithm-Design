
// Alberto Bañegil

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include "ConjuntosDisjuntos.h"

using namespace std;
using Mapa = vector<vector<char>>;

class Solucion {
    int F, C, maximo;
    ConjuntosDisjuntos c;
    vector<vector<bool>> visitado;
    const vector<pair<int, int>> dirs = { {1, 0}, {0, 1}, {-1, 0}, {0, -1}, {-1, -1}, {1, 1}, {-1, 1}, {1, -1} };

    bool correcta(int i, int j) const {
        return 0 <= i && i < F && 0 <= j && j < C;
    }

    int dfs(const Mapa &mapa, int i, int j) {
        visitado[i][j] = true;
        int tam = 1;
        for (auto d : dirs) {
            int ni = i + d.first;
            int nj = j + d.second;
            if (correcta(ni, nj) && !visitado[ni][nj] && mapa[ni][nj] == '#') {
                c.unir(i * C + j, ni * C + nj);
                tam += dfs(mapa, ni, nj);
            }
        }
        return tam;
    }

public:
    Solucion(const Mapa &mapa, int rows, int cols) : c(rows * cols) , visitado(rows, vector<bool>(cols, false)),
        F(rows), C(cols), maximo(0) {

        for (int i = 0; i < F; i++) 
            for (int j = 0; j < C; j++) 
                if (!visitado[i][j] && mapa[i][j] == '#')
                    maximo = max(maximo, dfs(mapa, i, j));
    }

    void add(const Mapa &mapa, int i, int j) {
        for (auto d : dirs) {
            int ni = i + d.first;
            int nj = j + d.second;
            if (correcta(ni, nj) && mapa[ni][nj] == '#')
                c.unir(i * C + j, ni * C + nj);
        }
        maximo = max(maximo, c.cardinal(i * C + j));
    }

    int maxMancha() {
        return maximo;
    }
};

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int F, C, N, fila, columna;
    char elem, b;

    cin >> F >> C;
    if (!cin)
        return false;

    Mapa mapa(F, vector<char>(C, ' '));
    for (int i = -1; i < F; ++i) {
        cin.get(elem);
        int j = 0;
        while(elem != '\n'){
            mapa[i][j] = elem;
            cin.get(elem);
            j++;
        }
    }

    Solucion s(mapa, F, C);

    cin >> N;
    cout << s.maxMancha() << " ";
    for (int i = 0; i < N; i++) {
        cin >> fila >> columna;
        mapa[fila - 1][columna - 1] = '#';
        s.add(mapa, fila - 1, columna - 1);
        cout << s.maxMancha() << " ";
    }

    cout << '\n';

    return true;
}

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
