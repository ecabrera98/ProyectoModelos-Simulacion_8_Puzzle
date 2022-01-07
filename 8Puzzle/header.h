#ifndef HEADER_INCLUDED
#define HEADER_INCLUDED

//Librerías Utilizadas
#include <queue>
#include <unordered_set>

using namespace std;

class puzzle {
	public:
		int p[3][3];//generación de la matriz de 3 x 3 necesaria para 8 PUZZLE
		int f, g; //generación de las funciones f(n) y g(n)

		puzzle(string st) { //generación del tablero 8 PUZZLE
		                    //mediante el uso de un string en una matriz (PUZZLE)
			f = 0;
			g = 0;
			int k=0;
			for(int i=0; i<3; i++) {
				for(int j=0; j<3; j++) {
					p[i][j] = st[k++] - '0';
				}
			}
		}

		void desplegar() { //función que imprime el tablero del 8 Puzzle
		    for(int i=0; i<3; i++) {
		        for(int j=0; j<3; j++) {
		            cout<<p[i][j]<<" ";
		        }
		        cout<<endl;
		    }

		}

		string to_string() { //transformación de los elementos del 8 Puzzle en string, separando con 0 cada número del tablero
		    string st = "123456780";
		    int k=0;
		    for(int i=0; i<3; i++) {
				for(int j=0; j<3; j++) {
					st[k++] = p[i][j] + '0';
				}
			}
			return st;
		}

		int distancia_mismatch() {//aplicación del método recuento de errores
			int count = 0;
			string est_objetivo = "123456780";
			string aux_st = to_string();
			for(int i=0; i<9; i++) {
				if(aux_st[i] != '0' && est_objetivo[i] != aux_st[i]) {
					count++;
				}
			}
			return count;
		}

		int distancia_manhattan() {//aplicacion del método de la Distancia Manhattan
                                   //métrica de distancia entre dos puntos en un espacio vectorial de dimensión N
                                   //es la suma de la diferencia absoluta entre las medidas en todas las dimensiones de dos puntos
			int dist = 0;
			for(int i=0; i<3; i++) {
				for(int j=0; j<3; j++) {
					switch(p[i][j]) {
						case 1: dist += abs(i - 0) + abs(j - 0); break;
						case 2: dist += abs(i - 0) + abs(j - 1); break;
						case 3: dist += abs(i - 0) + abs(j - 2); break;
						case 4: dist += abs(i - 1) + abs(j - 0); break;
						case 5: dist += abs(i - 1) + abs(j - 1); break;
						case 6: dist += abs(i - 1) + abs(j - 2); break;
						case 7: dist += abs(i - 2) + abs(j - 0); break;
						case 8: dist += abs(i - 2) + abs(j - 1); break;
					}
				}
			}
			return dist;
		}

		bool estado_objetivo() {//generación del estado objetivo del 8 PUZZLE
			string objetivo = "123456780";
			string aux = to_string();
			if(objetivo == aux) {
				return 1;
			}
			return 0;
		}

		int funcion_n(int n) {//generación de la función f(n) = g(n) + h(n) mediante el uso de DistMatch y Distancia Manhathan
			if(n==0) {
				f = 0;
				int mismatch_dis = distancia_mismatch();
				cout<<"--------------------------"<<endl;
				cout<<"h(n): "<<mismatch_dis<<"\n"<<endl;
				cout<<"g(n): "<<g<<"\n"<<endl;
				cout<<"--------------------------"<<endl;
				f = mismatch_dis + g;
			}
			else {
				f = 0;
				int manh_distancia = distancia_manhattan();
				cout<<"--------------------------"<<endl;
				cout<<"h(n): "<<manh_distancia<<"\n"<<endl;
				cout<<"g(n): "<<g<<"\n"<<endl;
				cout<<"--------------------------"<<endl;
				f = manh_distancia + g;
			}
			return f;
		}

		void initialiciar_f_g() {// inicializar f(n) y g(n) a 0 nuevamente para futuras asignaciones
			f = 0;
			g = 0;
		}

};
//esta parte de aquí se encarga de ordenar la cola de prioridad
bool operator<(const puzzle& p1, const puzzle& p2) { //operador booleano para los estados del 8 PUZZLE
                                                     //valida si un estado se aleja demasiado del estado objetivo
    return p1.f > p2.f;
}

priority_queue <puzzle> frontera; //generación de la estructura de datos: cola de prioridad

unordered_set <string> visitados; //utilización de un conjunto desordenado para
                                  //almacenar elementos únicos sin ningún orden en particular
                                  //en este caso para los nodos visitados


int m, no_nodos; //declaración de las variables tamaño "m" y número de nodos

bool isValid(int i, int j) {//validacion de las posiciones de la matriz
	if(i>=0 && j>=0 && i<3 && j<3)
		return 1;
	else
		return 0;
}

puzzle movimientos(puzzle s, int i1, int j1, int i2, int j2) {//función auxiliar para los movimientos de los elementos del tablero
	string st = s.to_string();
	int index1 = i1*3+j1, index2 = i2*3+j2;
	char temp_char = st[index1];
	st[index1] = st[index2];
	st[index2] = temp_char;
	puzzle new_puz(st);
	return new_puz;
}

