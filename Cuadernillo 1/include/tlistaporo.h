#ifndef _tlistaporo_
#define _tlistaporo_

#include "tporo.h"
#include "tvectorporo.h"
#include <iostream>
using namespace std;

class TListaNodo{    
    friend class TListaPosicion;
    friend class TListaPoro;

    private:
        TPoro e;        
        TListaNodo *anterior;
        TListaNodo *siguiente;
        TListaNodo* DevAnterior();
        TListaNodo* DevSiguiente();
        
    public:    
        TListaNodo();
        TListaNodo(const TListaNodo &);
        ~TListaNodo();
        TListaNodo & operator=(const TListaNodo &);

};

class TListaPosicion{
    friend class TListaPoro;   
    friend class TListaNodo; 

    private:
        TListaNodo *pos;

    public:
        TListaPosicion();
        TListaPosicion(const TListaPosicion &);
        ~TListaPosicion();
        TListaPosicion& operator=(const TListaPosicion &);

        bool operator==(const TListaPosicion &) const;
        TListaPosicion Anterior() const;
        TListaPosicion Siguiente() const;
        bool EsVacia() const;

};
    
class TListaPoro{
    friend class TListaPosicion;
    friend class TListaNodo; 
    
    friend ostream & operator<<(ostream &,const TListaPoro &);

    private:
        TListaNodo *primero;
        TListaNodo *ultimo;
        void vaciarMemoria();

    public:
        TListaPoro();
        TListaPoro(const TListaPoro &);
        ~TListaPoro();
        TListaPoro & operator=(const TListaPoro &);

        bool operator==(TListaPoro &);
        TListaPoro operator+(TListaPoro &);
        TListaPoro operator-(TListaPoro &);
        bool EsVacia() const;
        bool Insertar(const TPoro &);
        bool Borrar(const TPoro &);                 
        bool Borrar(const TListaPosicion &);          //apunta directamente al que hay que eliminar
        TPoro Obtener(const TListaPosicion &) const;
        bool Buscar(const TPoro &) const;
        int Longitud() const;
        TListaPosicion Primera() const;
        TListaPosicion Ultima() const;
        TListaPoro ExtraerRango(int, int);
};

#endif