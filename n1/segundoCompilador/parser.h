#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <queue>
#include <stack>
#include <fstream>
#include "scanner.h"

#include<iostream>

namespace COMPILADOR {



class Parser
{
private:
    FILE* arquivoEscrita;
    COMPILADOR::Scanner scanner;
    std::string mensagemErro;
    std::queue<COMPILADOR::Token> bufferToken;
    std::stack <double> numeroArmazenado;

    //metodos privados:
    COMPILADOR::Token lerProximoToken();
public:
    Parser();
    ~Parser();

    std::string getMensagemErro() const { return this->mensagemErro;}
    double  getResultadoExpressao() const { return this->numeroArmazenado.top();}

    bool analisar();
    bool expressao();
    bool restoExpressao();
    bool termo();
    bool restoTermo();
    bool fator();
    bool parenteses();
};


}//FIM DA NAMESPACE COMPILADOR
#endif // PARSER_H
