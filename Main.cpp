#include <iostream>
#include <string.h>
#include <fstream>
#include "Libreria.h"
using namespace std;

ofstream ficheroEscritura;
ifstream ficheroLectura;

bool VerificarFichero(string);
void AgregarDatos();
void EditarFichero();
void EliminarEquipo();
void Busqueda();
void MostrarEquipos();
void Partidos();
void Puntajes();

int main(){
    int menu;
    cout<<"Simulador de equipos deportivos!"<<endl;
    do{
        cout<<"\tBienvenido al menu:"<< endl << "1- Agregar equipo\n"<<"2- Editar la informacion de un equipo\n"
        <<"3- Eliminar un equipo en especifico\n"<<"4- Buscar un equipo\n"<<"5- Mostrar todos los equipos\n"
        <<"6- Mostrar una tabla de partidos\n" <<"7-Mostrar equipos por puntaje\n"<<"8-Salir\n"
        <<"Ingrese su opcion:\t";
        cin>> menu;
        switch(menu)
        {
        case 1:
            AgregarDatos();
            system("pause");
            break;
        case 2:
            EditarFichero();
            system("pause");
            break;
        case 3:
            EliminarEquipo();
            system("pause");
            break;
        case 4:
            Busqueda();
            system("pause");
            break;
        case 5:
            MostrarEquipos();
            system("pause");
            break;
        case 6:
            Partidos();
            system("pause");
            break;
        case 7:
            Puntajes();
            system("pause");
            break;
        case 8:
            cout<< "FIN DEL PROGRAMA!"<<endl;
            system("pause");
            break;
        default:
            cout<< "Ingrese una opcion correcta!"<<endl;
            break;
        }
    } while (menu!=7);
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
            ficheroEscritura<<nombreE<<"\t"<<paisE<<"\t"<<puntajeE<<"\n";
        }else{
            cout << "\tEquipo ya agregado!"<<endl;
        }
    }
    ficheroEscritura.close();
}

void EditarFichero(){
    int puntaje, temp_puntaje;
    string equipo, pais, temp_equipo, temp_pais;
    ficheroLectura.open("ProyectoFinalPED.txt", ios::in);
    ofstream temp("temporal.txt", ios::out);
    if (ficheroLectura.is_open()){
        cout << "Ingrese el nombre del nombre del equipo a modificar:\t";
        cin >> temp_equipo;
        ficheroLectura >> equipo;
        while (!ficheroLectura.eof()){
            ficheroLectura >> pais;
            ficheroLectura>>puntaje;
            if (!VerificarFichero(temp_equipo)){
                cout << "Ingresar el pais:\t";
                cin >> temp_pais;
                cout<< "Ingresar el nuevo puntaje:\t";
                cin >> temp_puntaje;
                BuscarNombre(temp_equipo)->pais=temp_pais;
                BuscarNombre(temp_equipo)->puntaje=temp_puntaje;
                cout << "Registro actualizado" << endl;
                temp << temp_equipo << " " << temp_pais << " "<< temp_puntaje << "\n";
            }else{
                temp << equipo << " " << pais << " "<< puntaje<< "\n";
            }
            ficheroLectura >> equipo;
        }
        ficheroLectura.close();
        temp.close();
    }else{
        cout << "Error al abrir el archivo";
    }
    remove("ProyectoFinalPED.txt");
    rename("temporal.txt", "ProyectoFinalPED.txt");
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
                cout << "\tRegistro eliminado"<<endl;
            }else{
                temp<<equipo<<"\t"<<pais<<"\t"<<puntaje<<"\n";
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