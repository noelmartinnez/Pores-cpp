#include "tabbporo.h"
#include <queue>

TNodoABB::TNodoABB() : item(), iz(), de() {     //Usamos layering para incializar los objetos, haciendolo (item = NULL) salta error
    
}

TNodoABB::TNodoABB(const TNodoABB &nodo) : item(nodo.item), iz(nodo.iz), de(nodo.de) {      //Usamos layering de la misma forma
    
}

TNodoABB::~TNodoABB() {     //No destruimos nodos, pero si destruimos los arboles
    
}

TNodoABB & TNodoABB::operator=(const TNodoABB &nodo) {      //Copiamos el nodo pasado por referencia
    if(this != &nodo) {     //Comprobamos que nodo no sea el mismo
        this->item = nodo.item;
        this->iz = nodo.iz;
        this->de = nodo.de;
    }

    return (*this);
}

void TABBPoro::InordenAux(TVectorPoro &vector, int &posicion) const {       //Metodo auxiliar Inorden
    if(!EsVacio()) {
        nodo->iz.InordenAux(vector,posicion);
        vector[posicion] = Raiz();
        posicion++;
        nodo->de.InordenAux(vector,posicion);
    }
}

void TABBPoro::PreordenAux(TVectorPoro &vector, int &posicion) const {      //Metodo auxiliar Preorden
    if(!EsVacio()) {
        vector[posicion] = Raiz();
        posicion++;
        this->nodo->iz.PreordenAux(vector, posicion);        
        this->nodo->de.PreordenAux(vector, posicion);
    }
}

void TABBPoro::PostordenAux(TVectorPoro &vector, int &posicion) const {     //Metodo auxiliar Postorden
    if(!EsVacio()) {
        nodo->iz.PostordenAux(vector,posicion);
        nodo->de.PostordenAux(vector,posicion);
        vector[posicion] = Raiz();
        posicion++;
    }
}

bool TABBPoro::Hoja() const {       //Comprobamos si es un nodo hoja; es decir, no tiene hijos
    if(!EsVacio() && nodo->iz.EsVacio() && nodo->de.EsVacio()) {
        return true;
    }

    return false;
}

TABBPoro::TABBPoro() {
    nodo = NULL;
}

void TABBPoro::Copiar(const TABBPoro &obj) {        //Copiamos a nuestro arbol, el pasado por referencia
    if(!obj.EsVacio()) {
        this->nodo = new TNodoABB();
        this->nodo->item = obj.nodo->item;
        this->nodo->de.Copiar(obj.nodo->de);
        this->nodo->iz.Copiar(obj.nodo->iz);
    }
    else {
        this->nodo = NULL;
    }
}

TABBPoro::TABBPoro(const TABBPoro &obj) {       //Llamamos a Copiar()
    Copiar(obj);
}

TABBPoro::~TABBPoro() {     //Destructor
    if(!EsVacio()) {
        nodo->de.~TABBPoro();
        nodo->iz.~TABBPoro();

        delete nodo;
        nodo = NULL;
    }
}

TABBPoro & TABBPoro::operator=(const TABBPoro &obj) {       //Asignación
    if(this != &obj){       //Para que no se auto asigne
        (*this).~TABBPoro();
        Copiar(obj);
    }

    return (*this);
}

bool TABBPoro::operator==(const TABBPoro &obj) const {      //Igualdad, usamos Preorden como podemos usar la que queramos
    if(Inorden() == obj.Inorden()) {
            return true;
    }
    
    return false;
}

bool TABBPoro::EsVacio() const {        //Comprueba si es vacio
    return (nodo == NULL);
}

bool TABBPoro::Insertar(const TPoro &obj) {        
    if(this->EsVacio()){        //Si está vacio se pondrá como nodo raiz, el pasado por referencia
        TNodoABB *nuevo = new TNodoABB();
        nuevo->item = obj;
        this->nodo = nuevo;
        return true;
    }
    
    if(!this->Buscar(obj)){     //Si no está vacio, y el poro pasado por referencia no está en el arbol
        if(this->nodo->item.Volumen() > obj.Volumen()){
            return this->nodo->iz.Insertar(obj);
        }
        else {
            return this->nodo->de.Insertar(obj);
        }
    }
    
    return false; 	
}

