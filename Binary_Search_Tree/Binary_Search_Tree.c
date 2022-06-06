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
// FUN��ES DA FILA
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
	// La�o que procura o elemento
	for(aux = f->inicio; aux != NULL; aux=aux->proximo){
		// Se encontrar, retorna true
		if(aux->chave == valor)
			return true;
	}
	
	// Se terminar o la�o, retorna false
	return false;
}

void insereFilaDinamica (FilaDinamica *f, int valor){
	// Se o elemento j� existir na fila, n�o insere
	if(buscaFilaDinamica(f, valor)) return;
	
// Alocar mem�ria e copiar o valor na chave
	PtrNoFila aux = malloc(sizeof(NoFila));
	aux->chave = valor;
	aux->proximo = NULL;
	
// 1. Primeira inser��o
	if(estaVaziaFilaDinamica(f)){
		f->inicio = aux;
	}
// 2. Fila n�o est� vazia
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
//  ESTRUTURAS DA �RVORE
// ---------------------------------------

// PtrNoArvore = NoArvore* -> PtNoArvore
typedef struct NoArvore* PtrNoArvore;

//NoArvore
typedef struct NoArvore {
	// Maior palavra da l�ngua portuguesa: Pneumoultramicroscopicossilicovulcanoconiose (46 letras)
	char chave[46]; // termo armazenado
	FilaDinamica fila; // onde ser�o armazenados os n�meros das p�ginas
	PtrNoArvore direita;
	PtrNoArvore esquerda;
} NoArvore;

// ---------------------------------------
//  FUN��ES DA �RVORE
// ---------------------------------------

// Inicializa��o
void iniciaArvoreBinaria(PtrNoArvore *r) {
  (*r) = NULL;
}

// Est� vazia
bool estaVaziaArvoreBinaria(PtrNoArvore *r) {
  return((*r) == NULL);
}

// Inser��o
bool inserirArvoreBinaria(PtrNoArvore *no, char* valor) {
  // clausulas base (true, false)
  // 1. NULL (ponto de inser��o)
  if((*no) == NULL) {
  	
  	// Alocar mem�ria para o novo n�
    (*no) = malloc(sizeof(NoArvore));
    
	//  Copiar no novo n� o termo recebido por par�metro
    strcpy((*no)->chave, valor);
    
    // Inicializar a fila do n�
    iniciaFilaDinamica(&(*no)->fila); 
	
    // Subarvores nulas
    (*no)->direita = NULL;
    (*no)->esquerda = NULL;
    return (true);
  }
  
  // 2. n� que j� possui o valor que eu quero inserir
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


// Impress�o em ordem
void EmOrdemArvoreBinaria(PtrNoArvore *no, FILE *arqSaida) {
  if((*no) == NULL) return; //clausula base
  
  // recurs�o pra esquerda
  EmOrdemArvoreBinaria(&(*no)->esquerda, arqSaida);
  
  // impress�o do n� de �rvore
  fprintf(arqSaida, "%s", (*no)->chave); // termo
  imprimeFilaDinamica(&(*no)->fila, arqSaida); // n�meros das p�ginas
  fprintf(arqSaida, "\n");
  
  // recurs�o para direita
  EmOrdemArvoreBinaria(&(*no)->direita, arqSaida);
}


// Pesquisar se o termo existe na �rvore
bool pesquisaArvoreBinaria(PtrNoArvore *no, char* valor, int nroPagina) {
  // clausulas base - recursao
  // se o elemento nao existir -> false
  if((*no) == NULL) return (false);
  
  // se existir o elemento -> true 
  if(strcmp(valor, (*no)->chave) == 0) {
  	// inserir o n�mero da p�gina na fila
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


//  Destruir / Desalocar mem�ria
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
	
	// === INICIAR �RVORE ===
	PtrNoArvore raiz;
	iniciaArvoreBinaria(&raiz);
	
	// === TERMOS ===
	// 1. ler a primeira linha at� :
	char c;
	do{
		c = fgetc(arqEntrada);
	} while (c != ':');
	
	// 2. ler o resto da primeira linha at� >
	char linha[64];
	fscanf(arqEntrada, "%[^>]s\n", linha);
	
	// 3. Separar os termos e inserir na �rvore
	char *termo;
	termo = strtok(linha, ",");
	while(termo){

		// verificar se o termo tem inicial mai�scula antes de inserir na �rvore
		if( isupper(termo[0]) ){
		   termo[0] = tolower(termo[0]);
		}
		inserirArvoreBinaria(&raiz, termo);
		
		// pr�ximo termo
		termo = strtok(NULL, ",");
	}
	
	// === P�GINAS ===
	while(c != EOF){
		
		// 1. ler a linha de numera��o da p�gina at� :
		do{
			c = fgetc(arqEntrada);
		} while (c != ':');

		// 2. ler e armazenar o n�mero da p�gina
		int nroPagina;
		fscanf(arqEntrada, "%d>\n", &nroPagina);
		
		// 3. ler e armazenar o conte�do da p�gina em uma string
		char pagina[1024];
		fscanf(arqEntrada, "%[^<]s\n", pagina);
		
		// 4. Separar e buscar as palavras
		char *palavra;
		palavra = strtok(pagina, " ,;()"".\n");
		
		while(palavra){
			
			// verificar se a palavra tem inicial mai�scula
			if( isupper(palavra[0])){
			   // se sim, converter para minuscula
			   palavra[0] = tolower(palavra[0]);
			}

			// pesquisar a palavra na �rvore
			pesquisaArvoreBinaria(&raiz, palavra, nroPagina);
			
			// pr�xima palavra
			palavra = strtok(NULL, " ,;()"".\n");
		}
		// l� o pr�ximo caractere da entrada
		c = fgetc(arqEntrada);
	}
	
	// imprimir na sa�da os n�s de �rvore
	EmOrdemArvoreBinaria(&raiz, arqSaida);
	
	// liberar a mem�ria da �rvore
	destroiArvore(&raiz);
	
	// fechar os arquivos
	fclose(arqEntrada);
	fclose(arqSaida);
	
	return 0;
}
