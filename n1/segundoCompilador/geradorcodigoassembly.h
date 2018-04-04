#ifndef GERADORCODIGOASSEMBLY_H
#define GERADORCODIGOASSEMBLY_H

#include <string>
#include <iostream>
#include <QString>
#include "enums.h"



namespace COMPILADOR {


class GeradorCodigoAssembly
{
private:
    unsigned int contadorLabel;

public:
    GeradorCodigoAssembly();


    std::string gerarCabecalho();
    std::string gerarInicioCodigo();
    std::string gerarFinalArquivo();
    std::string gerarLabel(std::string nomeLabel);
    std::string gerarComentario(std::string comentario);
    std::string gerarOperacao(ENUMS::tipoToken tipo);
    std::string gerarMacro(ENUMS::tipoToken tipo);
    std::string gerarEmpilhaNumero(ENUMS::tipoToken tipo,  ENUMS::numeroTipo valor);

};

}//FIM DA NAMESPACE COMPILADOR
#endif // GERADORCODIGOASSEMBLY_H
