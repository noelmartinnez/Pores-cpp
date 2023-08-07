#ifndef _tvectorporo_
#define _tvectorporo_

#include <iostream>
using namespace std;

#include "tporo.h"

class TVectorPoro{
    
    friend ostream& operator<<(ostream &,const TVectorPoro &);
    
    private:
        int dimension;
        TPoro *datos;
        TPoro error;
        
    public:    
        TVectorPoro();
        TVectorPoro(int);
        TVectorPoro(const TVectorPoro &);
        ~TVectorPoro();
        TVectorPoro & operator=(const TVectorPoro &);

        bool operator==(const TVectorPoro &);
        bool operator!=(const TVectorPoro &);
        TPoro & operator[](int);
        TPoro operator[](int) const;
        int Longitud() const;
        int Cantidad() const;
        bool Redimensionar(int);

};
    
#endif