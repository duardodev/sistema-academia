cmake_minimum_required(VERSION 3.10)
project(SistemaAcademia)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Encontrar as bibliotecas necessárias
find_package(CURL REQUIRED)

# Adicionar todos os arquivos fonte
add_executable(academia_programa 
    src/main.cpp
    src/http_utils.cpp
    src/aluno_crud.cpp
    src/instrutor_crud.cpp
    src/equipamento_crud.cpp
    src/plano_crud.cpp
    src/matricula_crud.cpp
)

# Linkar com cURL
target_link_libraries(academia_programa CURL::libcurl)

# Incluir diretórios de headers
target_include_directories(academia_programa PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${CURL_INCLUDE_DIR}
)
