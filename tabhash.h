typedef struct __registro
{
   char nome[30];
   char RG[15];
   unsigned short int anoNascimento;
   unsigned long long int CPF;
   struct __registro *prox;
} REGISTRO;

typedef REGISTRO* EntradaHash;

unsigned long int f_foldadd (char *, unsigned long int);     // chave, m
unsigned long int f_mult (char *, unsigned long int, long double); // chave, m, A

int addToHash (REGISTRO, EntradaHash*, unsigned long int);
REGISTRO isInHash (char*, EntradaHash*);
int removeFromHash (char*, EntradaHash*);
