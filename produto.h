#include <iostream>
using namespace std;
using std::string;

#ifndef PRODUTO_H
#define PRODUTO_H
#include "max.h" //tive que fazer uma classe declarando MAX=100 pq mesmo declarando MAX no escopo estava dando erro

class Produto
{
public:
    Produto();

    Produto(long long int id_produto, const char nome[], float preco, int estoque);

    void setId_produto(long long int id_produto);
    long long int getId_produto();

    void setNome_produto(const char *nome_produto);
    const char *getNome_produto();

    void setPreco_produto(float preco_produto);
    float getPreco_produto();

    void setQuant_estoque(int quant_estoque);
    int getQuant_estoque();

private:
    int id_produto;
    char nome_produto[30];
    float preco_produto;
    int quant_estoque;
};

// IMPLEMENTAÇÃO DA TABELA DE DISPERSÃO COM ENDEREÇAMENTO ABERTO

struct cel
{
    long long int chave;
    int estado;
};
typedef struct cel celula;

// método da divisão, função que vai calcular o indice da tabela que vai receber o elemento x
int h( long long int x, int i)
{
    // x-> chave, i->indice da tabela, MAX->valor máximo do vetor
    return (x + i) % MAX;
}

void inicializartabela(celula T[MAX])
{ // antes de adicionar as chaves, fiz com que o estado da tabela sejam todos VAZIOS
    for (int i = 0; i < MAX; i++)
    {
        T[i].estado = -1; //-1 -> VAZIA
    }
}

int busca_aberto(int m, celula T[MAX], long long int x)
{
    int i = 0;
    int j;

    do
    {
        j = h(x, i); // Calcula o índice com base no valor de i
        if (T[j].chave == x && T[j].estado == 1)
        { // 1->OCUPADA
            return j;
        }
        else
        {
            i++;
        }
    } while (T[j].estado != -1 && i != m); // não encontrou x

    return -1; // Retornar -1 significa que o produto não foi encontrado
}

int insere_aberto(int m, celula T[MAX], long long int x)
{ // m-> MAX (tamanho da tabela), x->chave (id do produto)
    int i, j;
    i = 0;
    do
    {
        j = h(x, i);
        if (T[j].estado != 1)
        {
            T[j].chave = x;
            T[j].estado = 1;
            return j;
        }
        else
        {
            i++;
        }
    } while (i != m);

    return m;
}

#endif
