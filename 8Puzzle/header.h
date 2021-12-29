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

		void desplegar() { //función que imprime el puzzle
		    for(int i=0; i<3; i++) {
		        for(int j=0; j<3; j++) {
		            cout<<p[i][j]<<" ";
		        }
		        cout<<endl;
		    }
		    cout<<"\n";
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

		int distancia_mismatch() {
			int count = 0;
			string goal = "123456780";
			string cur = to_string();
			for(int i=0; i<9; i++) {
				if(cur[i] != '0' && goal[i] != cur[i]) {
					count++;
				}
			}
			return count;
		}

		int distancia_manhattan() {
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

		void update_f(int n) {//generación de la función f(n) = g(n) + h(n) mediante el uso de DistMatch y Distancia Manhathan
			if(!n) {
				f = 0;
				int mismatch_dis = distancia_mismatch();
				f = mismatch_dis + g;
			}
			else {
				f = 0;
				int manh_distancia = distancia_manhattan();
				f = manh_distancia + g;
			}
		}

		void initialize() {// inicializar f(n) y g(n) a 0 nuevamente para futuras asignaciones
			f = 0;
			g = 0;
		}

};

bool operator<(const puzzle& p1, const puzzle& p2) {
    return p1.f > p2.f;
}

priority_queue <puzzle> frontera; //generación de la estructura de datos: cola de prioridad
unordered_set <string> visitados; //utilización de un conjunto desordenado para
                                  //almacenar elementos únicos sin ningún orden en particular
                                  //en este caso para los nodos visitados

int m, no_nodos; //declaración de las variables tamaño "n" y número de nodos

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

void expandir_arbol(puzzle s, queue <puzzle> &colaFrontera) {
	for(int i=0; i<3; i++) {
		for(int j=0; j<3; j++) {
			if(s.p[i][j] == 0) {
				if(isValid(i-1, j)) {
					puzzle new_puz = movimientos(s, i, j, i-1, j);
					if(visitados.find(new_puz.to_string()) == visitados.end()) {
						visitados.insert(new_puz.to_string());
						new_puz.g++;
						no_nodos++;
						colaFrontera.push(new_puz);
					}
				}
				if(isValid(i+1, j)) {
					puzzle new_puz = movimientos(s, i, j, i+1, j);
					if(visitados.find(new_puz.to_string()) == visitados.end()) {
						visitados.insert(new_puz.to_string());
						new_puz.g++;
						no_nodos++;
						colaFrontera.push(new_puz);
					}
				}
				if(isValid(i, j-1)) {
					puzzle new_puz = movimientos(s, i, j, i, j-1);
					if(visitados.find(new_puz.to_string()) == visitados.end()) {
						visitados.insert(new_puz.to_string());
						new_puz.g++;
						no_nodos++;
						colaFrontera.push(new_puz);
					}
				}
				if(isValid(i, j+1)) {
					puzzle new_puz = movimientos(s, i, j, i, j+1);
					if(visitados.find(new_puz.to_string()) == visitados.end()) {
						visitados.insert(new_puz.to_string());
						new_puz.g++;
						no_nodos++;
						colaFrontera.push(new_puz);
					}
				}

			}
		}
	}
	s.desplegar();

}

queue <puzzle> expasion_por_profundidad(puzzle s, int depth) {
	queue <puzzle> temp1;
	expandir_arbol(s, temp1);
	queue <puzzle> temp2(temp1);
	queue <puzzle> temp3;
	depth--;
	while(depth>0) {
		while(!temp2.empty()) {
			puzzle c = temp2.front();
			temp2.pop();
			expandir_arbol(c, temp3);
			queue <puzzle> temp4(temp3);
			while(!temp4.empty()) {
				temp1.push(temp4.front());
				temp4.pop();
			}
		}
		depth--;
		while(!temp3.empty()) {
			temp2.push(temp3.front());
			temp3.pop();
		}
	}
	return temp1;
}

puzzle comenzar_8PUZZLE(puzzle s, int h, int depth) {
	m = 0;
	no_nodos = 0;
	s.initialize();
	visitados.clear();
	visitados.insert(s.to_string());
	frontera = priority_queue <puzzle>();

	while(!s.estado_objetivo()) {
		queue <puzzle> mod_exp_result = expasion_por_profundidad(s, depth);
		deque <puzzle> temp;
		while(!mod_exp_result.empty()) {
			temp.push_back(mod_exp_result.front());
			mod_exp_result.pop();
		}
		for(int i = 0; i < temp.size(); i++) {
			temp[i].update_f(h);
			frontera.push(temp[i]);
			if(frontera.size() > m) {
				m = frontera.size();
			}
		}
		if(!frontera.empty()) {
			s = frontera.top();
			frontera.pop();
		}
		else break;
		// g++;
	}
	if(s.estado_objetivo())
    {
        s.desplegar();
		cout<<"Estado objetivo alcanzado!"<<endl;
    }
	else
		cout<<"Estado objetivo no alcanzado!"<<endl;
		s.desplegar();

	cout<<"Heurística : "<<m<<endl;
	cout<<"Número de nodos: "<<no_nodos<<endl;
	return s;
}

#endif // HEADER_INCLUDED
