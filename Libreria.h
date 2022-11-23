#include <iostream>
#include <string.h>
using namespace std;

struct Nodo{
    string equipo;
    string pais;
    string puntaje;
    Nodo *siguiente;
};

struct Nodo *lista = NULL;

void InsertarEquipo( string pEquipo, string pPais, string pPuntaje){
    Nodo *nuevo_nodo = new Nodo();
    nuevo_nodo->equipo = pEquipo;
    nuevo_nodo->pais = pPais;
    nuevo_nodo->puntaje = pPuntaje;
    Nodo *aux1 = lista;
    Nodo *aux2;
    while ((aux1 != NULL) && (aux1->equipo < pEquipo)){
        aux2 = aux1;
        aux1 = aux1->siguiente;
    }
    if (lista == aux1){
        lista = nuevo_nodo;
    }else{
        aux2->siguiente = nuevo_nodo;
    }
    nuevo_nodo->siguiente = aux1;
    cout << "Equipo agregado en la lista"<<endl;
};

void EliminarElemento(string &pEquipo){
    if (lista != NULL){
        Nodo *auxEliminar=lista;
        Nodo *temp;
        if (auxEliminar->siguiente != NULL){
            while ((auxEliminar != NULL) && (auxEliminar->equipo != pEquipo)){
                temp=auxEliminar;
                auxEliminar = auxEliminar->siguiente;
            }
            if (auxEliminar == NULL){
                cout << "Dato no encontrado"<<endl;
            }else{
                temp = auxEliminar->siguiente;
                delete auxEliminar;
                cout << "Se elimino al equipo seleccionado"<<endl;
            }
        }else{
            delete lista;
            lista = NULL;
        }
    }
};

struct Nodo *BuscarNombre(string &nombreE){
    struct Nodo *temp = lista;
    if (lista != NULL){
        while ((temp != NULL) && (temp->equipo != nombreE)){
            temp = temp->siguiente;
        }
        if (temp == NULL){
            cout << "Dato no encontrado";
            break;
        }else{
            return temp;
        }
    }
}

void BuscarEquipo(string &pEquipo){
    struct Nodo *temp = lista;
    struct Nodo equipoBuscado;
    if (lista != NULL){
        while ((temp != NULL) && (temp->equipo != pEquipo)){
            temp = temp->siguiente;
        }
        if (temp == NULL){
            cout << "Equipo no encontrado!"<<endl;
        }else{
            cout<< "Se encontro al equipo "<<temp->equipo<<", del pais "<< temp->pais
            <<", el cual tiene un puntaje actual de "<<temp->puntaje<<" puntos en total."<<endl;
        }
    }
}

void imprimirLista(){
    struct Nodo *temporal = lista;
    if (lista != NULL){
        while (temporal != NULL)
        {
            cout<< "El equipo "<<temporal->equipo<<", del pais "<<temporal->pais
            <<", tiene "<<temporal->puntaje<<" puntos en total"<<endl;
            temporal = temporal->siguiente;
        }
    }else{
        cout << "Lista vacia!"<<endl;
    }
}

int contador(){
    struct Nodo *temporal = lista;
    int conteo=0;
    if (lista != NULL){
        while (temporal != NULL)
        {
            conteo++;
            temporal = temporal->siguiente;
        }
    }
    return conteo;
}

void TablaPartidos(int n)
{
    struct Nodo *temp = lista;
    string **Equipos = new string *[n];
    for (int i = 0; i < n; i++)
    {
        Equipos[i] = new string[2];
    }
    while (temp != NULL)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                Equipos[i][j] = temp->equipo;
                temp = temp->siguiente;
            }
        }
    }
    cout << "Los partidos seran:" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << Equipos[i][1] << " VS " << Equipos[i][2] << endl;
    }
}

void MostrarPartidos(){
    int cant;
    cout<< "Cuantos partidos desea generar?\t";
    cin >> cant;
    if ((lista!=NULL)&&(cant<=contador()/2)){
        TablaPartidos(cant);
    }else{
        cout<<"ERROR: Lista vacia o datos insuficiente";
    }
}

void Ordenamiento(string puntos[], int marca){
    string aux;
    for (int i = 0; i < marca; i++){
        for (int j = 0; j < marca - 1; j++){
            if(puntos[j]>puntos[j+1]){
                aux = puntos[j];
                puntos[j] = puntos[j + 1];
                puntos[j + 1] = aux;
            }
        }
    }
}

struct Nodo *BuscarPuntaje(string &pPuntaje){
    struct Nodo *temp = lista;
    if (lista != NULL){
        while ((temp != NULL) && (temp->puntaje != pPuntaje)){
            temp = temp->siguiente;
        }
        if (temp == NULL){
            cout << "Dato no encontrado";
            break;
        }else{
            return temp;
        }
    }
}

void TablaPuntaje(){
    int n=contador()-1;
    string puntajes[n];
    struct Nodo *temp = lista;
    while (temp != NULL){
        for (int i = 0; i < n; i++){
            puntajes[i]=temp->puntaje;
            temp=temp->siguiente;
        }
    }
    Ordenamiento(puntajes, n);
    cout << "Los equipos, ordenados por puntaje, son:" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << BuscarPuntaje(puntajes[i])->equipo <<", con "
        <<BuscarPuntaje(puntajes[i])->puntaje<<" puntos en total\n";
    }
}