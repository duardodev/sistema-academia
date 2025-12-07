CREATE TABLE Aluno(
  id_aluno SERIAL PRIMARY KEY,
  cpf VARCHAR(11) NOT NULL UNIQUE,
  nome VARCHAR(100) NOT NULL,
  data_nascimento DATE NOT NULL,
  telefone VARCHAR(50) NOT NULL,
  sexo VARCHAR(20) NOT NULL,	
  CHECK (sexo IN ('Masculino', 'Feminino'))
);

CREATE TABLE Plano(
  id_plano SERIAL PRIMARY KEY,
  tipo VARCHAR(100) NOT NULL,
  valor NUMERIC(10,2) NOT NULL,
  validade INT NOT NULL,	
  descricao TEXT,
  CHECK (tipo IN ('Mensal', 'Trimestral', 'Semestral', 'Anual')),
  CHECK (valor > 0)
);

CREATE TABLE Matricula(
  id_matricula SERIAL PRIMARY KEY,
  id_aluno INT NOT NULL,
  id_plano INT NOT NULL,
  status VARCHAR(50) NOT NULL,
  data_inicio DATE NOT NULL DEFAULT CURRENT_DATE,
  data_termino DATE,
  FOREIGN KEY(id_aluno) REFERENCES Aluno(id_aluno),
  FOREIGN KEY(id_plano) REFERENCES Plano(id_plano),
  CHECK (status IN ('Ativa', 'Inativa', 'Suspensa', 'Cancelada')),
  CHECK (data_termino IS NULL OR data_termino >= data_inicio)
);

CREATE TABLE Pagamento(
  id_pagamento SERIAL PRIMARY KEY,
  id_aluno INT NOT NULL,
  id_plano INT NOT NULL,
  data DATE NOT NULL DEFAULT CURRENT_DATE,
  valor NUMERIC(10,2) NOT NULL,
  FOREIGN KEY(id_aluno) REFERENCES Aluno(id_aluno),
  FOREIGN KEY(id_plano) REFERENCES Plano(id_plano),
  CHECK (valor > 0)
);

CREATE TABLE Equipamento(
  id_equipamento SERIAL PRIMARY KEY,
  nome VARCHAR(100) NOT NULL,
  tipo VARCHAR(100),
  marca VARCHAR(100),
  status VARCHAR(50) NOT NULL,
  CHECK (status IN ('Disponível', 'Manutenção', 'Indisponível'))
);

CREATE TABLE Exercicio(
  id_exercicio SERIAL PRIMARY KEY,
  id_equipamento INT,
  nome VARCHAR(100) NOT NULL,
  descricao VARCHAR(200),
  grupo_muscular VARCHAR(100) NOT NULL,
  FOREIGN KEY(id_equipamento) REFERENCES Equipamento(id_equipamento),
  CHECK (grupo_muscular IN ('Peito', 'Costas', 'Pernas', 'Ombros', 'Braços', 'Abdômen', 'Cardio', 'Corpo inteiro'))
);

CREATE TABLE Treino(
  id_treino SERIAL PRIMARY KEY,
  id_aluno INT NOT NULL,
  duracao TIME NOT NULL,
  descricao VARCHAR(200) NOT NULL,
  frequencia INT NOT NULL,
  FOREIGN KEY(id_aluno) REFERENCES Aluno(id_aluno),
  CHECK (frequencia > 0 AND frequencia <= 7)
);

CREATE TABLE Treino_exercicio(
  id_treino INT NOT NULL,
  id_exercicio INT NOT NULL,
  PRIMARY KEY(id_treino, id_exercicio),
  FOREIGN KEY(id_treino) REFERENCES Treino(id_treino),
  FOREIGN KEY(id_exercicio) REFERENCES Exercicio(id_exercicio)
);

CREATE TABLE Modalidade(
  id_modalidade SERIAL PRIMARY KEY,
  nome VARCHAR(100) NOT NULL,
  descricao VARCHAR(200),
  nivel VARCHAR(50),
  status VARCHAR(50),
  CHECK (nivel IN ('Iniciante', 'Intermediário', 'Avançado')),
  CHECK (status IN ('Ativa', 'Inativa'))
);

CREATE TABLE Desafio_mensal(
  id_desafio_mensal SERIAL PRIMARY KEY,
  id_modalidade INT NOT NULL,
  nome VARCHAR(100) NOT NULL,
  data_inicio DATE,
  data_fim DATE,
  FOREIGN KEY(id_modalidade) REFERENCES Modalidade(id_modalidade),
  CHECK (data_fim >= data_inicio)
);

