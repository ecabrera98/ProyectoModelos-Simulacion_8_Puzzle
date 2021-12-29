/*
PERÍODO ACADÉMICO: 2021 B
ASIGNATURA: Modelos y Simulación
PROFESOR: Phd. José Lucio
FECHA DE ENTREGA: 13/01/2022
Autores:  Cabrera Edison
          Gallardo Erick
          Garcia Andres
          Hidalgo Valeria

Tema: Algoritmo A*  8-PUZZLE

*/


#include <iostream>
#include "header.h"



using namespace std;

int main()
{
	srand ( time(NULL) );
	//const string input_Arr[20] = {"413705826", "813402765", "246583017", "038145672",
	//"301682475", "182043765", "301682475", "361285047", "261705834", "203714568", "501837264",
	//"725368401", "157820643", "713248650", "274518306", "437165280", "452710836", "062537481", "804125376", "235107846"};

    const string input_Arr[] = {"813402765"};

	int RandIndex = rand() % 1; //-----(3)
    puzzle s(input_Arr[RandIndex]); //-----(4)

		/*string input = "123456780";
		random_shuffle(input.begin(), input.end());
		puzzle s(input);*/

		cout<<endl<<"-----------------------------------------------------"<<endl;
		cout<<"Algoritmo A*  8-PUZZLE GRUPO 1 "<<endl;
		cout<<endl<<"-----------------------------------------------------"<<endl;
		cout<<" Estado Inicial: "<<endl;
		s.desplegar();
		cout<<endl;
		cout<<endl<<"Solución 8 PUZZLE usando el Distmatch: "<<endl;
		comenzar_8PUZZLE(s, 0, 1);

		cout<<endl<<"Solución 8 PUZZLE usando la distancia de Manhattan: "<<endl;
		comenzar_8PUZZLE(s, 1, 1);


}
