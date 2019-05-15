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

/*int isInHash (char *nome, EntradaHash *agenda, REGISTRO cont) {
	const unsigned long int m = 43991;
	unsigned long index = f_foldadd(nome, m);
	EntradaHash p, q;
	if (agenda[index] != NULL) {
		p = agenda[index];
		q = NULL;
		while ((p != NULL) && (strcmp(p->nome, nome) != 0)) {
			q = p;
			p = p->prox;
		}
		if (q == NULL) {
			cont = *p;
			printf("Passando %s\n", p->nome);
			return 1;
		}
		cont = *q;
		printf("Passando %s\n", q->nome);
		return 1;
	} else {
		return;
	}
}*/

int isInHash (char *nome, EntradaHash *agenda, REGISTRO cont) {
	const unsigned long int m = 43991;
	unsigned long index = f_foldadd(nome, m);
	EntradaHash p, q;
	if (agenda[index] != NULL) {
		p = agenda[index];
		q = NULL;
		while ((p != NULL) && (strcmp(p->nome, nome) != 0)) {
			q = p;
			p = p->prox;
		}
		if (q == NULL) {
			cont = *p;
			printf("Passando %s\n", p->nome);
			return 1;
		}
		cont = *q;
		printf("Passando %s\n", q->nome);
		return 1;
	} else {
		return;
	}
}

int removeFromHash(char *nome, EntradaHash *agenda) {
	const unsigned long int m = 43991;
	unsigned long index = f_foldadd(nome, m);
	EntradaHash p, q, temp;
	if (agenda[index] != NULL) {
		p = agenda[index];
		q = NULL;
		while ((p != NULL) && (strcmp(p->nome, nome) != 0)) {
			q = p;
			p = p->prox;
		}
		if (q == NULL) {
			temp = p;
			p = p->prox;
		} else {
			temp = q;
			q = q->prox;	
		}
	} else {
		return;
	}
	free(temp);
	return 1;
}








