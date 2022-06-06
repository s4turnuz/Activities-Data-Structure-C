#include <stdio.h>
#include <stdbool.h> // true/false
#include <stdlib.h>  // free, malloc, sizeof
#include <string.h>
#include <ctype.h>

// Autores: Douglas Fernandes Sammur e Julia Mack Stahl

//-----------------------------------
// ESTRUTURAS -> LISTA DUPLAMENTE ENCADEADA
//-----------------------------------

// NoLista* = PtrNoLista
typedef struct NoLista* PtrNoLista;

//  - NoLista (chaves, ptr proximo, ptr anterior)
typedef struct NoLista {
    int chave;
    char nome[50];
    char sexo;
    int idade;
    double peso;
    double altura;
    char telefone[16];
    PtrNoLista proximo;
    PtrNoLista anterior;
} NoLista;

//  - Lista
typedef struct {
    PtrNoLista inicio;
    int qtdeElementos;
} ListaDuplaSentinela;


//----------------------------------------------
// inicializa��o da lista com n� sentinela
//----------------------------------------------
void iniciaListaDuplaSentinela(ListaDuplaSentinela *lista) {

  PtrNoLista sentinela = malloc(sizeof(NoLista));

  sentinela->chave = -999;
  sentinela->proximo = NULL;
  sentinela->anterior = NULL;

  lista->inicio = sentinela;
  lista->qtdeElementos = 0;
}

//----------------------------------------------
// estaVazia
//----------------------------------------------
bool estaVaziaListaDuplaSentinela(ListaDuplaSentinela *lista) {
  return(lista->qtdeElementos == 0);
}

//----------------------------------------------
// quantidade de elementos na lista
//----------------------------------------------
int tamanhoListaDuplaSentinela(ListaDuplaSentinela *lista) {
  return(lista->qtdeElementos);
}

//----------------------------------------------
//minimo = primeiro elemento
//----------------------------------------------
int minimoListaDuplaSentinela(ListaDuplaSentinela *lista) {
	return(lista->inicio->proximo->chave);
}

//----------------------------------------------
// m�ximo = �ltimo elemento
//----------------------------------------------
int maximoListaDuplaSentinela(ListaDuplaSentinela *lista) {
	return(lista->inicio->anterior->chave);
}

//----------------------------------------------
// imprimir em ordem crescente
//----------------------------------------------
void imprimeListaDuplaSentinelaCres(ListaDuplaSentinela *lista, FILE *arqSaida) {
  PtrNoLista aux;
  // aux = inicio->prox, aux!= -999; aux = aux->prx
  // la�o que percorre a lista come�ando pelo primeiro elemento
  for(aux = lista->inicio->proximo; aux->chave != -999; aux = aux->proximo) {
  	printf("{%d,%s,%c,", aux->chave, aux->nome, aux->sexo);
    printf("%d,%.2lf,%.2lf,%s}\n", aux->idade, aux->peso, aux->altura, aux->telefone);
    fprintf(arqSaida, "{%d,%s,%c,", aux->chave, aux->nome, aux->sexo);
    fprintf(arqSaida, "%d,%.2lf,%.2lf,%s}\n", aux->idade, aux->peso, aux->altura, aux->telefone);
  }
}

//----------------------------------------------
// imprimir em ordem decrescente
//----------------------------------------------
void imprimeListaDuplaSentinelaDecres(ListaDuplaSentinela *lista, FILE *arqSaida) {
    
    PtrNoLista aux;
    // aux = inicio->anterior, aux!= -999; aux = aux->anterior
    // la�o que percorre a lista come�ando pelo �ltimo elemento
    for(aux = lista->inicio->anterior ; aux->chave != -999; aux = aux->anterior) {
    	
        printf("{%d,%s,%c,", aux->chave, aux->nome, aux->sexo);
        printf("%d,%.2lf,%.2lf,%s}\n", aux->idade, aux->peso, aux->altura, aux->telefone);
        fprintf(arqSaida, "{%d,%s,%c,", aux->chave, aux->nome, aux->sexo);
        fprintf(arqSaida, "%d,%.2lf,%.2lf,%s}\n", aux->idade, aux->peso, aux->altura, aux->telefone);
    }
}

//----------------------------------------------
// Imprimir linha
//----------------------------------------------
void imprimeLinhaListaDuplaSentinela(ListaDuplaSentinela *lista, int codPaciente, FILE *arqSaida) {
    
    // La�o para percorrer a lista
    PtrNoLista aux;
    for(aux = lista->inicio->proximo ; aux->chave != -999; aux = aux->proximo) {
    	
        // quando achar o elemento, imprime
        if(aux->chave == codPaciente){
        	printf("{%d,%s,%c,", aux->chave, aux->nome, aux->sexo);
        	printf("%d,%.2lf,%.2lf,%s}\n", aux->idade, aux->peso, aux->altura, aux->telefone);
        	fprintf(arqSaida, "{%d,%s,%c,", aux->chave, aux->nome, aux->sexo);
        	fprintf(arqSaida, "%d,%.2lf,%.2lf,%s}\n", aux->idade, aux->peso, aux->altura, aux->telefone);
			break;	
		}
    }
}

