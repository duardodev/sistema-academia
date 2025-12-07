#include <iostream>
#include <curl/curl.h>
#include "aluno_crud.h"
#include "instrutor_crud.h"
#include "equipamento_crud.h"
#include "plano_crud.h"
#include "matricula_crud.h"

using namespace std;

void menuPrincipal()
{
  int opcao;

  do
  {
    cout << "\n╔════════════════════════════════════╗\n";
    cout << "║   SISTEMA DE ACADEMIA              ║\n";
    cout << "╠════════════════════════════════════╣\n";
    cout << "║  1. Gerenciar Alunos               ║\n";
    cout << "║  2. Gerenciar Planos               ║\n";
    cout << "║  3. Gerenciar Matrículas           ║\n";
    cout << "║  4. Gerenciar Equipamentos         ║\n";
    cout << "║  5. Gerenciar Instrutores          ║\n";
    cout << "║  0. Sair                           ║\n";
    cout << "╚════════════════════════════════════╝\n";
    cout << "Opção: ";
    cin >> opcao;

    switch (opcao)
    {
    case 1:
      menuAlunos();
      break;
    case 2:
      menuPlanos();
      break;
    case 3:
      menuMatriculas();
      break;
    case 4:
      menuEquipamentos();
      break;
    case 5:
      menuInstrutores();
      break;
    case 0:
      cout << "\nEncerrando...\n";
      break;
    default:
      cout << "Opção inválida!\n";
    }
  } while (opcao != 0);
}

int main()
{
  curl_global_init(CURL_GLOBAL_DEFAULT);

  cout << "\n╔════════════════════════════════════════╗\n";
  cout << "║  SISTEMA DE GESTÃO - ACADEMIA          ║\n";
  cout << "║  Cliente C++ + API REST                ║\n";
  cout << "╚════════════════════════════════════════╝\n";

  menuPrincipal();

  curl_global_cleanup();
  return 0;
}