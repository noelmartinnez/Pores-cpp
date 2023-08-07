#ifndef _tavlporo_
#define _tavlporo_

#include "tporo.h"
#include "tvectorporo.h"
#include <iostream>
using namespace std;

class TNodoAVL;

class TAVLPoro {
    friend class TNodoAVL;
    
    friend ostream & operator<<(ostream &os, const TAVLPoro &);
    
    private:
        TNodoAVL *raiz;
        
        void InordenAux(TVectorPoro &, int &) const;
        void PreordenAux(TVectorPoro &, int &) const;
        void PostordenAux(TVectorPoro &, int &) const;
        
        void Copiar(const TAVLPoro &);
        void Recorrido(TVectorPoro &, int) const;
        bool Hoja() const;
        
        int ValorFE();
        void Equilibrar();
        TPoro Ordenar()const;
        bool InsertarAux(TPoro &,bool);
        bool BorrarAux(TPoro &);
        void RotarDD();
        void RotarII();
        void RotarID();
        void RotarDI();
	
    public:
        TAVLPoro();
        TAVLPoro(const TAVLPoro &);
        ~TAVLPoro();
        TAVLPoro & operator=(const TAVLPoro &);
        
        bool operator==(const TAVLPoro &) const;
        bool operator!=(const TAVLPoro &) const;
        bool EsVacio() const;
        bool Insertar(TPoro &);
        bool Buscar(const TPoro &) const;
        bool Borrar(TPoro &);
        
        int Altura() const;
        TPoro Raiz() const;
        int Nodos() const;
        int NodosHoja() const;
        
        TVectorPoro Inorden() const;
        TVectorPoro Preorden() const;
        TVectorPoro Postorden() const;
};	

class TNodoAVL {
    friend class TAVLPoro;
    
    private:
        TPoro item;
        TAVLPoro iz, de;
        int fe;
	
    public:
        TNodoAVL();
        TNodoAVL(const TNodoAVL &);
        ~TNodoAVL();
        TNodoAVL & operator=(const TNodoAVL &);
};

#endif