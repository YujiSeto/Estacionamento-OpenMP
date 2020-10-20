// Estacionamento OpenMP.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//
#include <stdio.h>
#include <string>
#include <iostream>
#include <thread>
#include <omp.h>
#include <condition_variable>
using namespace std;

//Criação de Variáveis
string opcao = "0";             // Navegação no Menu
int qtdcancelas = 0;            // Quantidade de Cancelas
int qtdvagas = 0;               // Quantidade de Vagas Total
int qtdvagasdisponiveis = 0;    // Quantidade de Vagas Disponível
int qtdvagasocupadas = 0;       // Quantidade de Vagas Ocupadas
int qtdveiculos = 0;            // Quantidade de Veículos Entrando ou Saindo
int i;                          // Controle de FOR
int numeroveiculo = 1;          // Número do Veículo Entrando ou Saindo
int numerovaga = 0;             // Número da Vaga
int tempodeespera = 100;        // Tempo de Espera em ms para Entrada e Saída de Veículos
int numveiculos = 0;

int main()
{
    do
    {
        if (qtdvagas == 0) // Proteção para não acessar a Tela de Configuração Novamente
        {
            do
            {
                system("cls");
                cout << "+------------------------------------------+\n";
                cout << "|       CONFIGURACAO ESTACIONAMENTO        |\n";
                cout << "+------------------------------------------+\n";
                cout << "\n";
                cout << "Digite o numero de Vagas que o Estacionamento possui:\n";
                cin >> qtdvagas; //Cadastrar a quantidade Total de Vagas do Estacionamento

                if (qtdvagas <= 0)
                {
                    cout << "ERRO!!!\n";
                    cout << "O numero de vagas nao pode ser 0 ou menor que 0.\n";
                    system("pause");
                }

            } while (qtdvagas <= 0);

            qtdvagasdisponiveis = qtdvagas; //Inicializar a quantidade de Vagas Disponíveis do Estacionamento

            do
            {
                system("cls");
                cout << "+------------------------------------------+\n";
                cout << "|       CONFIGURACAO ESTACIONAMENTO        |\n";
                cout << "+------------------------------------------+\n";
                cout << "\n";
                cout << "Digite o numero de Cancelas:\n";
                cin >> qtdcancelas; //Cadastrar a quantidade Total de Cancelas do Estacionamento

                if (qtdcancelas <= 0)
                {
                    cout << "ERRO!!!\n";
                    cout << "O numero de cancelas nao pode ser 0 ou menor que 0.\n";
                    system("pause");
                }

            } while (qtdcancelas <= 0);
        }

        //Menu Principal
        system("cls");
        cout << "+------------------------------------------+\n";
        cout << "|       ESTACIONAMENTO                     |\n";
        cout << "+------------------------------------------+\n";
        cout << "";
        cout << "--------------------------------------------\n";
        cout << "  Quantidade Total de Vagas : " << qtdvagas << "\n";
        cout << "  Quantidade de Cancelas    : " << qtdcancelas << "\n";
        cout << "--------------------------------------------\n";
        cout << "";
        cout << "--------------------------------------------\n";
        cout << "  Quantidade de Vagas Disponiveis : "<< qtdvagasdisponiveis << "\n";
        cout << "  Quantidade de Vagas Ocupadas : " << qtdvagasocupadas << "\n";
        cout << "--------------------------------------------\n";
        cout << "\n";
        cout << "+------------------------------------------+\n";
        cout << "|       Selecione uma opcao                |\n";
        cout << "|  1  - Entrada de Veiculos                |\n";
        cout << "|  2  - Saida de Veiculos                  |\n";
        cout << "|  0  - Sair do Programa                   |\n";
        cout << "+------------------------------------------+\n";

        cin >> opcao;

        if (opcao == "1")
        {
            if (qtdvagasdisponiveis == 0)
            {
                system("cls");
                cout << "+------------------------------------------+\n";
                cout << "|       ESTACIONAMENTO LOTADO              |\n";
                cout << "+------------------------------------------+\n";
                cout << "\n";
            }
            else
            {
                do
                {
                    system("cls");
                    cout << "+------------------------------------------+\n";
                    cout << "|       ENTRADA DE VEICULOS                |\n";
                    cout << "+------------------------------------------+\n";
                    cout << "";
                    cout << "--------------------------------------------\n";
                    cout << "  Quantidade de Cancelas          : " << qtdcancelas << "\n";
                    cout << "  Quantidade de Vagas Disponiveis : " << qtdvagasdisponiveis << "\n";
                    cout << "--------------------------------------------\n";
                    cout << "\n";
                    cout << "Digite o numero de Veiculos Entrando:\n";
                    cin >> qtdveiculos; //Quantidade de Veículos Entrando

                    if (qtdveiculos > qtdcancelas)
                    {
                        cout << "ERRO!!!\n";
                        cout << "O numero de Veiculos Entrando nao pode ser maior que numero de Cancelas.\n";
                        system("pause");
                    }
                    if (qtdveiculos > qtdvagasdisponiveis)
                    {
                        cout << "ERRO!!!\n";
                        cout << "O numero de Veiculos Entrando nao pode ser maior que numero de Vagas Disponiveis.\n";
                        system("pause");
                    }

                } while (qtdveiculos > qtdcancelas || qtdveiculos > qtdvagasdisponiveis);

                numeroveiculo = 1; //Reset do Número do Veículo

                #pragma omp parallel for
                for (i = 0; i < qtdveiculos; i++)
                {
                    qtdvagasdisponiveis--; //Diminuir a quantidade de Vagas Disponíveis
                    qtdvagasocupadas++; //Aumentar a quantidade de Vagas Ocupadas
                    numerovaga++; //Avançar para a próxima Vaga Livre
                    //cout << "O veiculo " << i+1 << " preencheu a vaga numero " << numerovaga << "\n"; //Descrição da Thread que está atuando
                    numveiculos++;
                }
                cout << numveiculos << " veiculos ocuparam as vagas ate o numero de vaga " << numerovaga << "\n";
                numveiculos = 0;
            }
            system("pause");

        }
        if (opcao == "2")
        {
            if (qtdvagasocupadas == 0)
            {
                system("cls");
                cout << "+------------------------------------------+\n";
                cout << "|       ESTACIONAMENTO VAZIO               |\n";
                cout << "+------------------------------------------+\n";
                cout << "\n";
            }
            else
            {
                do
                {
                    system("cls");
                    cout << "+------------------------------------------+\n";
                    cout << "|       SAÍDA DE VEÍCULOS                  |\n";
                    cout << "+------------------------------------------+\n";
                    cout << "\n";
                    cout << "--------------------------------------------\n";
                    cout << "  Quantidade de Cancelas       : " << qtdcancelas << "\n";
                    cout << "  Quantidade de Vagas Ocupadas : " << qtdvagasocupadas << "\n";
                    cout << "--------------------------------------------\n";
                    cout << "\n";
                    cout << "Digite o numero de Veiculos saindo:\n";
                    cin >> qtdveiculos; //Quantidade de Veículos Saindo

                    if (qtdveiculos > qtdcancelas)
                    {
                        cout << "ERRO!!!\n";
                        cout << "O numero de veiculos saindo nao pode ser maior que numero de Cancelas.\n";
                        system("pause");
                    }
                    if (qtdveiculos > qtdvagasocupadas)
                    {
                        cout << "ERRO!!!\n";
                        cout << "O numero de veiculos saindo nao pode ser maior que numero de Vagas Ocupadas.\n";
                        system("pause");
                    }

                } while (qtdveiculos > qtdcancelas || qtdveiculos > qtdvagasocupadas);

                #pragma omp parallel for
                for (i = 0; i < qtdveiculos; i++)
                {
                    //cout << "O veiculo " << i+1 << " liberou a vaga numero " << numerovaga << "\n"; //Descrição da Thread que está atuando
                    qtdvagasdisponiveis++; //Aumentar a quantidade de Vagas Disponíveis
                    qtdvagasocupadas--; //Diminuir a quantidade de Vagas Ocupadas
                    numerovaga--; //Liberar Vaga e retornar para a Vaga Anterior
                    numveiculos++;
                }
                cout << numveiculos << " veiculos liberam as vagas ate o numero de vaga " << numerovaga << "\n";
                numveiculos = 0;
            }
            system("pause");
        }
    } while (opcao != "0"); //Sair
    system("cls");
    cout << "Programa Finalizado\n";
    system("pause");
}
