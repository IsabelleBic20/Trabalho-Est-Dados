#include "produto.h"
#include <cstring>
#include "max.h"

Produto::Produto() {//definindo os valores
    id_produto = 0; 
    nome_produto[0] = '\0';
    preco_produto = 0.0; 
    quant_estoque = 0; 
}

Produto::Produto(int id_produto, const char nome_produto[], float preco_produto, int quant_estoque) {
    this->id_produto = id_produto;
    strncpy(this->nome_produto, nome_produto, sizeof(this->nome_produto) - 1);
    this->nome_produto[sizeof(this->nome_produto) - 1] = '\0';
    this->preco_produto = preco_produto;
    this->quant_estoque = quant_estoque;
}

void Produto::setId_produto(int id_produto){
    this->id_produto=id_produto;
}

int Produto::getId_produto() {
  return id_produto;
}
void Produto::setNome_produto(const char* nome_produto) {
    strncpy(this->nome_produto, nome_produto, sizeof(this->nome_produto) - 1);
    this->nome_produto[sizeof(this->nome_produto) - 1] = '\0';
}

const char* Produto::getNome_produto() {
    return nome_produto;
}
void Produto::setPreco_produto(float preco_produto){
    this->preco_produto = preco_produto;
}

float Produto::getPreco_produto() {
  return preco_produto;
}

void Produto::setQuant_estoque(int quant_estoque){
    this->quant_estoque = quant_estoque;
}
int Produto::getQuant_estoque() {
  return quant_estoque;
}


