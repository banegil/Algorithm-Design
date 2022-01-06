
//
//  Digrafo.h
//
//  Implementaci�n de grafos dirigidos
//
//  Facultad de Inform�tica
//  Universidad Complutense de Madrid
//
//  Copyright (c) 2020  Alberto Verdejo
//

#ifndef DIGRAFO_H_
#define DIGRAFO_H_

#include <iostream>
#include <stdexcept>
#include <vector>

using Adys = std::vector<int>;  // lista de adyacentes a un v�rtice

class Digrafo {

	int _V;   // n�mero de v�rtices
	int _A;   // n�mero de aristas

	std::vector<std::vector<bool>> _adyMatriz;
public:

	/**
	 * Crea un grafo dirigido con V v�rtices.
	 */
	Digrafo(int V) : _V(V), _A(0), _adyMatriz(_V, std::vector<bool>(_V, false)) {}

	 /**
	  * Devuelve el n�mero de v�rtices del grafo.
	  */
	int V() const { return _V; }

	/**
	 * Devuelve el n�mero de aristas del grafo.
	 */
	int A() const { return _A; }

	/**
	 * A�ade la arista dirigida v-w al grafo.
	 * @throws domain_error si alg�n v�rtice no existe
	 */
	void ponArista(int v, int w) {
		if (v < 0 || v >= _V || w < 0 || w >= _V)
			throw std::domain_error("Vertice inexistente");
		++_A;
		_adyMatriz[v][w] = true;
	}


	bool hayArista(int v, int w) const {
		if (v < 0 || v >= _V || w < 0 || w >= _V)
			throw std::domain_error("Vertice inexistente");
		return _adyMatriz[v][w];
	}

	/**
	 * Devuelve la lista de adyacencia de v.
	 * @throws domain_error si v no existe
	 */
	Adys ady(int v) const {
		if (v < 0 || v >= _V)
			throw std::domain_error("Vertice inexistente");
		Adys res;
		for (int i = 0; i < _V; ++i) {
			if (_adyMatriz[v][i])
				res.push_back(i);
		}
		return res;
	}
};

/**
 * Para mostrar grafos por la salida est�ndar.
 */
inline std::ostream& operator<<(std::ostream& o, Digrafo const& g) {

	return o;
}


#endif /* DIGRAFO_H_ */