#include "http_utils.h"

size_t CapturarResposta(void *conteudo, size_t tamanho, size_t quantidade, std::string *resposta)
{
  resposta->append((char *)conteudo, tamanho * quantidade);
  return tamanho * quantidade;
}

std::string requisicaoGET(const std::string &url)
{
  CURL *curl = curl_easy_init();
  std::string resposta;

  if (curl)
  {
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CapturarResposta);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &resposta);
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
  }

  return resposta;
}

std::string requisicaoPOST(const std::string &url, const std::string &dados)
{
  CURL *curl = curl_easy_init();
  std::string resposta;

  if (curl)
  {
    struct curl_slist *headers = curl_slist_append(NULL, "Content-Type: application/json");

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, dados.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CapturarResposta);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &resposta);

    curl_easy_perform(curl);
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
  }

  return resposta;
}

std::string requisicaoPUT(const std::string &url, const std::string &dados)
{
  CURL *curl = curl_easy_init();
  std::string resposta;

  if (curl)
  {
    struct curl_slist *headers = curl_slist_append(NULL, "Content-Type: application/json");

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, dados.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CapturarResposta);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &resposta);

    curl_easy_perform(curl);
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
  }

  return resposta;
}

std::string requisicaoDELETE(const std::string &url)
{
  CURL *curl = curl_easy_init();
  std::string resposta;

  if (curl)
  {
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CapturarResposta);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &resposta);

    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
  }

  return resposta;
}