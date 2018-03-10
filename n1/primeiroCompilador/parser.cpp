#include "parser.h"

namespace COMPILADOR {



Parser::Parser()
{
}

bool Parser::expressao(){
    if(termo())
        return restoExpressao();

    return false;
}

bool Parser::restoExpressao(){//TERMINAL PRODUZ MSG DE ERRO
    COMPILADOR::Token proximoToken = lerProximoToken();
    if(proximoToken.getTipo() == ENUMS::ERRO){
        mensagemErro = "ERRO LEXICO: ESCREVE DIREITO";
        return false;
    }

    if(proximoToken.getTipo() == ENUMS::SOMA)
        return termo();

    if(proximoToken.getTipo() == ENUMS::SUB)
        return termo();


    if(proximoToken.getTipo() == ENUMS::EPSILON)
        return true;

    mensagemErro = "ERRO SINTATICO";
    return false;
}

bool Parser::termo(){
    if(fator())
        return restoTermo();

    return false;
}

bool Parser::restoTermo(){//TERMINAL PRODUZ MSG DE ERRO
    COMPILADOR::Token proximoToken = lerProximoToken();
    if(proximoToken.getTipo() == ENUMS::ERRO){
        mensagemErro = "ERRO LEXICO: ESCREVE DIREITO";
        return false;
    }

    if(proximoToken.getTipo() == ENUMS::MUL)
        return restoTermo();

    if(proximoToken.getTipo() == ENUMS::DIV){
        //Análise semantica:
        proximoToken = lerProximoToken();
        if(proximoToken.getValorDouble() == 0 || proximoToken.getValorInt() == 0){
            mensagemErro = "ERRO SEMANTICO: VAI QUERER DIVIDIR POR ZERO MESMO?";
            return false;
        }
        bufferToken.push(proximoToken);
        return restoTermo();
    }

    if(proximoToken.getTipo() == ENUMS::EPSILON)
        return true;

    mensagemErro = "ERRO SINTATICO: ESPERADO UM OPERADOR";
    return false;

}

bool Parser::fator(){ //TERMINAL, PRODUZ MSG DE ERRO
    COMPILADOR::Token proximoToken = lerProximoToken();
    if(proximoToken.getTipo() == ENUMS::ERRO){
        mensagemErro = "ERRO LEXICO: ESCREVE DIREITO";
        return false;
    }

    if(proximoToken.getTipo() == ENUMS::INT)
        return true;

    if(proximoToken.getTipo() == ENUMS::DOUBLE)
        return true;

    if(proximoToken.getTipo() == ENUMS::ABREPARENTESE){
        if(expressao()){
            if(lerProximoToken().getTipo() == ENUMS::FECHAPARENTESE){
                return true;
            }
            this->mensagemErro = "ERRO SINTATICO: FECHA PARENTESE MAIS NAO? SEU BOSTA";
        }
    }

    this->mensagemErro = "ERRO SINTATICO: ESPERADO UM NUMERO";
    return false;

}


Token Parser::lerProximoToken(){
    if(this->bufferToken.empty())
        return scanner.proximoToken();

    Token token = bufferToken.front();
    bufferToken.pop();

    return token;
}


}//FIM DA NAMESPACE COMPILADOR
