#include "manipulacaoarquivo.h"



ManipulacaoArquivo::ManipulacaoArquivo(std::string nomeDoArquivo, modoAbertura modo):
    nomeDoArquivo(nomeDoArquivo),
    arquivo(0)
{
    //definindo modo de abertura do arquivo: ESCRITA OU LEITURA
    std::string abertura;
    switch (modo) {
    case ESCRITA:
        abertura = "wt";
        break;
    case LEITURA:
        abertura = "rt";
        break;
    default:
        std::cout<<"Modo de leitura não identificado"<<std::endl;
        exit(1);
        break;
    }
    //Abrindo o arquivo
    arquivo = std::fopen(nomeDoArquivo.c_str(), abertura.c_str());
    if(arquivo == NULL){
        std::cout<<"problema ao abrir do arquivo"<<std::endl;
        exit(1);
    }
}

ManipulacaoArquivo::~ManipulacaoArquivo(){
    std::fclose(arquivo);
}

void ManipulacaoArquivo::escrever(std::string codigoEscrita){
    std::fputs(codigoEscrita.c_str(), arquivo);
}



