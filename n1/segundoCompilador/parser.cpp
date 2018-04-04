#include "parser.h"

namespace COMPILADOR {



Parser::Parser():
    arquivoEscrita(0)
{

      arquivoEscrita = new ManipulacaoArquivo("produzido.asm", ESCRITA);
      arquivoEscrita->escrever(geradorCodigo.gerarCabecalho());


      //escrevendo as macros
      arquivoEscrita->escrever(geradorCodigo.gerarComentario("Início da definição das macros"));
      arquivoEscrita->escrever(geradorCodigo.gerarMacro(ENUMS::INT));
//      arquivoEscrita->escrever(geradorCodigo.gerarMacro(ENUMS::SOMA));
//      arquivoEscrita->escrever(geradorCodigo.gerarMacro(ENUMS::SUB));
//      arquivoEscrita->escrever(geradorCodigo.gerarMacro(ENUMS::MUL));
//      arquivoEscrita->escrever(geradorCodigo.gerarMacro(ENUMS::DIV));

      //inicio das instruções:
      arquivoEscrita->escrever(geradorCodigo.gerarInicioCodigo());


}

Parser::~Parser(){
    arquivoEscrita->escrever(geradorCodigo.gerarFinalArquivo());
    delete arquivoEscrita;
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
    if(termo()){
        return restoExpressao();
    }

    return false;
}

bool Parser::restoExpressao(){//TERMINAL PRODUZ MSG DE ERRO
    COMPILADOR::Token proximoToken = lerProximoToken();
    if(proximoToken.getTipo() == ENUMS::ERRO){
        mensagemErro += "ERRO LEXICO: ESCREVE DIREITO\n";
        return false;
    }

    if(proximoToken.getTipo() == ENUMS::SOMA){
        if(termo()){
            double op1, op2;
            //interpretador
            op2 = numeroArmazenado.top();
            numeroArmazenado.pop();
            op1 = numeroArmazenado.top();
            numeroArmazenado.pop();
            numeroArmazenado.push(op1+op2);

            //compilador
            arquivoEscrita->escrever(geradorCodigo.gerarOperacao(ENUMS::SOMA));

            return restoExpressao();
        }
        mensagemErro += "ERRO SINTATICO: EXPRESSAO NAO ENCONTRADA APOS SINAL DE ADIÇÃO\n";
        return false;
     }

    if(proximoToken.getTipo() == ENUMS::SUB){
        if(termo()){
            //interpretador
            double op1, op2;
            op2 = numeroArmazenado.top();
            numeroArmazenado.pop();
            op1 = numeroArmazenado.top();
            numeroArmazenado.pop();
            numeroArmazenado.push(op1-op2);

            //compilador
           arquivoEscrita->escrever(geradorCodigo.gerarOperacao(ENUMS::SUB));

           return restoExpressao();
        }
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
        if(fator()){
            //interpretador
            double op1, op2;
            op2 = numeroArmazenado.top();
            numeroArmazenado.pop();
            op1 = numeroArmazenado.top();
            numeroArmazenado.pop();
            numeroArmazenado.push(op1*op2);

            //compilador
            arquivoEscrita->escrever(geradorCodigo.gerarOperacao(ENUMS::MUL));
            return restoTermo();
        }
        mensagemErro += "ERRO SINTATICO: NAO ENCONTRADO OPERADOR APOS MULTIPLICAÇÃO\n";
        return false;
    }

    if(proximoToken.getTipo() == ENUMS::DIV){
        //Análise semantica:
        proximoToken = lerProximoToken();
        if((proximoToken.getTipo() == ENUMS::INT && proximoToken.getValor().inteiro == 0)  ||  (proximoToken.getTipo() == ENUMS::DOUBLE && proximoToken.getValor().real == 0)){
            mensagemErro += "ERRO SEMANTICO: VAI QUERER DIVIDIR POR ZERO MESMO?\n";
            return false;
        }
        bufferToken.push(proximoToken);
        if(fator()){
            //interpretador
            double op1, op2;
            op2 = numeroArmazenado.top();
            numeroArmazenado.pop();
            op1 = numeroArmazenado.top();
            numeroArmazenado.pop();
            numeroArmazenado.push(op1/op2);

            //compilador
            arquivoEscrita->escrever(geradorCodigo.gerarOperacao(ENUMS::DIV));
            return restoTermo();
        }

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

    if(proximoToken.getTipo() == ENUMS::INT){
        ENUMS::numeroTipo numero;
        numero.inteiro= proximoToken.getValor().inteiro;
        //tradutor
        numeroArmazenado.push(numero.inteiro);

        //compilador
        arquivoEscrita->escrever(geradorCodigo.gerarEmpilhaNumero(ENUMS::INT, numero));
        return true;
    }

    if(proximoToken.getTipo() == ENUMS::DOUBLE){
        ENUMS::numeroTipo numero;
        numero.real = proximoToken.getValor().real;
        //tradutor
        numeroArmazenado.push(numero.real);

        //compilador
        arquivoEscrita->escrever(geradorCodigo.gerarEmpilhaNumero(ENUMS::DOUBLE, numero));
        return true;
    }

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
