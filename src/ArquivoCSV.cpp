#include "../include/ArquivoCSV.h"
#include <iostream>
#include <sstream>
#include <sys/stat.h>
#include <limits>

namespace ArquivoCSV {
    LeituraStatus safe_stoll(const std::string& str, long long& resultado) {
        char* end;
        errno = 0;
        resultado = std::strtoll(str.c_str(), &end, 10);

        if (end == str.c_str()) {
            std::cerr << "Erro: Valor não numérico encontrado: " << str << std::endl;
            return LeituraStatus::ERRO_NUMERO;
        }

        if (errno == ERANGE) {
            std::cerr << "Erro: Valor fora do intervalo: " << str << std::endl;
            return LeituraStatus::ERRO_NUMERO;
        }

        return LeituraStatus::SUCESSO;
    }

    bool arquivoExiste(const char* caminhoArquivo) {
        struct stat buffer;
        return (stat(caminhoArquivo, &buffer) == 0);
    }

    void lerArquivoCSV(std::ifstream& arquivo, Registro** registros, int& contadorRegistros, std::string& cabecalho) {
        std::string linha;
        int contadorLinha = 0;
        const int MAX_LINHAS = 10000;
        const int LINHAS_CABECALHO = 6;

        while (std::getline(arquivo, linha) && contadorRegistros < 10000) {
            contadorLinha++;

            // Ignora as primeiras 6 linhas
            if (contadorLinha <= LINHAS_CABECALHO) {
                cabecalho += linha + "\n";
                continue;
            }

            std::istringstream streamLinha(linha);
            std::string campos[4];
            int index = 0;

            while (std::getline(streamLinha, campos[index], ',') && index < 4) {
                ++index;

                if (index == 4) {
                    long long CPF;
                    LeituraStatus status = safe_stoll(campos[1], CPF);
                    if (status == LeituraStatus::SUCESSO) {
                        if (contadorRegistros >= MAX_LINHAS) {
                            std::cerr << "Limite máximo de registros atingido" << std::endl;
                            break;
                        }
                    registros[contadorRegistros++] = new Registro(campos[0], CPF, campos[2], campos[3]);
                    }
                    index = 0;  // Reinicia o índice para a próxima linha
                }
            }
            if (contadorRegistros == 0) {
            std::cerr << "Nenhum registro válido encontrado no arquivo." << std::endl;
            }
        }
    }
}