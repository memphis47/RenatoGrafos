#include <stdlib.h>
#include <stdio.h>
#include <cgraph.h>
#include <string.h>
#include "grafo.h"

//------------------------------------------------------------------------------
// estrutura de dados para representar um grafo simples
// 
// o grafo pode ser
// - direcionado ou não
// - com pesos nas arestas ou não
// 
// além dos vértices e arestas, o grafo tem um nome
// 
// os vértices do grafo também tem nome
// 
// os nomes do grafo e dos vértices são strings quaisquer
// 
// num grafo com pesos nas arestas todas as arestas tem peso, que é um double
// 
// o peso default de uma aresta é 0.0
typedef struct aresta
{
	double peso;
	char *verticeLigado;
} aresta;

typedef struct vertice
{
	char *nome;
	aresta *arestas;
	int n_arestas_vertice;
} vertice;

struct grafo {
	vertice *vertices;
	int direcionado;
	int n_vertices;
	int n_arestas;
};





static int direcionado,
  n_vertices,
  n_arestas,
  n_arestas_visitadas = 0;

//grafo{nVer*nAre*vertices)})})}
//------------------------------------------------------------------------------
// lê um grafo no formato dot de input, usando as rotinas de libcgraph
// 
// desconsidera todos os atributos do grafo lido
// exceto o atributo "peso" nas arestas onde ocorra
// 
// num grafo com pesos nas arestas todas as arestas tem peso, que é um double
// 
// o peso default de uma aresta num grafo com pesos é 0.0
// 
// devolve o grafo lido ou
//         NULL em caso de erro 
static void guarda_arestas(Agraph_t *g, Agnode_t *v, struct grafo *graf, int i) {
	int j=0;
	double pes=0.0;
	for (Agedge_t *a=agfstedge(g,v); a; a=agnxtedge(g,a,v)){
		char *peso = agget(a, (char *)"peso");
		if(peso!= NULL)
			pes = atof(peso);

  		graf->vertices[i].arestas[j].peso=pes;
  		if(strcmp(agnameof(agtail(a)),agnameof(v)) != 0){
  			int tam= (int) strlen(agnameof(agtail(a)));
  			graf->vertices[i].arestas[j].verticeLigado=(char *) malloc(sizeof(char)*tam);
  			graf->vertices[i].arestas[j].verticeLigado=agnameof(agtail(a));
  		}
  		else{
  			int tam=(int) strlen(agnameof(agtail(a)));
  			graf->vertices[i].arestas[j].verticeLigado=(char *) malloc(sizeof(char)*tam);
  			graf->vertices[i].arestas[j].verticeLigado=agnameof(aghead(a));
  		}
  		
  		j++;
  	}
  	graf->vertices[i].n_arestas_vertice=j-1;
}

static void getVerticeArestas(struct grafo *graf,Agraph_t *g){
	int i=0;
	for (Agnode_t *v=agfstnode(g); v; v=agnxtnode(g,v)) {

		int num_arest=agdegree(g,v,1,1);

		graf->vertices[i].nome=(char *) malloc(sizeof(char)*strlen(agnameof(v)));
		graf->vertices[i].nome=agnameof(v);
		graf->vertices[i].arestas=(aresta *) malloc (num_arest*sizeof (aresta)); //TODO: multiplicar pelo numero de arestas do vertice


		// if ( direcionado )
		//   //guarda_arcos(g, v, graf);
		// else
		guarda_arestas(g, v, graf, i);
		i++;
	}
}


grafo le_grafo(FILE *input) {
	Agraph_t *g = agread(input, NULL);
	if ( (g && agisstrict(g)) ){

		direcionado = agisdirected(g);

		n_vertices = agnnodes(g);

		n_arestas = agnedges(g);

		struct grafo *graf=(struct grafo *) malloc (sizeof(struct grafo));
		graf->vertices=(vertice *) malloc (n_vertices*sizeof(vertice));
		graf->direcionado=direcionado;
		graf->n_vertices=n_vertices;
		graf->n_arestas=n_arestas;
		getVerticeArestas(graf,g);
		escreve_grafo(stdout,graf);
	}
	
}






//------------------------------------------------------------------------------
// desaloca toda a memória utilizada em g
// 
// devolve 1 em caso de sucesso ou
//         0 em caso de erro

int destroi_grafo(grafo g) {
	return 0;
}
//------------------------------------------------------------------------------
// escreve o grafo g em output usando o formato dot, de forma que
// 
// 1. todos os vértices são escritos antes de todas as arestas/arcos 
// 2. se uma aresta tem peso, este deve ser escrito como um atributo
//
// devolve o grafo escrito ou
//         NULL em caso de erro 

grafo escreve_grafo(FILE *output,struct grafo *g) {
	int i=0;
	int j=0;
	char dir='>';

	for(i=0;i< g->n_vertices;i++){
		printf("%s\n",g->vertices[i].nome);
	}

	for(i=0;i < g->n_vertices;i++){
		for (j = 0; j < g->vertices[i].n_arestas_vertice; j++)
		{
			if(!g->direcionado)
				dir='-';
			if(g->vertices[i].arestas[j].peso > 0)
				printf("%s -%c %s [peso=%f]\n", g->vertices[i].nome,
											dir,
											g->vertices[i].
											arestas[j].verticeLigado, 
											g->vertices[i].arestas[j].peso);
			else
				printf("%s -%c %s \n", g->vertices[i].nome,
											dir,
											g->vertices[i].
											arestas[j].verticeLigado);
		}
	}
}

void main(int argc, char *argv[]) 
{ 
	if(argc>1){
		FILE *fp;
		fp=fopen(argv[1], "r" );
		le_grafo(fp);
	}
	else{
		le_grafo(stdin);

	}
	

}