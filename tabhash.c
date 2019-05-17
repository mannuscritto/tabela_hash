#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "tabhash.h"

unsigned long int f_foldadd (char *chave, unsigned long int m) {
	unsigned long int k, i = 0;
	char *t;

	k = 0;
	t = chave;

	while (t[i] != '\0') {
		k = k + ((unsigned long int) *t) % m;
		i++;
	}

	return k;
}

unsigned long int f_mult (char *chave, unsigned long int m, long double A) {
	unsigned long int k_temp, k;
	
	k_temp = f_foldadd (chave, 100010717);
	k = floor(m * (k_temp * A - floor (k_temp * A)));
	return k;
}

int addToHash (REGISTRO tcont, EntradaHash* agenda) {
	EntradaHash contato = (EntradaHash)malloc(sizeof(REGISTRO));
	if (contato == NULL) {
		printf("Erro ao alocar nó!\n");
		exit(1);
	}
	strcpy(contato->nome, tcont.nome);
	strcpy(contato->RG, tcont.RG);
	contato->anoNascimento = tcont.anoNascimento;
	contato->CPF = tcont.CPF;
	contato->prox = NULL;
	
	const unsigned long int m = 43991;
	unsigned long index = f_foldadd(tcont.nome, m);//index recebe a posicao dada pela tecnica fold and add
	if (agenda[index] == NULL) {//se nao tiver nenhum registro na posicao
		agenda[index] = contato;//atribui o contato alocado nessa posicao
	} else {//se ja tiver algum registro naquela posicao
		EntradaHash p, q;
		p = agenda[index];
		q = NULL;
		while (p != NULL) {//laco percorre do primeiro registro ate o ultimo
			q = p;
			p = p->prox;
		}
		q->prox = contato;//ultimo registro aponta para o novo registro alocado
	}
	return 1;
}

int isInHash (char *nome, EntradaHash *agenda, REGISTRO *cont) {
	const unsigned long int m = 43991;
	unsigned long index = f_foldadd(nome, m);
	EntradaHash p, q;
	int achou = 0;
	if (agenda[index] != NULL) {//se posicao dada pelo index ja tiver algum registro
		p = agenda[index];
		q = NULL;
		while ((p != NULL) && (strcmp(p->nome, nome) != 0)) {
			q = p;
			p = p->prox;
		}//laco percorre ate primeiro registro naquela posicao que tiver o nome igual ao pesquisado
		if (q == NULL) {//se laco nao rodar nenhuma vez = primeiro registro na posicao ja eh o pesquisado
			*cont = *p;//"retorna" primeiro registro
			return 1;
		} else if (p != NULL) {//se laco parar no meio = registro em alguma posicao
			*cont = *q;//"retorna" o registro apropriado
			return 1;			
		} else {//se laco rodar inteiro e nao achar
			return 0;//retorna erro
		}
	} else {//se posicao nao tiver registro
		return 0;//retorna erro
	}
}

int removeFromHash (char *nomeContato, EntradaHash *agenda) {
	REGISTRO contato;
	int numReg, i = 0;
	char conf;
	
	if (!isInHash(nomeContato, agenda, &contato)) {//verifica se contato existe na agenda
		printf("O contato nao esta na agenda!\n");
		return 0;
	} else {//se existir
		exibirRegistro(contato, nomeContato, 1);//mostra os registros encontrados com o mesmo nome (ver isInHash())
	}
	printf("Digite o numero do registro que deseja remover: ");
	do {
		scanf("%d", &numReg);//recebe numero do registro que deseja remover	
	} while (numReg < 0);
	if(numReg == 0) return 0;
	
	EntradaHash p, q;
	p = &contato;
	q = NULL;
	while (i < numReg) {
		if (strcmp(p->nome, nomeContato) == 0) {
			i++;
		}
		if (i == numReg) break;
		q = p;
		p = p->prox;
		if (p == NULL) {
			printf("Você digitou uma posição inválida!\n");
			return 0;
		}
	}
	
	unsigned long int m = 43991;
	unsigned long index = f_foldadd(nomeContato, m);
	if(q == NULL) {
		p = agenda[index];
		agenda[index] = agenda[index]->prox;
	} else {
		q->prox = p->prox;
	}
	free(p);
}

void exibirRegistro(REGISTRO cont, char *nome, int numerar) {
	REGISTRO contato = cont;
	EntradaHash temp = &contato;
	while (temp != NULL) {
		if (strcmp(temp->nome, nome) == 0) {
			printf("+------------------------------------------------+\n");
			if (numerar) printf("|[ %2d  ]%41s|\n", numerar++, "");
			printf("|Nome: %42s|\n|RG: %44s|\n|Ano de nascimento: %29hu|\n|CPF: %43llu|\n",
			temp->nome, temp->RG, temp->anoNascimento, temp->CPF);
		}
		temp = temp->prox;
	}
	printf("+------------------------------------------------+\n");
}

int importarRegistros(char *nomeArquivo, EntradaHash *agenda) {
	
	FILE *fhand = fopen(nomeArquivo, "r");
	
	int i;
	REGISTRO contato;
	char nome[45], rg[13];
	unsigned short int anoNasc;
	unsigned long long int cpf;
	if (fhand != NULL) {
		
		while (fscanf(fhand, "%s %s %hu %llu", nome, rg, &anoNasc, &cpf) == 4) {
			strcpy(contato.nome, nome);
 	   		strcpy(contato.RG, rg);
 	   		contato.anoNascimento = anoNasc;
 	   		contato.CPF = cpf;
 	   		contato.prox = NULL;
 	   		if (!addToHash(contato, agenda)) {
				printf("O contato não foi adicionado!");	
				exit(1);
			}
		}
		fclose(fhand);
		return 1;
	} else {
		printf("O arquivo não foi aberto!");
		return 0;
	}
}						
