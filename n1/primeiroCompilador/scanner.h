#ifndef SCANNER_H
#define SCANNER_H

#include <stdio.h>      //scanf
#include <QString>
#include <regex>        //expressao regular regex
#include <queue>
#include "token.h"

namespace COMPILADOR {



class Scanner
{
private:
    //atributos privados:
    Token *token;
    std::queue<char> buffer;

    //metodos privados:
    ENUMS::tipoToken verificarEnumNumero(QString numero);
public:
    Scanner();

    //metodos publicos:
    Token* proximoToken();
    QString lerRestoNumero();
};


}//FIM DA NAMESPACE COMPILADOR
#endif // SCANNER_H
