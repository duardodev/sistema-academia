# 🏋️ Sistema de Gestão de Academia

Sistema completo de gerenciamento de academia desenvolvido em **C++** (cliente) + **TypeScript/Node.js** (API REST) + **PostgreSQL** (banco de dados).

## 📋 Índice

- [Tecnologias](#tecnologias)
- [Pré-requisitos](#pré-requisitos)
- [Instalação](#instalação)
- [Como Executar](#como-executar)
- [Estrutura do Projeto](#estrutura-do-projeto)
- [Documentação (Relatório Final)](#documentação-relatório-final)

---

## 🚀 Tecnologias

### Backend (API)

- **Node.js** + **TypeScript**
- **Express** - Framework web
- **PostgreSQL** - Banco de dados relacional
- **pg** - Driver PostgreSQL para Node.js

### Programa C++ (Cliente)

- **C++17**
- **cURL** - Requisições HTTP
- **nlohmann/json** - Processamento JSON
- **CMake** - Sistema de build

---

## 📦 Pré-requisitos

### Para a API (Backend)

```bash
# Node.js (versão 16 ou superior)
node --version

# PostgreSQL
psql --version
```

### Para o Programa C++

**Linux (Fedora):**

```bash
sudo dnf install gcc-c++ cmake libcurl-devel json-devel
```

**Linux (Ubuntu/Debian):**

```bash
sudo apt install build-essential cmake libcurl4-openssl-dev nlohmann-json3-dev
```

**macOS:**

```bash
brew install cmake curl nlohmann-json
```

**Windows (MSYS2):**

1. **Instalar MSYS2:** Baixe em [msys2.org](https://www.msys2.org/) e instale

2. **Abrir terminal MSYS2 MinGW 64-bit** (importante usar esse!)

3. **Instalar dependências:**

```bash
# Atualizar sistema
pacman -Syu

# Instalar ferramentas de compilação
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-cmake mingw-w64-x86_64-curl mingw-w64-x86_64-nlohmann-json make
```

## 🔧 Instalação

### 1. Clonar o repositório

```bash
git clone https://github.com/seu-usuario/sistema-academia.git
cd sistema-academia
```

### 2. Configurar o Banco de Dados

```bash
# Criar banco de dados
createdb academia_db

# Executar script SQL (criar tabelas)
psql -d academia_db -f database/DDL.sql
```

### 3. Configurar a API

```bash
cd api

# Instalar dependências
npm install

# Criar arquivo .env
cp .env.example .env
```

**Exemplo de `.env` que deve ser preenchido:**

```env
PORT=3000
DB_HOST=localhost
DB_PORT=5432
DB_USER=seu_usuario
DB_PASSWORD=sua_senha
DB_NAME=academia_db
```

### 4. Compilar o Programa C++ C++

**Linux/macOS:**

```bash
# Voltar para a raiz do projeto
cd ..

# Criar pasta de build
mkdir build
cd build

# Configurar com CMake
cmake ..

# Compilar
cmake --build .
```

**Windows (MSYS2 MinGW 64-bit):**

```bash
# No terminal MSYS2 MinGW 64-bit
cd /c/Users/SeuUsuario/caminho/do/projeto

# Criar pasta de build
mkdir build
cd build

# Configurar com CMake
cmake -G "MinGW Makefiles" ..

# Compilar
make
```

---

## ▶️ Como Executar

### 1. Iniciar a API (Terminal 1)

```bash
cd api

# Modo desenvolvimento
npm run dev

# Ou modo produção
npm start
```

A API estará rodando em: **http://localhost:3000**

### 2. Executar o Programa C++

**Linux/macOS (Terminal 2):**

```bash
cd build
./academia_programa
```

**Para Windows - Terminal 2 (MSYS2 MinGW 64-bit):**

```bash
cd build
./academia_programa.exe
```

> **⚠️ Importante no Windows:**
>
> - **Terminal 1 (API Node.js)**: Use PowerShell ou CMD normal
> - **Terminal 2 (Programa C++)**: Use **MSYS2 MinGW 64-bit**

---

---

## 📂 Estrutura do Projeto

```
sistema-academia/
├── api/                          # API REST (Node.js + TypeScript)
│   ├── src/
│   │   ├── routes/              # Rotas da API
│   │   │   ├── alunos.ts
│   │   │   ├── instrutores.ts
│   │   │   ├── equipamentos.ts
│   │   │   ├── planos.ts
│   │   │   └── matriculas.ts
│   │   ├── db.ts                # Configuração do banco
│   │   ├── types/               # Tipagem TypeScript
│   │   └── index.ts             # Arquivo principal
│   ├── package.json
│   └── tsconfig.json
│
├── include/                      # Headers C++
│   ├── structs.h                # Estruturas de dados
│   ├── http_utils.h             # Funções HTTP
│   ├── aluno_crud.h
│   ├── instrutor_crud.h
│   ├── equipamento_crud.h
│   ├── plano_crud.h
│   └── matricula_crud.h
│
├── src/                          # Implementações C++
│   ├── main.cpp                 # Arquivo principal
│   ├── http_utils.cpp           # Implementação HTTP
│   ├── aluno_crud.cpp
│   ├── instrutor_crud.cpp
│   ├── equipamento_crud.cpp
│   ├── plano_crud.cpp
│   └── matricula_crud.cpp
│
├── database/                      # Scripts SQL
│   ├── DDL.sql                   # DDL do banco
│   └── DML.sql                   # DML para popular tabelas
│
├── CMakeLists.txt                # Configuração CMake
├── .gitignore
└── README.md
```

---

## 📖 Documentação (Relatório Final)

📊 **[Relatório Final do Projeto](https://docs.google.com/document/d/SEU_LINK_AQUI)**  
📄 **[Dicionário de Dados](https://docs.google.com/document/d/1Eslm9B1VxE0C76Xv4kONcCp0saPjEmDRnM_ljjWkhJI/edit?usp=sharing)**

## 🐛 Solução de Problemas

### Erro: "Connection refused"

```bash
# Verificar se a API está rodando
curl http://localhost:3000/api/alunos

# Verificar porta
netstat -tulpn | grep 3000
```

### Erro de compilação C++

```bash
# Verificar bibliotecas instaladas
pkg-config --modversion libcurl
ls /usr/include/nlohmann/json.hpp

# Limpar build e recompilar
cd build
rm -rf *
cmake ..
cmake --build .
```

### Erro de conexão com PostgreSQL

```bash
# Verificar se PostgreSQL está rodando
sudo systemctl status postgresql

# Testar conexão
psql -U seu_usuario -d academia_db
```

---

## 👥 Autores

- Deivit Eduardo
- Deivid de Oliveira
- Ruan Souza
- Lucas Souza
- João Marcos

**Disciplinas**: Modelagem de Dados e Estruturas de Dados  
**Instituição**: UNIMAM  
**Curso**: Sistemas para Internet  
**Semestre**: 2025.2  
**Professora**: Maria Eduarda Lima Santos

---

## 📄 Licença

Este projeto foi desenvolvido para fins acadêmicos.

---

## 🔗 Links Úteis

- [Documentação cURL](https://curl.se/libcurl/)
- [nlohmann/json](https://github.com/nlohmann/json)
- [Express.js](https://expressjs.com/)
- [PostgreSQL](https://www.postgresql.org/)
- [CMake](https://cmake.org/)
