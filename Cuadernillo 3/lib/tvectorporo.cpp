#include "tvectorporo.h"
#include <iostream>
using namespace std; 

TVectorPoro::TVectorPoro(){     
    this->dimension=0;
    this->datos=NULL;
}

TVectorPoro::TVectorPoro(int dimen){
    if(dimen <= 0){
        this->dimension=0;
        this->datos=NULL;
    }
    else{
        this->dimension=dimen;
        this->datos= new TPoro[dimension];
    }
}

TVectorPoro::TVectorPoro(const TVectorPoro &obj){
    if(obj.dimension == 0){
        this->dimension=0;
        this->datos=NULL;
    }
    else{
        this->dimension=obj.dimension;
        this->datos= new TPoro[this->dimension];

        for(int i=1;i <= this->dimension;i++){
            this->datos[i] = obj.datos[i];
        }
    }

}

TVectorPoro::~TVectorPoro(){
    this->dimension=0;

    if(this->datos != NULL){
        delete [] datos;
        this->datos=NULL;
    }
}

int TVectorPoro::Longitud() const{
    return this->dimension;
}

int TVectorPoro::Cantidad() const{
    int cantidad=0;

    for(int i=0;i<this->dimension;i++){
        if(this->datos[i] != this->error){
            cantidad++;
        }
    }

    return cantidad;
}

TPoro & TVectorPoro::operator[](int numero){
    if((numero >= 1) && (numero <= this->dimension)){
        return this->datos[numero-1];
    }
    else{
        return this->error;
    }
}

TPoro TVectorPoro::operator[](int numero) const{
    if((numero >= 1) && (numero <= this->dimension)){
        return this->datos[numero-1];
    }
    else{
        TPoro error;
        return error;
    } 
}

bool TVectorPoro::operator==(const TVectorPoro &obj){
    if(this->dimension == obj.dimension){
        for(int i=0;i<this->dimension;i++){
            if(this->datos[i] != obj.datos[i]){
                return false;
            }
        }

        return true;
    }
    else{
        return false;
    }
}

bool TVectorPoro::operator!=(const TVectorPoro &obj){
    if(this->dimension != obj.dimension){
        for(int i=0;i<this->dimension;i++){
            if(this->datos[i] == obj.datos[i]){
                return false;
            }
        }

        return true;
    }
    else{
        return false;
    }
}

TVectorPoro & TVectorPoro::operator=(const TVectorPoro &obj){
    if(this != &obj){
        (*this).~TVectorPoro();
        this->dimension=obj.Longitud();
        this->datos=new TPoro[this->dimension];

        for(int i=0; i<this->dimension ;i++){
            this->datos[i]=obj[i+1];
        }
    }

    return *this;
}

bool TVectorPoro::Redimensionar(int dimension){
    TPoro *vectorVacio = new TPoro();

    if(dimension <= 0){
        return false;
    }

    TPoro *auxiliar = new TPoro[dimension];

    if(dimension == this->dimension){
        return false;
    }
    else if(dimension > this->dimension){
        for(int i=0; i<dimension ;i++){
            if(i < this->dimension){
                auxiliar[i] = this->datos[i];
            }
            else{
                auxiliar[i] = (*vectorVacio);
            }
        }

        (*this).~TVectorPoro();
        this->dimension=dimension;
        this->datos=auxiliar;

        return true;
    }
    else{
        for(int i=0; i<dimension ;i++){
            auxiliar[i] = this->datos[i];
        }

        (*this).~TVectorPoro();
        this->dimension=dimension;
        this->datos=auxiliar;

        return true;
    }
}

ostream& operator<<(ostream &os,const TVectorPoro &obj){
    os<<"[";
    for(int i=1; i<=obj.Longitud() ;i++){
        os << i << " " << obj[i];
        
        if(i+1 <= obj.Longitud()){
            os<<" ";
        }
    }
    os<<"]";

    return os;
}