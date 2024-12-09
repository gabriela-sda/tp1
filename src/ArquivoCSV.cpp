#include "../include/ArquivoCSV.h"
#include <iostream>
#include <sstream>
#include <sys/stat.h>

namespace ArquivoCSV {

    long long safe_stoll(const std::string& str) {
        try {
            return std::stoll(str);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Erro: valor não numérico encontrado: " << str << std::endl;
            return -1;
        } catch (const std::out_of_range& e) {
            std::cerr << "Erro: valor fora do intervalo: " << str << std::endl;
            return -1;
        }
    }

    bool arquivoExiste(const char* caminhoArquivo) {
        struct stat buffer;
        return (stat(caminhoArquivo, &buffer) == 0);
    }

    void lerArquivoCSV(std::ifstream& arquivo, Registro** registros, int& contadorRegistros, std::string& cabecalho) {
        std::string linha;
        int contadorLinha = 0;

        while (std::getline(arquivo, linha) && contadorRegistros < 10000) {
            contadorLinha++;

            // Ignora as primeiras 6 linhas
            if (contadorLinha < 7) {
                cabecalho += linha + "\n";
                continue;
            }

            std::istringstream streamLinha(linha);
            std::string campos[4];
            int index = 0;

            while (std::getline(streamLinha, campos[index], ',') && index < 4) {
                ++index;

                if (index == 4) {
                    long long CPF = safe_stoll(campos[1]);
                    if (CPF != -1) {
                        registros[contadorRegistros++] = new Registro(campos[0], CPF, campos[2], campos[3]);
                    }
                    index = 0;  // Reinicia o índice para a próxima linha
                }
            }
        }
    }
}