//----------------------------------------------
// Pesquisar se um elemento existe na lista
//----------------------------------------------
bool pesquisaListaDuplaSentinela(ListaDuplaSentinela *lista, int n){
	
	// se a lista estiver vazia, n�o vai ter elemento a ser procurado
	if(estaVaziaListaDuplaSentinela(lista))
		return false;
		
	// se o elemento a ser procurado for menor que o primeiro elemento, ele n�o existe na lista
	if(n < lista->inicio->proximo->chave)
		return false;
		
	// se o elemento a ser procurado for maior que o �ltimo elemento, ele n�o existe na lista
	if(n > lista->inicio->anterior->chave)
		return false;
	
	// ptr auxiliar que vai percorrer a lista, se encontrar retorna true
	PtrNoLista aux;
	for(aux = lista->inicio->proximo ; aux->chave != -999; aux = aux->proximo) {
        if(aux->chave == n){
        	return true;
		} 
    }
    
    // se percorrer toda a lista e n�o encontrar, n�o existe na lista
    if(aux == lista->inicio)
    	return false;
}

//----------------------------------------------
// insere elementos
//----------------------------------------------
void inserirListaDuplaSentinela(ListaDuplaSentinela *lista, char *texto, FILE *arqSaida){

// Aloca��o de mem�ria do novo n�	
	PtrNoLista novo = malloc(sizeof(NoLista));
  
	char auxCod[2], auxNome[20]={' '}, auxSexo, auxIdade[3]={' '}, auxPeso[6]={' '}, auxAltura[5]={' '}, auxTelefone[20]={' '}; // coloquei com espa�o em branco para n bagun�ar a memoria
	int i=0, j=0, contV=0, contV2=0; // contadores padr�o
  

	// CONTROLE DE ERROS POR VIRGULAS
	for(i=0; texto[i]!='\n'; i++){
		if(texto[i]==','){
			contV2++; // contar virgulas separadamente
		}
	}

	if(contV2!=6){
		printf("ERROR: DADOS INVALIDOS! \n");
		fprintf(arqSaida, "ERROR: DADOS INVALIDOS!");
		exit(1); // return dava B.O, ent�o vai exit() mesmo
	}
	// FIM CONTROLE DE ERROS POR VIRGULAS


// colocar os dados nas strings	
	for(i=1; texto[i]!='\n'; i++){ // ou \0, ou }, etc...
	  	if(contV==0){
	  		while(texto[i]!=','){
	  			auxCod[j]=texto[i];
	  			j++;
	  			i++;
			}
			contV++;
			j = 0;
		}else if(contV==1){
		  	while(texto[i]!=','){
		  		auxNome[j]=texto[i];
		  		j++;
		  		i++;
			}
			contV++;
			j=0;
		}else if(contV==2){
		  	auxSexo=texto[i];
		  	i++;
		  	contV++;
		  	j=0;
		}else if(contV==3){
		  	while(texto[i]!=','){
		  		auxIdade[j]=texto[i];
		  		j++;
		  		i++;
			}
			contV++;
			j=0;
		}else if(contV==4){
		  	while(texto[i]!=','){
		  		auxPeso[j]=texto[i];
		  		j++;
		  		i++;
			}
			contV++;
			j=0;
		}else if(contV==5){
		  	while(texto[i]!=','){
		  		auxAltura[j]=texto[i];
		  		j++;
		  		i++;
			}
			contV++;
			j=0;
		}else if(contV==6){
		  	while(texto[i]!='}'){
		  		auxTelefone[j]=texto[i];
		  		j++;
		  		i++;
			}
			j=0;
		}	  
  	}
  
// CONTROLE DE ERROS POR DADOS EM LUGARES INVALIDOS
	// para o c�digo
	for(i=0; auxCod[i]!='\0'; i++){
		if(!isdigit(auxCod[i])){
			printf("ERROR: DADOS INVALIDOS1!");
			fprintf(arqSaida, "ERROR: DADOS INVALIDOS!");
		}
	}
	// para o nome
	for(i=0; auxNome[i]!='\0'; i++){
		if(!isalpha(auxNome[i]) && auxNome[i]!=39 && auxNome[i]!=' '){
			printf("ERROR: DADOS INVALIDOS2!");
			fprintf(arqSaida, "ERROR: DADOS INVALIDOS!");
		}
	}
	// para o sexo
	if(!isalpha(auxSexo)){
		printf("ERROR: DADOS INVALIDOS3!");
		fprintf(arqSaida, "ERROR: DADOS INVALIDOS!");
	}
	// para a idade
	for(i=0; auxIdade[i]!='\0'; i++){
		if(!isdigit(auxIdade[i])){
			printf("ERROR: DADOS INVALIDOS4!");
			fprintf(arqSaida, "ERROR: DADOS INVALIDOS!");
		}
	}
	// para o peso
	for(i=0; auxPeso[i]!='\0'; i++){
		if(!isdigit(auxPeso[i]) && auxPeso[i]!='.'){
			printf("ERROR: DADOS INVALIDOS5!");
			fprintf(arqSaida, "ERROR: DADOS INVALIDOS!");
		}
	}
	// para a altura
	for(i=0; auxAltura[i]!='\0'; i++){
		if(!isdigit(auxAltura[i]) && auxAltura[i]!='.'){
			printf("ERROR: DADOS INVALIDOS6!");
			fprintf(arqSaida, "ERROR: DADOS INVALIDOS!");
		}
	}
	// para o telefone
	for(i=0; auxTelefone[i]!='\0'; i++){
		if(!isdigit(auxTelefone[i]) && auxTelefone[i]!='(' && auxTelefone[i]!=')' && auxTelefone[i]!='-'){
			printf("ERROR: DADOS INVALIDOS7!");
			fprintf(arqSaida, "ERROR: DADOS INVALIDOS!");
		}
	}
// FIM CONTROLE DE ERROS POR DADOS EM LUGARES INVALIDOS


// Convers�o e atribui��o de valores no novo n�
	// Convers�o string para inteiro
	novo->chave = atoi(auxCod);
	novo->idade = atoi(auxIdade);
	// Convers�o string para double
	novo->peso = atof(auxPeso);
	novo->altura = atof(auxAltura);
	// Atribui��o de strings e char
	strcpy(novo->nome, auxNome);
	strcpy(novo->telefone, auxTelefone);
	novo->sexo = auxSexo;

		
// Inser��o na lista (ponteiros e ordena��o)

  // Primeira insercao
  if(estaVaziaListaDuplaSentinela(lista)){
    // ligar o novo ao sentinela (lista->inicio == sentinela)
    novo->proximo  = lista->inicio;
    novo->anterior = lista->inicio;

    // conectar o sentinela ao novo
    lista->inicio->proximo  = novo;
    lista->inicio->anterior = novo;
  }

  // Insercao de um elemento menor que o primeiro
  else if(novo->chave < minimoListaDuplaSentinela(lista)){

    // conectar o novo ao proximo do sentinela (primeiro)
    novo->proximo = lista->inicio->proximo;
    lista->inicio->proximo->anterior = novo;

    // conectar o sentinela ao novo
    novo->anterior = lista->inicio;
    lista->inicio->proximo = novo;
  }
  
  // Inser��o de um elemento no meio da lista ou maior que o �ltimo
  else {
	// Ponteiro que percorre a lista at� achar o elemento menor que o novo
	PtrNoLista aux = lista->inicio->proximo;
	while(aux->proximo->chave != -999 && novo->chave > aux->proximo->chave){
		aux = aux->proximo;
	}  
	
	novo->proximo = aux->proximo;
	aux->proximo = novo;
	
	novo->proximo->anterior = novo;
	novo->anterior = aux;
  }

  // incrementar contador de elementos
  lista->qtdeElementos++;
}

