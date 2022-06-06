#include <stdio.h>
#include <stdbool.h> 
#include <stdlib.h>  
#include <ctype.h>
#include <string.h>

// Autores: Douglas Fernandes Sammur e Julia Mack Stahl

//-----------------------------------
// ESTRUTURAS -> PILHA DIN�MICA 
//-----------------------------------

// 1. NoPilha
//struct NoPilha* -> PtrNoPilha
typedef struct NoPilha* PtrNoPilha;

struct NoPilha {
  char elemento;
  PtrNoPilha proximo; 
} NoPilha;

// 2. PilhaDinamica
typedef struct {
  PtrNoPilha topo; 
  int qtde;  
} PilhaDinamica;

//-----------------------------------
// FUN��ES -> PILHA DIN�MICA
//-----------------------------------

// ===== INICIAR PILHA =====
void  iniciaPilhaDinamica(PilhaDinamica *p){
    p->qtde = 0;    // int
    p->topo = NULL; // PtrNoPilha
}

// ===== SABER SE A PILHA EST� VAZIA =====
bool estaVaziaPilhaDinamica(PilhaDinamica *p) {
    return(p->topo == NULL);
}

// ===== TAMANHO DA PILHA || QUANTIDADE DE ELEMENTOS =====
int tamanhoPilhaDinamica(PilhaDinamica *p) {
    return(p->qtde);
}

// ===== IMPRIMIR PILHA =====
void imprimirPilhaDinamica(PilhaDinamica *p) {
    printf("Pilha = [ ");
    PtrNoPilha aux;
    for(aux = p->topo; aux != NULL; aux = aux->proximo){
      printf("%d ", aux->elemento);
    }
    printf("]\n");
}

// ===== INSERIR ELEMENTO NA PILHA =====
void pushPilhaDinamica(PilhaDinamica *p, char num){
    PtrNoPilha Aux = malloc(sizeof(NoPilha));
    Aux->elemento = num;
    Aux->proximo = p->topo;
    p->topo = Aux;
    p->qtde++;
}

// ===== REMOVER ELEMENTO DA PILHA =====
char popPilhaDinamica(PilhaDinamica *p) {
	char elementoRemovido;
	
    if(!estaVaziaPilhaDinamica(p)) {
    	PtrNoPilha aux;
    	aux = p->topo;
	    elementoRemovido = topoPilhaDinamica(p);
	    p->topo = p->topo->proximo;
	    free(aux);
	    p->qtde--;
	    return elementoRemovido;
    } 
	else {
	    printf("Warning: pilha est� vazia!\n");
	    return 1;
  	}
}

// ===== PESQUISA: TOPO DA PILHA =====
int topoPilhaDinamica(PilhaDinamica *p){
	int aux = p->topo->elemento;
	printf("%c\n", aux);
	return aux;
}

// ===== DESTRUIR PILHA =====
void destroiPilhaDinamica(PilhaDinamica *p){
	
	// verificar se a pilha est� vazia
	if(!estaVaziaPilhaDinamica(p)){
		// aux vai percorrer a pilha
		PtrNoPilha aux;
		// liberar a mem�ria ocupada por cada n�
		for(aux = p->topo; aux != NULL; aux = aux->proximo){
			free(aux);
   		}
		// depois de desalocar os n�s, precisa desalocar a pilha	
	}
	// se a pilha est� vazia, desaloca apenas a pilha
	free(p);
}


//-----------------------------------
// FUN��ES -> COMPILADOR
//-----------------------------------

void Operador(FILE *arqSaida, PilhaDinamica *p, char c, int temp){
	
	// ler/desempilhar os dois �ltimos operandos
	char op1, op2;
	op1 = popPilhaDinamica(p);
	op2 = popPilhaDinamica(p);
	
	// verificar se os operandos desempilhados s�o letras mai�sculas ou vari�veis tempor�rias ('t')
	if(op1 != 't' && op2 == 't'){
		
		fprintf(arqSaida, "LDR %c\n", op1);
		fprintf(arqSaida, "LDR TEMP%d\n", temp);	
	}
	else if(op1 == 't' && op2 != 't'){

		fprintf(arqSaida, "LDR TEMP%d\n", op1);
		fprintf(arqSaida, "LDR %c\n", op2);		
	}
	else if(op1 == 't' && op2 == 't'){
		
		fprintf(arqSaida, "LDR TEMP%d\n", temp);
		fprintf(arqSaida, "LDR TEMP%d\n", temp-1);
	}
	else{
		
		fprintf(arqSaida, "LDR %c\n", op1);
		fprintf(arqSaida, "LDR %c\n", op2);	
	}
	
	// verficar qual � o operador e imprimir
	switch(c){
		case '+':{
			fprintf(arqSaida, "ADD ");
			break;
		}
		case '-':{
			fprintf(arqSaida, "SUB ");
			break;
		}
		case '*':{
			fprintf(arqSaida, "MUL ");
			break;
		}
		case '/':{
			fprintf(arqSaida, "DIV ");
			break;
		}		
	}
	
	// imprimir os OPERANDOS ao lado dos OPERADORES
	if(op1 == 't' && op2 != 't'){
		
		fprintf(arqSaida, "TEMP%d ", temp);
		fprintf(arqSaida, "%c\n", op2);
	}
	else if(op2 == 't' && op1 != 't'){
		
		fprintf(arqSaida, "%c ", op1);
		fprintf(arqSaida, "TEMP%d\n", temp);	
	}
	else if(op1 == 't' && op2 == 't'){
		
		fprintf(arqSaida, "TEMP%d ", temp);
		fprintf(arqSaida, "TEMP%d\n", temp-1);	
	}
	else{

		fprintf(arqSaida, "%c %c\n", op1, op2);	
	}
}


