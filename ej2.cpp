#include <iostream>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;

#define INF numeric_limits<int>::max()

using Costo = unsigned long int;
using Arista = pair<size_t,size_t>;

// M = matriz de adyacencia TODO
vector<vector<int>> M;

//Estructura Union-Find.
struct UF {
    //vectores internos
    //  p: Vector con los parents
    //  s: Vector con tamaños
    //  m: Vector con arista mínima
    vector<int> p, s, m;
    //  h: Vector con todos los hijos
	vector<list<int>> h; //tiene que ser un vector [[0],[1],[2],[3]...]
    
    //Constructor
    UF(int n): p(n, -1), s(n, 1), m(n, INF) {} //falta el constructor de h
    
    //unite: Hace la unión, teniendo en cuenta todas las variables internas
    int unite(int v, int w) {
        v = find(v); w = find(w);
        if(v == w) return s[v];
        if(s[v] < s[w]) swap(v, w);
        p[w] = v; //El árbol de mayor tamaño queda como padre
		//Acá hace un doble for para poder mantener cuál es el arista mínima del set
		int arista_minima = INF;
		for (auto i : h[v]) {
			for (auto j : h[w]){
				if (M[i][j] < arista_minima) arista_minima = M[i][j];
			}
		}
		m[v] = min({arista_minima, m[v], m[w]});

        s[v] += s[w];
		//h me enumera todos los nodos que son parte del set
        h[v].splice(h[v].end(), h[w]);
    }
    
    //find: Devuelve la raiz del set
    int find(int v) {
        return p[v] == -1 ? v : p[v] = find(p[v]); //Recursión para path compression
    }

    int minima_arista(int v) {
		v = find(v);
        return m[v];
    }

	int size(int v) {
		v = find(v);
		return s[v];
	}

};


int main() {
	//Esto no lo toqué
    size_t n,m;
    cin >> n >> m;

    UF componentes(n+1);                //Para indexar desde 1
    vector<pair<Costo, Arista>> valores(m);

    //Lectura del vector de aristas
    for (auto& v : valores) cin >> v.second.first >> v.second.second >> v.first;

    //Ordenamiento de las aristas por peso
    sort(valores.begin(), valores.end());
	//Esto no lo toqué
	
	int suma_total = 0;


    //Recorre las aristas ordenadas y se queda con aquellas que unan
    //dos vértices de componentes conexas distintas, uniéndolas
    vector<int> this_level_trees; //Acá guardo todos los árboles que fueron expandidos para este costo de arista
	for (int i = 0; i < valores.size() - 1; i++) {
        int c,u,v;
        Arista e;
		tie(c,e) = valores[i];
        tie(u, v) = e;
        if (componentes.find(u) != componentes.find(v)) {
            componentes.unite(u,v);
			this_level_trees.push_back(componentes.find(v));
        }
		//Si es la última arista de este peso, paso a sumar todo
		int peso_proxima_arista = valores[i + 1].first;
		if (c > peso_proxima_arista){
			//Acá necesito convertir this_level_trees en una lista de raíces sin repetir
			for (int & this_level_tree : this_level_trees){
				this_level_tree = componentes.find(this_level_tree);
			}
            sort(this_level_trees.begin(), this_level_trees.end());
            vector<int>::iterator it;
            it = unique(this_level_trees.begin(), this_level_trees.end());

            this_level_trees.resize(distance(this_level_trees.begin(),it));



			for (auto t : this_level_trees){
				if (componentes.minima_arista(t) == c) suma_total = suma_total + componentes.size(t);
			}
		}
    }

    //Salida en formato CSES
    //if (mst.size()<n-1) {
        //cout << "IMPOSSIBLE";
    //} else {
        //cout << costo_total;
    //}

    //return 0;
}
