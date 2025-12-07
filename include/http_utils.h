#ifndef HTTP_UTILS_H
#define HTTP_UTILS_H

#include <string>
#include <curl/curl.h>

// URL base da API
const std::string API_URL = "http://localhost:3000/api";

// Função auxiliar para capturar resposta HTTP
size_t CapturarResposta(void *conteudo, size_t tamanho, size_t quantidade, std::string *resposta);

// Requisições HTTP
std::string requisicaoGET(const std::string &url);
std::string requisicaoPOST(const std::string &url, const std::string &dados);
std::string requisicaoPUT(const std::string &url, const std::string &dados);
std::string requisicaoDELETE(const std::string &url);

#endif