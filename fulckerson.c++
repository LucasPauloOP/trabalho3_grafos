/*
Essa implementação de Ford-Fulkerson é chamada de Edmonds-Karp, onde é utilizado a busca em largura (bfs) para encontrar o caminho de aumento de fluxo (augmenting path).

O algoritmo implementado com busca em profundidade (dfs) é uma variação também de Ford-Fulkerson.

*/


#include <iostream> 
#include <limits.h> 
#include <string.h> 
#include <queue> 
using namespace std; 
  
// Numero de vértices
#define V 12
  
/* Retorna verdadeiro se há um caminho entre a origem e o destino no grafo residual. Preenche o vetor parent[] para armazenar o caminho utilizando busca em largura
Versão Edmonds-Karp*/
bool bfs(int rGraph[V][V], int s, int t, int parent[], bool visited[]) 
{ 
    // Cria uma fila que enfileira o vertice de origem e o marca
    // como vistado
    queue <int> q; 
    q.push(s); 
    visited[s] = true; 
    parent[s] = -1; 
  
    // Loop busca em largura
    while (!q.empty()) 
    { 
        int u = q.front(); // Pega o primeiro da fila
        q.pop(); // Retira da fila o primeiro
  
        for (int v=0; v<V; v++) 
        { 
            if (visited[v]==false && rGraph[u][v] > 0) 
            { 
                q.push(v); // Insere na fila o caminho encontrado
                parent[v] = u; // Preenche o caminho encontrado
                visited[v] = true; 
            } 
        } 
    } 
    // Se o destino foi encontrado partindo da origem retorna 
    // verdadeiro senão falso
    return (visited[t] == true); 
} 

/* Retorna verdadeiro se há um caminho entre a origem e o destino no grafo residual. Preenche o vetor parent[] para armazenar o caminho utilizando busca em produndidade */
bool dfs(int rGraph[V][V], int s, int t, int parent[], bool visited[]) 
{ 
  /* Condição de parada */
  if(s == t) return true;
  visited[s] = true;
 
  for (int v=0; v<V; v++) {
    if(rGraph[s][v] > 0 && !visited[v]){
        parent[v] = s;
        //printf("%d %d %d %d %d %d \n", parent[0], parent[1], parent[2], parent[3], parent[4], parent[5]);
        //printf("%d \n", s);
        if(dfs(rGraph, v, t, parent, visited))
          return true;
    }
  }
  return false;
}
  
// Retorna o fluxo máximo de s para t no grafo passado como parâmetro
int fordFulkerson(int graph[V][V], int s, int t) 
{ 
  int u, v, c; 
  bool visited[V]; 
  memset(visited, 0, sizeof(visited)); 
  c= 0;
  
  // Cria um grafo residual e o preenche com a capacidade
  // do grafo original
  int rGraph[V][V]; // Grafo residual
  for (u = 0; u < V; u++) 
      for (v = 0; v < V; v++) 
        rGraph[u][v] = graph[u][v]; 
  
  int parent[V];  // Armazena o caminho
  
  int max_flow = 0;  // Inicialização da variável que armazenará o valor máximo de fluxo.

  //Enquanto tiver caminho da origem para o destino aplica o busca em largura 
  while (dfs(rGraph, s, t, parent, visited)) 
  { 
    //Encontra a aresta de menor peso no caminho encontrado
    int path_flow = INT_MAX; 
    for (v=t; v!=s; v=parent[v]) 
    { 
      u = parent[v]; 
      path_flow = min(path_flow, rGraph[u][v]); 
      //printf("%d \n", u);
    }  
    //Atualiza as capacidades das arestas do grafo residual e as arestas reversas
    for (v=t; v != s; v=parent[v]) 
    { 
      u = parent[v]; 
      rGraph[u][v] -= path_flow; 
      rGraph[v][u] += path_flow; 
      //printf("%d \n", u);
    } 
    //Imprimir na tela path_flow
    //Imprimir grafo residual

    for (u = 0; u < V; u++) {
      printf("\n");
      for (v = 0; v < V; v++) 
        printf("%d ", rGraph[u][v]);
    }

    // Adicionar fluxo de caminho ao fluxo geral 
    max_flow += path_flow; 
    c++;
    memset(visited, 0, sizeof(visited)); 
    printf ("\n\nIteração %d, fluxo máximo encontrado: %d \n",c ,max_flow);
  } 
  
  // Retorna o fluxo máximo 
   printf ("Fluxo maximo do grafo é: %d",max_flow);
  return max_flow; 
} 
  
int main() 
{    
  int graph[V][V] = {
  { 0, 6, 8, 14, 0, 0, 0, 0, 0, 0, 0, 0 }, 
  { 0, 0, 4, 0, 6, 2, 0, 0, 0, 0, 0, 0 }, 
  { 0, 0, 0, 0, 0, 0, 7, 0, 0, 3, 0, 0 }, 
  { 0, 0, 1, 0, 0, 0, 8, 2, 0, 0, 0, 0 }, 
  { 0, 0, 0, 0, 0, 8, 0, 0, 2, 0, 0, 0 }, 
  { 0, 0, 0, 0, 0, 0, 0, 0, 9, 1, 6, 0 }, 
  { 0, 5, 0, 0, 0, 0, 0, 11, 0, 0, 0, 0 }, 
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 9, 2 }, 
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 9 }, 
  { 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 8, 6 }, 
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12 }, 
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },  
}; 

    fordFulkerson(graph, 0, 11);

  //cout << "Fluxo maximo do grafo é: " << fordFulkerson(graph, 0, 7);
  return 0; 
} 