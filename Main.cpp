#include <iostream>
#include <string.h>
#include <fstream>
#include "Libreria.h"
using namespace std;

ofstream ficheroEscritura;
ifstream ficheroLectura;

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
            break;
        case 2:
            EliminarEquipo();
            break;
        case 3:
            Busqueda();
            break;
        case 4:
            MostrarEquipos();
            break;
        case 5:
            Partidos();
            break;
        case 6:
            Puntajes();
            break;
        case 7:
            break;
        default:
            cout<< "Ingrese una opcion correcta!"<<endl;
            break;
        }
    } while (menu!=7);
    cout<< "FIN DEL PROGRAMA!"<<endl;
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
    ficheroEscritura.open("ProyectoFinalPED.txt", ios::out|ios::app);
    string nombreE, paisE, aux;
    int cant, puntajeE;
    cout<< "Cuantos equipos desea ingresar?";
    cin >>cant;
    for(int i=0; i<cant; i++){
        cout<<"Ingresar el nombre del equipo: ";
        getline(cin, nombreE);
        if(VerificarFichero(nombreE)){
            cout<<"Ingresar el pais del equipo: ";
            getline(cin, paisE);
            cout<<"Ingrese el puntaje actual del equipo: ";
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
    ficheroLectura.open("Informacion.txt", ios::in);
    ofstream temp("auxiliar.txt", ios::out);
    if (ficheroLectura.is_open()){
        cout << "Ingrese el nombre del equipo al eliminar";
        cin >> auxEquipo;
        ficheroLectura >> equipo;
        while (!ficheroLectura.eof()){
            ficheroLectura >> pais;
            ficheroLectura >> puntaje;
            if (!VerificarFichero(auxEquipo)){
                EliminarElemento(auxEquipo);
                cout << "Registro eliminado";
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
    remove("Informacion.txt");
    rename("tmp.txt", "Informacion.txt");
}

void Busqueda(){
    string equipo;
    cout<<"Ingresa el nombre del equipo a buscar:\t";
    cin>>equipo;
    BuscarEquipo(equipo);
}

void MostrarEquipos(){
    int option;
    cout<< "Tienes un total de "<<contador()<<" equipos.\nDesea agregar otro equipo?(1=Si, 2=No)\t";
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
    cout<< "Tienes un total de "<<contador()<<" equipos.\nDesea agregar otro equipo?(1=Si, 2=No)\t";
    cin>>option;
    if(option==1){
        AgregarDatos();
    }
    TablaPuntaje();
}