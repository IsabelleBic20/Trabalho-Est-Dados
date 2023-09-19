/**************************************************
 *
 * Estudantes: Igmar Flores e Isabelle Bicudo
 * Trabalho 1
 * Professor(a): Fábio Henrique Martinez
 *
 */

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

// Processamento de Pedido
void ProcessarPedidos(Cliente &cliente, Produto produtos[])
{
    int id_produto_cliente = cliente.getId_produto_cliente();
    int quantidade_pedido = cliente.getQuant_pedido();

    // Verificando se o produto existe na tabela de dispersão
    int id_prod = busca_aberto(MAX, T, id_produto_cliente);
    if (id_prod != -1)
    {
        int estoque;
        int index;
        for (int i = 0; i < MAX; i++)
        {
            if (produtos[i].getId_produto() == id_produto_cliente)
            {

                estoque = produtos[i].getQuant_estoque();
                index = i;
            }
        }

        if (estoque >= quantidade_pedido)
        {
            // Se houver estoque suficiente, decrementa a quantidade e imprime [OK]
            produtos[index].setQuant_estoque(estoque - quantidade_pedido);
            cout<<"\n"<<endl;
            cout << "------------- [ PEDIDO EFETUADO ] -------------" << endl;
        }
        else
        {    
            cout<<"\n"<<endl;
            // Se o estoque for insuficiente, imprime [ESTOQUE INSUFICIENTE]
            cout << endl
                 << "------------- [ ESTOQUE INSUFICIENTE ] -------------" << endl;
        }

        // Imprime informações sobre o cliente e o pedido
        cout << "ID do Cliente : [ " << cliente.getId_cliente() << " ]" << endl;
        cout << "Nome          : [ " << cliente.getNome_cliente() << "]" << endl;
        cout << "ID do Produto : [ " << id_produto_cliente << " ]" << endl;
        cout << "Quantidade    : [ " << quantidade_pedido << " ]" << endl
             << endl;
    }
}

void imprimirEstoque(Produto produtos[], long long int tam)
{
    cout<<"\n"<<endl;
    cout << "------------- RELATORIO DE ESTOQUE -------------" << endl;
    for (int i = 0; i < tam; i++)
    {
        if (produtos[i].getId_produto() != 0)
        {
            cout << "ID            : [ " << produtos[i].getId_produto() << " ]" << endl;
            cout << "Nome          : [ " << produtos[i].getNome_produto() << " ]" << endl;
            cout << "Preco         : [ " << produtos[i].getPreco_produto() << " ]" << endl;
            cout << "Quantidade    : [ " << produtos[i].getQuant_estoque() << " ]" << endl;
            cout << "-" << endl;
        }
    }
}

void ImprimirPedidos(Cliente *cliente, Produto *produtos, int MAX)
{
    for (int i = 0; i < MAX; i++)
    {
        if (cliente[i].getId_cliente() != -1)
        {
            // Chama a função de processamento de pedidos para cada cliente válido
            ProcessarPedidos(cliente[i], produtos);
        }
    }
}

Produto CriaProduto(long long int id_produto)
{
    Produto produto;
    char nome[30];
    float preco;
    int quant;

    produto.setId_produto(id_produto);

    // Solicita informações sobre o produto ao usuário
    cout << "Digite o nome do produto: ";
    cin.ignore();
    cin.getline(nome, sizeof(nome));

    cout << "Digite o preco do produto: ";
    cin >> preco;
    cin.ignore();

    cout << "Digite a quantidade em estoque: ";
    cin >> quant;
    cin.ignore();

    produto.setId_produto(id_produto);
    produto.setNome_produto(nome);
    produto.setPreco_produto(preco);
    produto.setQuant_estoque(quant);

    return produto;
}

