#include <QCoreApplication>
#include <iostream>

#include "parser.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

     //teste do scanner OK
//    COMPILADOR::Scanner scaner;
//    COMPILADOR::Token *token;

//    while(true){
//        token = scaner.proximoToken();
//        std::cout<<"Tipo: "<<token->getTipo()<<" valor int: "<<token->getValorInt()<<" valor double: "<<token->getValorDouble()<<std::endl;
//        delete token;
//    }

    COMPILADOR::Parser parser;
    if(parser.expressao()){
         std::cout<<"Expressãao OK"<<std::endl;
    }else{
        std::cout<<parser.getMensagemErro()<<std::endl;
    }



    return a.exec();
}
