#ifndef MANIPULACAOARQUIVO_H
#define MANIPULACAOARQUIVO_H

#include <string>
#include <iostream>
#include <fstream> //para a manipulação dos arquivos



enum modoAbertura {LEITURA, ESCRITA};

class ManipulacaoArquivo
{
private:
    std::string nomeDoArquivo;
    FILE* arquivo;
public:
    ManipulacaoArquivo(std::string nomeDoArquivo, modoAbertura modo);
    ~ManipulacaoArquivo();

    void escrever(std::string codigoEscrita);
};


#endif // MANIPULACAOARQUIVO_H