CREATE TABLE Sala(
  id_sala SERIAL PRIMARY KEY,
  nome VARCHAR(50) NOT NULL,
  numero INT NOT NULL,
  capacidade INT NOT NULL,
  tipo VARCHAR(50),
  CHECK (capacidade > 0),
  CHECK (tipo IN ('Musculação', 'Cardio', 'Funcional', 'Spinning', 'Pilates', 'Yoga', 'Dança'))
);

CREATE TABLE Instrutor(
  id_instrutor SERIAL PRIMARY KEY,
  nome VARCHAR(100) NOT NULL,
  especialidade VARCHAR(100),
  turno VARCHAR(50) NOT NULL,	
  telefone VARCHAR(50) NOT NULL,
  CHECK (turno IN ('Manhã', 'Tarde', 'Noite', 'Integral'))
);

CREATE TABLE Aula_particular(
  id_aula_particular SERIAL PRIMARY KEY,
  id_aluno INT NOT NULL,
  id_instrutor INT NOT NULL,
  modalidade VARCHAR(100) NOT NULL,
  data DATE NOT NULL,
  duracao TIME NOT NULL,
  FOREIGN KEY(id_aluno) REFERENCES Aluno(id_aluno),
  FOREIGN KEY(id_instrutor) REFERENCES Instrutor(id_instrutor)
);

CREATE TABLE Horario_aula(
  id_horario_aula SERIAL PRIMARY KEY,
  id_instrutor INT NOT NULL,
  id_modalidade INT NOT NULL,
  id_sala INT NOT NULL,
  horario_inicio TIME NOT NULL,
  horario_termino TIME NOT NULL,
  dia_semana VARCHAR(20) NOT NULL,
  FOREIGN KEY(id_instrutor) REFERENCES Instrutor(id_instrutor),
  FOREIGN KEY(id_modalidade) REFERENCES Modalidade(id_modalidade),
  FOREIGN KEY(id_sala) REFERENCES Sala(id_sala),
  CHECK (dia_semana IN ('Segunda', 'Terça', 'Quarta', 'Quinta', 'Sexta', 'Sábado', 'Domingo')),
  CHECK (horario_termino > horario_inicio)
);

CREATE TABLE Evento(
  id_evento SERIAL PRIMARY KEY,
  nome VARCHAR(100) NOT NULL,
  data DATE NOT NULL,
  local VARCHAR(100) NOT NULL,
  descricao TEXT,
  horario TIME
);

CREATE TABLE Evento_aluno(
  id_evento INT NOT NULL,
  id_aluno INT NOT NULL,
  PRIMARY KEY(id_evento, id_aluno),
  FOREIGN KEY(id_evento) REFERENCES Evento(id_evento),
  FOREIGN KEY(id_aluno) REFERENCES Aluno(id_aluno)
);

CREATE TABLE Evento_instrutor(
  id_evento INT NOT NULL,
  id_instrutor INT NOT NULL,
  PRIMARY KEY(id_evento, id_instrutor),
  FOREIGN KEY(id_evento) REFERENCES Evento(id_evento),
  FOREIGN KEY(id_instrutor) REFERENCES Instrutor(id_instrutor)
);

CREATE TABLE Feedback(
  id_feedback SERIAL PRIMARY KEY,
  id_aluno INT NOT NULL,
  id_instrutor INT NOT NULL,
  comentario TEXT NOT NULL,
  data_feedback DATE NOT NULL DEFAULT CURRENT_DATE,
  FOREIGN KEY(id_aluno) REFERENCES Aluno(id_aluno),
  FOREIGN KEY(id_instrutor) REFERENCES Instrutor(id_instrutor)
);

CREATE TABLE Nutricionista(
  id_nutricionista SERIAL PRIMARY KEY,
  nome VARCHAR(100) NOT NULL,
  telefone VARCHAR(100) NOT NULL,
  email VARCHAR(100),
  crn VARCHAR(100) NOT NULL
);

CREATE TABLE Plano_alimentar(
  id_plano_alimentar SERIAL PRIMARY KEY,
  id_aluno INT NOT NULL,
  id_nutricionista INT NOT NULL,
  descricao TEXT NOT NULL,
  data_inicio DATE NOT NULL,
  FOREIGN KEY(id_aluno) REFERENCES Aluno(id_aluno),
  FOREIGN KEY(id_nutricionista) REFERENCES Nutricionista(id_nutricionista)
);