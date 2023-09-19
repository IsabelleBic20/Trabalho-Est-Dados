#ifndef HEAP_H
#define HEAP_H
#include "max.h"

class Heap
{
public:
    Heap();
    void inicializar_lista_prioridades(int S[]);
    void insere_lista(int *n, int S[MAX], int p);
    void troca(int *menor, int *maior);
    int extrai_maxima(int *n, int S[MAX]);
    // void aumenta_prioridade(int n, int S[MAX],  int i, int p);
    // int consulta_maxima(int S[MAX]);

private:
    int S[MAX];
    int tamanho;

    int esquerdo(int i);
    int direito(int i);
    int pai(int i);
    void desce(int n, int S[MAX], int i);
    void sobe(int n, int S[MAX], int i);
};

#endif