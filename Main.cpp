#include <iostream>
#include <string.h>
#include <fstream>
#include "Libreria.h"
using namespace std;

ofstream ficheroEscritura;
ifstream ficheroLectura;

void Pausa();
bool VerificarFichero(string);
void AgregarDatos();
void EliminarEquipo();
void Busqueda();
void MostrarEquipos();
void Partidos();
void Puntajes();

int main(){
    int menu;
    do{
        cout<<"Simulador de equipos deportivos!\n Bienvenido al menu:"<<endl;
        cout<< "1- Agregar equipo\n"<<"2- Eliminar un equipo en especifico\n"
        <<"3- Buscar un equipo\n"<<"4- Mostrar todos los equipos\n"<<"5- Mostrar una tabla de partidos\n"
        <<"6-Mostrar equipos por puntaje\n"<<"7-Salir\n"<<"Ingrese su opcion:\t";
        cin>> menu;
        switch(menu)
        {
        case 1:
            AgregarDatos();
            Pausa();
            break;
        case 2:
            EliminarEquipo();
            Pausa();
            break;
        case 3:
            Busqueda();
            Pausa();
            break;
        case 4:
            MostrarEquipos();
            Pausa();
            break;
        case 5:
            Partidos();
            Pausa();
            break;
        case 6:
            Puntajes();
            Pausa();
            break;
        case 7:
            cout<< "FIN DEL PROGRAMA!"<<endl;
            Pausa();
            break;
        default:
            cout<< "Ingrese una opcion correcta!"<<endl;
            Pausa();
            break;
        }
    } while (menu!=7);
}

void Pausa(){
    system("pause");
}

bool VerificarFichero(string auxEquipo){
    ficheroLectura.open("ProyectoFinalPED.txt", ios::in);
    string equipo, pais;
    int puntaje;
    ficheroLectura >> equipo;
    while (!ficheroLectura.eof()){
        ficheroLectura >> pais;
        ficheroLectura>> puntaje;
        if (equipo == auxEquipo){
            ficheroLectura.close();
            return false;
        }
        ficheroLectura >> equipo;
    }
    ficheroLectura.close();
    return true;
}

void AgregarDatos(){
    if(lista==NULL){
        ficheroEscritura.open("ProyectoFinalPED.txt");
    }else{
        ficheroEscritura.open("ProyectoFinalPED.txt", ios::out|ios::app);
    }
    string nombreE, paisE, aux;
    int cant, puntajeE;
    cout<< "Cuantos equipos desea ingresar?\t";
    cin >>cant;
    getline(cin, aux);
    for(int i=0; i<cant; i++){
        cout<<"Ingresar el nombre del equipo:\t";
        getline(cin, nombreE);
        if(VerificarFichero(nombreE)){
            cout<<"Ingresar el pais del equipo:\t";
            getline(cin, paisE);
            cout<<"Ingrese el puntaje actual del equipo:\t";
            cin>>puntajeE;
            getline(cin, aux);
            InsertarEquipo(nombreE, paisE, puntajeE);
            ficheroEscritura<<nombreE<<" "<<paisE<<" "<<puntajeE<<"\n";
        }else{
            cout << "Equipo ya agregado!";
        }
    }
    ficheroEscritura.close();
}

void EliminarEquipo(){
    int puntaje;
    string equipo, pais, auxEquipo;
    ficheroLectura.open("ProyectoFinalPED.txt", ios::in);
    ofstream temp("auxiliar.txt", ios::out);
    if (ficheroLectura.is_open()){
        cout << "Ingrese el nombre del equipo al eliminar:\t";
        cin >> auxEquipo;
        ficheroLectura >> equipo;
        while (!ficheroLectura.eof()){
            ficheroLectura >> pais;
            ficheroLectura >> puntaje;
            if (!VerificarFichero(auxEquipo)){
                EliminarElemento(auxEquipo);
                cout << "Registro eliminado"<<endl;
            }else{
                temp<<equipo<<" "<<pais<<" "<<puntaje<<"\n";
            }
            ficheroLectura >> equipo;
        }
        ficheroLectura.close();
        temp.close();
    }else{
        cout << "Error al abrir el archivo";
    }
    remove("ProyectoFinalPED.txt");
    rename("auxiliar.txt", "ProyectoFinalPED.txt");
}

void Busqueda(){
    string equipo;
    cout<<"Ingresa el nombre del equipo a buscar:\t";
    cin>>equipo;
    BuscarEquipo(equipo);
}

void MostrarEquipos(){
    int option;
    cout<< "Tienes un total de "<< contador() <<" equipos.\nDesea agregar otro equipo?(1=Si, 2=No)\t";
    cin>>option;
    if(option==1){
        AgregarDatos();
    }
    imprimirLista();
}

void Partidos(){
    int option;
    while(contador()%2!=0){
        cout<< "Tienes una cantidad impar de equipos. Por favor, ingrese mas equipos."<<endl;
        AgregarDatos();
    }
    MostrarPartidos();
}

void Puntajes(){
    int option;
    cout<< "Tienes un total de "<< contador() <<" equipos.\nDesea agregar otro equipo?(1=Si, 2=No)\t";
    cin>>option;
    if(option==1){
        AgregarDatos();
    }
    TablaPuntaje();
}