#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

/* retorna um número aleatório entre min e max, inclusive. */
long aleat (long min, long max) {

    return min + rand() % (max - min + 1);
}

/* Máximo Divisor Comum entre a e b      */
long mdc (long a, long b) {

    if (b == 0)
      return a;

    return mdc(b, a % b); //recursivo
  
}

/* Mínimo Múltiplo Comum entre a e b */
long mmc (long a, long b) {
    
    return (a * b) / mdc (a, b);
}

/* Recebe um número racional e o simplifica.*/
struct racional simplifica_r (struct racional r) {
      
    int divisor;
    
    //caso invalido
    if (valido_r(r) == 0)
        return r;

    //divide num e den pelo mdc
    divisor = mdc(r.num, r.den);
    r.num /= divisor;
    r.den /= divisor;
    
    /* Se ambos numerador e denominador forem negativos, deve retornar um positivo.
    * Se o denominador for negativo, o sinal deve migrar para o numerador. */
    if (r.den < 0) {
        r.num = r.num * (-1);
        r.den = r.den * (-1);
    }
    return r;
}
/* Cria um número racional com o numerador e denominador indicados. */
struct racional cria_r (long numerador, long denominador) {

    struct racional r; 

    r.num = numerador;
    r.den = denominador;

    return simplifica_r(r);
}


/* Retorna um número racional aleatório na forma simplificada.*/
struct racional sorteia_r (long min, long max){

    struct racional r;

    r.num = aleat (min,max);
    r.den = aleat (min, max);

    return simplifica_r(r);
}

/* Retorna 1 se o racional r for válido ou 0 se for inválido. */
int valido_r (struct racional r) {
    if (r.den != 0)
        return 1;
    return 0;
}

/* Imprime um racional r */
void imprime_r (struct racional r) {

    //confere se r eh valido, caso nao, imprime invalido
    if (valido_r(r) == 0) {
        printf("NaN");
        return;
    }
    //verifica se o numerador eh 0, se for, imprime apenas 0
    if (r.num == 0)
        printf("0");

    //verifica se o denominador eh 1, se for imprime apenas numerador
    else if (r.den == 1)
        printf("%ld", r.num);

    //verifica se numerador e denominador são iguais
    else if (r.num == r.den)
        printf("1");

    else
    //imprime padrao
    printf("%ld/%ld", r.num, r.den);
}

/* Compara dois racionais r1 e r2.*/
int compara_r (struct racional r1, struct racional r2){
    int den, num1, num2;

    if(!valido_r(r1) || !valido_r(r2))
        return -2;

    den = mmc(r1.den, r2.den);

    num1 = r1.num * (den / r1.den);
    num2 = r2.num * (den / r2.den);

    if (num1 < num2)
        return -1;
    else if (num1 > num2)
            return 1;
    else
        return 0;
}

/* Retorna a soma dos racionais r1 e r2 no parametro *r3.*/
int soma_r (struct racional r1, struct racional r2, struct racional *r3) {
    if (r3 == NULL)
        return 0;
    
    if (!valido_r(r1) || !valido_r(r2))
        return 0;
    
    //soma de racionais
    r3->num = (r1.num * r2.den) + (r2.num * r1.den);
    r3->den = r1.den * r2.den;

    ///simplifica
    *r3 = simplifica_r(*r3);

    return 1;
}

/* Retorna a subtracao dos racionais r1 e r2 no parametro *r3.*/
int subtrai_r (struct racional r1, struct racional r2, struct racional *r3){
    if (r3 == NULL)
        return 0;
    
    if (!valido_r(r1) || !valido_r(r2))
        return 0;
    
    //soma de racionais
    r3->num = (r1.num * r2.den) - (r2.num * r1.den);
    r3->den = r1.den * r2.den;

    //simplifica
    *r3 = simplifica_r(*r3);

    return 1;
}
/* Retorna a multiplicacao dos racionais r1 e r2 no parametro *r3.*/
int multiplica_r (struct racional r1, struct racional r2, struct racional *r3) {

    if (r3 == NULL)    
        return 0;
    
    if (!valido_r(r1) || !valido_r(r2))
        return 0;
    
    //operação de multiplicação
    r3->num = r1.num * r2.num;
    r3->den = r1.den * r2.den;

    //simplifica
    *r3 = simplifica_r(*r3);

    return 1;
}        

/* Retorna a divisao dos racionais r1 e r2 no parametro *r3.*/
int divide_r (struct racional r1, struct racional r2, struct racional *r3) {
    
    if (r3 == NULL)    
        return 0;
    
    if (!valido_r(r1) || !valido_r(r2))
        return 0;
    
    r3->num = r1.num * r2.den;
    r3->den = r2.num * r1.den;

    //simplifica
    *r3 = simplifica_r(*r3);

    return 1;
}