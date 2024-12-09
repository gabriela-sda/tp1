#include <iostream>
#include <fstream>
#include "../include/ArquivoCSV.h"
#include "../include/Registro.h"
#include "../include/Ordenacao.h"

const int MAX_REGISTROS = 10000;

// Função para escolher o arquivo de entrada, caso nenhum seja passado
const char* escolherArquivo() {
    // Lista de arquivos
    const char* arquivos[] = {
        "./data/cad.r1000.p1000.xcsv",
        "./data/cad.r1000.p5000.xcsv",
        "./data/cad.r5000.p1000.xcsv",
        "./data/cad.r5000.p5000.xcsv",
        "./data/input.xcsv"
    };

    int indice = 0;  // Índice padrão
    std::cout << "Escolha um arquivo: \n";
    std::cout << "Digite o número do arquivo: ";
    std::cin >> indice;

    if (indice >= 1 && indice <= 5) {
        return arquivos[indice - 1];  // Retorna o arquivo escolhido
    } else {
        std::cout << "Opção inválida. Usando o arquivo padrão.\n";
        return arquivos[0];  // Retorna o arquivo padrão
    }
}

int main(int argc, char* argv[]) {

    // Se um argumento for passado, usa ele. Caso contrário, escolhe um arquivo padrão.
    const char* arquivoEscolhido = (argc > 1) ? argv[1] : escolherArquivo();

    std::cout << "\nLendo arquivo: " << arquivoEscolhido << std::endl;

    Registro* registros[MAX_REGISTROS] = {nullptr}; // array de ponteiros para registros, com tamanho fixo
    int contadorRegistros = 0; // conta a quantidade de registros
    std::string cabecalho; // Para armazenar as 6 primeiras linhas

    if (!ArquivoCSV::arquivoExiste(arquivoEscolhido)) {
        std::cerr << "Arquivo não encontrado: " << arquivoEscolhido << std::endl;
        return 1;  // Termina o programa em caso de erro
    }

    std::ifstream arquivo(arquivoEscolhido);
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo: " << arquivoEscolhido << std::endl;
        return 1;  // Termina o programa em caso de erro
    }

    try {
        ArquivoCSV::lerArquivoCSV(arquivo, registros, contadorRegistros, cabecalho);
    } catch (const std::exception& e) {
        std::cerr << "Erro ao ler arquivo: " << e.what() << std::endl;
        // Libera memória em caso de erro
        for (int i = 0; i < contadorRegistros; i++) {
            delete registros[i];
        }
        return 1;
    }
    arquivo.close();

    if (contadorRegistros == 0) {
        std::cerr << "Nenhum registro encontrado no arquivo." << std::endl;
        return 1;
    }

    Ordenacao ordenacao(registros, contadorRegistros);

    //Ordenacao por nome por quickSort
    ordenacao.quickSort(0, contadorRegistros-1, 1);
    std::cout << cabecalho;
    ordenacao.printRegistros();

    //Ordenacao por nome por heapSort
    ordenacao.heapSort(1);
    std::cout << cabecalho;
    ordenacao.printRegistros();

    //Ordenacao por nome por mergeSort
    ordenacao.mergeSort(0, contadorRegistros-1, 1);
    std::cout << cabecalho;
    ordenacao.printRegistros();

    std::cout << "Número de registros: " << contadorRegistros << std::endl;

    // Libera a memória dos registros
    for (int i = 0; i < contadorRegistros; i++) {
        delete registros[i];
        registros[i] = nullptr;
    }

    return 0;
}
