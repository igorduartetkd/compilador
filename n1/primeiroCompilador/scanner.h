#ifndef SCANNER_H
#define SCANNER_H

#include <stdio.h>      //scanf
#include <QString>
#include <QRegExp>        //expressao regular Do QT
#include <queue>
#include "token.h"

namespace COMPILADOR {



class Scanner
{
private:
    //atributos privados:
    std::queue<char> buffer;

    //metodos privados:
    ENUMS::tipoToken verificarEnumNumero(QString numero);
    QString lerRestoNumero();
    char lerProximoChar();
public:
    Scanner();

    //metodos publicos:
    Token proximoToken();

};


}//FIM DA NAMESPACE COMPILADOR
#endif // SCANNER_H
