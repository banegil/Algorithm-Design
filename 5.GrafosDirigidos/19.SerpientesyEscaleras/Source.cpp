
// Alberto Bañegil

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>


using namespace std;

class SerpientesYEscaleras {
public:
    SerpientesYEscaleras(const int n, const int k, const vector<int>& atajs) : n(n), atajos(atajs), dist(n* n) {
        int w;
        queue<int> q;
        vector<bool> visitados(n * n, false);
        dist[0] = 0; visitados[0] = true;
        q.push(0);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (int i = 1; i <= k && v + i < n * n; i++) {
                w = v + i;
                if (atajos[w] != 0) w = atajos[w];
                if (!visitados[w]) {
                    visitados[w] = true;
                    dist[w] = dist[v] + 1;
                    q.push(w);
                }

            }
        }
    }

    int saltos() {
        return dist[n * n - 1];
    }

private:
    int n;
    vector<int> dist;
    vector<int> atajos;

};


// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int n, k, s, e, in, out;


    cin >> n >> k >> s >> e;

    if (n == 0)  // fin de la entrada
        return false;

    vector<int> atajos(n * n, 0);

    for (int i = 0; i < s + e; i++) {
        cin >> in >> out;
        atajos[in - 1] = out - 1;
    }

    SerpientesYEscaleras sol(n, k, atajos);

    cout << sol.saltos() << "\n";

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
