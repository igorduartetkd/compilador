#ifndef SCANNER_H
#define SCANNER_H

#include <stdio.h>      //scanf
#include <QString>
#include <regex>        //expressao regular regex
#include "token.h"

namespace COMPILADOR {



class Scanner
{
private:
    Token *token;

public:
    Scanner();

    Token* proximoToken();
};


}//FIM DA NAMESPACE COMPILADOR
#endif // SCANNER_H
