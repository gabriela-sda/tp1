#include <iostream>
#include "../include/Ordenacao.h"

Ordenacao::Ordenacao(Registro** registros, int contadorRegistros) {
        numRegistros = contadorRegistros;
        for(int i = 0; i < numRegistros; i++) {
            listaRegistros[i] = registros[i];
        }
    }

Ordenacao::~Ordenacao() {
    for (int i = 0; i < numRegistros; ++i) {
        listaRegistros[i] = nullptr; // Apenas limpa os ponteiros
    }
}

void Ordenacao::trocar(int i, int j) {
        Registro* temp = listaRegistros[i];
        listaRegistros[i] = listaRegistros[j];
        listaRegistros[j] = temp;
    }

int Ordenacao::particionar(int inicio, int fim, int criterio) {
    Registro* pivo = listaRegistros[fim]; // Escolhe o último elemento como pivô
    int i = inicio - 1;

    for (int j = inicio; j < fim; ++j) {
        bool condicao = false;

        // Verifica o critério de ordenação
        if (criterio == 1) { // Nome
            condicao = listaRegistros[j]->getNome() < pivo->getNome();
        } else if (criterio == 2) { // CPF
            condicao = listaRegistros[j]->getCPF() < pivo->getCPF();
        } else if (criterio == 3) { // Endereço
            condicao = listaRegistros[j]->getEndereco() < pivo->getEndereco();
        }

        if (condicao) {
            ++i;
            trocar(i, j);
        }
    }
    trocar(i + 1, fim);
    return i + 1;
}

bool Ordenacao::comparar(int i, int j, int criterio) {
    switch (criterio) {
        case 1: // Ordenar por Nome
            return listaRegistros[i]->getNome() > listaRegistros[j]->getNome();
        case 2: // Ordenar por CPF
            return listaRegistros[i]->getCPF() > listaRegistros[j]->getCPF();
        case 3: // Ordenar por Endereço
            return listaRegistros[i]->getEndereco() > listaRegistros[j]->getEndereco();
        default:
            return false; // Caso critério inválido
        }
    }

void Ordenacao::reorganizarHeap(int n, int i, int criterio) {
    int maior = i; // Inicializa o maior como raiz
    int esquerda = 2 * i + 1; // Esquerda = 2*i + 1
    int direita = 2 * i + 2; // Direita = 2*i + 2

    // Se o filho da esquerda for maior que a raiz
    if (esquerda < n && comparar(esquerda, maior, criterio)) {
        maior = esquerda;
    }

    // Se o filho da direita for maior que o maior até agora
    if (direita < n && comparar(direita, maior, criterio)) {
        maior = direita;
    }

    // Se o maior não for a raiz
    if (maior != i) {
        trocar(i, maior); // Troca a raiz com o maior
        reorganizarHeap(n, maior, criterio); // Recursivamente reorganiza o sub-árvore afetado
    }
}

void Ordenacao::merge(int inicio, int meio, int fim, int criterio) {
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;

    // Criando arrays temporários
    Registro* esq[n1];
    Registro* dir[n2];

    // Copiando os dados para os arrays temporários
    for (int i = 0; i < n1; i++) {
        esq[i] = listaRegistros[inicio + i];
    }
    for (int j = 0; j < n2; j++) {
        dir[j] = listaRegistros[meio + 1 + j];
    }

    // Mesclando os arrays temporários de volta em listaRegistros[]
    int i = 0, j = 0, k = inicio;
    while (i < n1 && j < n2) {
        bool compara = false;

        // Comparação com base no critério (1 = nome, 2 = CPF, 3 = endereço)
        switch (criterio) {
            case 1: // Ordenar por nome
                compara = esq[i]->getNome() <= dir[j]->getNome();
                break;
            case 2: // Ordenar por CPF
                compara = esq[i]->getCPF() <= dir[j]->getCPF();
                break;
            case 3: // Ordenar por endereço
                compara = esq[i]->getEndereco() <= dir[j]->getEndereco();
                break;
        }

        if (compara) {
            listaRegistros[k] = esq[i];
            i++;
        } else {
            listaRegistros[k] = dir[j];
            j++;
        }
        k++;
    }

    // Copiando os elementos restantes de esq[], se houver
    while (i < n1) {
        listaRegistros[k] = esq[i];
        i++;
        k++;
    }

    // Copiando os elementos restantes de dir[], se houver
    while (j < n2) {
        listaRegistros[k] = dir[j];
        j++;
        k++;
    }
}

void Ordenacao::quickSort(int inicio, int fim, int criterio) {
    if (inicio < fim) {
        int pivo = particionar(inicio, fim, criterio);
        quickSort(inicio, pivo - 1, criterio);
        quickSort(pivo + 1, fim, criterio);
    }
}

void Ordenacao::heapSort(int criterio) {
    // Construa o heap (reorganiza o array)
    for (int i = numRegistros / 2 - 1; i >= 0; i--) {
        reorganizarHeap(numRegistros, i, criterio);
    }

    // Um a um, extraímos os elementos do heap
    for (int i = numRegistros - 1; i >= 1; i--) {
        trocar(0, i); // Troca a raiz (máximo) com o último elemento
        reorganizarHeap(i, 0, criterio); // Reorganiza o heap
    }
}

void Ordenacao::mergeSort(int inicio, int fim, int criterio) {
    if (inicio < fim) {
        int meio = (inicio + fim) / 2;
        mergeSort(inicio, meio, criterio); // Ordena a metade esquerda
        mergeSort(meio + 1, fim, criterio); // Ordena a metade direita
        merge(inicio, meio, fim, criterio); // Combina as duas metades
    }
}

void Ordenacao::printRegistros() const {
    for (int i = 0; i < numRegistros; ++i) {
        listaRegistros[i]->printRegistro();
    }
    std::cout << std::endl;
}
