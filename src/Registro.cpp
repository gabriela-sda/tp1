#include <iostream>
#include "../include/Registro.h"

Registro::Registro(const std::string& x, long long y, const std::string& z, const std::string& w) {
    nome = x;
    CPF = y;
    endereco = z;
    outros = w;
    }

Registro::~Registro() {};

std::string Registro::getNome() const { 
    return nome; 
    }

long long Registro::getCPF() const {
     return CPF; 
    }

std::string Registro::getEndereco() const { 
    return endereco; 
    }

void Registro::printRegistro() const {
    std::cout
    << nome << ","
    << CPF << ","
    << endereco << ","
    << outros << std::endl;
    }
