#ifndef HEADER_INCLUDED
#define HEADER_INCLUDED

#include <bits/stdc++.h>

# En primer lugar se estableció una clase NODO
struct Nodo{
Nodo * sig;  // nodo principal
Nodo * ant;       // contiene el costo total para lograr un estado
int E[3];   // {M,C,B} (eg. {3,3,1} -> 3 misioneros, 3 canibales, 1 bote en la izquierda)
priority_queue <puzzle> fringe;
unordered_set <string> visited;
};




class Puzzle {
	public:
		int p[3][3];
		int f, g;

		puzzle(string st) {
			f = 0;
			g = 0;
			int k=0;
			for(int i=0; i<3; i++) {
				for(int j=0; j<3; j++) {
					p[i][j] = st[k++] - '0';
				}
			}
		}

		void display() {
		    for(int i=0; i<3; i++) {
		        for(int j=0; j<3; j++) {
		            cout<<p[i][j]<<" ";
		        }
		        cout<<endl;
		    }
		}

		string to_string() {
		    string st = "123456780";
		    int k=0;
		    for(int i=0; i<3; i++) {
				for(int j=0; j<3; j++) {
					st[k++] = p[i][j] + '0';
				}
			}
			return st;
			// cout<<"String: "<<st;
		}

		int m_mismatch() {										//PART - 2
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

		int m_manhattan() {										//PART - 2
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

		bool estado_objetivo() {
			string goal = "123456780";
			string cur = to_string();
			if(goal == cur) {
				return 1;
			}
			return 0;
		}

		void evaluar(int h) {
			if(!h) {
				f = 0;
				int tile_count = tile_mismatch_count();
				f = tile_count + g;
			}
			else {
				f = 0;
				int manh_distance = manhattan_distance();
				f = manh_distance + g;
			}
		}

		void initialize() {
			f = 0;
			g = 0;
		}

};













#endif // HEADER_INCLUDED
