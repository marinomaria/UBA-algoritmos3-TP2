#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using Costo = unsigned long int;
using Arista = pair<size_t,size_t>;


//Estructura Union-Find.
//Proporciona dos funciones: Unite y Find
struct UF {
    //vectores internos
    //  p: Vector con los parents
    //  s: Vector con tamaños
    //  m: Vector con arista mínima
    vector<int> p, s, m;
    
    //Constructor
    UF(int n): p(n, -1), s(n, 1), m(n, inf) {} //poner algo de verdad en inf
    
    //unite: Hace la unión y devuelve el tamaño del resultante
    int unite(int v, int w) {
        v = find(v); w = find(w);
        if(v == w) return s[v];
        if(s[v] < s[w]) swap(v, w);
        p[w] = v; //El árbol de mayor tamaño queda como padre
		//HACER EL DOBLE FOR y poner m[v] = mínima_arista_del_doble_for
        return s[v] += s[w];
    }
    
    //find: Devuelve el parent (mentira, devuelve la raíz)
    int find(int v) {
        return p[v] == -1 ? v : p[v] = find(p[v]); //Recursión para path compression
    }

    int minima_arista(int v) {
        return m[componentes.find(v)]; //Recursión para path compression
    }

};


int main() {
    size_t n,m;
    cin >> n >> m;

    UF componentes(n+1);                //Para indexar desde 1
    vector<pair<Costo, Arista>> valores(m);

    //Lectura del vector de aristas
    for (auto& [c, e] : valores) cin >> e.first >> e.second >> c;

    //Ordenamiento de las aristas por peso
    sort(valores.begin(), valores.end());

    vector<Arista> mst;
    unsigned long int costo_total = 0;

    //Recorre las aristas ordenadas y se queda con aquellas que unan
    //dos vértices de componentes conexas distintas, uniéndolas
    //for (auto [c, e] : valores) {
	for (int i=0; i<size(valores); i++){
		vector<int> this_level_trees;
		auto [c,e] = valores[i];
        auto [i,j] = e;
        if (componentes.find(i) != componentes.find(j)) {
            costo_total += c#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using Costo = unsigned long int;
using Arista = pair<size_t,size_t>;


//Estructura Union-Find.
//Proporciona dos funciones: Unite y Find
struct UF {
    //vectores internos
    //  p: Vector con los parents
    //  s: Vector con tamaños
    vector<int> p, s;
    
    //Constructor
    UF(int n): p(n, -1), s(n, 1) {}
    
    //unite: Hace la unión y devuelve el tamaño del resultante
    int unite(int v, int w) {
        v = find(v); w = find(w);
        if(v == w) return s[v];
        if(s[v] < s[w]) swap(v, w);
        p[w] = v; //El árbol de mayor tamaño queda como padre
        return s[v] += s[w];
    }
    
    //find: Devuelve el parent
    int find(int v) {
        return p[v] == -1 ? v : p[v] = find(p[v]); //Recursión para path compression
    }
    
};


int main() {
    size_t n,m;
    cin >> n >> m;

    UF componentes(n+1);                //Para indexar desde 1
    vector<pair<Costo, Arista>> valores(m);

    //Lectura del vector de aristas
    for (auto& [c, e] : valores) cin >> e.first >> e.second >> c;

    //Ordenamiento de las aristas por peso
    sort(valores.begin(), valores.end());

    vector<Arista> mst;
    unsigned long int costo_total = 0;

    //Recorre las aristas ordenadas y se queda con aquellas que unan
    //dos vértices de componentes conexas distintas, uniéndolas
    for (auto [c, e] : valores) {
        auto [i,j] = e;
        if (componentes.find(i) != componentes.find(j)) {
            mst.push_back(Arista(i,j));
            costo_total += c;
            componentes.unite(i,j);
        }
    }

    //Salida en formato CSES
    if (mst.size()<n-1) {
        cout << "IMPOSSIBLE";
    } else {
        cout << costo_total;
    }

    return 0;
};
            componentes.unite(i,j);
			this_level_trees.push_back(componentes.find(j))
        }
		int peso_proxima_arista = valores[i+1][0];
		if (c > peso_proxima_arista){
			for (int i = 0; i<size(this_level_trees); i++){
				this_level_trees[i] = componentes.find(this_level_trees[i])
			}
			//this_level_trees = std::unique(this_level_trees) HACER QUE ESTO ANDE
			for (auto t : this_level_trees){
				if (componentes.arista_minima(t) == c) {suma_total = suma_total + componentes.size(t) }
			}
			//componentes tiene que tener una forma de ver size y una forma de ver arista mínima
		}
    }

    //Salida en formato CSES
    if (mst.size()<n-1) {
        cout << "IMPOSSIBLE";
    } else {
        cout << costo_total;
    }

    return 0;
}
