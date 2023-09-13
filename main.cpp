#include <iostream>
#include "produto.h"
#include "produto.cpp"
#include "heap.h"
#include "heap.cpp"
#include "clientes_pedidos.h"
#include "clientes_pedidos.cpp"
#include "max.h"

using namespace std;

celula T[MAX]; // Tabela de dispersão, Produtos

//Processamento de Pedido
void ProcessarPedidos(Cliente& cliente, int estoque_produto[]) {
    int id_produto_cliente = cliente.getId_produto_cliente();
    int quantidade_pedido = cliente.getQuant_pedido();

    //id_produto_cliente é o id do produto que é fornecido pelo cliente
    cout << cliente.getId_cliente() << " " << cliente.getNome_cliente() << " " << id_produto_cliente << " " << quantidade_pedido;

    // Verificando se o produto existe
    int id_prod = busca_aberto(MAX, T, id_produto_cliente);

    if (id_prod != -1) {//se o id_prod foi encontrao
        int estoque = estoque_produto[id_produto_cliente];//estoque_produto recebe o id do cliente, associando estoque com o cliente e seus pedidos

        if (estoque >= quantidade_pedido) {//os produtos que estao no estoque devem ser maior ou igual que o pedido dos clientes
            estoque_produto[id_produto_cliente] -= quantidade_pedido;
            cout << " [OK]" << endl;
        } else {
            cout << " [NAO ATENDIDO]" << endl;
        }
    }
}

void ImprimirPedidos(Cliente* cliente, int estoque_produto[], int MAX){
    int i;
    for(i=0;i<MAX;i++){
        if (cliente[i].getId_cliente() != -1) {
            ProcessarPedidos(cliente[i], estoque_produto);   
        }
    }
}

int main() {
    int tam, i;
    int n = 0; // número de clientes que serão adicionados na lista de prioridade
    char nome_cliente[50];


    //INSTANCIANDO OBJETOS
    Cliente cliente;
    Produto produto; 
    Heap heap;
    //Tab_disper tab_dis

    int lista_prioridade[MAX];

    inicializartabela(T);//inicializar tabela dispersao
    heap.inicializar_lista_prioridades(lista_prioridade);  // Fazendo a lista de prioridades iniciar com zero

    cout << "Digite a quantidade de produtos a serem cadastrados: ";
    cin >> tam;

    cin.ignore();

   int estoque_produto[MAX];

    for (i = 0; i < tam; i++) {
        int id;
        char nome[30];
        float preco;
        int quant;

        cout << "Digite o ID do produto: ";
        cin >> id;
        cin.ignore();

        cout << "Digite o nome do produto: ";
        cin.getline(nome, sizeof(nome));

        cout << "Digite o preco do produto: ";
        cin >> preco;
        cin.ignore();

        cout << "Digite a quantidade em estoque: ";
        cin >> quant;
        cin.ignore();

        produto.setId_produto(id);
        produto.setNome_produto(nome);
        produto.setPreco_produto(preco);
        produto.setQuant_estoque(quant);

        int inserir_tabela = insere_aberto(MAX, T, produto.getId_produto());

         // Associando o ID do produto ao estoque 
        estoque_produto[produto.getId_produto()] = produto.getQuant_estoque();

        //apenas para imprimir qnd o produto for inserido na tabela 
       /* if (inserir_tabela != MAX) {
            cout << "Produto " << produto.getId_produto() << " inserido " << endl;            
        } else {
            cout << "Não foi inserido" << endl;
        }*/
    }

    //Instanciando objetos de cada prioridade do tipo array da classe Cliente
    //Cada cliente sera armazenado em listas especificas de acordo com a prioridade
     Cliente premium[MAX];
     Cliente regular[MAX];
     Cliente eventual[MAX];



    //inicializando os objetos do tipo array com VAZIO (-1) 
    for (int i = 0; i < MAX; i++) {
    premium[i].setId_cliente(-1);
    regular[i].setId_cliente(-1);
    eventual[i].setId_cliente(-1);
}

    while (true) {
        int id_cliente;
        int id_produto_cliente;
        int quant_pedido;
        int prioridade;

        //Processar o cliente com maior prioridade
        int cliente_prioridade = heap.extrai_maxima(&n, lista_prioridade);//n clientes

        cout << "ID cliente: ";
        cin >> id_cliente;

        if (id_cliente == -1) {
            break; // Se o usuário inserir -1, finalizar
        }

        cin.ignore(); 

        cout << "Nome do cliente: ";
        cin.getline(nome_cliente, sizeof(nome_cliente));

        cout << "Digite o ID do produto: ";
        cin >> id_produto_cliente;

        cin.ignore(); 

        cout << "Quantidade do pedido: ";
        cin >> quant_pedido;

        cin.ignore(); 

        cout << "Prioridade (3: Premium, 2: Regular, 1: Eventual) ";
        cin >> prioridade;

        heap.insere_lista(&n, lista_prioridade, prioridade);   // inserindo na lista de prioridades

        cliente.setId_cliente(id_cliente);
        cliente.setNome_cliente(nome_cliente);
        cliente.setId_produto_cliente(id_produto_cliente);
        cliente.setPrioridade(prioridade);
        cliente.setQuant_pedido(quant_pedido);

        //Os clientes serão armazenados cada um em sua respectiva prioridade
        if (prioridade == 3) {
            premium[cliente_prioridade] = cliente;
        } else if (prioridade == 2) {
            regular[cliente_prioridade] = cliente;
        } else if (prioridade == 1) {
            eventual[cliente_prioridade] = cliente;
        }
    }

//chamando a função ImprimirPedidos 
ImprimirPedidos(premium, estoque_produto, MAX);
ImprimirPedidos(regular, estoque_produto, MAX);
ImprimirPedidos(eventual, estoque_produto, MAX);


    return 0;
}


