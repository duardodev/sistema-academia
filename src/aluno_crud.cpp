#include "structs.h"
#include "aluno_crud.h"
#include "http_utils.h"
#include <iostream>
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;

void listarAlunos()
{
  cout << "\n========== LISTA DE ALUNOS ==========\n";

  string url = API_URL + "/alunos";
  string resposta = requisicaoGET(url);

  try
  {
    vector<Aluno> alunos;
    json dados = json::parse(resposta);

    for (auto &item : dados)
    {
      Aluno aluno;
      aluno.id_aluno = item["id_aluno"];
      aluno.cpf = item["cpf"];
      aluno.nome = item["nome"];
      aluno.data_nascimento = item["data_nascimento"];
      aluno.sexo = item["sexo"];
      aluno.telefone = item["telefone"];
      alunos.push_back(aluno);
    }

    if (alunos.empty())
    {
      cout << "Nenhum aluno cadastrado.\n";
      return;
    }

    for (const auto &aluno : alunos)
    {
      cout << "\nID: " << aluno.id_aluno;
      cout << "\nNome: " << aluno.nome;
      cout << "\nCPF: " << aluno.cpf;
      cout << "\nSexo: " << aluno.sexo;
      cout << "\nTelefone: " << aluno.telefone;
      cout << "\n-------------------------------------\n";
    }
  }
  catch (json::exception &e)
  {
    cout << "Erro ao processar dados: " << e.what() << "\n";
  }
}

void cadastrarAluno()
{
  cout << "\n========== CADASTRAR ALUNO ==========\n";

  string cpf, nome, data_nasc, sexo, telefone;

  cin.ignore();
  cout << "Nome: ";
  getline(cin, nome);

  do
  {
    cout << "CPF (11 dígitos): ";
    getline(cin, cpf);
    if (cpf.length() != 11)
    {
      cout << "Erro: CPF deve ter exatamente 11 dígitos!\n";
    }
  } while (cpf.length() != 11);

  cout << "Data Nascimento (YYYY-MM-DD): ";
  getline(cin, data_nasc);

  do
  {
    cout << "Sexo (Masculino/Feminino): ";
    getline(cin, sexo);
    if (sexo != "Masculino" && sexo != "Feminino")
    {
      cout << "Erro: Digite apenas Masculino ou Feminino!\n";
    }
  } while (sexo != "Masculino" && sexo != "Feminino");

  cout << "Telefone: ";
  getline(cin, telefone);

  json dados;
  dados["nome"] = nome;
  dados["cpf"] = cpf;
  dados["data_nascimento"] = data_nasc;
  dados["sexo"] = sexo;
  dados["telefone"] = telefone;

  string url = API_URL + "/alunos";
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
      cout << "\nAluno cadastrado com sucesso!\n";
    }
  }
  catch (...)
  {
    cout << "\nErro ao processar resposta do servidor!\n";
  }
}

void atualizarAluno()
{
  cout << "\n========== ATUALIZAR ALUNO ==========" << endl;
  cout << "Dica: Deixe em branco para não alterar o campo\n\n";

  int id;
  string nome, data_nasc, sexo, telefone;

  cout << "ID do Aluno: ";
  cin >> id;

  cin.ignore();
  cout << "Novo Nome (Enter para manter): ";
  getline(cin, nome);
  cout << "Nova Data Nascimento (YYYY-MM-DD) (Enter para manter): ";
  getline(cin, data_nasc);

  cout << "Novo Sexo (Masculino/Feminino) (Enter para manter): ";
  getline(cin, sexo);
  if (!sexo.empty() && sexo != "Masculino" && sexo != "Feminino")
  {
    cout << "Erro: Digite apenas Masculino ou Feminino!\n";
    return;
  }

  cout << "Novo Telefone (Enter para manter): ";
  getline(cin, telefone);

  json dados;
  if (!nome.empty())
    dados["nome"] = nome;
  if (!data_nasc.empty())
    dados["data_nascimento"] = data_nasc;
  if (!sexo.empty())
    dados["sexo"] = sexo;
  if (!telefone.empty())
    dados["telefone"] = telefone;

  if (dados.empty())
  {
    cout << "\nNenhum campo foi alterado!\n";
    return;
  }

  string url = API_URL + "/alunos/" + to_string(id);
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
      cout << "\nAluno atualizado com sucesso!\n";
    }
  }
  catch (json::exception &e)
  {
    cout << "\nErro ao processar resposta do servidor!\n";
  }
}

void deletarAluno()
{
  cout << "\n========== DELETAR ALUNO ==========\n";

  int id;
  cout << "ID do Aluno: ";
  cin >> id;

  string url = API_URL + "/alunos/" + to_string(id);
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
      cout << "\nAluno deletado com sucesso!\n";
    }
  }
  catch (...)
  {
    cout << "\nErro ao processar resposta do servidor!\n";
  }
}

void menuAlunos()
{
  int opcao;

  do
  {
    cout << "\n╔════════════════════════════════════╗\n";
    cout << "║     GERENCIAR ALUNOS               ║\n";
    cout << "╠════════════════════════════════════╣\n";
    cout << "║  1. Listar Alunos                  ║\n";
    cout << "║  2. Cadastrar Aluno                ║\n";
    cout << "║  3. Atualizar Aluno                ║\n";
    cout << "║  4. Deletar Aluno                  ║\n";
    cout << "║  0. Voltar                         ║\n";
    cout << "╚════════════════════════════════════╝\n";
    cout << "Opção: ";
    cin >> opcao;

    switch (opcao)
    {
    case 1:
      listarAlunos();
      break;
    case 2:
      cadastrarAluno();
      break;
    case 3:
      atualizarAluno();
      break;
    case 4:
      deletarAluno();
      break;
    case 0:
      cout << "Voltando...\n";
      break;
    default:
      cout << "Opção inválida!\n";
    }
  } while (opcao != 0);
}