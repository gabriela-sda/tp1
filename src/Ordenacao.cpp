#include <iostream>
#include "../include/Ordenacao.h"
#include "../include/memlog.h"

Ordenacao::Ordenacao(Registro** registros, int contadorRegistros) {
    numRegistros = (contadorRegistros < MAX_REGISTROS) ? contadorRegistros : MAX_REGISTROS;
    for(int i = 0; i < numRegistros; i++) {
        listaRegistros[i] = registros[i];
        listaInicial[i] = registros[i];
    }
    for(int i = numRegistros; i < MAX_REGISTROS; i++) {
        listaRegistros[i] = nullptr;
        listaInicial[i] = nullptr;
    }
}

Ordenacao::~Ordenacao() {}

void Ordenacao::trocar(int i, int j) {
        Registro* temp = listaRegistros[i];
        LEMEMLOG((long int)&listaRegistros[i], sizeof(Registro), 0);

        listaRegistros[i] = listaRegistros[j];
        ESCREVEMEMLOG((long int)&listaRegistros[i], sizeof(Registro), 0);
        LEMEMLOG((long int)&listaRegistros[j], sizeof(Registro), 0);

        listaRegistros[j] = temp;
        ESCREVEMEMLOG((long int)&listaRegistros[j], sizeof(Registro), 0);
    }

int Ordenacao::particionar(int inicio, int fim, int criterio) {
    Registro* pivo = listaRegistros[fim]; // Escolhe o último elemento como pivô
    LEMEMLOG((long int)&listaRegistros[fim], sizeof(Registro), 0);
    int i = inicio - 1;

    for (int j = inicio; j < fim; ++j) {
        bool condicao = false;
        comparacoes++;
        if (criterio == 1) {
            condicao = listaRegistros[j]->getNome() < pivo->getNome();
        } else if (criterio == 2) {
            condicao = listaRegistros[j]->getCPF() < pivo->getCPF();
        } else if (criterio == 3) {
            condicao = listaRegistros[j]->getEndereco() < pivo->getEndereco();
        }
        LEMEMLOG((long int)&listaRegistros[j], sizeof(Registro), 0);
        LEMEMLOG((long int)&listaRegistros[fim], sizeof(Registro), 0);

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
        case 1:
            LEMEMLOG((long int)&listaRegistros[i], sizeof(Registro), 0);
            LEMEMLOG((long int)&listaRegistros[j], sizeof(Registro), 0);
            comparacoes++;
            return listaRegistros[i]->getNome() > listaRegistros[j]->getNome();

        case 2:
            LEMEMLOG((long int)&listaRegistros[i], sizeof(Registro), 0);
            LEMEMLOG((long int)&listaRegistros[j], sizeof(Registro), 0);
            comparacoes++;
            return listaRegistros[i]->getCPF() > listaRegistros[j]->getCPF();

        case 3:
            LEMEMLOG((long int)&listaRegistros[i], sizeof(Registro), 0);
            LEMEMLOG((long int)&listaRegistros[j], sizeof(Registro), 0);
            comparacoes++;
            return listaRegistros[i]->getEndereco() > listaRegistros[j]->getEndereco();

        default:
            return false;
        }
    }

void Ordenacao::reorganizarHeap(int n, int i, int criterio) {
    int maior = i;
    int esquerda = 2 * i + 1;
    int direita = 2 * i + 2;

    if (esquerda < n && comparar(esquerda, maior, criterio)) {
        maior = esquerda;
    }

    if (direita < n && comparar(direita, maior, criterio)) {
        maior = direita;
    }

    if (maior != i) {
        trocar(i, maior);
        reorganizarHeap(n, maior, criterio);
    }
}

