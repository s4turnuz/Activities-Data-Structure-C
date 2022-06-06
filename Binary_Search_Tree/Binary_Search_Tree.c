#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

// Autores: Douglas Sammur e Julia Stahl

// ---------------------------------------
// ESTRUTURAS DA FILA
// ---------------------------------------

typedef struct NoFila* PtrNoFila;

typedef struct NoFila {
	int chave;
	PtrNoFila proximo;
} NoFila;

typedef struct FilaDinamica {
	PtrNoFila inicio;
	PtrNoFila fim;
	int qtdElementos;
} FilaDinamica;

// ---------------------------------------
// FUNÇÕES DA FILA
// ---------------------------------------

void iniciaFilaDinamica (FilaDinamica *f){
	f->inicio = NULL;
	f->fim = NULL;
	f->qtdElementos = 0;
}

bool estaVaziaFilaDinamica (FilaDinamica *f){
	return (f->inicio == NULL);
}

int tamanhoFilaDinamica (FilaDinamica *f){
	return (f->qtdElementos);
}

bool buscaFilaDinamica(FilaDinamica *f, int valor){
	PtrNoFila aux;
	// Laço que procura o elemento
	for(aux = f->inicio; aux != NULL; aux=aux->proximo){
		// Se encontrar, retorna true
		if(aux->chave == valor)
			return true;
	}
	
	// Se terminar o laço, retorna false
	return false;
}

void insereFilaDinamica (FilaDinamica *f, int valor){
	// Se o elemento já existir na fila, não insere
	if(buscaFilaDinamica(f, valor)) return;
	
// Alocar memória e copiar o valor na chave
	PtrNoFila aux = malloc(sizeof(NoFila));
	aux->chave = valor;
	aux->proximo = NULL;
	
// 1. Primeira inserção
	if(estaVaziaFilaDinamica(f)){
		f->inicio = aux;
	}
// 2. Fila não está vazia
	else{
		f->fim->proximo = aux;
	}
	
	f->fim = aux;
	f->qtdElementos++;
	
}

void imprimeFilaDinamica(FilaDinamica *f, FILE *arqSaida){
	// percorrer a fila
	PtrNoFila aux;
	for(aux = f->inicio; aux != NULL; aux=aux->proximo){
		fprintf(arqSaida, ",%d", aux->chave);
	}
}

// ---------------------------------------
//  ESTRUTURAS DA ÁRVORE
// ---------------------------------------

// PtrNoArvore = NoArvore* -> PtNoArvore
typedef struct NoArvore* PtrNoArvore;

//NoArvore
typedef struct NoArvore {
	// Maior palavra da língua portuguesa: Pneumoultramicroscopicossilicovulcanoconiose (46 letras)
	char chave[46]; // termo armazenado
	FilaDinamica fila; // onde serão armazenados os números das páginas
	PtrNoArvore direita;
	PtrNoArvore esquerda;
} NoArvore;

// ---------------------------------------
//  FUNÇÕES DA ÁRVORE
// ---------------------------------------

// Inicialização
void iniciaArvoreBinaria(PtrNoArvore *r) {
  (*r) = NULL;
}

// Está vazia
bool estaVaziaArvoreBinaria(PtrNoArvore *r) {
  return((*r) == NULL);
}

// Inserção
bool inserirArvoreBinaria(PtrNoArvore *no, char* valor) {
  // clausulas base (true, false)
  // 1. NULL (ponto de inserção)
  if((*no) == NULL) {
  	
  	// Alocar memória para o novo nó
    (*no) = malloc(sizeof(NoArvore));
    
	//  Copiar no novo nó o termo recebido por parâmetro
    strcpy((*no)->chave, valor);
    
    // Inicializar a fila do nó
    iniciaFilaDinamica(&(*no)->fila); 
	
    // Subarvores nulas
    (*no)->direita = NULL;
    (*no)->esquerda = NULL;
    return (true);
  }
  
  // 2. nó que já possui o valor que eu quero inserir
  if(strcmp(valor, (*no)->chave) == 0){
  	printf("%s: ja existe na arvore\n", valor);
   return (false);
   } 

  // clausula recursiva
  if(strcmp(valor,(*no)->chave) == 1){
    return(inserirArvoreBinaria(&(*no)->direita, valor));
  } else{
    return(inserirArvoreBinaria(&(*no)->esquerda, valor));
  }
}


