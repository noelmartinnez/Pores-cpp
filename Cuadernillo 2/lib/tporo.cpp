#include "tporo.h"
#include <iostream>
#include <ctype.h>
#include <cstring>
#include <string.h>
#include <stdio.h>
using namespace std;

TPoro::TPoro(){
    x=0;
    y=0;
    volumen=0;
    color=NULL;
}

TPoro::TPoro(int x, int y, double volumen){
    this->x=x;
    this->y=y;
    this->volumen=volumen;
    this->color=NULL;
}

TPoro::TPoro(int x, int y, double volumen,const char* color){
    this->x=x;
    this->y=y;
    this->volumen=volumen;

    if(color == NULL){
        this->color=NULL;
    }
    else{
        this->color=new char[strlen(color+1)];
        
        if(this->color == NULL){
            cerr << "Error: Color its NULL" << endl;
        }
        else{
            strcpy(this->color,color);

            for(int i=0; color[i] != '\0';i++){
                this->color[i]=tolower(this->color[i]);
            }
        }
    }
    
}

TPoro & TPoro::operator=(const TPoro &poro){
    if(this != &poro){
        (*this).~TPoro();

        x=poro.PosicionX();
        y=poro.PosicionY();
        volumen=poro.Volumen();

        if(color != NULL){
            delete color;
        }
        else if(poro.color == NULL){
            color = NULL;
        }
        else{
            this->color=new char[strlen(poro.color+1)];

            if(this->color == NULL){
                cerr << "Error: Color its NULL" << endl;
            }
            else{
                strcpy(this->color,poro.color);
            }
        }
    }

    return *this;   //aquí se devuelve el propio objeto
}

TPoro::TPoro(const TPoro &poro){
    this->x=poro.PosicionX();
    this->y=poro.PosicionY();
    this->volumen=poro.Volumen();
    
    if(poro.color != NULL){
        this->color=new char[strlen(poro.color+1)];

        if(this->color == NULL){
            cerr << "Error: Color its NULL" << endl;
        }
        else{
            strcpy(this->color,poro.color);
        }        
    }
    else{
        color = NULL;
    }
}

TPoro::~TPoro(){
    x=y=volumen=0;
    if(this->color != NULL){
        delete [] color;
    }
    color=NULL;
}

int TPoro::PosicionX() const{
    return x;
}

int TPoro::PosicionY() const{
    return y;
}

char * TPoro::Color() const{
    return color;
}

double TPoro::Volumen() const{
    return volumen;
}

void TPoro::Posicion(int x, int y){
    this->x=x;
    this->y=y;
}

void TPoro::Color(const char * color){
    if(color == NULL){
        this->color=NULL;
    }
    else{
        this->color=new char[strlen(color+1)];

        if(this->color == NULL){
            cerr << "Error: Color its NULL" << endl;
        }
        else{
            strcpy(this->color,color);

            for(int i=0; color[i] != '\0';i++){
                this->color[i]=tolower(this->color[i]);
            }
        }
    }
}

void TPoro::Volumen(double volumen){
    this->volumen=volumen;
}

bool TPoro::EsVacio() const{
    if((x==0)&&(y==0)&&(volumen==0)&&(color==NULL)){
        return true;
    }

    return false;
}

bool TPoro::operator==(const TPoro &poro){
    bool iguales=false;
    
    if(color==NULL && poro.color==NULL){
        iguales=true;
    }
    else if(color==NULL || poro.color==NULL){
        iguales=false;
    }
    else if(strcmp(color,poro.color)==0){
        iguales=true;
    }

    return (iguales && poro.PosicionX()==this->PosicionX() && poro.PosicionY()==this->PosicionY()
    && poro.Volumen()==this->Volumen());
}

bool TPoro::operator!=(const TPoro &poro){
    return !(*this==poro);
}

ostream& operator<<(ostream &os,const TPoro &poro){
    if(!poro.EsVacio()){
        os.setf(ios::fixed);
        os.precision( 2 );
        os<<"("<<poro.x<<", "<<poro.y<<") "<<poro.volumen<<" ";
        if(poro.color!=NULL)
        os<<poro.color;
        else
        os<<"-";
    }
    else{
        os << "()";
    }

    return os;
}