// // // // // // // // // // // // //
//                                  //
// ====== PROGRAMA PRINCIPAL ====== //
//                                  //
// // // // // // // // // // // // //


int main(int argc, char* argv[]) {
	
	//printf("argc: %d\n", argc);
	//printf("argv: %s\n", argv[0]);
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
	
	// === INICIAR PILHA ===
	PilhaDinamica pilha;
    iniciaPilhaDinamica(&pilha);
	
	// Vari�veis para controle dos arquivos
	char Leitor[10], *controle; 
	int i=0, contAlpha=0, contOp=0;
	
	// Armazenar os caracteres do arquivo de entrada em um vetor
	controle = fgets(Leitor, 10, arqEntrada);
	
	
// ===== CONTROLE DE ERROS DE SINTAXE ===== //

	// la�o de repeti��o para verificar os caracteres
	for(i=0; Leitor[i] != '\0'; i++){
		
		// teste para verificar se h� mais de uma linha/equa��o no arquivo de entrada
		if(Leitor[i] =='\n'){
			printf("ERROR: MAIS DE UMA LINHA DETECTADA! \n");
			fprintf(arqSaida, "ERROR: MAIS DE UMA LINHA DETECTADA! \n");
			return 1;
		}
		// teste para verificar a validade dos caracteres lidos
				// n�meros da tabela ascii para A...Z e operadores (+,-,*,/)
		else if(Leitor[i]>=65 && Leitor[i]<=90 || Leitor[i] == 42 || Leitor[i] == 43 || Leitor[i] == 45 || Leitor[i] == 47){ 
			if(Leitor[i]>=65 && Leitor[i]<=90){
				// contador para operandos
				contAlpha++;
			}
			else{
				// contador para operadores
				contOp++;
			}
		}
		else{
			// se conter caracter inv�lido, aponta erro e encerra o programa
			printf("ERROR: EQUA�AO CONTEM UM CARACTERE INVALIDO! \n");
			fprintf(arqSaida, "ERROR: EQUA�AO CONTEM UM CARACTERE INVALIDO!");
			return 1;
		}
	}
	
// ===== CONTROLE DE ERROS MATEM�TICOS ===== //	

	// Toda opera��o simples precisa de dois operandos
	//	 1 operador -> 2 operandos; 2 operadores -> 3 operandos....
		// 1. O n�mero de operadores deve ser igual ao n�mero de operandos - 1
	if(contOp != contAlpha-1){ 
		printf("ERROR: EQUACAO INVALIDA! \n");
		fprintf(arqSaida, "ERROR: EQUACAO INVALIDA! \n");
		return 1;
	}
	
	// A equa��o mais simples deve ser apresentada como: 'operando' 'operando' 'operador'
		// 2. Em nota��o p�s-fixa, pelo menos os dois primeiros caracteres lidos devem ser operandos
	if(Leitor[0]>=65 && Leitor[0]<=90){
		if(Leitor[1]>=65 && Leitor[1]<=90){
			//printf("ok\n");
		}else{
			printf("ERROR: Operacao invalida!\n");
			fprintf(arqSaida, "ERROR: Operacao invalida!\n");
			return 1;
		}
	}
		// 3. Em nota��o p�s-fixa, �ltimo caractere lido deve ser um operador
	int tam = strlen(Leitor);
	if(Leitor[tam-1]>=65 && Leitor[tam-1]<=90){
		printf("ERROR: Operacao invalida! \n");
		fprintf(arqSaida, "ERROR: Operacao invalida! \n");
		return 1;
	}


// ===== FUNCIONAMENTO DO PROGRAMA ===== //	

	// contador de vari�veis tempor�rias (resultado de opera��o)
	int contaTemp = 0;
	
	// la�o de repeti��o percorre o vetor de caracteres lidos
	for(i = 0; Leitor[i]!='\0'; i++){
		
		// verifica se � operando e empilha-o
		if(Leitor[i]>=65 && Leitor[i]<=90){
			pushPilhaDinamica(&pilha, Leitor[i]);
		}
		// se n�o for operando, � operador
		else{
			// chamada da fun��o Operador que vai realizar a opera��o
			Operador(arqSaida, &pilha, Leitor[i], contaTemp);
			
			// verificar se h� mais algum caracter no vetor
			if(Leitor[i+1] != '\0'){
				// se sim, empilhar e imprimir uma vari�vel tempor�ria 't'
				pushPilhaDinamica(&pilha, 't');
				contaTemp++;
				printf("STR TEMP%d \n", contaTemp);
				fprintf(arqSaida, "STR TEMP%d\n", contaTemp);
			}	
		}	
	}
  	
	//destroiPilhaDinamica(&pilha);
	
	fclose(arqEntrada);
	fclose(arqSaida);
	
    return 0;
}
