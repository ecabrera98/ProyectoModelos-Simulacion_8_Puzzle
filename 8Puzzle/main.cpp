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

using namespace std;

int main()
{
	//"413705826", "813402765", "246583017", "038145672",
	//"301682475", "182043765", "301682475", "361285047", "261705834", "203714568", "501837264",
	//"725368401", "157820643", "713248650", "274518306", "437165280", "452710836", "062537481",
	//"804125376", "235107846"


        puzzle s("413705826"); //generamos una matriz de tipo Puzzle con el estado inicial "413705826"

		cout<<endl<<"-----------------------------------------------------"<<endl;
		cout<<"Algoritmo A*  8-PUZZLE GRUPO 1 "<<endl;
		cout<<endl<<"-----------------------------------------------------"<<endl;
		cout<<"Estado Inicial: "<<endl;
		s.desplegar();
		cout<<endl;
		cout<<endl<<"Solución 8 PUZZLE usando Distmatch: "<<endl;
		comenzar_8PUZZLE(s, 0, 1);

		cout<<endl<<"Solución 8 PUZZLE usando la Distancia Manhattan: "<<endl;
		comenzar_8PUZZLE(s, 3, 1);
}
