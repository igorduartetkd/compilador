#include "scanner.h"

namespace COMPILADOR {


Scanner::Scanner():
    token(0)
{
}

Token* Scanner::proximoToken(){
    char caracter;
    bool fimTokenFlag = false;
    QString caracterToString;
    QString valorToken;
    std::regex eRNumero("[[:digit:]]");     //expressao regular para representar um digito
    std::scanf("%c", &caracter);
    while(caracter != '\0' && !fimTokenFlag){
        caracterToString = caracter;
        if(std::regex_match(caracterToString.toStdString(), eRNumero)){         //caracter e um digito?
            valorToken = caracterToString.toInt();
        }else
        if(caracter == '-'){
            //VERIFICAR SE PROXIMO E NUMERO COLADO
            token = new Token(ENUMS::SUB);
            fimTokenFlag = true;
        }else
        if(caracter == '+'){
            token = new Token(ENUMS::SOMA);
            fimTokenFlag = true;
        }else
        if(caracter == '*'){
            token = new Token(ENUMS::MUL);
            fimTokenFlag = true;
        }else
        if(caracter == '/'){
            token = new Token(ENUMS::DIV);
            fimTokenFlag = true;
        }else{  //DEFAULT

        }


        std::scanf("%c", &caracter);
    }

    return this->token;
    this->token = 0;
}

}//FIM DA NAMESPACE COMPILADOR
