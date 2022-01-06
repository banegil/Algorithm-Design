// Alberto Bañegil

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "EnterosInf.h"
using namespace std;

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta

/*
Caso Base :
  diana(i,0) = 0      1 <= i <= n
  diana(0,j) = +inf   0 < j <= L
Caso recursivo :
               / min(diana(i-1,j), diana(i-1,j-M[i-1] + 1))   j > M[i-1]
  diana(i,j) = |
               \ diana(i-1,j)                                 j < M[i-1]
*/
vector<int> diana(vector<int> const& M, int C) {
    int n = M.size();
    vector<EntInf> puntuaciones(C + 1, Infinito);
    puntuaciones[0] = 0;

    // calcular la matriz sobre el propio vector
    for (int i = 1; i <= n; ++i) 
        for (int j = M[i - 1]; j <= C; ++j) 
            puntuaciones[j] = min(puntuaciones[j], puntuaciones[j - M[i - 1]] + 1);

    // Reconstruccion solucion
    vector<int> sol;
    if (puntuaciones[C] != Infinito) {
        int i = n, j = C;
        while (j > 0) { 
            if (M[i - 1] <= j && puntuaciones[j] == puntuaciones[j - M[i - 1]] + 1) {
                sol.push_back(M[i - 1]);
                j = j - M[i - 1];
            }
            else 
                --i;
        }
    }

    return sol;
}

bool resuelveCaso() {
    int P, S;

    cin >> P >> S;
    if (!cin)
        return false;

    vector<int> v(S);
    for (int i = 0; i < S; i++)
        cin >> v[i];

    vector<int> sol(S);
    sol = diana(v, P);

    if (sol.empty())
        cout << "Imposible";
    else {
        cout << sol.size() << ": ";
        for (int i : sol)
            cout << i << " ";
    }
    cout << '\n';

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