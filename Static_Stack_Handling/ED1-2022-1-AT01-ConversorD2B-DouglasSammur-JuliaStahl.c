#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> // true/false
#define TAM 10


// // // // // // // // // // // // // //
//                                     //
// ======  FUNÇÕES P/ PROGRAMA  ====== //
//                                     //
// // // // // // // // // // // // // //


// ===== ESTRUTURA DA PILHA =====
typedef struct {
	int Item[TAM];
	int Top;
} Pilha;


//-----------------------
// OPERAÇÕES:
//-----------------------
// return 1 - Problemas nos arquivos
// exit(2) - Problemas nas funções da pilha


// ===== INICIAR PILHA =====
void Pilha_Inicia(Pilha *p){
	p->Top = 0; // Topo definido como 0
}

// ===== SABER SE PILHA ESTÁ VAZIA =====
bool Pilha_Vazia(Pilha *p){
	return(p->Top == 0);
}

// ===== SABER SE PILHA ESTÁ CHEIA =====
bool Pilha_Cheia(Pilha *p){
	return(p->Top == TAM);
}

// ===== TAMANHO DA PILHA =====
int Pilha_Tamanho(Pilha *p){
	return(p->Top);
}

// ===== IMPRESSÃO DA PILHA =====
void Pilha_Impressao(Pilha *p){
	printf("Pilha = [ ");
	int i;
	for(i=0; i < p->Top; i++){
		printf("%d ", p->Item[i]);
	}
	printf("]\n");
}

// ===== INSERIR ITENS NA PILHA =====
void Pilha_Inserir(Pilha *p, int x){
	if(!Pilha_Cheia(p)){
		p->Item[p->Top] = x;	
		p->Top++;
	} else{
		printf("ERROR: Pilha cheia!");	
		exit(2);
	}
}

// ===== RETIRAR ITENS DA PILHA =====
int Pilha_Remove(Pilha *p){
	int aux;
	if(!Pilha_Vazia(p)){
		aux = p->Item[p->Top-1];
		p->Top--;
		return aux;
	} else{
		printf("ERROR: Pilha vazia!");
		exit(2);
	}
}

// ===== CONSULTAR TOPO DA PILHA =====
int Pilha_Topo(Pilha *p){
	int ret = p->Item[p->Top-1];
	return ret;
}

// ===== FUNÇÃO PARA CONVERTER =====
int binario(int n){
	int bin = 0, rem = 0, place = 1;
	while(n){
		rem = n%2;
		n = n/2;
		bin = bin+(rem*place);
		place = place*10;
	}
	return bin;	
}


// // // // // // // // // // // // //
//                                  //
// ====== PROGRAMA PRINCIPAL ====== //
//                                  //
// // // // // // // // // // // // //


int main(int argc, const char *argv[]){	
	//printf("argc: %d\n", argc);
	//printf("argv: %s\n", argv[0]);
	printf("Total de parametros passados: %d \n", argc);
	if(argc!=3){
		printf("ERROR: Quantidade de parametros passados invalida! \n");
		return 1;
	}

	Pilha pilhaEntrada; // onde serão armazenados os decimais para conversão
	Pilha pilhaBinario; // onde serão armazenados os dígitos binarios

	// ===== INICIAR OS ARQUIVOS =====
	FILE* arqEntrada = fopen(argv[1], "r"); //entrada
	FILE* arqSaida = fopen(argv[2], "w"); //saida
	
	// teste para arquivos de entrada vazios
	if (arqEntrada == NULL){
		printf("ERROR: Arquivo inexistente ou vazio!");
		return 1;
	}
	
	// ===== INICIAR AS PILHAS =====
	Pilha_Inicia(&pilhaEntrada);
	Pilha_Inicia(&pilhaBinario);
	
	// Gravar os inteiros na pilhaEntrada
	int decimal;
	char ch[10], *controle;
	controle = fgets(ch, 10, arqEntrada); // a variavél controle vai percorrer todo o arquivo
	int i=0, j=0, c=0, b=0, a=0; // variáveis genéricas para controle de dados
	
	while(controle != NULL){ // enquanto não chegar na linha "Null"....
	
		if(ch[0] == '0'){ // se o valor inserido for 0, só precisa testar o primeiro elemento da string ch
			decimal = 0;
		}
		else{
			decimal = atoi(ch); // converter o valor para int
			if(decimal == 0){ // função atoi retorna 0 se a string lida não conter inteiros
				fprintf(arqSaida, "ERROR: Arquivo de Entrada invalido \n");
				printf("ERROR: Arquivo de Entrada invalido \n");
				return 1;
			}
		}
		
		Pilha_Inserir(&pilhaEntrada, decimal); // empilhar decimais na pilhaEntrada
		controle = fgets(ch, 10, arqEntrada); // lê a próxima linha do arquivo		
	}
	
	Pilha_Impressao(&pilhaEntrada); // vizualizar valores da pilhaEntrada
	
	j = Pilha_Tamanho(&pilhaEntrada); // variável j armazena o tamanho da pilhaEntrada
	
	for(i=0; i<j; i++){ // converter valores em bin, desempilhar os valores da pilhaBinario e imprimir em arqSaida
		c = Pilha_Remove(&pilhaEntrada);
		b = binario(c);
		Pilha_Inserir(&pilhaBinario, b);
		fprintf(arqSaida, "%d", pilhaBinario.Item[i]);
		fprintf(arqSaida, "\n");
	}	

	Pilha_Impressao(&pilhaBinario); // vizualizar os valores da pilhaBinario

	fclose(arqEntrada);
	fclose(arqSaida);
	
	system("pause");
	return 0;
}
