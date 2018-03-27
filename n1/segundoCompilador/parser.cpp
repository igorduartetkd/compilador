#include "parser.h"

namespace COMPILADOR {



Parser::Parser():
    arquivoEscrita(0)
{
    arquivoEscrita = std::fopen("arquivoGerado.asm", "wt");
    if(arquivoEscrita == NULL){
        std::cout<<"problema na criação do arquivo"<<std::endl;
        exit(1);
    }

    std::fprintf(arquivoEscrita, "\tglobal main\n");
    std::fprintf(arquivoEscrita, "\textern printf, scanf\n");
    std::fprintf(arquivoEscrita, "\n\tsection .data\t\t\t;contem as constantes\n");

    //adicionando macro para somar
    std::fprintf(arquivoEscrita, "\n\t%%macro somar\t\t\t;macro para somar\n");
    std::fprintf(arquivoEscrita, "\t\tpop rcx\t\t\t;desempilha o segundo operador\n");
    std::fprintf(arquivoEscrita, "\t\tpop rbx\t\t\t;desempilha o primeiro operador\n");
    std::fprintf(arquivoEscrita, "\t\tadd rbx, rcx\t\t;soma rbx a rcx e guarda em rbx\n");
    std::fprintf(arquivoEscrita, "\t\tpush rbx\t\t;empilha o resultado\n");
    std::fprintf(arquivoEscrita, "\t\%%endmacro \t\t\t;sai da macro\n");

    //adicionando macro para subtrair
    std::fprintf(arquivoEscrita, "\n\t\%%macro subtrair\t\t\t;macro para subtrair\n");
    std::fprintf(arquivoEscrita, "\t\tpop rcx\t\t\t;desempilha o segundo operador\n");
    std::fprintf(arquivoEscrita, "\t\tpop rbx\t\t\t;desempilha o primeiro operador\n");
    std::fprintf(arquivoEscrita, "\t\tsub rbx, rcx\t\t;subtrai rbx = rbx - rcx\n");
    std::fprintf(arquivoEscrita, "\t\tpush rbx\t\t;empilha o resultado\n");
    std::fprintf(arquivoEscrita, "\t\%%endmacro \t\t\t;sai da macro\n");

    //adicionando macro para multiplicar
    std::fprintf(arquivoEscrita, "\n\t\%%macro multiplicar\t\t;macro para multiplicar\n");
    std::fprintf(arquivoEscrita, "\t\tpop rdx\t\t\t;desempilha o segundo operador\n");
    std::fprintf(arquivoEscrita, "\t\tpop rax\t\t\t;desempilha o primeiro operador\n");
    std::fprintf(arquivoEscrita, "\t\tmul rdx\t\t\t;multiplica rax = rax * rdx\n");
    std::fprintf(arquivoEscrita, "\t\tpush rbx\t\t;empilha o resultado\n");
    std::fprintf(arquivoEscrita, "\t\%%endmacro \t\t\t;sai da macro\n");


    //adicionando macro para dividir
    std::fprintf(arquivoEscrita, "\n\t\%%macro dividir\t\t\t;macro para dividir\n");
    std::fprintf(arquivoEscrita, "\t\tpop rdx\t\t\t;desempilha o segundo operador\n");
    std::fprintf(arquivoEscrita, "\t\tpop rax\t\t\t;desempilha o primeiro operador\n");
    std::fprintf(arquivoEscrita, "\t\tdiv rdx\t\t\t;divide rax = rax / rdx\n");
    std::fprintf(arquivoEscrita, "\t\tpush rbx\t\t;empilha o resultado\n");
    std::fprintf(arquivoEscrita, "\t\%%endmacro \t\t\t;sai da macro\n");

    //inicio do codigo
    std::fprintf(arquivoEscrita, "\n\tsection .text\n");
    std::fprintf(arquivoEscrita, "\tmain:\n");


}

Parser::~Parser(){
     std::fprintf(arquivoEscrita, "\n\tret\t\t\t\t;final do programa\n");
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
            std::fprintf(arquivoEscrita, "\n\t\tsomar\t\t\t;chama macro de soma\n");


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
            return restoExpressao();

            //compilador
            std::fprintf(arquivoEscrita, "\n\t\tsubtrair\t\t\t;chama macro de subtrair\n");
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
            std::fprintf(arquivoEscrita, "\n\t\tmultiplicar\t\t;chama macro de multiplicar\n");
            return restoTermo();
        }
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
        if(fator()){
            //interpretador
            double op1, op2;
            op2 = numeroArmazenado.top();
            numeroArmazenado.pop();
            op1 = numeroArmazenado.top();
            numeroArmazenado.pop();
            numeroArmazenado.push(op1/op2);

            //compilador
            std::fprintf(arquivoEscrita, "\n\t\tdividir\t\t\t;chama macro de dividir\n");
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
        //tradutor
        numeroArmazenado.push(proximoToken.getValorInt());

        //compilador
        std::fprintf(arquivoEscrita, "\t\tpush,%d\t\t\t;Empilha o numero encontrado\n", proximoToken.getValorInt());
        return true;
    }

    if(proximoToken.getTipo() == ENUMS::DOUBLE){
        numeroArmazenado.push(proximoToken.getValorDouble());
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
