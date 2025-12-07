#include "structs.h"
#include "plano_crud.h"
#include "http_utils.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;

void listarPlanos()
{
  cout << "\n========== LISTA DE PLANOS ==========\n";

  string url = API_URL + "/planos";
  string resposta = requisicaoGET(url);

  try
  {
    vector<Plano> planos;
    json dados = json::parse(resposta);

    for (auto &item : dados)
    {
      Plano plano;
      plano.id_plano = item["id_plano"];
      plano.tipo = item["tipo"];
      plano.valor = item["valor"].is_string() ? stod(item["valor"].get<string>()) : item["valor"].get<double>();
      plano.validade = item["validade"];
      plano.descricao = item.contains("descricao") && !item["descricao"].is_null() ? item["descricao"].get<string>() : "Sem descrição";
      planos.push_back(plano);
    }

    if (planos.empty())
    {
      cout << "Nenhum plano cadastrado.\n";
      return;
    }

    for (const auto &plano : planos)
    {
      cout << "\nID: " << plano.id_plano;
      cout << "\nTipo: " << plano.tipo;
      cout << fixed << setprecision(2);
      cout << "\nValor: R$ " << plano.valor;
      cout << "\nValidade: " << plano.validade << " meses";
      cout << "\nDescrição: " << plano.descricao;
      cout << "\n-------------------------------------\n";
    }
  }
  catch (json::exception &e)
  {
    cout << "Erro ao processar dados: " << e.what() << "\n";
  }
}

void cadastrarPlano()
{
  cout << "\n========== CADASTRAR PLANO ==========\n";

  string tipo, descricao;
  double valor;
  int validade;

  cin.ignore();

  // Validação do Tipo
  do
  {
    cout << "Tipo (Mensal/Trimestral/Semestral/Anual): ";
    getline(cin, tipo);
    if (tipo != "Mensal" && tipo != "Trimestral" && tipo != "Semestral" && tipo != "Anual")
    {
      cout << "Erro: Digite Mensal, Trimestral, Semestral ou Anual!\n";
    }
  } while (tipo != "Mensal" && tipo != "Trimestral" && tipo != "Semestral" && tipo != "Anual");

  // Validação do Valor
  do
  {
    cout << "Valor (R$): ";
    cin >> valor;
    if (valor <= 0)
    {
      cout << "Erro: Valor deve ser maior que zero!\n";
    }
  } while (valor <= 0);

  // Validação da Validade
  do
  {
    cout << "Validade (em meses): ";
    cin >> validade;
    if (validade <= 0)
    {
      cout << "Erro: Validade deve ser maior que zero!\n";
    }
  } while (validade <= 0);

  cin.ignore();
  cout << "Descrição (opcional): ";
  getline(cin, descricao);

  json dados;
  dados["tipo"] = tipo;
  dados["valor"] = valor;
  dados["validade"] = validade;
  if (!descricao.empty())
  {
    dados["descricao"] = descricao;
  }

  string url = API_URL + "/planos";
  string resposta = requisicaoPOST(url, dados.dump());

  try
  {
    json resultado = json::parse(resposta);
    if (resultado.contains("error"))
    {
      cout << "\nErro ao cadastrar: " << resultado["error"] << "\n";
    }
    else
    {
      cout << "\nPlano cadastrado com sucesso!\n";
    }
  }
  catch (...)
  {
    cout << "\nErro ao processar resposta do servidor!\n";
  }
}

void atualizarPlano()
{
  cout << "\n========== ATUALIZAR PLANO ==========\n";
  cout << "Dica: Deixe em branco para não alterar o campo\n\n";

  int id;
  string tipo, descricao, valorStr, validadeStr;

  cout << "ID do Plano: ";
  cin >> id;

  cin.ignore();

  cout << "Novo Tipo [Mensal/Trimestral/Semestral/Anual] (Enter para manter): ";
  getline(cin, tipo);

  if (!tipo.empty() && tipo != "Mensal" && tipo != "Trimestral" && tipo != "Semestral" && tipo != "Anual")
  {
    cout << "Erro: Tipo inválido! Cancelando atualização.\n";
    return;
  }

  cout << "Novo Valor [R$] (Enter para manter): ";
  getline(cin, valorStr);

  cout << "Nova Validade [meses] (Enter para manter): ";
  getline(cin, validadeStr);

  cout << "Nova Descrição (Enter para manter): ";
  getline(cin, descricao);

  json dados;

  if (!tipo.empty())
    dados["tipo"] = tipo;

  if (!valorStr.empty())
  {
    try
    {
      dados["valor"] = stod(valorStr);
    }
    catch (...)
    {
      cout << "Erro: Valor inválido!\n";
      return;
    }
  }

  if (!validadeStr.empty())
  {
    try
    {
      dados["validade"] = stoi(validadeStr);
    }
    catch (...)
    {
      cout << "Erro: Validade inválida!\n";
      return;
    }
  }

  if (!descricao.empty())
    dados["descricao"] = descricao;

  if (dados.empty())
  {
    cout << "\nNenhum campo foi alterado!\n";
    return;
  }

  string url = API_URL + "/planos/" + to_string(id);
  string resposta = requisicaoPUT(url, dados.dump());

  try
  {
    json resultado = json::parse(resposta);
    if (resultado.contains("error"))
    {
      cout << "\nErro: " << resultado["error"] << "\n";
    }
    else
    {
      cout << "\nPlano atualizado com sucesso!\n";
    }
  }
  catch (...)
  {
    cout << "\nErro ao processar resposta do servidor!\n";
  }
}

void deletarPlano()
{
  cout << "\n========== DELETAR PLANO ==========\n";

  int id;
  cout << "ID do Plano: ";
  cin >> id;

  string url = API_URL + "/planos/" + to_string(id);
  string resposta = requisicaoDELETE(url);

  try
  {
    json resultado = json::parse(resposta);
    if (resultado.contains("error"))
    {
      cout << "\nErro: " << resultado["error"] << "\n";
    }
    else
    {
      cout << "\nPlano deletado com sucesso!\n";
    }
  }
  catch (...)
  {
    cout << "\nErro ao processar resposta do servidor!\n";
  }
}

void menuPlanos()
{
  int opcao;

  do
  {
    cout << "\n╔════════════════════════════════════╗\n";
    cout << "║     GERENCIAR PLANOS               ║\n";
    cout << "╠════════════════════════════════════╣\n";
    cout << "║  1. Listar Planos                  ║\n";
    cout << "║  2. Cadastrar Plano                ║\n";
    cout << "║  3. Atualizar Plano                ║\n";
    cout << "║  4. Deletar Plano                  ║\n";
    cout << "║  0. Voltar                         ║\n";
    cout << "╚════════════════════════════════════╝\n";
    cout << "Opção: ";
    cin >> opcao;

    switch (opcao)
    {
    case 1:
      listarPlanos();
      break;
    case 2:
      cadastrarPlano();
      break;
    case 3:
      atualizarPlano();
      break;
    case 4:
      deletarPlano();
      break;
    case 0:
      cout << "Voltando...\n";
      break;
    default:
      cout << "Opção inválida!\n";
    }
  } while (opcao != 0);
}