int main()
{
   long long int tam, i;
    int n = 0; // Número de clientes que serão adicionados na lista de prioridade
    char nome_cliente[50];

    // INSTANCIANDO OBJETOS
    Cliente cliente;
    Produto produto;
    Heap heap;

    int lista_prioridade[MAX];

    inicializartabela(T);                                 // Inicializa a tabela de dispersão
    heap.inicializar_lista_prioridades(lista_prioridade); // Inicializa a lista de prioridades

    cout << "=================================================" << endl;
    cout << "               CADASTRO DE PRODUTOS              " << endl;
    cout << "=================================================" << endl;
    cout << "Digite a quantidade de produtos a serem cadastrados (100 no maximo): ";
    cin >> tam;

    cin.ignore();

    long long int ids[tam];
    Produto *produtos = new Produto[tam];

    for (i = 0; i < tam; i++)
    {
        ids[i] = 0;
        produtos[i].setId_produto(0); // Inicializando vetores
    }

    for (i = 0; i < tam; i++)
    {

        long long int id;
        cout << "Digite o ID do produto: ";
        cin >> id;
        cin.ignore();

        if (ids[id] != 0)
        {
            cout << "Produto ja existe" << endl;
            i--;
        }
        else
        {
            // Cria um novo produto e insere na tabela de dispersão
            produtos[i] = CriaProduto(id);

            int inserir_tabela = insere_aberto(MAX, T, id);
            // Associa o ID do produto ao estoque
            ids[id] = id;
        }
    }

    // Instanciando objetos de cada prioridade do tipo array da classe Cliente
    // Cada cliente será armazenado em listas específicas de acordo com a prioridade
    Cliente premium[MAX];
    Cliente regular[MAX];
    Cliente eventual[MAX];

    // Inicializando os objetos do tipo array com VAZIO (-1)
    for (int i = 0; i < MAX; i++)
    {
        premium[i].setId_cliente(-1);
        regular[i].setId_cliente(-1);
        eventual[i].setId_cliente(-1);
    }

    cout<<"\n"<<endl;
    cout << "=================================================" << endl;
    cout << "               CADASTRO DE CLIENTES              " << endl;
    cout << "=================================================" << endl;
    while (true)
    {
        int id_cliente;
        int id_produto_cliente;
        int quant_pedido;
        int prioridade;

        // Processar o cliente com maior prioridade da lista de prioridades
        int cliente_prioridade = heap.extrai_maxima(&n, lista_prioridade);
        cout << "ID cliente (Insira -1 para sair): ";
        cin >> id_cliente;
        cin.ignore();

        if (id_cliente == -1)
        {
            break;
        }

        const char *nome[1];
        nome[0] = 0;
        // Verifica em todas as listas se existe alguém com o ID, para não repetir
        for (int i = 0; i < MAX; i++)
        {
            if (id_cliente == premium[i].getId_cliente())
            {
                nome[0] = premium[i].getNome_cliente();
            }
            if (regular[i].getId_cliente() == id_cliente)
            {
                nome[0] = regular[i].getNome_cliente();
            }
            if (eventual[i].getId_cliente() == id_cliente)
            {
                nome[0] = eventual[i].getNome_cliente();
            }
        }
        // Se não existir, pega o nome do cliente novo.
        if (nome[0] == 0)
        {
            cout << "Nome do cliente: ";
            cin.getline(nome_cliente, sizeof(nome_cliente));
            cliente.setNome_cliente(nome_cliente);
        }
        else // Se já existir, só seta busca por ID
        {
            cliente.setNome_cliente(nome[0]);
        }

        bool validar_produto = false;
        while (!validar_produto)
        {
            cout << "Digite o ID do produto: ";
            cin >> id_produto_cliente;
            cin.ignore();

            for (i = 0; i < tam; i++)
            {
                if (produtos[i].getId_produto() == id_produto_cliente)
                {
                    validar_produto = true;
                    break;
                }
            }
            if (!validar_produto)
            {
                cout << "ID do produto invalido, tente novamente." << endl;
            }
        }

        cout << "Quantidade do pedido: ";
        cin >> quant_pedido;
        cin.ignore();

        cout << "Prioridade (1 - Eventual, 2 - Regular, 3 - Premium ): ";
        cin >> prioridade;
        cin.ignore();

        heap.insere_lista(&n, lista_prioridade, prioridade); // Insere o cliente na lista de prioridades

        cliente.setId_cliente(id_cliente);
        cliente.setId_produto_cliente(id_produto_cliente);
        cliente.setPrioridade(prioridade);
        cliente.setQuant_pedido(quant_pedido);

        // Os clientes serão armazenados em suas respectivas prioridades
        if (prioridade == 3)
        {
            premium[cliente_prioridade] = cliente;
        }
        else if (prioridade == 2)
        {
            regular[cliente_prioridade] = cliente;
        }
        else if (prioridade == 1)
        {
            eventual[cliente_prioridade] = cliente;
        }
    }
    imprimirEstoque(produtos, tam);

    // Chamando a função ImprimirPedidos para cada lista de clientes
    ImprimirPedidos(premium, produtos, MAX);
    ImprimirPedidos(regular, produtos, MAX);
    ImprimirPedidos(eventual, produtos, MAX);

    imprimirEstoque(produtos, tam);

    delete[] produtos;

    return 0;
}