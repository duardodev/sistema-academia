#include "structs.h"
#include "http_utils.h"
#include "equipamento_crud.h"
#include <iostream>
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;

void listarEquipamentos()
{
  cout << "\n========== LISTA DE EQUIPAMENTOS ==========" << endl;

  string url = API_URL + "/equipamentos";
  string resposta = requisicaoGET(url);

  try
  {
    vector<Equipamento> equipamentos;
    json dados = json::parse(resposta);

    for (auto &item : dados)
    {
      Equipamento equipamento;
      equipamento.id_equipamento = item["id_equipamento"];
      equipamento.nome = item["nome"];
      equipamento.tipo = item.contains("tipo") && !item["tipo"].is_null() ? item["tipo"].get<string>() : "Não informado";
      equipamento.marca = item.contains("marca") && !item["marca"].is_null() ? item["marca"].get<string>() : "Não informada";
      equipamento.status = item["status"];
      equipamentos.push_back(equipamento);
    }

    if (equipamentos.empty())
    {
      cout << "Nenhum equipamento cadastrado.\n";
      return;
    }

    for (const auto &eq : equipamentos)
    {
      cout << "\nID: " << eq.id_equipamento;
      cout << "\nNome: " << eq.nome;
      cout << "\nTipo: " << eq.tipo;
      cout << "\nMarca: " << eq.marca;
      cout << "\nStatus: " << eq.status;
      cout << "\n-------------------------------------\n";
    }
  }
  catch (json::exception &e)
  {
    cout << "Erro ao processar dados: " << e.what() << "\n";
  }
}

void cadastrarEquipamento()
{
  cout << "\n========== CADASTRAR EQUIPAMENTO ==========\n";

  string nome, tipo, marca, status;

  cin.ignore();
  cout << "Nome: ";
  getline(cin, nome);

  cout << "Tipo (opcional): ";
  getline(cin, tipo);

  cout << "Marca (opcional): ";
  getline(cin, marca);

  // Validação do Status
  do
  {
    cout << "Status (Disponível/Manutenção/Indisponível): ";
    getline(cin, status);
    if (status != "Disponível" && status != "Manutenção" && status != "Indisponível")
    {
      cout << "Erro: Digite Disponível, Manutenção ou Indisponível!\n";
    }
  } while (status != "Disponível" && status != "Manutenção" && status != "Indisponível");

  json dados;
  dados["nome"] = nome;
  dados["status"] = status;
  if (!tipo.empty())
    dados["tipo"] = tipo;
  if (!marca.empty())
    dados["marca"] = marca;

  string url = API_URL + "/equipamentos";
  string resposta = requisicaoPOST(url, dados.dump());

  try
  {
    json resultado = json::parse(resposta);
    if (resultado.contains("erro"))
    {
      cout << "\nErro ao cadastrar: " << resultado["erro"] << "\n";
    }
    else
    {
      cout << "\nEquipamento cadastrado com sucesso!\n";
    }
  }
  catch (...)
  {
    cout << "\nErro ao processar resposta do servidor!\n";
  }
}

void atualizarEquipamento()
{
  cout << "\n========== ATUALIZAR EQUIPAMENTO ==========" << endl;
  cout << "Dica: Deixe em branco para não alterar o campo\n\n";

  int id;
  string nome, tipo, marca, status;

  cout << "ID do Equipamento: ";
  cin >> id;

  cin.ignore();
  cout << "Novo Nome (Enter para manter): ";
  getline(cin, nome);
  cout << "Novo Tipo (Enter para manter): ";
  getline(cin, tipo);
  cout << "Nova Marca (Enter para manter): ";
  getline(cin, marca);
  cout << "Novo Status (Disponível/Manutenção/Indisponível) (Enter para manter): ";
  getline(cin, status);
  if (!status.empty() && status != "Disponível" && status != "Manutenção" && status != "Indisponível")
  {
    cout << "Erro: Digite Disponível, Manutenção ou Indisponível!\n";
    return;
  }

  json dados;
  if (!nome.empty())
    dados["nome"] = nome;
  if (!tipo.empty())
    dados["tipo"] = tipo;
  if (!marca.empty())
    dados["marca"] = marca;
  if (!status.empty())
    dados["status"] = status;

  if (dados.empty())
  {
    cout << "\nNenhum campo foi alterado!\n";
    return;
  }

  string url = API_URL + "/equipamentos/" + to_string(id);
  string resposta = requisicaoPUT(url, dados.dump());

  try
  {
    json resultado = json::parse(resposta);
    if (resultado.contains("erro"))
    {
      cout << "\nErro: " << resultado["erro"] << "\n";
    }
    else
    {
      cout << "\nEquipamento atualizado com sucesso!\n";
    }
  }
  catch (...)
  {
    cout << "\nErro ao processar resposta do servidor!\n";
  }
}

void deletarEquipamento()
{
  cout << "\n========== DELETAR EQUIPAMENTO ==========\n";

  int id;
  cout << "ID do Equipamento: ";
  cin >> id;

  string url = API_URL + "/equipamentos/" + to_string(id);
  string resposta = requisicaoDELETE(url);

  try
  {
    json resultado = json::parse(resposta);
    if (resultado.contains("erro"))
    {
      cout << "\nErro: " << resultado["erro"] << "\n";
    }
    else
    {
      cout << "\nEquipamento deletado com sucesso!\n";
    }
  }
  catch (...)
  {
    cout << "\nErro ao processar resposta do servidor!\n";
  }
}

void menuEquipamentos()
{
  int opcao;

  do
  {
    cout << "\n╔════════════════════════════════════╗\n";
    cout << "║     GERENCIAR EQUIPAMENTOS         ║\n";
    cout << "╠════════════════════════════════════╣\n";
    cout << "║  1. Listar Equipamentos            ║\n";
    cout << "║  2. Cadastrar Equipamento          ║\n";
    cout << "║  3. Atualizar Equipamento          ║\n";
    cout << "║  4. Deletar Equipamento            ║\n";
    cout << "║  0. Voltar                         ║\n";
    cout << "╚════════════════════════════════════╝\n";
    cout << "Opção: ";
    cin >> opcao;

    switch (opcao)
    {
    case 1:
      listarEquipamentos();
      break;
    case 2:
      cadastrarEquipamento();
      break;
    case 3:
      atualizarEquipamento();
      break;
    case 4:
      deletarEquipamento();
      break;
    case 0:
      cout << "Voltando...\n";
      break;
    default:
      cout << "Opção inválida!\n";
    }
  } while (opcao != 0);
}