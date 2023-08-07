#include "tlistaporo.h"
#include <iostream>
using namespace std; 

TListaNodo::TListaNodo() : e(){
    anterior=NULL;
    siguiente=NULL;
}

TListaNodo::TListaNodo(const TListaNodo &object){
    e=object.e;
    this->anterior=object.anterior;
    this->siguiente=object.siguiente;
}

TListaNodo::~TListaNodo(){
    this->anterior=NULL;    //estos son punteros y solo hace falta asignarlos a NULL
    this->siguiente=NULL;
    this->e.~TPoro();       //es un objeto y hay que destruirlo con el destructor de su clase
}

TListaNodo & TListaNodo::operator=(const TListaNodo &object){
    if(this != &object){
        (*this).~TListaNodo();
        this->e=object.e;
        this->anterior=object.anterior;
        this->siguiente=object.siguiente;
    }

    return *this;
}

TListaNodo* TListaNodo::DevSiguiente(){
    return siguiente;
}

TListaNodo* TListaNodo::DevAnterior(){
    return anterior;
}

TListaPosicion::TListaPosicion(){
    pos=NULL;
}

bool TListaPosicion::EsVacia() const{
    if(pos==NULL){
        return true;
    }
    else{
        return false;
    }
}

TListaPosicion::TListaPosicion(const TListaPosicion &object){
    this->pos=object.pos;
}

TListaPosicion::~TListaPosicion(){
    pos=NULL;
}

TListaPosicion & TListaPosicion::operator=(const TListaPosicion &object){
    if(this != &object){            //esto es para evitar que asigne un objeto a él mismo
        (*this).~TListaPosicion();
        this->pos=object.pos;
    }

    return *this;
}

bool TListaPosicion::operator==(const TListaPosicion &object) const{
    if(this->pos == object.pos){
        return true;
    }
    else{
        return false;
    }
}

TListaPosicion TListaPosicion::Anterior() const{
    TListaPosicion posicion;

    if(pos->DevAnterior() == NULL){ 
        return posicion;
    }
    else{
        posicion.pos = pos->DevAnterior(); 
        return posicion;
    }
}

TListaPosicion TListaPosicion::Siguiente() const{
    TListaPosicion posicion;

    if(pos->DevSiguiente() == NULL){ 
        return posicion;
    }
    else{
        posicion.pos = pos->DevSiguiente(); 
        return posicion;
    }
}

TListaPoro::TListaPoro(){
    primero = NULL;
    ultimo = NULL;
}

TListaPoro::TListaPoro(const TListaPoro &object){
    this->primero = NULL;
    this->ultimo = NULL;

    for(TListaPosicion i = object.Primera(); i.EsVacia() == false ; i=i.Siguiente()){
        this->Insertar(i.pos->e);
    }
}

void TListaPoro::vaciarMemoria(){
    TListaNodo *sustituto;

    while(primero != NULL){
        sustituto = primero->DevSiguiente();
        delete primero;
        primero = sustituto;
    }
}

TListaPoro::~TListaPoro(){
    vaciarMemoria();
}

TListaPoro & TListaPoro::operator=(const TListaPoro &object){
    if(this != &object){
        this->~TListaPoro();
        for(TListaPosicion i = object.Primera(); i.EsVacia() == false; i = i.Siguiente()){ 
            this->Insertar(i.pos->e);
        }   
    }

    return (*this);
}

bool TListaPoro::operator==(TListaPoro &object){
    TListaPosicion propia = this->Primera();
    TListaPosicion deObject = object.Primera();

    if(this->Longitud() == object.Longitud()){
        do{
            if((propia.EsVacia() == false) && (deObject.EsVacia() == false)){
                if(propia.pos->e != deObject.pos->e){
                    return false;
                }
                
                propia = propia.Siguiente();
                deObject = deObject.Siguiente();
            }
        }while(propia.EsVacia() == false);

        return true;
    }
    else{
        return false;
    }
} 

bool TListaPoro::EsVacia() const{
    if(primero == NULL && ultimo == NULL){
        return true;
    }
    else{
        return false;
    }
}

TListaPoro TListaPoro::operator+(TListaPoro &lista){
    TListaPoro *operacion = new TListaPoro(*this);

    for(TListaNodo *i = lista.primero; i != NULL ; i=i->DevSiguiente()){
        operacion->Insertar(i->e);
    }

    return (*operacion);
}

TListaPoro TListaPoro::operator-(TListaPoro &lista){
    TListaPoro *operacion = new TListaPoro(*this);

    for(TListaNodo *i = lista.primero; i != NULL ; i=i->DevSiguiente()){
        operacion->Borrar(i->e);
    }

    return (*operacion);
}

