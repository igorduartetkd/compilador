#ifndef TOKEN_H
#define TOKEN_H

#include "enums.h"

namespace COMPILADOR{

class Token
{
private:
    ENUMS::tipoToken tipo;
    int valorInt;
    double valorDouble;

public:
    Token(ENUMS::tipoToken tipo);
    Token(ENUMS::tipoToken tipo, int valor);
    Token(ENUMS::tipoToken tipo, double valor);

    //gets
    ENUMS::tipoToken getTipo() const    {return this->tipo;}
    int getValorInt() const                {return this->valorInt;}
    int getValorDouble() const             {return this->valorDouble;}

    //sets
    void setTipo(ENUMS::tipoToken tipo) {this->tipo = tipo;}
    void setValorInt(int valor)            {this->valorInt = valor;}
    void setValorDouble(int valor)            {this->valorDouble = valor;}
};


}                                                                                              //FIM DA NAMESPACE COMPILADOR
#endif // TOKEN_H
