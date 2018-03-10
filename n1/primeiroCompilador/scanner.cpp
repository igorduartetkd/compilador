#include "scanner.h"

namespace COMPILADOR {


Scanner::Scanner():
    token(0)
{
}
/* --- PROXIMOS PASSOS: SUBSTITUIR BIBLIOTECA DE EXPRESSAO REGULAR PELA QRegExp --- */
Token Scanner::proximoToken(){
    char caracter;
    QString caracterQString;
    QString valorToken;
    QRegExp eRNumero("\\d");     //expressao regular para representar um digito

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
    if(caracter == '\0' || caracter == 'EOF'){
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
        scanf("%c", &caracter);
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

    if(caracter == '+'){
        return Token(ENUMS::SOMA);
    }

    if(caracter == '*'){
        return Token(ENUMS::MUL);

    }

    if(caracter == '/'){
        return Token(ENUMS::DIV);

    }

    if(caracter == '('){
        return Token(ENUMS::ABREPARENTESE);

    }

    if(caracter == ')'){
        return Token(ENUMS::FECHAPARENTESE);

    }

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

    std::scanf("%c", &caracter) ;           //lendo proximo caracter
    caracterQString = caracter;            //transformando para QString

    if(eRNumero.exactMatch(caracterQString)){         //caracter e um digito?
        valorToken = caracterQString;
        valorToken += lerRestoNumero();
        return valorToken;
    }else
        if(caracter == '.'){ //numero decimal é verificado posteriormente
            valorToken = caracterQString;
            valorToken += lerRestoNumero();
            return valorToken;
        }else
            if(caracter == ' ' || caracter == '\n'){   // se for final de arquivo ou espaço em branco ou quebra de linha
                return "\0";
            }else{  //se for um operador
                buffer.push(caracter);      //armazena o caracter em buffer para ser tratado na próxima chamada
                return "\0";
            }
}

}//FIM DA NAMESPACE COMPILADOR
