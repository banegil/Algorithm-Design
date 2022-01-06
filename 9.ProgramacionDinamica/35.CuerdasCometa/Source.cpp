// Alberto Bañegil

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

/*
Caso Base :
  posible(i,0) = 1    0 <= i <= n
  posible(0,j) = 0    0 < j <= L
Caso recursivo :
                 / posible(i-1,j) || posible(i-1,j-longitudes[i-1])     j > longitudes[i-1]
  posible(i,j) = |
                 \ posible(i-1,j)                                       j < longitudes[i-1]
*/

/*
Caso Base :
  combinaicones(i,0) = 1    1 <= i <= n+1
  combinaicones(0,j) = 0    0 < j <= L
Caso recursivo :
                       / combinaicones(i+1,j) || combinaicones(i+1,j-longitudes[i-1])    j > longitudes[i-1]
  combinaicones(i,j) = |
                       \ combinaicones(i+1,j)                                            j < longitudes[i-1]
*/

/*
Caso Base :
  minCordeles(i,0) = 0      1 <= i <= n
  minCordeles(0,j) = +inf   0 < j <= L
Caso recursivo :
                     / min(minCordeles(i-1,j), minCordeles(i-1,j-longitudes[i-1] + 1))   j > longitudes[i-1]
  minCordeles(i,j) = |
                     \ minCordeles(i-1,j)                                                j < longitudes[i-1]
*/

/*
Caso Base :
  minCoste(i,0) = 0      1 <= i <= n
  minCoste(0,j) = +inf   0 < j <= L
Caso recursivo :
                  / min(minCoste(i-1,j), minCoste(i-1,j-longitudes[i-1] + precios[i-1]))   j > longitudes[i-1]
  minCoste(i,j) = |
                  \ minCoste(i-1,j)                                                        j < longitudes[i-1]
*/


#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta

long long combinaciones(vector<int> const& longitudes, int L) {
    int n = longitudes.size();
    vector<long long> cordeles(L + 1);
    cordeles[0] = 1;

    // calcular la matriz sobre el propio vector
    for (int i = 1; i <= n; ++i)
        for (int j = L; j >= longitudes[i - 1]; j--)
            cordeles[j] += cordeles[j - longitudes[i - 1]];

    return cordeles[L];
}

long long minCordeles(vector<int> const& longitudes, int L) {
    int n = longitudes.size();
    vector<long long> cordeles(L + 1, 1000000000000000000);
    cordeles[0] = 0;

    // calcular la matriz sobre el propio vector
    for (int i = 1; i <= n; ++i)
        for (int j = L; j >= longitudes[i - 1]; j--)
            cordeles[j] = min(cordeles[j], cordeles[j - longitudes[i - 1]] + 1);

    return cordeles[L];
}

long long minPrecios(vector<int> const& longitudes, vector<int> const& precios, int L) {
    int n = longitudes.size();
    vector<long long> cordeles(L + 1, 1000000000000000000);
    cordeles[0] = 0;

    // calcular la matriz sobre el propio vector
    for (int i = 1; i <= n; ++i)
        for (int j = L; j >= longitudes[i - 1]; j--)
            cordeles[j] = min(cordeles[j], cordeles[j - longitudes[i - 1]] + precios[i - 1]);

    return cordeles[L];
}

bool resuelveCaso() {
    int N, L, l, p = 0;

    cin >> N >> L;
    if (!cin)
        return false;

    vector<int> longitudes(N), precios(N);
    for (int i = 0; i < N; i++)
        cin >> longitudes[i] >> precios[i];

    long long c = combinaciones(longitudes, L);
    if (c == 0)
        cout << "NO\n";
    else
        cout << "SI " << c << " " << minCordeles(longitudes, L) << " " << minPrecios(longitudes, precios, L) << '\n';

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
