#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <queue>
#include "scanner.h"

namespace COMPILADOR {



class Parser
{
private:
    COMPILADOR::Scanner scanner;
    std::string mensagemErro;
    std::queue<COMPILADOR::Token> bufferToken;

    //metodos privados:
    COMPILADOR::Token lerProximoToken();
public:
    Parser();

    std::string getMensagemErro() const { return this->mensagemErro;}

    bool expressao();
    bool restoExpressao();
    bool termo();
    bool restoTermo();
    bool fator();
};


}//FIM DA NAMESPACE COMPILADOR
#endif // PARSER_H
