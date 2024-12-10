#include <iostream>
#include <fstream>
#include "../include/ArquivoCSV.h"
#include "../include/memlog.h"
#include "../include/Registro.h"
#include "../include/Ordenacao.h"

const int MAX_REGISTROS = 10000;

void logError(const std::string& mensagem) {
    std::cerr << "ERRO: " << mensagem << std::endl;
}

int main(int argc, char* argv[]) {
    const char* arquivoEscolhido = "./data/cad.r1000.p1000.xcsv";
    if (argc > 1) {
        arquivoEscolhido = argv[1];
    }

    std::cout << "\nLendo arquivo: " << arquivoEscolhido << std::endl;

    Registro* registros[MAX_REGISTROS] = {nullptr}; // array de ponteiros para registros, com tamanho fixo
    int contadorRegistros = 0;
    std::string cabecalho; 

    if (!ArquivoCSV::arquivoExiste(arquivoEscolhido)) {
        logError("Arquivo não encontrado: " + std::string(arquivoEscolhido));
        return 1;
    }

    std::ifstream arquivo(arquivoEscolhido);
    if (!arquivo.is_open()) {
        logError("Não foi possível abrir o arquivo: " + std::string(arquivoEscolhido));
        return 1;
    }

    try {
        ArquivoCSV::lerArquivoCSV(arquivo, registros, contadorRegistros, cabecalho);
    } catch (const std::exception& e) {
        logError("Exceção durante leitura do arquivo: " + std::string(e.what()));
        // Libera memória em caso de erro
        for (int i = 0; i < contadorRegistros; i++) {
            delete registros[i];
        }
        return 1;
    }
    arquivo.close();

    if (contadorRegistros == 0) {
        logError("Nenhum registro válido encontrado.");
        return 1;
    }
    
    //const char* arquivoLog = "./bin/memlog.out";
    //iniciaMemLog(arquivoLog);
    //ativaMemLog();
    //defineFaseMemLog(0);

    Ordenacao ordenacao(registros, contadorRegistros);
    if (!ordenacao.validarRegistros()) {
        logError("Registros contêm dados inválidos.");
        return 1;
    }
    ordenacao.executarQuickSort(1); // 1 = ordenacao por nome, 2 = ordenacao por CPF, 3 = ordenacao por endereco
    //std::cout << cabecalho;
    //ordenacao.printRegistros();

    ordenacao.reiniciarLista();
    ordenacao.executarHeapSort(1); // 1 = ordenacao por nome, 2 = ordenacao por CPF, 3 = ordenacao por endereco
    //std::cout << cabecalho;
    //ordenacao.printRegistros();

    ordenacao.reiniciarLista();
    ordenacao.executarMergeSort(1); // 1 = ordenacao por nome, 2 = ordenacao por CPF, 3 = ordenacao por endereco
    //std::cout << cabecalho;
    //ordenacao.printRegistros();

    //finalizaMemLog();

    // Libera a memória dos registros
    for (int i = 0; i < contadorRegistros; i++) {
        delete registros[i];
        registros[i] = nullptr;
    }

    return 0;
}