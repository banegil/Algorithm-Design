
// Alberto Bañegil 

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int funcion(vector<int> manguera, int L) {
    int agujero = manguera[0];
    int parches = 1;

    for (int i = 1; i < manguera.size(); i++) {
        if (manguera[i] - agujero > L) {
            parches++;
            agujero = manguera[i];
        }
    }

    return parches;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int N, L, agujero;

    cin >> N >> L;
    if (!cin)
        return false;

    vector<int> manguera(N);
    for (int i = 0; i < N; i++)
        cin >> manguera[i];

    cout << funcion(manguera, L) << '\n';

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