void Ordenacao::merge(int inicio, int meio, int fim, int criterio) {
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;

    Registro* esq[n1];
    Registro* dir[n2];

    for (int i = 0; i < n1; i++) {
        copias++;
        esq[i] = listaRegistros[inicio + i];
        ESCREVEMEMLOG((long int)&esq[i], sizeof(Registro), 0);
        LEMEMLOG((long int)&listaRegistros[inicio + i], sizeof(Registro), 0);
    }
    for (int j = 0; j < n2; j++) {
        copias++;
        dir[j] = listaRegistros[meio + 1 + j];
        ESCREVEMEMLOG((long int)&dir[j], sizeof(Registro), 0);
        LEMEMLOG((long int)&listaRegistros[meio + 1 + j], sizeof(Registro), 0);
    }

    int i = 0, j = 0, k = inicio;
    while (i < n1 && j < n2) {
        comparacoes++;
        bool compara = false;
        switch (criterio) {
            case 1: // Ordenar por nome
                compara = esq[i]->getNome() <= dir[j]->getNome();
                LEMEMLOG((long int)&esq[i], sizeof(Registro), 0);
                LEMEMLOG((long int)&dir[j], sizeof(Registro), 0);
                break;

            case 2: // Ordenar por CPF
                compara = esq[i]->getCPF() <= dir[j]->getCPF();
                LEMEMLOG((long int)&esq[i], sizeof(Registro), 0);
                LEMEMLOG((long int)&dir[j], sizeof(Registro), 0);
                break;

            case 3: // Ordenar por endereço
                compara = esq[i]->getEndereco() <= dir[j]->getEndereco();
                LEMEMLOG((long int)&esq[i], sizeof(Registro), 0);
                LEMEMLOG((long int)&dir[j], sizeof(Registro), 0);
                break;
        }

        if (compara) {
            listaRegistros[k] = esq[i];
            ESCREVEMEMLOG((long int)&listaRegistros[k], sizeof(Registro), 0);
            LEMEMLOG((long int)&esq[i], sizeof(Registro), 0);
            i++;
        } else {
            listaRegistros[k] = dir[j];
            ESCREVEMEMLOG((long int)&listaRegistros[k], sizeof(Registro), 0);
            LEMEMLOG((long int)&dir[j], sizeof(Registro), 0);
            j++;
        }
        copias++;
        k++;
    }

    // Copia os elementos restantes de esq[], se houver
    while (i < n1) {
        listaRegistros[k] = esq[i];
        copias++;
        ESCREVEMEMLOG((long int)&listaRegistros[k], sizeof(Registro), 0);
        LEMEMLOG((long int)&esq[i], sizeof(Registro), 0);
        i++;
        k++;
    }

    // Copia os elementos restantes de dir[], se houver
    while (j < n2) {
        listaRegistros[k] = dir[j];
        copias++;
        ESCREVEMEMLOG((long int)&listaRegistros[k], sizeof(Registro), 0);
        LEMEMLOG((long int)&dir[j], sizeof(Registro), 0);
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

void Ordenacao::executarQuickSort(int criterio) {
    comparacoes = 0; // Zera as contagens
    copias = 0;

    auto inicioTempo = std::chrono::high_resolution_clock::now();
    quickSort(0, numRegistros - 1, criterio);
    auto fimTempo = std::chrono::high_resolution_clock::now();

    printRelatorio("QuickSort", fimTempo - inicioTempo);
}

void Ordenacao::heapSort(int criterio) {
    for (int i = numRegistros / 2 - 1; i >= 0; i--) {
        reorganizarHeap(numRegistros, i, criterio);
    }

    for (int i = numRegistros - 1; i >= 1; i--) {
        trocar(0, i);
        reorganizarHeap(i, 0, criterio);
    }
}

void Ordenacao::executarHeapSort(int criterio) {
    comparacoes = 0;
    copias = 0;

    auto inicioTempo = std::chrono::high_resolution_clock::now();
    heapSort(criterio);
    auto fimTempo = std::chrono::high_resolution_clock::now();

    printRelatorio("HeapSort", fimTempo - inicioTempo);
}

void Ordenacao::mergeSort(int inicio, int fim, int criterio) {
    if (inicio < fim) {
        int meio = (inicio + fim) / 2;
        mergeSort(inicio, meio, criterio); // Ordena a metade esquerda
        mergeSort(meio + 1, fim, criterio); // Ordena a metade direita
        merge(inicio, meio, fim, criterio); // Combina as duas metades
    }
}

void Ordenacao::executarMergeSort(int criterio) {
    comparacoes = 0; 
    copias = 0;

    auto inicioTempo = std::chrono::high_resolution_clock::now();
    mergeSort(0, numRegistros - 1, criterio);
    auto fimTempo = std::chrono::high_resolution_clock::now();

    printRelatorio("MergeSort", fimTempo - inicioTempo);
}

void Ordenacao::printRegistros() const {
    for (int i = 0; i < numRegistros; ++i) {
        if (listaRegistros[i] != nullptr) {
            listaRegistros[i]->printRegistro();
            }
    }
    std::cout << std::endl;
}

void Ordenacao::printRelatorio(const std::string& algoritmo, std::chrono::duration<double> duracao) const {
    std::cout << "### " << algoritmo << " ###" << std::endl;
    std::cout << "Comparações: " << comparacoes << std::endl;
    std::cout << "Cópias: " << copias << std::endl;
    std::cout << "Tempo de execução: " << duracao.count() << " segundos\n" << std::endl;
}


bool Ordenacao::validarRegistros() const {
    for (int i = 0; i < numRegistros; ++i) {
        if (listaRegistros[i] == nullptr) {
            std::cerr << "Registro nulo encontrado no índice " << i << std::endl;
            return false;
        }

        if (listaRegistros[i]->getNome().empty() || 
            listaRegistros[i]->getCPF() <= 0 || 
            listaRegistros[i]->getEndereco().empty()) {
            std::cerr << "Registro inválido no índice " << i << std::endl;
            return false;
        }
    }
    return true;
}

void Ordenacao::reiniciarLista() {
    for(int i = 0; i < numRegistros; i++) {
        listaRegistros[i] = listaInicial[i];
    }
}