#include<iostream> 
#include <list> 
#include <stack> 
using namespace std; 
#define N 14

int ordely[N];
int cost[N];
int cam_max[N];  
// Classe que representa o grafo
class Graph 
{ 
// Num de vertices
    int V;
    // Ponteiro para lista de adjacencia
    list<int> *adj; 
    void topologicalSortUtil(int v, bool visited[], stack<int> &Stack); 

public: 
// Construtor 
    Graph(int V);    
  
    void addEdge(int v, int w); 
    void topologicalSort(); 
    void max_path();
}; 

Graph::Graph(int V) 
{ 
    this->V = V; 
    adj = new list<int>[V]; 
} 
  
void Graph::addEdge(int v, int w) 
{ 
  //Adiciona o vertice na lista
    adj[v].push_back(w);  
} 
  
void Graph::topologicalSortUtil( 
int v, bool visited[], stack<int> &Stack) 
{ 
    // Marca o vertice atual como visitado 
    visited[v] = true; 
  
    // Percorre todos os vertices adjacentes do vertice
    list<int>::iterator i; 
    for (i = adj[v].begin(); i != adj[v].end(); ++i) 
        if (!visited[*i]) 
            topologicalSortUtil(*i, visited, Stack); 
        
// Insere o vertice analisado para pilha  
    Stack.push(v); 
} 
  
void Graph::topologicalSort() 
{ 
    stack<int> Stack; 
  
    // Marca todos os vertices como nao visitados
    bool *visited = new bool[V]; 
    for (int i = 0; i < V; i++) 
        visited[i] = false; 
  
    // Chama recursivamente a funcao topologicalSortUtil para armazenar a ordenacao topologica
    for (int i = 0; i < V; i++) 
      if (visited[i] == false) 
        topologicalSortUtil(i, visited, Stack); 
  
    int i = 0;
	// Exibir elementos da pilha
    while (Stack.empty() == false) 
    { 
		ordely[i] = Stack.top();
        Stack.pop(); 
        i++;
        
    } 
} 

void Graph::max_path(){
	// relaxa todas as arestas
	for(int i=0; i <N; i++){
		cost[i]=0;
    cam_max[i]=999;
	}
	 // Percorre todos os vertices adjacentes do vertice
	int max = 0;
  list<int>::iterator i; 
  for (int a = 0; a < N ; a++){
  	int v = ordely[a];
		for (i = adj[v].begin(); i != adj[v].end(); ++i){
	      int viz = *i;
	      if (cost[viz]<cost[v]+1){
	  			cost[viz] = cost[v]+1;
				if(cost[viz]>max) max = cost[viz];
	    }
	  }
	}
  cout << "\nCusto maximo " << max;
}
  
int main() 
{ 
  //Obs.: No C++ o indice sempre começa por zero
  //Ex: Vértice 1 = 0
  //Ex: Vértice 2 = 1 ....
Graph g(N); 
    g.addEdge(0, 5);
    g.addEdge(0, 4);
    g.addEdge(0, 10); 
    g.addEdge(1, 4); 
    g.addEdge(1, 2); 
    g.addEdge(1, 8);
    g.addEdge(2, 5);
    g.addEdge(2, 9);
    g.addEdge(2, 6);
    g.addEdge(3, 2);
    g.addEdge(3, 6);
    g.addEdge(3, 13);
    g.addEdge(4, 7);
    g.addEdge(5, 8);
    g.addEdge(5, 12);
    g.addEdge(6, 5);
    g.addEdge(8, 7);
    g.addEdge(9, 10);
    g.addEdge(9, 11);
    g.addEdge(11, 13);
    g.addEdge(12, 9);
   
    
    cout << "Ordenacao Topologia do grafo: \n"; 
    g.topologicalSort(); 
    
    //Atenção ao soma ordely[i]+1 é necessária, caso o vértice desenhado começar por 1, caso contrário ele começar por zero tem que retirar o +1 do vetor ordely
    for(int i = 0; i< N; i++){
    	cout << ordely[i]<<" ";
	  }
	  
 	  g.max_path();
  return 0; 
} 