//----------------------------------------------
// remover elementos
//----------------------------------------------
bool removeListaDuplaSentinela(ListaDuplaSentinela *lista, int valor){
	
	// se a lista estiver vazia, n�o vai ter elemento a ser procurado
	if(estaVaziaListaDuplaSentinela(lista))
		return false;
		
	// se o elemento a ser procurado for menor que o primeiro elemento, ele n�o existe na lista
	if(valor < lista->inicio->proximo->chave)
		return false;
		
	// se o elemento a ser procurado for maior que o �ltimo elemento, ele n�o existe na lista
	if(valor > lista->inicio->anterior->chave)
		return false;
	
	PtrNoLista rm;
	
	// Remover o primeiro elemento
	if(valor == lista->inicio->proximo->chave){
		rm = lista->inicio->proximo;
		
		lista->inicio->proximo = rm->proximo;
		rm->anterior = lista->inicio;
		free(rm);
		lista->qtdeElementos--;
	}
	
	// Remover um elemento que n�o � o primeiro
	else{
		PtrNoLista aux = lista->inicio->proximo;
		//   percorrer a lista at� encontrar o elemento que vai ser removido
	    while(aux->proximo->chave != -999 && valor > aux->proximo->chave) {
	        aux = aux->proximo;
	    }
    
//    - A: valor n�o existe
	    if(aux->proximo == lista->inicio) {
	        // percorreu a lista e o elemento nao existe
	        return false;
	    }
    
//    - B: valor existe, e Aux � uma posi��o antes de quem vai ser removido
		else{
		//    Salvar o Proximo do Auxiliar num Ptr remove/tmp
	    rm = aux->proximo;
	    aux->proximo = rm->proximo;
	    rm->proximo->anterior = aux;
	    
	    //   desaloca memoria
	    free(rm);
	    lista->qtdeElementos--;
	    return true;
		}
	}	
}

