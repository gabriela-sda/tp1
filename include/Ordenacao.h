#ifndef ORDENACAO_H
#define ORDENACAO_H

#include <chrono>
#include "../include/Registro.h"

class Ordenacao {
    private:
    static const int MAX_REGISTROS = 10000;
    Registro* listaRegistros[MAX_REGISTROS]; //array de ponteiros para objetos Registro
    Registro* listaInicial[MAX_REGISTROS];
    int numRegistros; //quantidade de registros no array

    long long comparacoes;
    long long copias;

    void trocar(int i, int j);
    int particionar(int inicio, int fim, int criterio);
    bool comparar(int i, int j, int criterio);
    void reorganizarHeap(int n, int i, int criterio);
    void merge(int inicio, int meio, int fim, int criterio);

    public:
    Ordenacao(Registro** registros, int contadorRegistros);
    ~Ordenacao();

    void quickSort(int inicio, int fim, int criterio);
    void executarQuickSort(int criterio);
    void heapSort(int criterio);
    void executarHeapSort(int criterio);
    void mergeSort(int inicio, int fim, int criterio);
    void executarMergeSort(int criterio);

    void printRegistros() const;
    void printRelatorio(const std::string& algoritmo, std::chrono::duration<double> duracao) const;
    bool validarRegistros() const;
    void reiniciarLista();
};

#endif // ORDENACAO_H