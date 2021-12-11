#include <iostream>
#include "header.h"

using namespace std;

int main()
{
    int depth;
	int rand_gen_initial_states = 10;
	cout<<"Ingrese la profundidad: ";
	cin>>depth;

	while(rand_gen_initial_states--) {

		string input = "123456780";
		random_shuffle(input.begin(), input.end());
		puzzle s(input);

		cout<<endl<<"-----------------------------------------------------"<<endl;
		cout<<"                       INTENTO "<<10-rand_gen_initial_states;
		cout<<endl<<"-----------------------------------------------------"<<endl;
		cout<<"Initial State: "<<endl;
		s.display();
		cout<<endl;
		cout<<endl<<"Profundidad 1 usando el recuento de errores de coincidencia: "<<endl;
		aStar(s, 0, 1);
		cout<<endl<<"Profundidad "<<depth<<" usando el recuento de errores de coincidencia: "<<endl;
		aStar(s, 0, depth);
		cout<<endl<<"Profundidad 1 usando la distancia de Manhattan: "<<endl;
		aStar(s, 1, 1);
		cout<<endl<<"Profundidad "<<depth<<" usando la distancia de Manhattan: "<<endl;
		aStar(s, 1, depth);

	}
}