//----------------------------------------------
// destruir
//----------------------------------------------
void destroiListaDuplaSentinela(ListaDuplaSentinela *lista){
	
	// ptr auxiliar que vai percorrer a lista e remover os elementos/n�s
	PtrNoLista aux;
	for(aux = lista->inicio->proximo ; aux->chave != -999; aux = aux->proximo) {
        removeListaDuplaSentinela(lista, aux->chave); 
    }
    
    // remover o n� sentinela
    free(lista->inicio);
    // desalocar a lista
    free(lista);
}

//----------------------------------------------
// PROGRAMA PRINCIPAL
//----------------------------------------------

int main(int argc, const char * argv[]) {
	
	
	// ===== CONTROLE DE PARAMETROS =====
	printf("Total de parametros passados: %d \n", argc);
	if(argc!=3){
		printf("ERROR: Quantidade de parametros passados invalida! \n");
		return 1;
	}
	
	// ===== INICIAR OS ARQUIVOS =====
	FILE* arqEntrada = fopen(argv[1], "r"); //entrada
	FILE* arqSaida = fopen(argv[2], "w"); //sa�da
	
	// teste para arquivos de entrada vazios
	if (arqEntrada == NULL){
		printf("ERROR: Arquivo inexistente ou vazio!");
		fprintf(arqSaida,"ERROR: Arquivo inexistente ou vazio!");
		return 1;
	}
	
	// instancia e inicializa a lista
	ListaDuplaSentinela lista;
	iniciaListaDuplaSentinela(&lista);

	// 	Vari�veis para analisar a linha
	int chaveBusca;
	char ch, linha[100], *leitor;
	PtrNoLista temp = malloc(sizeof(NoLista));
	leitor = fgets(linha, 100, arqEntrada);
	
	
	while(leitor != NULL){
		
// 		se o primeiro caracter da linha for '{', insere os dados da linha na lista
		if(linha[0] == '{'){
			//printf("Fora: ");
			//printf("%s", leitor);
			
			// armazenar os dados lidos na lista
			inserirListaDuplaSentinela(&lista, linha, arqSaida);
			
		}

//		se o primeiro caracter da linha for um n�mero, executar 1 das 3 opera��es		
		else if(isdigit(linha[0])){
			
			// imprime em ordem crescente
			if(linha[0] == '1'){
				imprimeListaDuplaSentinelaCres(&lista, arqSaida);
				break;	
			}
			
			// imprime em ordem decrescente
			else if (linha[0] == '2'){
				imprimeListaDuplaSentinelaDecres(&lista, arqSaida);
				break;
			}
			
			// busca
			else if(linha[0] == '3'){
				
				// l� a pr�xima linha (elemento a ser procurado)
				fscanf(arqEntrada, "%d", &chaveBusca);
				
				// se n�o achar, entrada inv�lida
				if( !pesquisaListaDuplaSentinela(&lista, chaveBusca) ){
					printf("Arquivo invalido2!");
					fprintf(arqSaida,"Arquivo invalido!");
					return 1;
				}
				// se achar, imprime a linha
				else{
					imprimeLinhaListaDuplaSentinela(&lista, chaveBusca, arqSaida);	
				}
			}
			
			// se comando da opera��o for diferente de 1, 2 ou 3 (caso de teste 4)
			else{
				printf("Elemento n�o encontrado!");
				fprintf(arqSaida,"Elemento n�o encontrado!");
				return 1;
			}
		}

//		se o primeiro caracter da linha n�o for '{', 1, 2, ou 3, entrada inv�lida
		else{
			printf("Arquivo Invalido!");
			fprintf(arqSaida,"Arquivo Inv�lido!");
			return 1;
		}
		
		// ler a pr�xima linha do arquivo
		leitor = fgets(linha, 100, arqEntrada);
	}
	
	// desalocar mem�ria da lista e dos n�s
	//destroiListaDuplaSentinela(&lista);
	
	// fechar os arquivos
  	fclose(arqEntrada);
	fclose(arqSaida);

  return 0;
}

//----------------------------------------------
//----------------------------------------------
