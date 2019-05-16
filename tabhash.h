typedef struct __registro
{
   char nome[45];
   char RG[15];
   unsigned short int anoNascimento;
   unsigned long long int CPF;
   struct __registro *prox;
} REGISTRO;

typedef REGISTRO* EntradaHash;

unsigned long int f_foldadd (char *, unsigned long int);     // chave, m
unsigned long int f_mult (char *, unsigned long int, long double); // chave, m, A

int addToHash (REGISTRO, EntradaHash*);
int isInHash (char*, EntradaHash*, REGISTRO*);
int removeFromHash (char*, EntradaHash*);

void exibirRegistro(REGISTRO, char*, int);
int importarRegistros(char*, EntradaHash*);
