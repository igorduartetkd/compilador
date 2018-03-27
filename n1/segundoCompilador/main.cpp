#include <QCoreApplication>
#include <iostream>
#include <stdio.h>

#include "parser.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    COMPILADOR::Parser parser;
    if(parser.analisar()){
         std::cout<<"Resultado da expressão: "<<parser.getResultadoExpressao()<<std::endl;
    }else{
        std::cout<<parser.getMensagemErro()<<std::endl;
    }


    return 0;
}
