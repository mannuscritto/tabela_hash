/*
 * Vamos fazer uma pequena agenda de telefone que armazena
 * os dados em uma tabela hash
 *
 * Voce deve construir um pequeno menu com, no minimo, as seguintes
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
#include <locale.h>
#include "tabhash.h"

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "Portuguese");
	const unsigned long int m = 43991; // http://compoasso.free.fr/primelistweb/page/prime/liste_online_en.php
	const long double A = (sqrt(5) - 1) / 2.0;
	
	EntradaHash tabelaHash[m];

	int opt;
	REGISTRO contato;
	char nome[45], rg[13];
	unsigned short int anoNasc;
	unsigned long long int cpf;
	while (1) {
		system("cls");
		printf("\t\tMenu\n\n");
		printf("\tInserir um contato..............[1]\n");
		printf("\tBuscar um contato...............[2]\n");
		printf("\tRemover um contato..............[3]\n");
		printf("\tImportar contatos...............[4]\n");
		printf("\tSair............................[0]\n");
		printf("\nDigite a opção: ");
		scanf("%d", &opt);
		system("cls");
		switch (opt) {
			   case 1:
			   		printf("\t\tADICIONAR CONTATO\n\n");
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
		 	   		
		 	   		if (!addToHash(contato, tabelaHash)) {
		 	   		   printf("O contato não foi adicionado!");	
		 	   		   exit(1);
					}
					break;
				case 2:
					printf("Digite o nome do contato: ");
		 	   		scanf("%s", nome);
		 	   		if (!isInHash(nome, tabelaHash, &contato)) {
		 	   			printf("O contato não foi encontrado!\n");
					} else {
						exibirRegistro(contato, nome, 0);
					}
		 	   		break;
		 	   	case 3:
		 	   		printf("Digite o nome do contato: ");
		 	   		scanf("%s", nome);
		 	   		if (!removeFromHash(nome, tabelaHash)) {
						printf("O contato não foi removido!\n");
					}
					break;
				case 4:
					//printf("Digite o nome do arquivo: ");
		 	   		//scanf("%s", nome);
		 	   		if (!importarRegistros("registros.txt", tabelaHash)) {
		 	   			printf("Os contatos não foram importados!\n");
		 	   			exit(1);
					} else {
						printf("Os contatos foram importados com sucesso!\n");
					}
					break;
				case 0:
					exit(0);
					break;
				default:
					printf("Opção inválida!\n");
		}
		system("pause");
	}
	 
	system("PAUSE");
	return 0;
}
