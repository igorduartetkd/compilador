#include "parser.h"

namespace COMPILADOR {



Parser::Parser()
{
}

bool Parser::analisar(){
    if(expressao()){
        if(lerProximoToken().getTipo() == ENUMS::EPSILON)
            return true;

        mensagemErro += "CARACTERES NO FINAL DO PROGRAMA\n";
    }
    return false;
}

bool Parser::expressao(){
    if(termo())
        return restoExpressao();

    return false;
}

bool Parser::restoExpressao(){//TERMINAL PRODUZ MSG DE ERRO
    COMPILADOR::Token proximoToken = lerProximoToken();
    if(proximoToken.getTipo() == ENUMS::ERRO){
        mensagemErro += "ERRO LEXICO: ESCREVE DIREITO\n";
        return false;
    }

    if(proximoToken.getTipo() == ENUMS::SOMA){
        if(termo())
            return restoExpressao();
        mensagemErro += "ERRO SINTATICO: EXPRESSAO NAO ENCONTRADA APOS SINAL DE ADIÇÃO\n";
        return false;
     }

    if(proximoToken.getTipo() == ENUMS::SUB){
        if(termo())
            return restoExpressao();
        mensagemErro += "ERRO SINTATICO: EXPRESSAO NAO ENCONTRADA APOS SINAL DE SUBTRAÇÃO\n";
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
        mensagemErro += "ERRO LEXICO: ESCREVE DIREITO, PORRA\n";
        return false;
    }

    if(proximoToken.getTipo() == ENUMS::MUL){
        if(fator())
            return restoTermo();
        mensagemErro += "ERRO SINTATICO: NAO ENCONTRADO OPERADOR APOS MULTIPLICAÇÃO\n";
        return false;
    }

    if(proximoToken.getTipo() == ENUMS::DIV){
        //Análise semantica:
        proximoToken = lerProximoToken();
        if((proximoToken.getTipo() == ENUMS::INT && proximoToken.getValorInt() == 0)  ||  (proximoToken.getTipo() == ENUMS::DOUBLE && proximoToken.getValorDouble() == 0)){
            mensagemErro += "ERRO SEMANTICO: VAI QUERER DIVIDIR POR ZERO MESMO?\n";
            return false;
        }
        bufferToken.push(proximoToken);
        if(fator())
            return restoTermo();

        mensagemErro += "ERRO SINTATICO: NAO ENCONTRADO OPERADOR APOS DIVISAO\n";
        return false;
    }

    //coringa
    bufferToken.push(proximoToken);
    return true;

}

bool Parser::fator(){
    COMPILADOR::Token proximoToken = lerProximoToken();
    if(proximoToken.getTipo() == ENUMS::ERRO){
        mensagemErro += "ERRO LEXICO: ESCREVE DIREITO\n";
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
            this->mensagemErro += "ERRO SINTATICO: FECHA PARENTESE MAIS NAO? SEU BOSTA\n";
            return false;
        }
        this->mensagemErro += "NAO ENCONTRADA EXPRESSAO APOS ABRIR PARENTESE\n";
        return false;
    }

    this->mensagemErro += "ERRO SINTATICO: ESPERADO UM NUMERO\n";
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
