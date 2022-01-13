/*
PERÍODO ACADÉMICO: 2021 B
ASIGNATURA: Modelos y Simulación
PROFESOR: Phd. José Lucio
PROYECTO PRIMER BIMESTRE
FECHA DE ENTREGA: 13/01/2022
Autores:  Cabrera Edison
          Gallardo Erick
          Garcia Andres
          Hidalgo Valeria
Tema: Algoritmo A*  8-PUZZLE
*/


#include <iostream>
#include "header.h"
#include "time.h"

using namespace std;

int main()
{
    int op = -1;//operador para el menu
    srand ( time(NULL) ); //temporizador
    //generación de tableros validos
	const string input_Arr[20] = {"413705826", "813402765", "246583017", "038145672",
	"301682475", "182043765", "301682475", "361285047", "261705834", "203714568", "501837264",
	"725368401", "157820643", "713248650", "274518306", "437165280", "452710836", "062537481",
	"804125376", "235107846"};

       //inicializacion del menu
       do {
             //generamos una matriz para los estados iniciales del Puzzle
             int randIndex = rand() % 20;
             puzzle s(input_Arr[randIndex],0);//generación del tablero inicial

		     cout<<endl<<"-----------------------------------------------------"<<endl;
		     cout<<"Algoritmo A*  8-PUZZLE GRUPO 1 "<<endl;
		     cout<<endl<<"-----------------------------------------------------"<<endl;
		     cout<<"Estado Inicial: "<<endl;
		     s.desplegar();
		     cout<<"Distancia manhattan actual: "<<s.distancia_manhattan()<<endl;//calculo inicial del DistMatch
		     cout<<"Distancia mismatch actual: "<<s.distancia_mismatch()<<endl;//caclculo inicial de la Distancia Manhattan

		     cout<<endl<<"~~~~~~~~~~~~~~~~~~M E N U~~~~~~~~~~~~~~~~~~~~~~~~~ "<<endl;
		     cout<<endl<<"Seleccione una opcion: "<<endl;
		     cout<<"0: Ejecutar puzzle actual f(n) Distmatch "<<endl;
		     cout<<"1: Ejecutar puzzle actual f(n) Distancia Manhattan"<<endl;
		     cout<<"2: Cambiar puzzle actual"<<endl;
		     cout<<"3: Cerrar programa"<<endl;
		     cout<<endl;
		     cout<<endl<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<<endl;
		     cin>>op;


		     switch (op){
                case 0:
                    cout<<endl<<"Solución 8 PUZZLE usando Distmatch: "<<endl;//utilizacion del metodo DistMatch
                    comenzar_8PUZZLE(s, 0);

                    break;

                case 1:
                    cout<<endl<<"Solución 8 PUZZLE usando la Distancia Manhattan: "<<endl;//utilizacion del metodo Distancia Manhattan
                    comenzar_8PUZZLE(s, 1);
                    break;

                case 3:
                    exit(0);// salir del programa
                    break;
		     }

		} while(op != -1);//caso contrario cambiar de tablero

		return 0;
}

