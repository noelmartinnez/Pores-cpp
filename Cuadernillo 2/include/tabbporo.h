#ifndef _tabbporo_
#define _tabbporo_

#include "tporo.h"
#include "tvectorporo.h"
#include <iostream>
using namespace std;

class TNodoABB;     //Para poder usar TNodoABB antes de declarar la clase

class TABBPoro {
    friend class TNodoABB;

    friend ostream & operator<<(ostream &, const TABBPoro &);

    private:
		TNodoABB *nodo;

		void InordenAux(TVectorPoro &, int &) const;
		void PreordenAux(TVectorPoro &, int &) const;
		void PostordenAux(TVectorPoro &, int &) const;

		void Copiar(const TABBPoro &);
                void Recorrido(TVectorPoro &, int) const;
                bool Hoja() const;

	public:
		TABBPoro();
		TABBPoro(const TABBPoro &);
		~TABBPoro();
		TABBPoro & operator=(const TABBPoro &);

		bool operator==(const TABBPoro &) const;
		bool EsVacio() const;
		bool Insertar(const TPoro &);
		bool Borrar(const TPoro &);
		bool Buscar(const TPoro &) const;

		TPoro Raiz() const;
		int Altura() const;
		int Nodos() const;
		int NodosHoja() const;

		TVectorPoro Inorden() const;
		TVectorPoro Preorden() const;
		TVectorPoro Postorden() const;
		TVectorPoro Niveles() const;

		TABBPoro operator+(const TABBPoro &);
		TABBPoro operator-(const TABBPoro &);
};

class TNodoABB {
    friend class TABBPoro;

    private:
		TPoro item;
		TABBPoro iz,de;

	public:
		TNodoABB();
		TNodoABB(const TNodoABB &);
		~TNodoABB();
		TNodoABB & operator=(const TNodoABB &);
};

#endif