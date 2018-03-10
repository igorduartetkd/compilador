#include "scanner.h"

namespace COMPILADOR {


Scanner::Scanner():
    token(0)
{
}
/* --- PROXIMOS PASSOS: SUBSTITUIR BIBLIOTECA DE EXPRESSAO REGULAR PELA QRegExp --- */
Token* Scanner::proximoToken(){
    char caracter;
    QString caracterQString;
    QString valorToken;
    std::regex eRNumero("[[:digit:]]");     //expressao regular para representar um digito

    if(buffer.empty()){ // se o buffer estiver vazio
        std::scanf("%c", &caracter);
    }else{ //se o buffer tiver algo utiliza o que tem
        caracter = buffer.front();
        buffer.pop();
    }
    caracterQString = caracter;

    //ignorando espaços em branco e quebras de linha
    if(caracter == ' ' || caracter == '\n'){
        return proximoToken();
    }

    //testa fim de arquivo
    if(caracter == '\0'){
        return new Token(ENUMS::EPSILON);
    }

    //testa se é digito
    if(std::regex_match(caracterQString.toStdString(), eRNumero)){
        valorToken = caracterQString;
        valorToken += lerRestoNumero();
        ENUMS::tipoToken tipoToken = verificarEnumNumero(valorToken);
        if(tipoToken == ENUMS::INT){ //se o tipo for inteiro
            return new Token(tipoToken, valorToken.toInt());
        }else{ //se o tipo for double, ou então se for erro vai junto
            return new Token(tipoToken, valorToken.toDouble());
        }

    }

    if(caracter == '-'){
        //VERIFICAR SE PROXIMO E NUMERO COLADO
        scanf("%c", &caracter);
        caracterQString = caracter;
        if(std::regex_match(caracterQString.toStdString(), eRNumero)){// se for digito o token será numero
            valorToken = "-";
            valorToken += lerRestoNumero();
            ENUMS::tipoToken tipoToken = verificarEnumNumero(valorToken);
            if(tipoToken == ENUMS::INT){ //se o tipo for inteiro
                return new Token(tipoToken, valorToken.toInt());
            }else{ //se o tipo for double, ou então se for erro vai junto
                return new Token(tipoToken, valorToken.toDouble());
            }

        }

        //nao é um numero, ou seja, é um operador -
        this->buffer.push(caracter); //armazena o caracter lido para saber se era numero
        return new Token(ENUMS::SUB);
    }

    if(caracter == '+'){
        return new Token(ENUMS::SOMA);
    }

    if(caracter == '*'){
        return new Token(ENUMS::MUL);

    }

    if(caracter == '/'){
        return new Token(ENUMS::DIV);

    }

    if(caracter == '('){
        return new Token(ENUMS::ABREPARENTESE);

    }

    if(caracter == ')'){
        return new Token(ENUMS::FECHAPARENTESE);

    }

    //DEFAULT
    return new Token(ENUMS::ERRO);


}

/* Método necessário para verificar se o número é double, int, ou um número com vários pontos, o que retorna erro
 */
ENUMS::tipoToken Scanner::verificarEnumNumero(QString numero){
    int qntPontos = numero.count('.');  //conta a quantidade de ocorrencias do caracter '.'
    if(qntPontos == 0)
        return ENUMS::INT;
    if(qntPontos == 0)
        return ENUMS::DOUBLE;

    return ENUMS::ERRO;
}


/* Metodo recursivo para ler o resto do número por completo e armazenar
 a ultima leitura, que pode ser um caractere, em buffer*/
QString Scanner::lerRestoNumero(){
    char caracter;
    QString caracterToString;
    QString valorToken;
    std::regex eRNumero("[[:digit:]]");     //expressao regular para representar um digito

    std::scanf(" %c", &caracter) ;           //lendo proximo caracter
    caracterToString = caracter;            //transformando para QString

    if(std::regex_match(caracterToString.toStdString(), eRNumero)){         //caracter e um digito?
        valorToken = caracterToString;
        valorToken += lerRestoNumero();
        return valorToken;
    }else
        if(caracter == '.'){ //agora fudeu muito
            valorToken = caracterToString;
            valorToken += lerRestoNumero();
            return valorToken;
        }else
            if(caracter == '\0'){   // se for final de arquivo
                return "\0";
            }else{  //se for um operador
                buffer.push(caracter);      //armazena o caracter em buffer para ser tratado na próxima chamada
                return "\0";
            }
}

}//FIM DA NAMESPACE COMPILADOR
