#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

#define MAX_SIZE 100

// função para ordenar um vetor de números racionais
void ordenar_vet(struct racional v[], int tamanho) {
    // verifica se há denominador zero no vetor
    for (int j = 0; j < tamanho; j++) {
        if (v[j].den == 0) 
            return; 
    }

    // insertion sort
    for (int j = 1; j < tamanho; j++) {
        struct racional chave = v[j];  // acha a chave 
        int i = j - 1;

        // passa os elementos maiores que a chave para frente
        while (i >= 0 && compara_r(v[i], chave) > 0) {
            v[i + 1] = v[i];  // move v[i] para a frente
            i--;
        }
        
        // coloca chave na posição correta
        v[i + 1] = chave;
    }
}

// função para eliminar racionais inválidos de um vetor e passar pra posicao do NaN
void eliminar_elemento(struct racional v[], int *tamanho) {

    int i;

    for (i = 0; i < (*tamanho); i++) {
        
        if (!valido_r(v[i])) {

            v[i] = v[(*tamanho) - 1];
            (*tamanho) --;
            i --;
        }
    }
}


// Função para somar todos os racionais em um vetor usando soma_r
struct racional soma_total_racionais(struct racional v[], int tamanho) {
    struct racional soma = {0, 1}; // inicializa como 0
    struct racional temp;

    for (int i = 0; i < tamanho; i++) {
        if (!valido_r(v[i])) {
            // se o racional racional for inválido, retorna 0
            return soma; 
        }

        if (soma_r(soma, v[i], &temp)) {
            soma = temp; // atualiza
        }
    }

    return soma;
}


int main () {

   
    struct racional v_racionais[MAX_SIZE]; 
    struct racional soma;
    int fim, n, i, num, den;

    //le um valor n (tamanho do vetor) tal que 0 < n < 100, garante o numero dentro do intervalo
    fim = 1;
    do {
          scanf("%d", &n);
          if (n > 0 && n < 100)
              fim = 0;
    } while (fim); 

    //preenche o vetor com n numeros racionais lidos na entrada
    for (i = 0; i < n; i++) {

        scanf("%d %d", &num, &den);
        v_racionais[i] = cria_r(num, den);

   }

    //imprime o vetor de racionais
    printf("VETOR = ");
    for (i = 0; i < n; i++) {
        imprime_r(v_racionais[i]);
        printf(" "); 
    }
    printf("\n");

    //elimina os NaNs e imprime
    eliminar_elemento(v_racionais,&n);

    printf("VETOR = ");
    for (i = 0; i < n; i++) {
        imprime_r(v_racionais[i]);
        printf(" "); 
    }
     printf(" \n"); 


    //ordena o vetor e imprime
    ordenar_vet(v_racionais,n);

    printf("VETOR = ");
    for (i = 0; i < n; i++) {
        imprime_r(v_racionais[i]);
        printf(" "); 
    }
     printf(" \n"); 


    //soma os racionais do vetor e imprime
    soma = soma_total_racionais(v_racionais, n);

    printf("SOMA = ");
    imprime_r(soma);
    printf(" \n");

  return (0);
}
