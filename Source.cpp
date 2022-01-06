
// Alberto Bañegil

#include <iostream>
#include <fstream>
#include <algorithm>
#include <climits>
#include "PriorityQueue.h" 

using namespace std;

struct Trabajador {
    vector<int> tiempoTrabajo;
};

struct Nodo {
    vector<int> trabajos;
    int k;
    int tiempoAcumulado;
    int tiempoEstimado;
    bool operator<(Nodo const& otro) const {
        return tiempoEstimado < otro.tiempoEstimado;
    }
};

/*
int calculo_estimado(const vector<int>& tiemposMin, const Nodo& X) {
    int estimado = X.tiempoAcumulado;
    for (int i = X.k + 1; i < tiemposMin.size(); i++)
        estimado += tiemposMin[i];
    return estimado;
}
*/

void precalculacion_tiemposMin(const vector<Trabajador>& trabajadores, vector<int>& tiemposMinimos) {
    int N = trabajadores.size();
    int tiempoMin = trabajadores[N - 1].tiempoTrabajo[0];

    for (int j = 1; j < N; j++) 
        tiempoMin = min(trabajadores[N - 1].tiempoTrabajo[j], tiempoMin);

    tiemposMinimos[N - 1] = tiempoMin;

    for (int i = N - 2; i >= 0; i--) {
        tiempoMin = trabajadores[i].tiempoTrabajo[0];
        for (int j = 1; j < N; j++) 
            tiempoMin = min(trabajadores[i].tiempoTrabajo[j], tiempoMin);
        tiemposMinimos[i] = tiempoMin + tiemposMinimos[i + 1];
    }
}

int min_tiempo(const vector<Trabajador>& trabajadores) {
    int N = trabajadores.size();
    int tiempoMejor = INT_MAX;
    vector<int> tiemposMinimos(N);

    precalculacion_tiemposMin(trabajadores, tiemposMinimos);

    Nodo Y;
    Y.trabajos = vector<int>(N, -1);
    Y.k = -1;
    Y.tiempoAcumulado = 0;
    Y.tiempoEstimado = tiemposMinimos[0];
    PriorityQueue<Nodo> cola;
    cola.push(Y);

    while (!cola.empty() && cola.top().tiempoEstimado < tiempoMejor) {
        Y = cola.top(); cola.pop();
        Nodo X(Y);
        ++X.k;
        for (int i = 0; i < N; i++) {
            if (Y.trabajos[i] == -1) {
                X.trabajos[i] = X.k;
                X.tiempoAcumulado = Y.tiempoAcumulado + trabajadores[X.k].tiempoTrabajo[i];
                if (X.k == N - 1) {
                    if (tiempoMejor > X.tiempoAcumulado) 
                        tiempoMejor = X.tiempoAcumulado;
                }
                else {
                    X.tiempoEstimado = X.tiempoAcumulado + tiemposMinimos[X.k + 1];
                    cola.push(X);
                }
                X.trabajos[i] = -1;
            }
        }
    }
    return tiempoMejor;
}

bool resuelveCaso() {
    int n;

    cin >> n;
    if (n == 0) 
        return false;

    vector<Trabajador> trabajadores(n);
    vector<int> tiemposTrabajos(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) 
            cin >> tiemposTrabajos[j];
        trabajadores[i].tiempoTrabajo = tiemposTrabajos;
    }

    cout << min_tiempo(trabajadores) << "\n";

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
