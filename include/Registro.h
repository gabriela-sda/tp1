#ifndef REGISTRO_H
#define REGISTRO_H

#include <string>

class Registro {
    private:
    std::string nome;
    long long CPF;
    std::string endereco;
    std::string outros;

    public:
    Registro(const std::string& x, long long y, const std::string& z, const std::string& w);
    ~Registro();
    std::string getNome() const;
    long long getCPF() const;
    std::string getEndereco() const;
    void printRegistro() const;
};

#endif // REGISTRO_H