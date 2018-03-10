#include <QCoreApplication>

#include "QString"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString teste;
    teste = "-12.5";

    double numero= teste.toDouble();

    std::cout<<numero<<std::endl;

    return a.exec();
}
