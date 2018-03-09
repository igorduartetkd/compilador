#ifndef TOKEN_H
#define TOKEN_H

#include "enums.h"

namespace COMPILADOR{

class Token
{
private:
    ENUMS::tipoToken tipo;
    int valor;

public:
    Token(ENUMS::tipoToken tipo);
    Token(ENUMS::tipoToken tipo, int valor);

    //gets
    ENUMS::tipoToken getTipo() const    {return this->tipo;}
    int getValor() const                {return this->valor;}

    //sets
    void setTipo(ENUMS::tipoToken tipo) {this->tipo = tipo;}
    void setValor(int valor)            {this->valor = valor;}
};


}                                                                                              //FIM DA NAMESPACE COMPILADOR
#endif // TOKEN_H
