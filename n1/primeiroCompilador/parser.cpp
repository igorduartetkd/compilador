#include "parser.h"

namespace COMPILADOR {



Parser::Parser()
{
}

bool Parser::analisar(){
    if(expressao()){
        if(lerProximoToken().getTipo() == ENUMS::EPSILON)
            return true;

        mensagemErro = "CARACTERES NO FINAL DO PROGRAMA";
    }
    return false;
}

bool Parser::expressao(){
    if(termo())
        if(restoExpressao())
            return true;

    return false;
}

bool Parser::restoExpressao(){//TERMINAL PRODUZ MSG DE ERRO
    COMPILADOR::Token proximoToken = lerProximoToken();
    if(proximoToken.getTipo() == ENUMS::ERRO){
        mensagemErro = "ERRO LEXICO: ESCREVE DIREITO";
        return false;
    }

    if(proximoToken.getTipo() == ENUMS::SOMA){
        if(termo())
            return restoExpressao();
        return false;
     }

    if(proximoToken.getTipo() == ENUMS::SUB){
        if(termo())
            return restoExpressao();
        return false;
    }

    //coringa
    bufferToken.push(proximoToken);
    return true;
}

bool Parser::termo(){
    if(fator())
        return restoTermo();

    return false;
}

bool Parser::restoTermo(){
    COMPILADOR::Token proximoToken = lerProximoToken();
    if(proximoToken.getTipo() == ENUMS::ERRO){
        mensagemErro = "ERRO LEXICO: ESCREVE DIREITO, PORRA";
        return false;
    }

    if(proximoToken.getTipo() == ENUMS::MUL)
        if(fator())
            return restoTermo();

    if(proximoToken.getTipo() == ENUMS::DIV){
        //Análise semantica:
        proximoToken = lerProximoToken();
        if((proximoToken.getTipo() == ENUMS::INT && proximoToken.getValorInt() == 0)  ||  (proximoToken.getTipo() == ENUMS::DOUBLE && proximoToken.getValorDouble() == 0)){
            mensagemErro = "ERRO SEMANTICO: VAI QUERER DIVIDIR POR ZERO MESMO?";
            return false;
        }
        bufferToken.push(proximoToken);
        if(fator())
            return restoTermo();
    }

    //coringa
    bufferToken.push(proximoToken);
    return true;

}

bool Parser::fator(){
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
        return false;
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