void expandir_arbol(puzzle s, queue <puzzle> &colaFrontera) { //Utilización del algoritmo A *, el cual realiza
                                                              //un seguimiento de cada nodo visitado,
                                                              //ignorando los nodos que ya se visitaron,
	for(int i=0; i<3; i++) {
		for(int j=0; j<3; j++) {
			if(s.p[i][j] == 0) {
				if(isValid(i-1, j)) { //moverse  una posición a la izquierda
					puzzle aux_puz = movimientos(s, i, j, i-1, j);
					if(visitados.find(aux_puz.to_string()) == visitados.end()) {
						visitados.insert(aux_puz.to_string());
						aux_puz.g++;
						no_nodos++;
						colaFrontera.push(aux_puz);
					}
				}
				if(isValid(i+1, j)) { //moverse  una posición a la derecha
					puzzle aux_puz = movimientos(s, i, j, i+1, j);
					if(visitados.find(aux_puz.to_string()) == visitados.end()) {
						visitados.insert(aux_puz.to_string());
						aux_puz.g++;
						no_nodos++;
						colaFrontera.push(aux_puz);
					}
				}
				if(isValid(i, j-1)) {//moverse una posición hacia abajo
					puzzle aux_puz = movimientos(s, i, j, i, j-1);
					if(visitados.find(aux_puz.to_string()) == visitados.end()) {
						visitados.insert(aux_puz.to_string());
						aux_puz.g++;
						no_nodos++;
						colaFrontera.push(aux_puz);
					}
				}
				if(isValid(i, j+1)) {//moverse una posición hacia arriba
					puzzle aux_puz = movimientos(s, i, j, i, j+1);
					if(visitados.find(aux_puz.to_string()) == visitados.end()) {
						visitados.insert(aux_puz.to_string());
						aux_puz.g++;
						no_nodos++;
						colaFrontera.push(aux_puz);
					}
				}

			}
		}
	}
	//
}

queue <puzzle> expasion_por_profundidad(puzzle s, int prof) { //prof número de brazos desde la raíz del árbol hasta un nodo
	queue <puzzle> temp1;// declaración de una cola temporal para la expación de los nodos
	expandir_arbol(s, temp1);//evaluación de posibles nodos para el estado actual

	return temp1;//devolvemos la cola temporal generada
}

puzzle comenzar_8PUZZLE(puzzle s, int n) {//metodo principal del juego 8 PUZZLE
	//inicializamos las variables
	int cont_estado_obj = 0;

    int prof=1;
	no_nodos = 0;
	s.initialiciar_f_g();
	visitados.clear();
	visitados.insert(s.to_string());
	frontera = priority_queue <puzzle>();


	//realizamos operaciones del algoritmo A* mientras el tablero sea diferente del estado objetivo
	while(!s.estado_objetivo() ) {
		queue <puzzle> aux_puzzle = expasion_por_profundidad(s, prof); //devuelve la cola frontera
		deque <puzzle> temp;

		cout<<"Estado Actual: "<<endl;  //impresión de los diferentes estados generados
        s.desplegar();
        cout<<"---------------------"<<endl;  //impresión de los diferentes estados generados


		//pongo los resultados de la cola frontera al final
		while(!aux_puzzle.empty()) {
			temp.push_back(aux_puzzle.front());
			aux_puzzle.pop();
		}

        cout<<"Opc ultima frontera--------"<<endl;
		//calculo el f(n) para cada posibilidad
		for(int i = 0; i < temp.size(); i++) {//recorrer los posibles movimientos
			temp[i].funcion_n(n);//calculo el fn de cada posible nodo
			temp[i].desplegar();//imprimo todas las opciones de la última frontera
			cout<<"f(n): "<<temp[i].f<<"\n"<<endl;
			frontera.push(temp[i]);//se realiza un push a la frontera con los nodos ya evaluados
		}
		 cout<<"--------------------------"<<endl;


		if(!frontera.empty()) {
			s = frontera.top();//retornamos el valor más reciente de la frontera
			frontera.pop();//asignamos ese valos a la frontera
		}
		else break;
		cout<<"Mejor f(n): "<<s.f<<endl; //imprimimos el mejor f(n) encontrado
		cont_estado_obj = cont_estado_obj + s.f;
		cout<<"f(n) Acumulado: "<<cont_estado_obj<<endl; //imprimimos el valor acumulado de los mejores f(n) encontrados
		cout<<endl;
	}

	if(s.estado_objetivo()){  //si ya se llega al estado objetivo "12345678" hemos ganado
		cout<<"Estado objetivo alcanzado!"<<endl;
		s.desplegar();
    }

	else{ //en caso de que nuestro estado inicial no tenga solución nos dirá que el estado objetivo no fue alcanzado
	   cout<<"Estado objetivo no alcanzado!"<<endl;
		s.desplegar();
	}
	cout<<"Número de nodos: "<<no_nodos<<endl;
	cout<<"f(n) Total: "<<cont_estado_obj<<endl; //imprimimos el valor acumulado de los mejores f(n) encontrados
    cout<<endl;
    return s;
}

#endif // HEADER_INCLUDED