bool TListaPoro::Insertar(const TPoro &object){       
    TListaNodo *nodo = new TListaNodo();   
    TListaNodo *aux = new TListaNodo();      
    nodo->e = object;

    if(Buscar(object)){
        return false;
    }

    if(this->EsVacia()){    //está vacía
        nodo->anterior = NULL;
        nodo->siguiente = NULL;
        this->primero = nodo;
        this->ultimo = nodo;
        
        return true;
    }
    
    TListaNodo *pivote = new TListaNodo(); 

    for(pivote=this->primero; pivote != NULL ; pivote = pivote->DevSiguiente()){
        if(pivote->e == nodo->e){
            return false;
        }
        
        else if(nodo->e.Volumen() < primero->e.Volumen() && nodo->e != pivote->e){    //al principio de la lista
            if(this->primero->DevSiguiente() == NULL){
                this->ultimo=this->primero;
            }
            
            nodo->siguiente = this->primero;
            this->primero->anterior = nodo;
            this->primero = nodo;
            
            return true;
        }

        else if((nodo->e.Volumen() < pivote->e.Volumen()) && nodo->e != pivote->e){                        //los volumenes son iguales                                 
            aux = pivote->DevAnterior();
            nodo->siguiente = pivote;
            nodo->anterior = pivote->DevAnterior();
            aux->siguiente = nodo;
            pivote->anterior = nodo;
            
            return true;
        }

        else if((nodo->e.Volumen() == pivote->e.Volumen()) && nodo->e != pivote->e){           //en medio de la lista
            aux=pivote->DevSiguiente();
            nodo->siguiente = pivote->DevSiguiente();
            nodo->anterior = pivote;
            pivote->siguiente = nodo;
            aux->anterior = nodo;

            if(aux->DevSiguiente() == NULL){
                this->ultimo = aux;
            }

            return true;
        }

        else if(pivote->DevSiguiente() == NULL){             //al final de la lista
            nodo->siguiente = NULL;
            nodo->anterior = pivote;
            pivote->siguiente = nodo;
            this->ultimo = nodo;
            
            return true;
        }
    }

    return false;
}

bool TListaPoro::Borrar(const TPoro &object){
    TListaNodo *sig = new TListaNodo;
    TListaNodo *ant = new TListaNodo;
    TListaNodo *auxiliar = new TListaNodo;

    for(auxiliar=primero; auxiliar != NULL ;auxiliar=auxiliar->DevSiguiente()){
        if(auxiliar==this->primero && auxiliar->e==this->primero->e && auxiliar->e==object){
            this->primero=auxiliar->DevSiguiente();
            delete auxiliar;
            
            return true;
        }
        else if(auxiliar==this->ultimo && auxiliar->e==this->ultimo->e && auxiliar->e==object){
            ant=auxiliar->DevAnterior();
            ant->siguiente=NULL;
            this->ultimo=ant;
            delete auxiliar;
            
            return true;
        }
        else if(auxiliar->e==object){
            ant=auxiliar->DevAnterior();
            sig=auxiliar->DevSiguiente();
            ant->siguiente=sig;
            sig->anterior=ant;
            auxiliar->siguiente=NULL;
            auxiliar->anterior=NULL;
            delete auxiliar;
            
            return true;
        }
    }

    return false;
}

bool TListaPoro::Borrar(const TListaPosicion &object){
    if(object.EsVacia() == false){
        return Borrar(object.pos->e);
    }
    else{
        return false;
    }
}

TPoro TListaPoro::Obtener(const TListaPosicion &object) const{
    TPoro poro;
    
    if(object.EsVacia()){
        return poro;
    }
    else{
        poro = object.pos->e;
        return poro;
    }
}

bool TListaPoro::Buscar(const TPoro &object) const{
    for(TListaPosicion i=Primera(); i.EsVacia() == false ; i=i.Siguiente()){
        if(i.pos->e == object){
            return true;
        }
    }

    return false;
}

int TListaPoro::Longitud() const{
    int longitud = 0;

    for(TListaPosicion i=Primera(); i.EsVacia() == false ; i=i.Siguiente()){
        longitud++;
    }

    return longitud;
}

TListaPosicion TListaPoro::Primera() const{
    TListaPosicion primera;

    if(EsVacia()){
        return primera;
    }
    else{
        primera.pos = primero;
        return primera;
    }
}

TListaPosicion TListaPoro::Ultima() const{
    TListaPosicion ultima;

    if(EsVacia()){
        return ultima;
    }
    else{
        ultima.pos = ultimo;
        return ultima;
    }
}

TListaPoro TListaPoro::ExtraerRango(int n1, int n2){
    TListaPoro *nueva = new TListaPoro(*this);
    TListaPoro extraccion;

    if(n1 > n2){
        return extraccion;
    }

    if(n1 <= 0){
        n1 = 1;
    }

    if(n2 > this->Longitud()){
        n2 = this->Longitud();
    }
    
    int indice = 1;

    for(TListaPosicion i = nueva->Primera(); i.EsVacia() == false; i=i.Siguiente() ){
        if(indice >= n1 && indice <= n2){
            this->Borrar(i);
            extraccion.Insertar(i.pos->e);
        }

        indice ++;
    }
    
    nueva->~TListaPoro();

    return extraccion;
}

ostream & operator<<(ostream &os,const TListaPoro &obj){
    os << "(";

    for(TListaPosicion i = obj.Primera(); i.EsVacia() == false; i=i.Siguiente() ){
        os << obj.Obtener(i);
        if((i ==  obj.Ultima()) ==  false){
            os << " "; 
        }   
    }
       
    os << ")";

    return os;
}