bool TABBPoro::Borrar(const TPoro &obj) {
    if(!this->EsVacio() && this->Buscar(obj)){      //Si está en el arbol y no es vacio, se puede borrar
        if(this->nodo->item.Volumen() > obj.Volumen()){
            return this->nodo->iz.Borrar(obj);
        }
        else if(this->nodo->item.Volumen() < obj.Volumen()){
            return this->nodo->de.Borrar(obj);
        }
        else if(this->nodo->iz.EsVacio() && this->nodo->de.EsVacio() && this->Raiz() == obj){       //Si es un nodo hoja, y es nuestra raiz
            this->nodo = NULL;
            delete this->nodo;
            return true;
        }
        else if(!this->nodo->iz.EsVacio() && this->nodo->de.EsVacio()){     //Si tiene hijo izquierdo y no derecho
            TNodoABB *viejo = this->nodo;
            this->nodo = this->nodo->iz.nodo;
            viejo = NULL;
            
            delete viejo;
            return true;
        }
        else if(this->nodo->iz.EsVacio() && !this->nodo->de.EsVacio()){     //Si tiene hijo derecho y no izquierdo
            TNodoABB *viejo = this->nodo;
            this->nodo = this->nodo->de.nodo;
            viejo = NULL;
            
            delete viejo;
            return true;
        }
        else if(!this->nodo->iz.EsVacio() && !this->nodo->de.EsVacio()){        //Si tiene los dos hijos no vacios
            TNodoABB *viejo = this->nodo;
            this->nodo = this->nodo->de.nodo;
            
            if(viejo->iz.nodo != this->nodo) {
                this->nodo->iz.nodo = viejo->iz.nodo;
            }
            
            if(viejo->de.nodo != this->nodo) {
                this->nodo->de.nodo = viejo->de.nodo;
            }
            
            viejo->de.nodo = NULL;
            viejo->iz.nodo = NULL;
            
            delete viejo;
            return true;
        }
        else{
            return false;
        }
    }
    
    return false;
}

bool TABBPoro::Buscar(const TPoro &obj) const {     //Busca un poro en el arbol
    if(!EsVacio()) {
        if(this->Raiz() == obj) {       //si es la raiz se devuelve true
            return true;
        }
        else {
            if(this->nodo->de.Buscar(obj) || this->nodo->iz.Buscar(obj)) {      //sino, buscamos en el resto del arbol
                return true;
            }
            else {
                return false;
            }
        }
    }
    
    return false;
}

TPoro TABBPoro::Raiz() const {      //Devuelve el elemento raiz
    if(EsVacio()) {     
        TPoro error;
        return error;
    }
    
    return nodo->item;
}

int TABBPoro::Altura() const {      //Devuelve la altura del arbol
    if(EsVacio()) {     //la altura de un arbol vacio es 0
        return 0;
    }
    else {
        return (1 + max(nodo->iz.Altura(),nodo->de.Altura()));
    }
}

int TABBPoro::Nodos() const {       //Devuelve el numero de nodos del arbol
    if(EsVacio()) {     //el numero de nodos de un arbol vacio es 0
        return 0;
    }
    else {
        return (1 + nodo->de.Nodos() + nodo->iz.Nodos());
    }
}

int TABBPoro::NodosHoja() const {       //Devuelve las hojas que tiene el arbol
    if(EsVacio()) {
        return 0;
    }
    else {
        if(Hoja()) {        //la raiz puede ser un nodo hoja
            return 1;
        }
        else {
            return (nodo->de.NodosHoja() + nodo->iz.NodosHoja());
        }
    }
}

