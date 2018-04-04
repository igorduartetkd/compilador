#ifndef TOKEN_H
#define TOKEN_H

#include "enums.h"
#include <stdio.h>

namespace COMPILADOR{


class Token
{
private:
    ENUMS::tipoToken tipo;
    ENUMS::numeroTipo valor;

public:
    Token(ENUMS::tipoToken tipo);
    Token(ENUMS::tipoToken tipo, ENUMS::numeroTipo valor);

    //gets
    ENUMS::tipoToken getTipo() const            {return this->tipo;}
    ENUMS::numeroTipo getValor() const                 {return this->valor;}

    //sets
    void setTipo(ENUMS::tipoToken tipo)         {this->tipo = tipo;}
    void setValorInt(ENUMS::numeroTipo valor)          {this->valor = valor;}
};


}                                                                                              //FIM DA NAMESPACE COMPILADOR
#endif // TOKEN_H