// Impressão em ordem
void EmOrdemArvoreBinaria(PtrNoArvore *no, FILE *arqSaida) {
  if((*no) == NULL) return; //clausula base
  
  // recursão pra esquerda
  EmOrdemArvoreBinaria(&(*no)->esquerda, arqSaida);
  
  // impressão do nó de árvore
  fprintf(arqSaida, "%s", (*no)->chave); // termo
  imprimeFilaDinamica(&(*no)->fila, arqSaida); // números das páginas
  fprintf(arqSaida, "\n");
  
  // recursão para direita
  EmOrdemArvoreBinaria(&(*no)->direita, arqSaida);
}


// Pesquisar se o termo existe na árvore
bool pesquisaArvoreBinaria(PtrNoArvore *no, char* valor, int nroPagina) {
  // clausulas base - recursao
  // se o elemento nao existir -> false
  if((*no) == NULL) return (false);
  
  // se existir o elemento -> true 
  if(strcmp(valor, (*no)->chave) == 0) {
  	// inserir o número da página na fila
  	insereFilaDinamica(&(*no)->fila, nroPagina);
  	return (true);
  }
  
  // recursiva
  if(strcmp(valor, (*no)->chave) == 1) {
    return(pesquisaArvoreBinaria(&(*no)->direita, valor, nroPagina));
  } else {
    return(pesquisaArvoreBinaria(&(*no)->esquerda, valor, nroPagina));
  }
}


//  Destruir / Desalocar memória
void destroiArvore(PtrNoArvore *no) {
  if((*no) != NULL) {
    destroiArvore(&(*no)->esquerda);
    destroiArvore(&(*no)->direita);
    free(*no);
    *no = NULL;
  }
}

// ---------------------------------------
//  PROGRAMA PRINCIPAL
// ---------------------------------------
int main(int argc, char* argv[]){
	
	printf("Total de parametros passados: %d \n", argc);
	if(argc!=3){
		printf("ERROR: Quantidade de parametros passados invalida! \n");
		return 1;
	}

	// ===== INICIAR OS ARQUIVOS =====
	FILE* arqEntrada = fopen(argv[1], "r"); //entrada
	FILE* arqSaida = fopen(argv[2], "w"); //saida
	
	// teste para arquivo de entrada vazio
	if (arqEntrada == NULL){
		printf("ERROR: Arquivo inexistente ou vazio!");
		return 1;
	}
	
	// === INICIAR ÁRVORE ===
	PtrNoArvore raiz;
	iniciaArvoreBinaria(&raiz);
	
	// === TERMOS ===
	// 1. ler a primeira linha até :
	char c;
	do{
		c = fgetc(arqEntrada);
	} while (c != ':');
	
	// 2. ler o resto da primeira linha até >
	char linha[64];
	fscanf(arqEntrada, "%[^>]s\n", linha);
	
	// 3. Separar os termos e inserir na árvore
	char *termo;
	termo = strtok(linha, ",");
	while(termo){

		// verificar se o termo tem inicial maiúscula antes de inserir na árvore
		if( isupper(termo[0]) ){
		   termo[0] = tolower(termo[0]);
		}
		inserirArvoreBinaria(&raiz, termo);
		
		// próximo termo
		termo = strtok(NULL, ",");
	}
	
	// === PÁGINAS ===
	while(c != EOF){
		
		// 1. ler a linha de numeração da página até :
		do{
			c = fgetc(arqEntrada);
		} while (c != ':');

		// 2. ler e armazenar o número da página
		int nroPagina;
		fscanf(arqEntrada, "%d>\n", &nroPagina);
		
		// 3. ler e armazenar o conteúdo da página em uma string
		char pagina[1024];
		fscanf(arqEntrada, "%[^<]s\n", pagina);
		
		// 4. Separar e buscar as palavras
		char *palavra;
		palavra = strtok(pagina, " ,;()"".\n");
		
		while(palavra){
			
			// verificar se a palavra tem inicial maiúscula
			if( isupper(palavra[0])){
			   // se sim, converter para minuscula
			   palavra[0] = tolower(palavra[0]);
			}

			// pesquisar a palavra na árvore
			pesquisaArvoreBinaria(&raiz, palavra, nroPagina);
			
			// próxima palavra
			palavra = strtok(NULL, " ,;()"".\n");
		}
		// lê o próximo caractere da entrada
		c = fgetc(arqEntrada);
	}
	
	// imprimir na saída os nós de árvore
	EmOrdemArvoreBinaria(&raiz, arqSaida);
	
	// liberar a memória da árvore
	destroiArvore(&raiz);
	
	// fechar os arquivos
	fclose(arqEntrada);
	fclose(arqSaida);
	
	return 0;
}
