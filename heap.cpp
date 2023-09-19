#include "heap.h"
#include "max.h"
#include <cstdio>

Heap::Heap()
{
}
// antes de adicionar as chaves, fazer com que o estado da tabela sejam VAZIOS
void Heap::inicializar_lista_prioridades(int S[])
{
  for (int i = 0; i < MAX; i++)
  {
    S[i] = -1; //-1 -> VAZIA
  }
}

int Heap::pai(int i)
{
  return (i - 1) / 2;
}

int Heap::esquerdo(int i)
{
  return 2 * (i + 1) - 1;
}

int Heap::direito(int i)
{
  return 2 * (i + 1);
}

void Heap::troca(int *menor, int *maior)
{
  int aux = *menor;

  *menor = *maior;
  *maior = aux;
}

void Heap::desce(int n, int S[MAX], int i)
{
  int e, d, maior;
  e = esquerdo(i);
  d = direito(i);
  if (e < n && S[e] > S[i])
    maior = e;
  else
    maior = i;
  if (d < n && S[d] > S[maior])
    maior = d;
  if (maior != i)
  {
    troca(&S[i], &S[maior]);
    desce(n, S, maior);
  }
}

void Heap::sobe(int n, int S[MAX], int i)
{
  while (S[pai(i)] < S[i])
  {
    troca(&S[i], &S[pai(i)]);
    i = pai(i);
  }
}
void Heap::insere_lista(int *n, int S[MAX], int p) // n-> quantidade de clientes a serem adicionados, p->prioridade
{
  S[*n] = p;
  *n = *n + 1;
  sobe(*n, S, *n - 1);
}

int Heap::extrai_maxima(int *n, int S[MAX])
{ 
  int maior = 0;

  for (int i = 0; i < *n; i++)
  {
    if (S[i] > maior)
    {
      maior = S[i];
    }
  }
  if (maior != 0)
  {
    int indice_maior = 0;
    for (int i = 0; i < *n; i++)
    {
      if (S[i] == maior)
      {
        indice_maior = i;
        break;
      }
    }
    // Trocar a maior prioridade com a última da lista
    troca(&S[indice_maior], &S[*n - 1]);
    (*n)--; // Diminui a quantidade de elementos na lista

    return maior;
  }

  return 0; // Se não tiver elementos na lista, retornar -1
}

