#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "tabhash.h"

unsigned long int f_foldadd (char *chave, unsigned long int m)
{
   unsigned long int k;
   char *t;
   
   k = 0;
   t = chave;
   
   while (*t != '\0')
      k = k + ((unsigned long int) *t) % m;
   
   return k;
}

unsigned long int f_mult (char *chave, unsigned long int m, long double A)
{
   unsigned long int k_temp, k;
   
   k_temp = f_foldadd (chave, 100010717);
   k = floor(m * (k_temp * A - floor (k_temp * A)));
   return k;
}
