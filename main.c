/*
 * Vamos fazer uma pequena agenda de telefone que armazena
 * os dados em uma tabela hash
 *
 * Voce deve construir um pequeno meu com, no minimo, as seguintes
 * opcoes
 *
 * 1) Inserir um contato;
 * 2) Mostrar os dados de um contato;
 * 3) Remover um contato;
 *
 * Escolha um metodo de geracao da chave (fold&Add ou Mult) e
 * faca funcionar
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "tabhash.h"

int main(int argc, char *argv[]) {
	const unsigned long int m = 43991; // http://compoasso.free.fr/primelistweb/page/prime/liste_online_en.php
	const long double A = (sqrt(5) - 1) / 2.0;
	
	EntradaHash tabelaHash[m];
	 
	int opt;
	REGISTRO contato;
	char nome[30], rg[15];
	unsigned short int anoNasc;
	unsigned long long int cpf;
	while (1) {
		system("cls");
		printf("\t\tMenu\n\n\tInserir o contato [1]\n\tMostrar os dados de um contato [2]\n\tRemover um contato [3]\n\nDigite a opcao: ");
		scanf("%d", &opt);
		switch (opt) {
			   case 1:
		 	   		printf("Digite o nome do contato: ");
		 	   		scanf("%s", nome);
		 	   		printf("Digite o RG: ");
		 	   		scanf("%s", rg);
		 	   		printf("Digite o ano de nascimento: ");
		 	   		scanf("%hu", &anoNasc);
		 	   		printf("Digite o CPF: ");
		 	   		scanf("%llu", &cpf);
		 	   		
		 	   		strcpy(contato.nome, nome);
		 	   		strcpy(contato.RG, rg);
		 	   		contato.anoNascimento = anoNasc;
		 	   		contato.CPF = cpf;
		 	   		contato.prox = NULL;
		 	   		
		 	   		if (!addToHash(contato, tabelaHash, m)) {
		 	   		   printf("Erro ao adicionar contato!");	
		 	   		   exit(1);
					}
					break;
				case 2:
					printf("Digite o nome do contato: ");
		 	   		scanf("%s", nome);
		 	   		EntradaHash cont;
		 	   		if (!isInHash(nome, tabelaHash, cont)) {
		 	   			printf("O contato nao esta na agenda!\n");
					} else {
						do {
							printf("Nome: %s\nRG: %s\nAno de nascimento: %hu\nCPF: %llu\n", 
							contato.nome, contato.RG, contato.anoNascimento, contato.CPF);	
							if (cont->prox != NULL)
								cont = cont->prox;
							else
								break;
						} while(cont != NULL);
					}
		 	   		break;
		 	   	case 3:
		 	   		printf("Digite o nome do contato: ");
		 	   		scanf("%s", nome);
		 	   		if (!isInHash(nome, tabelaHash, &contato)) {
		 	   			printf("O contato nao esta na agenda!\n");
					} else {
						do {
							printf("Nome: %s\nRG: %s\nAno de nascimento: %hu\nCPF: %llu\n", 
							contato.nome, contato.RG, contato.anoNascimento, contato.CPF);	
							if (contato.prox != NULL)
								contato = *contato.prox;
							else
								break;
						} while(&contato.prox != NULL);
					}
					char conf;
					printf("Tem certeza que deseja remover %s? [S/N]", toupper(contato.nome));
					scanf(" %c", &conf);
					if (conf == 'S') {
						if (!removeFromHash(contato.nome, tabelaHash)) {
							printf("Erro ao remover contato!");
						}
					}
					//break;
		}
		system("pause");
	}
	 
	system("PAUSE");
	return 0;
}
