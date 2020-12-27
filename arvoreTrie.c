#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// ITALO DE MATOS SALDANHA 21854113
// ENGENHARIA DA COMPUTACAO

#define SIZE (26)

//função que converte todas as letras de uma palavra para minuscula
char converteMinuscula(char palavra[20]){
	int tamanhoString = strlen(palavra);

	for(int i=0; i<tamanhoString; i++){
		palavra[i] = tolower(palavra[i]);
	}
	return *palavra;
}

//estrutura da arvore em questao
typedef struct arvoreT{
	struct arvoreT *filhos[SIZE];
	int ehFolha; //1 quando no eh folha
}arvorePatricia;

//funcao que aloca espaco para os nos
arvorePatricia *novoNo(){
	arvorePatricia* no = (arvorePatricia*)malloc(sizeof(arvorePatricia));
	no->ehFolha=0;

	for(int i=0; i<SIZE; i++)
		no->filhos[i]=NULL;

	return no;
}

//funcao para inserir determinada palavra em uma arvore 
void inserir(arvorePatricia *raiz, char* palavra){
	arvorePatricia* atual = raiz;
	while(*palavra){
		if(atual->filhos[*palavra - 'a']==NULL)
			atual->filhos[*palavra - 'a'] = novoNo();

		atual = atual->filhos[*palavra - 'a'];

		palavra++; //char subsequente
	}

	atual->ehFolha=1;
}

//funcao que indica se um determinado no eh folha
int ehFolha(arvorePatricia *raiz){
	return raiz->ehFolha; //0 falso 1 verdadeiro
}

//funcao que busca determinada palavra na arvore
//1 se verdadeiro
//0 se falso
int buscar(arvorePatricia *raiz, char* palavra){

	if(raiz==NULL) return 0;
	arvorePatricia* atual = raiz;

	while(*palavra){
		atual=atual->filhos[*palavra - 'a'];

		if(atual==NULL) return 0;

		palavra++;
	}
	return atual->ehFolha;
}

//funcao para imprimir arvore de maneira ordenada
void imprimir(arvorePatricia* raiz,  char* str, int nivel){
	if(ehFolha(raiz)==1){
		str[nivel]='\0';
		printf("%s\n", str);
	}
	int i;
	for(i=0; i<SIZE; i++){
		if(raiz->filhos[i]){
			str[nivel] = i+'a';
			imprimir(raiz->filhos[i], str, nivel+1);
		}
	}
}


int main(){

	arvorePatricia* raiz = novoNo();
	FILE *arquivo;
	char palavra[20];

	//arquivo = fopen("brasil.txt", "r");
	arquivo = fopen("faroeste.txt", "r");

	if(arquivo==NULL){
		printf("Erro ao abrir arquivo.\n");
	}

	int linha=1;
	while(!feof(arquivo)) {
		
		fscanf(arquivo, "%s", palavra);
		if(strlen(palavra)>=3){
			converteMinuscula(palavra);
			inserir(raiz, palavra);
			if(buscar(raiz, palavra) == 1){//verifica se a palavra ja existe
				printf("\n%s %d ", palavra, linha);
				linha++;
			}
		}
	}

	fclose(arquivo);
	imprimir(raiz, palavra, 0);
}