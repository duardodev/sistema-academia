#ifndef STRUCTS_H
#define STRUCTS_H

#include <string>

struct Aluno
{
  int id_aluno;
  std::string cpf;
  std::string nome;
  std::string data_nascimento;
  std::string sexo;
  std::string telefone;
};

struct Plano
{
  int id_plano;
  std::string tipo;
  double valor;
  int validade;
  std::string descricao;
};

struct Matricula
{
  int id_matricula;
  int id_aluno;
  int id_plano;
  std::string status;
  std::string data_inicio;
  std::string data_termino;
  // Campos extras do JOIN
  std::string nome_aluno;
  std::string tipo_plano;
  double valor_plano;
};

struct Instrutor
{
  int id_instrutor;
  std::string nome;
  std::string especialidade;
  std::string turno;
  std::string telefone;
};

struct Equipamento
{
  int id_equipamento;
  std::string nome;
  std::string tipo;
  std::string marca;
  std::string status;
};

#endif