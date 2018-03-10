#include "token.h"

namespace COMPILADOR {

Token::Token(ENUMS::tipoToken tipo):
    tipo(tipo),
    valor(0)
{
}

Token::Token(ENUMS::tipoToken tipo, int valor):
    tipo(tipo),
    valor(valor)
{
}

Token::Token(ENUMS::tipoToken tipo, double valor):
    tipo(tipo),
    valor(valor)
{
}


}//FIM DA NAMESPACE COMPILADOR
