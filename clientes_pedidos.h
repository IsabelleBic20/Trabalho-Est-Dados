#include <iostream>
using namespace std;
using std::string;
#ifndef CLIENTES_PEDIDOS_H
#define CLIENTES_PEDIDOS_H
class Cliente{
public:
Cliente();

Cliente(int id_cliente, const char nome_cliente[],int id_produto_cliente, int quant_pedido,int prioridade );
  
  void setId_cliente(int id_cliente);
  int getId_cliente();

  void setNome_cliente(const char* nome_cliente);
  const char* getNome_cliente();

void setId_produto_cliente(int id_produto_cliente);
    int getId_produto_cliente();

  void setQuant_pedido(int quant_pedido);
  int getQuant_pedido();

  void setPrioridade(int prioridade);
  int getPrioridade();
   
  
private:

    int id_cliente;
    char nome_cliente[50];
    int id_produto_cliente;
    int quant_pedido;
    int prioridade;


};

#endif
