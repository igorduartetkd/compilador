#include "token.h"

namespace COMPILADOR {

Token::Token(ENUMS::tipoToken tipo):
    tipo(tipo),
    valorInt(0),
    valorDouble(0)
{
}

Token::Token(ENUMS::tipoToken tipo, int valor):
    tipo(tipo),
    valorInt(valor),
    valorDouble(0)
{
}

Token::Token(ENUMS::tipoToken tipo, double valor):
    tipo(tipo),
    valorInt(0),
    valorDouble(valor)
{
}


}//FIM DA NAMESPACE COMPILADOR