void TABBPoro::Recorrido(TVectorPoro &vector, int numero) const {
    int posicion = 1;
    
    if(numero == 1){
        InordenAux(vector,posicion);
    }
    else if(numero == 2){
        PreordenAux(vector,posicion);
    }
    else{
        PostordenAux(vector,posicion);
    }
}

TVectorPoro TABBPoro::Inorden() const {
    TVectorPoro vector(Nodos());
    Recorrido(vector,1);
    return vector;
}

TVectorPoro TABBPoro::Preorden() const {
    TVectorPoro vector(Nodos());
    Recorrido(vector,2);
    return vector;
}

TVectorPoro TABBPoro::Postorden() const {
    TVectorPoro vector(Nodos());
    Recorrido(vector,3);
    return vector;
}

TVectorPoro TABBPoro::Niveles() const {
    int i = 1;
    
    TVectorPoro vector(Nodos());
    queue<TABBPoro*> cola;

    TABBPoro copia(*this);
    TABBPoro *arbAux = &copia;
	
    if(!EsVacio()) {
        cola.push(&copia);

        while(!cola.empty()) {
            arbAux = cola.front();
            vector[i++] = arbAux->nodo->item;
            cola.pop();

            if(!arbAux->nodo->iz.EsVacio()) {
                cola.push(&(arbAux->nodo->iz));
            }
            
            if(!arbAux->nodo->de.EsVacio()) {
                cola.push(&(arbAux->nodo->de));
            }
        }
    }

    return vector;
}

TABBPoro TABBPoro::operator+(const TABBPoro &obj) {
    TABBPoro resultado(*this);
    TABBPoro auxiliar(obj);

    TVectorPoro vector = auxiliar.Inorden();

    int cantidad = obj.Nodos();
	
    for(int i=1; i<=cantidad ;i++) {
        resultado.Insertar(vector[i]);
    }

    return resultado;
}

TABBPoro TABBPoro::operator-(const TABBPoro &obj) {
    TABBPoro resultado;
    TVectorPoro vector = Inorden();

    int cantidad = Nodos();

    for(int i=1; i<=cantidad ;i++) {
        if(!obj.Buscar(vector[i])) {
            resultado.Insertar(vector[i]);
        }
    }

    return resultado;
}

ostream & operator<<(ostream &os, const TABBPoro &obj) {    //Imprime por pantalla todo el arbol en orden por niveles
    os << obj.Niveles();
    return os;
}

/*
 //FUNCION EXAMEN
TComplejo*  TABBCom::MostrarNiveles (TListaCom & lista)
{

    //Eliminamos los elementos pares de la lista
    int cont = 1;
    for(TListaPos i = lista.Primera(); !i.EsVacia(); i = i.Siguiente())
    {
        if(cont%2 == 0)
            lista.Borrar(i);
        cont++;
    }

    //Copiamos los elementos en el vector dinamico
    int tamanyo = lista.Longitud();
    TComplejo *arr = new TComplejo[tamanyo];

    TListaPos j = lista.Primera();
    for (int i = 0; i < tamanyo && !j.EsVacia(); i++)
    {
        arr[i] = lista.Obtener(j);
        j = j.Siguiente();
    }
    

    //Vaciamos el ABB
    if(!this->EsVacio())
    {
        while (!this->EsVacio())
        {
            this->Borrar(this->nodo->item);
        }
    }

    //Insertamos los elementos del array dinamico al ABB
    for (int i = 0; i < tamanyo; i++)
    {
        this->Insertar(arr[i]);
    }

    if(arr == NULL)
    {
        cout << "{}" << endl;
    }
    else
    {
        for (int i = 0; i < tamanyo; i++)
        {
            int l = getNivel(arr[i], 1);
            cout << "{ Elemento: " << arr[i] << ". Elementos de su nivel: ";
            for (int j = 0; j < tamanyo; j++)
            {
                int l2 = getNivel(arr[j], 1);
                if(l2 == l)
                {
                    cout << arr[j] << " ";
                }
            }
            cout << "}" << endl;
        }
    }
    
    return arr;
} 
 
*/