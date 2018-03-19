#include "scanner.h"

namespace COMPILADOR {


Scanner::Scanner()
{
}
/* --- PROXIMOS PASSOS: SUBSTITUIR BIBLIOTECA DE EXPRESSAO REGULAR PELA QRegExp --- */
Token Scanner::proximoToken(){
    char caracter;
    QString caracterQString;
    QString valorToken;
    QRegExp eRNumero("\\d");     //expressao regular para representar um digito

    caracter = lerProximoChar();
    caracterQString = caracter;

    //ignorando espaços em branco e quebras de linha
    if(caracter == ' ' || caracter == '\n' || caracter == '\t'){
        return proximoToken();
    }

    //testa fim de arquivo
    if(caracter == EOF){
        return Token(ENUMS::EPSILON);
    }

    //testa se é digito
    if(eRNumero.exactMatch(caracterQString)){
        valorToken = caracterQString;
        valorToken += lerRestoNumero();
        ENUMS::tipoToken tipoToken = verificarEnumNumero(valorToken);
        if(tipoToken == ENUMS::INT){ //se o tipo for inteiro
            return Token(tipoToken, valorToken.toInt());
        }else{ //se o tipo for double, ou então se for erro vai junto
            return Token(tipoToken, valorToken.toDouble());
        }

    }

    if(caracter == '-'){
        //VERIFICAR SE PROXIMO E NUMERO NEGATIVO
        caracter = lerProximoChar();
        caracterQString = caracter;
        if(eRNumero.exactMatch(caracterQString)){// se for digito o token será numero
            valorToken = "-";
            valorToken.append(caracter);
            valorToken += lerRestoNumero();
            ENUMS::tipoToken tipoToken = verificarEnumNumero(valorToken);
            if(tipoToken == ENUMS::INT){ //se o tipo for inteiro
                return Token(tipoToken, valorToken.toInt());
            }else{ //se o tipo for double, ou então se for erro vai junto
                return Token(tipoToken, valorToken.toDouble());
            }

        }

        //nao é um numero, ou seja, é um operador -
        this->buffer.push(caracter); //armazena o caracter lido para saber se era numero
        return Token(ENUMS::SUB);
    }

    if(caracter == '+')
        return Token(ENUMS::SOMA);


    if(caracter == '*')
        return Token(ENUMS::MUL);

    if(caracter == '/')
        return Token(ENUMS::DIV);


    if(caracter == '(')
        return Token(ENUMS::ABREPARENTESE);


    if(caracter == ')')
        return Token(ENUMS::FECHAPARENTESE);


    //DEFAULT
    return Token(ENUMS::ERRO);


}

/* Método necessário para verificar se o número é double, int, ou um número com vários pontos, o que retorna erro
 */
ENUMS::tipoToken Scanner::verificarEnumNumero(QString numero){
    int qntPontos = numero.count('.');  //conta a quantidade de ocorrencias do caracter '.'
    if(qntPontos == 0)
        return ENUMS::INT;
    if(qntPontos == 1)
        return ENUMS::DOUBLE;

    return ENUMS::ERRO;
}


/* Metodo recursivo para ler o resto do número por completo e armazenar
 a ultima leitura, que pode ser um caractere, em buffer*/
QString Scanner::lerRestoNumero(){
    char caracter;
    QString caracterQString;
    QString valorToken;
    QRegExp eRNumero("\\d");     //expressao regular para representar um digito

    caracter = lerProximoChar();           //lendo proximo caracter
    caracterQString = caracter;            //transformando para QString

    if(eRNumero.exactMatch(caracterQString)){//caracter e um digito?
        valorToken = caracterQString;
        valorToken += lerRestoNumero();
        return valorToken;
    }

    if(caracter == '.'){ //numero decimal é verificado posteriormente
        valorToken = caracterQString;
        valorToken += lerRestoNumero();
        return valorToken;
    }

    buffer.push(caracter);      //armazena o caracter em buffer para ser tratado na próxima chamada
    return "";
}

char Scanner::lerProximoChar(){
    char caracter;
    if(buffer.empty()){ // se o buffer estiver vazio
        if(std::scanf("%c", &caracter) != EOF)
            return caracter;
        return EOF;
    }
    //se o buffer tiver algo utiliza o que tem
    caracter = buffer.front();
    buffer.pop();
    return caracter;
}

}//FIM DA NAMESPACE COMPILADOR
