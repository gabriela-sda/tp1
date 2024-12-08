#ifndef ARQUIVOCSV_H
#define ARQUIVOCSV_H

#include <string>    
#include <fstream>   
#include "../include/Registro.h"

namespace ArquivoCSV {
    // Função para converter string para long long com verificação de erro
    long long safe_stoll(const std::string& str);

    // Função para verificar se o arquivo existe
    bool arquivoExiste(const char* caminhoArquivo);

    // Função para ler CSV e preencher os registros; recebe um ponteiro para a primeira posição de um array de ponteiros de objetos Registro
    void lerArquivoCSV(std::ifstream& arquivo, Registro** registros, int& contadorRegistros, std::string& cabecalho);
}

#endif // ARQUIVOCSV_H