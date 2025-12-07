#include "structs.h"
#include "matricula_crud.h"
#include "http_utils.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;

void listarMatriculas()
{
  cout << "\n========== LISTA DE MATRÍCULAS ==========\n";

  string url = API_URL + "/matriculas";
  string resposta = requisicaoGET(url);

  try
  {
    vector<Matricula> matriculas;
    json dados = json::parse(resposta);

    for (auto &item : dados)
    {
      Matricula matricula;
      matricula.id_matricula = item["id_matricula"];
      matricula.id_aluno = item["id_aluno"];
      matricula.id_plano = item["id_plano"];
      matricula.status = item["status"];
      matricula.data_inicio = item["data_inicio"];
      matricula.data_termino = item.contains("data_termino") && !item["data_termino"].is_null() ? item["data_termino"] : "Indefinida";
      matricula.nome_aluno = item["nome_aluno"];
      matricula.tipo_plano = item["tipo_plano"];
      matricula.valor_plano = item["valor_plano"].is_number() ? item["valor_plano"].get<double>() : stod(item["valor_plano"].get<string>());
      matriculas.push_back(matricula);
    }

    if (matriculas.empty())
    {
      cout << "Nenhuma matrícula cadastrada.\n";
      return;
    }

    for (const auto &m : matriculas)
    {
      cout << "\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━";
      cout << "\nID Matrícula: " << m.id_matricula;
      cout << "\nAluno: " << m.nome_aluno << " (ID: " << m.id_aluno << ")";
      cout << "\nPlano: " << m.tipo_plano;
      cout << fixed << setprecision(2);
      cout << " - R$ " << m.valor_plano;
      cout << "\nStatus: " << m.status;
      cout << "\nInício: " << m.data_inicio;
      cout << "\nTérmino: " << m.data_termino;
      cout << "\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
    }
  }
  catch (json::exception &e)
  {
    cout << "Erro ao processar dados: " << e.what() << "\n";
  }
}

void cadastrarMatricula()
{
  cout << "\n========== CADASTRAR MATRÍCULA ==========\n";

  int id_aluno, id_plano;
  string status, data_inicio, data_termino;

  cout << "ID do Aluno: ";
  cin >> id_aluno;

  cout << "ID do Plano: ";
  cin >> id_plano;

  cin.ignore();

  do
  {
    cout << "Status (Ativa/Inativa/Suspensa/Cancelada): ";
    getline(cin, status);
    if (status != "Ativa" && status != "Inativa" && status != "Suspensa" && status != "Cancelada")
    {
      cout << "Erro: Digite Ativa, Inativa, Suspensa ou Cancelada!\n";
    }
  } while (status != "Ativa" && status != "Inativa" && status != "Suspensa" && status != "Cancelada");

  cout << "Data Início (YYYY-MM-DD) [Enter para hoje]: ";
  getline(cin, data_inicio);

  cout << "Data Término (YYYY-MM-DD) [Enter para indefinida]: ";
  getline(cin, data_termino);

  json dados;
  dados["id_aluno"] = id_aluno;
  dados["id_plano"] = id_plano;
  dados["status"] = status;

  if (!data_inicio.empty())
  {
    dados["dataInicio"] = data_inicio;
  }
  if (!data_termino.empty())
  {
    dados["dataTermino"] = data_termino;
  }

  string url = API_URL + "/matriculas";
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
      cout << "\nMatrícula cadastrada com sucesso!\n";
    }
  }
  catch (...)
  {
    cout << "\nErro ao processar resposta do servidor!\n";
  }
}

void atualizarMatricula()
{
  cout << "\n========== ATUALIZAR MATRÍCULA ==========\n";
  cout << "Dica: Deixe em branco para não alterar o campo\n\n";

  int id;
  string id_plano_str, status, data_inicio, data_termino;

  cout << "ID da Matrícula: ";
  cin >> id;

  cin.ignore();

  cout << "Novo ID do Plano (Enter para manter): ";
  getline(cin, id_plano_str);

  cout << "Novo Status [Ativa/Inativa/Suspensa/Cancelada] (Enter para manter): ";
  getline(cin, status);

  if (!status.empty() && status != "Ativa" && status != "Inativa" &&
      status != "Suspensa" && status != "Cancelada")
  {
    cout << "Erro: Status inválido! Cancelando atualização.\n";
    return;
  }

  cout << "Nova Data Início [YYYY-MM-DD] (Enter para manter): ";
  getline(cin, data_inicio);

  cout << "Nova Data Término [YYYY-MM-DD] (Enter para manter): ";
  getline(cin, data_termino);

  json dados;

  if (!id_plano_str.empty())
  {
    try
    {
      dados["id_plano"] = stoi(id_plano_str);
    }
    catch (...)
    {
      cout << "Erro: ID do plano inválido!\n";
      return;
    }
  }
  if (!status.empty())
    dados["status"] = status;
  if (!data_inicio.empty())
    dados["dataInicio"] = data_inicio;
  if (!data_termino.empty())
    dados["dataTermino"] = data_termino;

  if (dados.empty())
  {
    cout << "\nNenhum campo foi alterado!\n";
    return;
  }

  string url = API_URL + "/matriculas/" + to_string(id);
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
      cout << "\nMatrícula atualizada com sucesso!\n";
    }
  }
  catch (...)
  {
    cout << "\nErro ao processar resposta do servidor!\n";
  }
}

void deletarMatricula()
{
  cout << "\n========== DELETAR MATRÍCULA ==========\n";

  int id;
  cout << "ID da Matrícula: ";
  cin >> id;

  char confirmacao;
  cout << "Tem certeza que deseja deletar esta matrícula? (s/N): ";
  cin >> confirmacao;

  if (confirmacao != 's' && confirmacao != 'S')
  {
    cout << "Operação cancelada.\n";
    return;
  }

  string url = API_URL + "/matriculas/" + to_string(id);
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
      cout << "\nMatrícula deletada com sucesso!\n";
    }
  }
  catch (...)
  {
    cout << "\nErro ao processar resposta do servidor!\n";
  }
}

void menuMatriculas()
{
  int opcao;

  do
  {
    cout << "\n╔════════════════════════════════════╗\n";
    cout << "║     GERENCIAR MATRÍCULAS           ║\n";
    cout << "╠════════════════════════════════════╣\n";
    cout << "║  1. Listar Matrículas              ║\n";
    cout << "║  2. Cadastrar Matrícula            ║\n";
    cout << "║  3. Atualizar Matrícula            ║\n";
    cout << "║  4. Deletar Matrícula              ║\n";
    cout << "║  0. Voltar                         ║\n";
    cout << "╚════════════════════════════════════╝\n";
    cout << "Opção: ";
    cin >> opcao;

    switch (opcao)
    {
    case 1:
      listarMatriculas();
      break;
    case 2:
      cadastrarMatricula();
      break;
    case 3:
      atualizarMatricula();
      break;
    case 4:
      deletarMatricula();
      break;
    case 0:
      cout << "Voltando...\n";
      break;
    default:
      cout << "Opção inválida!\n";
    }
  } while (opcao != 0);
}