#include "clientes_pedidos.h"
#include "produto.h" //para acessar o id do produto VERIFICAR SE É NECESSÁRIO MANTER
#include <cstring>
#include "max.h"

Cliente::Cliente()
{ // definindo os valores
  id_cliente = 0;
  nome_cliente[0] = '\0';
  id_produto_cliente = 0.0;
  quant_pedido = 0;
  prioridade = 0;
}

Cliente::Cliente(int id_cliente, const char nome_cliente[], int id_produto_cliente, int quant_pedido, int prioridade)
{
  this->id_cliente = id_cliente;
  strncpy(this->nome_cliente, nome_cliente, sizeof(this->nome_cliente) - 1);
  this->id_produto_cliente = id_produto_cliente;
  this->quant_pedido = quant_pedido;
  this->prioridade = prioridade;
}
void Cliente::setId_cliente(int id_cliente)
{
  this->id_cliente = id_cliente;
}

int Cliente::getId_cliente()
{
  return id_cliente;
}
void Cliente::setId_produto_cliente(int id_produto_cliente)
{
  this->id_produto_cliente = id_produto_cliente;
}

int Cliente::getId_produto_cliente()
{
  return id_produto_cliente;
}
void Cliente::setNome_cliente(const char *nome_cliente)
{
  strncpy(this->nome_cliente, nome_cliente, sizeof(this->nome_cliente) - 1);
  this->nome_cliente[sizeof(this->nome_cliente) - 1] = '\0';
}

const char *Cliente::getNome_cliente()
{
  return nome_cliente;
}
void Cliente::setQuant_pedido(int quant_pedido)
{
  this->quant_pedido = quant_pedido;
}

int Cliente::getQuant_pedido()
{
  return quant_pedido;
}

void Cliente::setPrioridade(int prioridade)
{
  this->prioridade = prioridade;
}

int Cliente::getPrioridade()
{
  return prioridade;
}
