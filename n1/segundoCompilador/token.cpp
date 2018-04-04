#include "token.h"

namespace COMPILADOR {

Token::Token(ENUMS::tipoToken tipo):
    tipo(tipo)
{
}

Token::Token(ENUMS::tipoToken tipo, ENUMS::numeroTipo valor):
    tipo(tipo),
    valor(valor)
{
}



}//FIM DA NAMESPACE COMPILADOR
