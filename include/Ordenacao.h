#ifndef ORDENACAO_H
#define ORDENACAO_H

#include "../include/Registro.h"

class Ordenacao {
    private:
    Registro* listaRegistros[10000]; //array de ponteiros para objetos Registro
    int numRegistros; //quantidade de registros no array

    void trocar(int i, int j);
    int particionar(int inicio, int fim, int criterio);
    bool comparar(int i, int j, int criterio);
    void reorganizarHeap(int n, int i, int criterio);
    void merge(int inicio, int meio, int fim, int criterio);

    public:
    Ordenacao(Registro* registros[10000], int contadorRegistros);
    ~Ordenacao();

    void quickSort(int inicio, int fim, int criterio);
    void heapSort(int criterio);
    void mergeSort(int inicio, int fim, int criterio);


    void printRegistros() const;
};


#endif // ORDENACAO_H