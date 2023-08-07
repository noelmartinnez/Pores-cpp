#ifndef _tporo_
#define _tporo_
#include <iostream>
using namespace std;

class TPoro{
    
    friend ostream& operator<<(ostream &,const TPoro &);
    
    private:
        int x,y;
        double volumen;
        char * color;
        
        
    public:    
        TPoro();
        TPoro(int,int,double);
        TPoro(int,int,double,const char *);
        TPoro(const TPoro &);
        TPoro & operator=(const TPoro &);
        ~TPoro();

        void Volumen(double);
        void Color(const char *);
        void Posicion(int,int);
        int PosicionX() const;
        int PosicionY() const;
        bool operator==(const TPoro &);
        bool operator!=(const TPoro &);
        bool EsVacio() const;
        double Volumen() const;
        char * Color() const;

};
    
#endif