#include "tavlporo.h"

TNodoAVL::TNodoAVL() : item(), iz(), de(), fe() {     //Usamos layering para incializar los objetos, haciendolo (item = NULL) salta error

}

TNodoAVL::TNodoAVL(const TNodoAVL &nodo) : item(nodo.item), iz(nodo.iz), de(nodo.de), fe(nodo.fe) {      //Usamos layering de la misma forma

}

TNodoAVL::~TNodoAVL() {     //No destruimos nodos, pero si destruimos los arboles
    fe=0;
}

TNodoAVL & TNodoAVL::operator=(const TNodoAVL &nodo) {      //Copiamos el nodo pasado por referencia
    if(this != &nodo) {     //Comprobamos que nodo no sea el mismo
        this->~TNodoAVL();

        this->item = nodo.item;
        this->iz = nodo.iz;
        this->de = nodo.de;
        this->fe = nodo.fe;
    }

    return (*this);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void TAVLPoro::InordenAux(TVectorPoro &vector, int &posicion) const {       //Metodo auxiliar Inorden
    if(!EsVacio()) {
        raiz->iz.InordenAux(vector,posicion);
        vector[posicion] = Raiz();
        posicion++;
        raiz->de.InordenAux(vector,posicion);
    }
}

void TAVLPoro::PreordenAux(TVectorPoro &vector, int &posicion) const {      //Metodo auxiliar Preorden
    if(!EsVacio()) {
        vector[posicion] = Raiz();
        posicion++;
        this->raiz->iz.PreordenAux(vector,posicion);        
        this->raiz->de.PreordenAux(vector,posicion);
    }
}

void TAVLPoro::PostordenAux(TVectorPoro &vector, int &posicion) const {     //Metodo auxiliar Postorden
    if(!EsVacio()) {
        raiz->iz.PostordenAux(vector,posicion);
        raiz->de.PostordenAux(vector,posicion);
        vector[posicion] = Raiz();
        posicion++;
    }
}

bool TAVLPoro::Hoja() const {       //Comprobamos si es un nodo hoja; es decir, no tiene hijos
    if(!EsVacio() && raiz->iz.EsVacio() && raiz->de.EsVacio()) {
        return true;
    }

    return false;
}
/*
int TAVLPoro::ValorFE(){                                //Calcula el valor de equilibrio
    return (raiz->de.Altura() - raiz->iz.Altura());
}

void TAVLPoro::Actualizar(){                            //Actualiza el valor de equlibrio de los hijos
    if(raiz->iz.raiz != NULL){
        raiz->iz.raiz->fe = ValorFE();
    }

    if(raiz->de.raiz != NULL){
        raiz->de.raiz->fe = ValorFE();
    }
}

void TAVLPoro::rotacionII(){        //Explicado con el PDF-AVL teoría                            
    TNodoAVL *auxiliar;    //aux             

    auxiliar = raiz->iz.raiz;       //Copiamos nuestro hijoIzquierdo a la raiz del aux
    raiz->iz.raiz = raiz->iz.raiz->de.raiz;     //Sustituimos nuestro hijoIzquierdo por el hijo derecho de nuestro hijoIzquierdo
    auxiliar->de.raiz = raiz;       //Ahora el arbol que se nos queda, lo asginamos como hijoDerecho del aux
    raiz = auxiliar;    
    
}

void TAVLPoro::rotacionID(){
    TNodoAVL *auxiliar;     //aux

    auxiliar = raiz->iz.raiz;       //Inicializamos el arbol aux con el hijoIzquierdo del nuestro
    raiz->iz.raiz = auxiliar->de.raiz->de.raiz;     //Ahora cambiamos nuestro hijoIzquierdo por el hijoDerecho del hijoDerecho del aux
    auxiliar->de.raiz->de.raiz = raiz;      //Asignamos al hijoDerecho del hijoDerecho del aux, nuestro arbol actual 
    raiz = auxiliar->de.raiz;       //Ahora nuestro arbol es el hijoDerecho del aux
    auxiliar->de.raiz = raiz->iz.raiz;      //Cambiamos el hijoDerecho del aux por el hijoIzquierdo de nuestro arbol
    raiz->iz.raiz = auxiliar;       //Asignamos el aux al hijoIzquierdo de nuestro arbol, y ya tendriamos el arbol equilibrado
}

void TAVLPoro::rotacionDD(){        //Igual que II pero al revés
    TNodoAVL *auxiliar;

    auxiliar = raiz->de.raiz;
    raiz->de.raiz = raiz->de.raiz->iz.raiz;
    auxiliar->iz.raiz = raiz;
    raiz = auxiliar;
}

void TAVLPoro::rotacionDI(){        //Igual que ID pero al revés
    TNodoAVL *auxiliar;

    auxiliar = raiz->de.raiz;
    raiz->de.raiz = auxiliar->iz.raiz->iz.raiz;
    auxiliar->iz.raiz->iz.raiz = raiz;
    raiz = auxiliar->iz.raiz;
    auxiliar->iz.raiz = raiz->de.raiz;
    raiz->de.raiz = auxiliar;
}

void TAVLPoro::Equilibrar(){
    raiz->fe = ValorFE();       //Calculamos el valor de equilibrio

    if(raiz->fe == -2){                 //Está desequilibrado y rotamos izquierda
        if(raiz->iz.raiz->fe <= 0){
            rotacionII();

        } else{
            rotacionID();
        }

        raiz->fe = ValorFE();
        Actualizar();
    }
    
    if(raiz->fe == 2){             //Está desequilibrado y rotamos derecha
        if (raiz->de.raiz->fe >= 0){
            rotacionDD();

        } else{
            rotacionDI();
        }

        raiz->fe = ValorFE();       //Actualizamos el nuevo valor de equilibrio
        Actualizar();
    }
}*/

TAVLPoro::TAVLPoro() {     //Constructor por defecto
    raiz = NULL;
}

void TAVLPoro::Copiar(const TAVLPoro &obj) {        //Copiamos a nuestro arbol, el pasado por referencia
    if(!obj.EsVacio()) {
        this->raiz = new TNodoAVL();
        this->raiz->item = obj.raiz->item;
        this->raiz->de.Copiar(obj.raiz->de);
        this->raiz->iz.Copiar(obj.raiz->iz);
    }
    else {
        this->raiz = NULL;
    }
}

TAVLPoro::TAVLPoro(const TAVLPoro &obj) {       //Llamamos a Copiar()
    this->raiz = NULL;
    Copiar(obj);
}

TAVLPoro::~TAVLPoro() {     //Destructor
    if(!EsVacio()) {
        raiz->de.~TAVLPoro();
        raiz->iz.~TAVLPoro();

        delete raiz;
        raiz = NULL;
    }
}

TAVLPoro & TAVLPoro::operator=(const TAVLPoro &obj) {       //Asignación
    if(this != &obj){       //Para que no se auto asigne
        (*this).~TAVLPoro();
        Copiar(obj);
    }

    return (*this);
}

bool TAVLPoro::operator==(const TAVLPoro &obj) const {      //Igualdad, usamos Inorden para que no de fallo
    if(Inorden() == obj.Inorden()) {
            return true;
    }
    
    return false;
}

bool TAVLPoro::operator!=(const TAVLPoro &obj) const {      //Desigualdad
    return !((*this) == obj);
}

bool TAVLPoro::EsVacio() const {        //Comprueba si es vacio
    return (raiz == NULL);
}

void TAVLPoro::RotarDD() {
	TNodoAVL *auxiliar = raiz;
	TNodoAVL *derecha = raiz->de.raiz;
	TNodoAVL *izquierda = derecha->iz.raiz;

	raiz = derecha;
	auxiliar->de.raiz = izquierda;
	raiz->iz.raiz = auxiliar;
}

void TAVLPoro::RotarII() {
	TNodoAVL *auxiliar = raiz;
	TNodoAVL *izquierda = raiz->iz.raiz;
	TNodoAVL *derecha = izquierda->de.raiz;

	raiz = izquierda;
	raiz->de.raiz = auxiliar;
	raiz->de.raiz->iz.raiz = derecha;
}

void TAVLPoro::RotarDI() {
	raiz->de.RotarII();
	RotarDD();
}

void TAVLPoro::RotarID() {
	raiz->iz.RotarDD();
	RotarII();
}

int TAVLPoro::ValorFE(){                                //Calcula el valor de equilibrio
    return (raiz->de.Altura() - raiz->iz.Altura());
}

void TAVLPoro::Equilibrar() {
    if(!EsVacio())
	{
		raiz->iz.Equilibrar();
		raiz->de.Equilibrar();
		raiz->fe = ValorFE();

		if(raiz->fe == 2 || raiz->fe == -2)
		{
			if(raiz->fe==2 && (raiz->de.raiz->fe >= 0)){
                RotarDD();
            }
            else if(raiz->fe==2 && (raiz->de.raiz->fe == -1)){
                RotarDI();
            }
			else if(raiz->fe==-2 && (raiz->iz.raiz->fe <= 0)){
                RotarII();
            }
			else if(raiz->fe==-2 && (raiz->iz.raiz->fe == 1)){
                RotarID();
            }			
		}
	}
}

TPoro TAVLPoro::Ordenar() const{
    TPoro aux;

    if(!EsVacio()){
        if(!this->raiz->de.EsVacio()) {
            return this->raiz->de.Ordenar();
        }   
        else {
            return this->raiz->item;
        }
    }

    return aux;
}

bool TAVLPoro::InsertarAux(TPoro &obj, bool crece){
    bool resultado=crece, creceIzq=crece, creceDer=crece;

    if(this->EsVacio()){
        raiz=new TNodoAVL;
        raiz->item=obj;

        resultado = true;
    }
    else{
        if(obj.Volumen() == raiz->item.Volumen()){
            resultado = false;
        }
        else if(raiz->de.EsVacio() && raiz->iz.EsVacio()){
            if(obj.Volumen() > raiz->item.Volumen()){
                raiz->de.raiz = new TNodoAVL;
                raiz->de.raiz->item = obj;

                resultado = true;
            }
            else{
                raiz->iz.raiz = new TNodoAVL;
                raiz->iz.raiz->item = obj;

                resultado = true;
            }
        }
        else{
            if(obj.Volumen() > raiz->item.Volumen()){
                resultado = raiz->de.InsertarAux(obj,creceDer);
            }
            else{
                resultado = raiz->iz.InsertarAux(obj,creceIzq);
            }
        }
    }

    return resultado;
}

bool TAVLPoro::Insertar(TPoro &obj){
    if(InsertarAux(obj,false)){
        Equilibrar();
        return true;
    }

    return false;  
}

bool TAVLPoro::BorrarAux(TPoro &obj){
    if(!EsVacio() && this->Buscar(obj)){
        if(raiz->item == obj && raiz->de.EsVacio() && raiz->iz.EsVacio()){
            raiz = NULL;
            delete raiz;

            return true;
        }
        else if(raiz->de.EsVacio() && !raiz->iz.EsVacio() && raiz->item == obj){
            TNodoAVL *viejo=raiz;

            raiz = raiz->iz.raiz;
            viejo = NULL;
            delete viejo;

            return true;

        }
        else if(!raiz->de.EsVacio() && raiz->iz.EsVacio() && raiz->item == obj){
            TNodoAVL *viejo=raiz;
            
            raiz = raiz->de.raiz;
            viejo = NULL;
            delete viejo;

            return true;
            
        }
        else if(!raiz->de.EsVacio() && !raiz->iz.EsVacio() && raiz->item==obj){
            TPoro auxIzq = this->raiz->iz.Ordenar();
            this->raiz->item = auxIzq;
            this->raiz->iz.Borrar(auxIzq);
        }
        else if(raiz->item != obj && (obj.Volumen() > raiz->item.Volumen())){
            return raiz->de.Borrar(obj);
        }
        else if(raiz->item != obj && (obj.Volumen() < raiz->item.Volumen())){
            return raiz->iz.Borrar(obj);
        }
    }
    else{
        return false;
    }

    return true;
}

bool TAVLPoro::Borrar(TPoro &obj){
    if(BorrarAux(obj)){
        Equilibrar();
        return true;
    }
    
    return false;
}

bool TAVLPoro::Buscar(const TPoro &obj) const {     //Busca un poro en el arbol
    if(!EsVacio()) {
        if(this->Raiz() == obj) {       //si es la raiz se devuelve true
            return true;
        }
        else {
            if(obj.Volumen()>raiz->item.Volumen()){
                return raiz->de.Buscar(obj);
            }
            else{
                return raiz->iz.Buscar(obj);
            }
        }
    }
    
    return false;
}

TPoro TAVLPoro::Raiz() const {      //Devuelve el elemento raiz
    if(EsVacio()) {     
        TPoro error;
        return error;
    }
    
    return raiz->item;
}

int TAVLPoro::Altura() const {      //Devuelve la altura del arbol
    if(EsVacio()) {     //la altura de un arbol vacio es 0
        return 0;
    }
    else {
        return (1 + max(raiz->iz.Altura(),raiz->de.Altura()));
    }
}

int TAVLPoro::Nodos() const {       //Devuelve el numero de nodos del arbol
    if(EsVacio()) {     //el numero de nodos de un arbol vacio es 0
        return 0;
    }
    else {
        return (1 + raiz->de.Nodos() + raiz->iz.Nodos());
    }
}

int TAVLPoro::NodosHoja() const {       //Devuelve las hojas que tiene el arbol
    if(EsVacio()) {
        return 0;
    }
    else {
        if(Hoja()) {        //la raiz puede ser un nodo hoja
            return 1;
        }
        else {
            return (raiz->de.NodosHoja() + raiz->iz.NodosHoja());
        }
    }
}

void TAVLPoro::Recorrido(TVectorPoro &vector, int numero) const {
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

TVectorPoro TAVLPoro::Inorden() const {
    TVectorPoro vector(Nodos());
    Recorrido(vector,1);
    return vector;
}

TVectorPoro TAVLPoro::Preorden() const {
    TVectorPoro vector(Nodos());
    Recorrido(vector,2);
    return vector;
}

TVectorPoro TAVLPoro::Postorden() const {
    TVectorPoro vector(Nodos());
    Recorrido(vector,3);
    return vector;
}

ostream & operator<<(ostream &os, const TAVLPoro &obj) {    //Imprime por pantalla todo el arbol en orden por Inorden
    os << obj.Inorden();
    return os;
}

/*
int TAVLPoro::Caminos(TListaPoro &lista){
    int a[3];
    int * vetcor = a;
    TListaPosicion posicion, aux;
    posicion = lista.Primera();
    int i=1;
    
    while(posicion.EsVacia() == false){
        os << lista.Obtener(posicion);
        if(i%2 == 0){
            aux = posicion;
            posicion.Siguiente();
            lista.Borrar(lista.Obtener(aux));
        }
        else{
            posicion = posicion.Siguiente();
        }
        i++;
    }
}   
 * /