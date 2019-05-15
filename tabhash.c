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
		//if (!toupper(t[i])) return;
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

int addToHash (REGISTRO tcont, EntradaHash* agenda, unsigned long int m) {
	EntradaHash contato = (EntradaHash)malloc(sizeof(REGISTRO));
	if (contato == NULL) {
		printf("Erro ao alocar noh!\n");
		exit(1);
	}
	strcpy(contato->nome, tcont.nome);
	strcpy(contato->RG, tcont.RG);
	contato->anoNascimento = tcont.anoNascimento;
	contato->CPF = tcont.CPF;
	contato->prox = NULL;
	
	unsigned long index = f_foldadd(contato->nome, m);
	if (agenda[index] == NULL) {
		agenda[index] = contato;
	} else {
		EntradaHash p, q;
		p = agenda[index];
		q = NULL;
		while (p != NULL) {
			q = p;
			p = p->prox;
		}
		q->prox = contato;
	}
	return 1;
}

int isInHash (char *nome, EntradaHash *agenda, REGISTRO *cont) {
	const unsigned long int m = 43991;
	unsigned long index = f_foldadd(nome, m);
	EntradaHash p, q;
	int achou = 0;
	if (agenda[index] != NULL) {
		p = agenda[index];
		q = NULL;
		printf("Procurando...\n");
		while ((p != NULL) && (strcmp(p->nome, nome) != 0)) {
			q = p;
			printf("RG: %s\n", q->RG);
			p = p->prox;
		}
		if (q == NULL) {
			printf("Laco nao rodou - Retornando p, RG: %s\n", p->RG);
			*cont = *p;
			return 1;
		} else if (p != NULL) {
			printf("Laco parou no meio - Retornando q, RG: %s\n", q->RG);
			*cont = *q;
			return 1;			
		} else {
			printf("Laco rodou inteiro e nao achou\n");
			return 0;
		}
	} else {
		return 0;
	}
}

int removeFromHash (char *nomeContato, EntradaHash *agenda) {
	REGISTRO contato;
	int numReg, i = 0;
	
	if (!isInHash(nomeContato, agenda, &contato)) {
		printf("O contato nao esta na agenda!\n");
	} else {
		exibirRegistro(contato, nomeContato, 1);
	}
	printf("Digite o numero do registro que deseja remover: ");
	scanf("%d", &numReg);
	
	EntradaHash p, q;
	p = &contato;
	q = NULL;
	while (i < numReg) {
		if (strcmp(p->nome, nomeContato) == 0) {
			i++;	
			if (i == numReg) break;
		}
		q = p;
		p = p->prox;
	}
	char conf;
	printf("Tem certeza que deseja remover %s? [S/N]", toupper(p->nome));
	scanf(" %c", &conf);
	if (conf == 'S') {
		q->prox = p->prox;
		free(p);
	}
	return 1;
}

void exibirRegistro(REGISTRO contato, char *nome, int numerar) {
	REGISTRO contTemp = contato;
	EntradaHash temp = &contTemp;
	if (&contato == temp) {
		printf("Ponteiros iguais\n");
	} else {
		printf("Ponteiros diferentes\n");
	}
	system("pause");
	char *cont_nome = _strupr(nome);
	while(temp != NULL) {
		char *temp_nome = _strupr(temp->nome);
		if (strcmp(temp->nome, cont_nome) == 0) {
			printf("+------------------------------------------------+\n");
			if (numerar) printf("|[ %2d  ]%41s|\n", numerar++, "");
			printf("|Nome: %42s|\n|RG: %44s|\n|Ano de nascimento: %29hu|\n|CPF: %43llu|\n",
			temp->nome, temp->RG, temp->anoNascimento, temp->CPF);
		}
		temp = temp->prox;
	}
	printf("+------------------------------------------------+\n");
}

						






