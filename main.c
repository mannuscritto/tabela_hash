#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "tabhash.h"

int main(int argc, char *argv[])
{
  const unsigned long int m = 43991; // http://compoasso.free.fr/primelistweb/page/prime/liste_online_en.php
  const long double A = (sqrt(5) - 1) / 2.0;
  
  EntradaHash tabelaHash[m];
  
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
  
  /*
  char nome[30];
  printf("Digite um nome: ");
  scanf("%s", nome);
  
  unsigned long index1 = f_foldadd(nome, m);
  unsigned long index2 = f_mult(nome, m, A);
  printf("Index para Fold and Add: %lu\nIndex para Mult: %lu\n", index1, index2);
	*/
	
	REGISTRO contato;
	char nome[30], rg[15];
	unsigned short anoNasc;
	unsigned long cpf;
	printf("Digite o nome: ");
	scanf("%s", nome);
	printf("Digite o RG: ");
	scanf("%s", rg);
	printf("Digite o ano de nascimento: ");
	scanf("%hu", &anoNasc);
	printf("Digite o CPF: ");
	scanf("%lu", &cpf);
	strcpy(contato.nome, nome);
	strcpy(contato.RG, rg);
	contato.anoNascimento = anoNasc;
	contato.CPF = cpf;
	contato.prox = NULL;
	
	int ok = addToHash(contato, tabelaHash, m);
	
	if (!ok) {
		printf("Erro ao inserir novo contato!");
		exit(1);
	}
	
	strcpy(contato.nome, "Testes");
	ok = addToHash(contato, tabelaHash, m);
	
	if (!ok) {
		printf("Erro ao inserir novo contato!");
		exit(1);
	}
	
	strcpy(contato.nome, "Testamentario");
	ok = addToHash(contato, tabelaHash, m);
	
	if (!ok) {
		printf("Erro ao inserir novo contato!");
		exit(1);
	}
	
	REGISTRO pesq_contato = isInHash("Testudo", tabelaHash);
	
	if (pesq_contato) {
		printf("%s esta na agenda!\n", pesq_contato.nome);
	} else {
		printf("%s nao esta na agenda!\n", nome);
	}
	  
  system("PAUSE");	
  return 0;
}
