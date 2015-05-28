#include <stdio.h>
#include <stdlib.h>

/*------- Definições -------- */

#define BRANCO -1
#define CINZA 0
#define PRETO 1

/*------- Estruturas -------- */

/*Lista encadeada para guardar os vizinhos de cada nó.*/
typedef struct node {
   int id; /*identificação do vértice*/
   struct node *proximo;
} Node;

typedef struct graph {
   int V; /*Número de vértices no Grafo.*/
   int E; /*Número de arestas no Grafo.*/
   Node **listadj; /*Lista de adjacências.*/
} Graph;

/*------------------------*/


/*------- Funções -------- */

Graph* criar_grafo (int V);

void adicionar_aresta (Graph *G, int v, int w);

Node* criar_vertice (int v, Node *lista);

void DFS (Graph *G);

void DFS_Visit (int u, Graph *G, int cor[], Node **lista);

/*------------------------*/

/* A função abaixoc cria um Grafo e inicializa seus atributos. */
/* Também são criadas listas de adjancência vazias para cada um dos vértices. */
Graph* criar_grafo (int V) {
   Graph *G = (Graph *)malloc(sizeof(Graph));
   G->V = V;
   G->E = 0;
   G->listadj = (Node **)malloc(V * sizeof (Node *));
   int v;
   for (v = 0; v < V; v++)
      G->listadj[v] = NULL;
   return G;
}

/* A função abaixo insere uma aresta u-v no Grafo G.
Se o Grafo já tem a aresta então nada é feito. */
void adicionar_aresta (Graph *G, int u, int v) {
   Node *aux; /*Variável para percorrer a lista de adjacência do vértice {u}*/
   for (aux = G->listadj[u]; aux != NULL; aux = aux->proximo)
      if (aux->id == v) return;
   G->listadj[u] = criar_vertice (v, G->listadj[u]);
   G->E++; /*Incrementa o número de arestas no Grafo.*/
}

/*A função abaixo aloca um novo nó {v} na lista encadeada {lista}.*/
Node* criar_vertice (int v, Node *lista) {
   Node *novo = (Node *)malloc(sizeof(Node));
   novo->id = v;
   novo->proximo = lista;
   return novo;
}

/**/
Node* inicializa_lista () {
  return NULL;
}

/**/
Node* insere_inicio (Node *lista, int vertex) {
   Node *novo = (Node *)malloc(sizeof(Node));
   novo->id = vertex;
   novo->proximo = lista;
   return novo;
}

/*Ordenacao topológica: */
void OrdenacaoTopologica (Graph *G) {

   Node *lista = inicializa_lista ();

   int cor[G->V];
   int u;
   for (u = 0; u < G->V; u++) {
      cor[u] = BRANCO;
   }

   for (u = 0; u < G->V; u++) {
      if (cor[u] == BRANCO) {
         DFS_Visit (u, G, cor, &lista);
      }
   }

   printf("Ordenação topológica: ");
   /*... Insira o código para imprimir a lista! ...*/
   Node *listatmp = lista;
   while (listatmp!=NULL)
   {
        printf("%d\n", listatmp->id);
        listatmp = listatmp->proximo;
   }
   printf("\n\n");
}

void DFS_Visit (int u, Graph *G, int cor[], Node **lista) {
   cor[u] = CINZA;
   Node *v; /*Variável para percorrer a lista de adjacência do vértice {u}*/
   for (v = G->listadj[u]; v != NULL; v = v->proximo) {
      if (cor[v->id] == BRANCO) {
         DFS_Visit (v->id, G, cor, lista);
      }
      else if(cor[v->id] == CINZA)
      {
        printf("Tem ciclo.\n");
        exit(0);
      }
   }
   cor[u] = PRETO;
   *lista = insere_inicio (*lista, u);
}

int main () {

   /*Número de vértices necessários no Grafo: */
   int V = 6;

   /*Inicializando o Grafo: */
   Graph *G = criar_grafo (V);

   /* Posição dos vértices vistos nos slides em aula: */
   /*       0     1         */
   /*       2     3         */
   /*       4     5         */
   /*Adicionando as arestas:*/
   adicionar_aresta (G, 0, 1);
   adicionar_aresta (G, 2, 0);
   adicionar_aresta (G, 2, 1);
    adicionar_aresta (G, 1, 3);
   adicionar_aresta (G, 2, 3);
   adicionar_aresta (G, 3, 0);
   adicionar_aresta (G, 4, 1);
   adicionar_aresta (G, 4, 2);
   adicionar_aresta (G, 5, 0);
   adicionar_aresta (G, 5, 3);

   /*... Adicione uma aresta para criar um ciclo ... */

   OrdenacaoTopologica (G);

   return 0;
}

