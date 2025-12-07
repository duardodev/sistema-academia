#include "structs.h"
#include "instrutor_crud.h"
#include "http_utils.h"
#include <iostream>
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;

void listarInstrutores()
{
  cout << "\n========== LISTA DE INSTRUTORES ==========\n";

  string url = API_URL + "/instrutores";
  string resposta = requisicaoGET(url);

  try
  {
    vector<Instrutor> instrutores;
    json dados = json::parse(resposta);

    for (auto &item : dados)
    {
      Instrutor instrutor;
      instrutor.id_instrutor = item["id_instrutor"];
      instrutor.nome = item["nome"];
      instrutor.especialidade = item.contains("especialidade") && !item["especialidade"].is_null() ? item["especialidade"].get<string>() : "Não informado";
      instrutor.turno = item["turno"];
      instrutor.telefone = item["telefone"];
      instrutores.push_back(instrutor);
    }

    if (instrutores.empty())
    {
      cout << "Nenhum instrutor cadastrado.\n";
      return;
    }

    for (const auto &instrutor : instrutores)
    {
      cout << "\nID: " << instrutor.id_instrutor;
      cout << "\nNome: " << instrutor.nome;
      cout << "\nEspecialidade: " << instrutor.especialidade;
      cout << "\nTurno: " << instrutor.turno;
      cout << "\nTelefone: " << instrutor.telefone;
      cout << "\n-------------------------------------\n";
    }
  }
  catch (json::exception &e)
  {
    cout << "Erro ao processar dados: " << e.what() << "\n";
  }
}

void cadastrarInstrutor()
{
  cout << "\n========== CADASTRAR INSTRUTOR ==========\n";

  string nome, especialidade, turno, telefone;

  cin.ignore();
  cout << "Nome: ";
  getline(cin, nome);

  cout << "Especialidade (opcional): ";
  getline(cin, especialidade);

  do
  {
    cout << "Turno (Manhã/Tarde/Noite/Integral): ";
    getline(cin, turno);
    if (turno != "Manhã" && turno != "Tarde" && turno != "Noite" && turno != "Integral")
    {
      cout << "Erro: Digite Manhã, Tarde, Noite ou Integral!\n";
    }
  } while (turno != "Manhã" && turno != "Tarde" && turno != "Noite" && turno != "Integral");

  cout << "Telefone: ";
  getline(cin, telefone);

  json dados;
  dados["nome"] = nome;
  dados["telefone"] = telefone;
  dados["turno"] = turno;
  if (!especialidade.empty())
  {
    dados["especialidade"] = especialidade;
  }

  string url = API_URL + "/instrutores";
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
      cout << "\nInstrutor cadastrado com sucesso!\n";
    }
  }
  catch (...)
  {
    cout << "\nErro ao processar resposta do servidor!\n";
  }
}

void atualizarInstrutor()
{
  cout << "\n========== ATUALIZAR INSTRUTOR ==========" << endl;
  cout << "Dica: Deixe em branco para não alterar o campo\n\n";

  int id;
  string nome, especialidade, turno, telefone;

  cout << "ID do Instrutor: ";
  cin >> id;

  cin.ignore();
  cout << "Novo Nome (Enter para manter): ";
  getline(cin, nome);
  cout << "Nova Especialidade (Enter para manter): ";
  getline(cin, especialidade);
  cout << "Novo Turno (Manhã/Tarde/Noite/Integral) (Enter para manter): ";
  getline(cin, turno);
  if (!turno.empty() && turno != "Manhã" && turno != "Tarde" && turno != "Noite" && turno != "Integral")
  {
    cout << "Erro: Digite Manhã, Tarde, Noite ou Integral!\n";
    return;
  }
  cout << "Novo Telefone (Enter para manter): ";
  getline(cin, telefone);

  json dados;
  if (!nome.empty())
    dados["nome"] = nome;
  if (!especialidade.empty())
    dados["especialidade"] = especialidade;
  if (!turno.empty())
    dados["turno"] = turno;
  if (!telefone.empty())
    dados["telefone"] = telefone;

  if (dados.empty())
  {
    cout << "\nNenhum campo foi alterado!\n";
    return;
  }

  string url = API_URL + "/instrutores/" + to_string(id);
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
      cout << "\nInstrutor atualizado com sucesso!\n";
    }
  }
  catch (...)
  {
    cout << "\nErro ao processar resposta do servidor!\n";
  }
}

void deletarInstrutor()
{
  cout << "\n========== DELETAR INSTRUTOR ==========\n";

  int id;
  cout << "ID do Instrutor: ";
  cin >> id;

  string url = API_URL + "/instrutores/" + to_string(id);
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
      cout << "\nInstrutor deletado com sucesso!\n";
    }
  }
  catch (...)
  {
    cout << "\nErro ao processar resposta do servidor!\n";
  }
}

void menuInstrutores()
{
  int opcao;

  do
  {
    cout << "\n╔════════════════════════════════════╗\n";
    cout << "║     GERENCIAR INSTRUTORES          ║\n";
    cout << "╠════════════════════════════════════╣\n";
    cout << "║  1. Listar Instrutores             ║\n";
    cout << "║  2. Cadastrar Instrutor            ║\n";
    cout << "║  3. Atualizar Instrutor            ║\n";
    cout << "║  4. Deletar Instrutor              ║\n";
    cout << "║  0. Voltar                         ║\n";
    cout << "╚════════════════════════════════════╝\n";
    cout << "Opção: ";
    cin >> opcao;

    switch (opcao)
    {
    case 1:
      listarInstrutores();
      break;
    case 2:
      cadastrarInstrutor();
      break;
    case 3:
      atualizarInstrutor();
      break;
    case 4:
      deletarInstrutor();
      break;
    case 0:
      cout << "Voltando...\n";
      break;
    default:
      cout << "Opção inválida!\n";
    }
  } while (opcao != 0);
}