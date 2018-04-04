#include "geradorcodigoassembly.h"

namespace COMPILADOR {



GeradorCodigoAssembly::GeradorCodigoAssembly():
    contadorLabel(0)
{

}

std::string GeradorCodigoAssembly::gerarCabecalho(){
    std::string codigo;
    codigo = "\tglobal main\t\t\t;indica que o main sera visivel fora do arquivo\n";
    codigo += "\textern printf\t\t\t;funções escritas em c que serão usadas no programa\n";

    codigo += "\n\tsection .data\t\t\t;segmento de dados inicializados\n";
    codigo += "\t\timprimir db \"Resultado da expressao: %lf\",10,0\t;constante utilizada para imprimir um double\n";
    codigo += "\t\tc dq 1.0\t\t;variavel utilizada para mover para xmm0\n";
    //se precisar de dados nao inicializados adicionar section .bss
    return codigo;
}

std::string GeradorCodigoAssembly::gerarInicioCodigo(){
    std::string codigo;
    codigo += gerarComentario("Segmento de codigo, onde ficam as instruções");
    codigo += "\tsection .text\t\t\t;segmento de procedimentos";
    codigo += gerarLabel("main");
    codigo += "\t\tpush rbp\t;constante utilizada para imprimir um double\n";

    return codigo;
}

std::string GeradorCodigoAssembly::gerarFinalArquivo(){
    std::string codigo;
    codigo += gerarComentario("imprimindo o resultado");
    codigo += "\t\tmov rdi, imprimir\t;desempilhando a pilha de float na variavel c\n";
    codigo += "\t\tfstp qword [c]\t\t;desempilhando a pilha de float na variavel c\n";
    codigo += "\t\tmovq xmm0, [c]\t\t;xmm0 = [c], printf utiliza xmm0 para passagem de float \n";
    codigo += "\t\tmov rax, 1\t\t;uma variavel float passada para o printf\n";
    codigo += "\t\tcall printf\t\t;chamada a funçao do c printf\n";

    codigo += "\n\t\tpop rbp\t\t\t;desempilha novamente rbp\n";
    codigo += "\t\txor rax, rax\t\t;indica que não houve erro no programa\n";
    codigo += "\n\tret\t\t\t\t;final do programa\n";
    return codigo;
}

std::string GeradorCodigoAssembly::gerarLabel(std::string nomeLabel){
    std::string codigo;
    codigo = "\n\t";
    codigo += nomeLabel;
    codigo += ":\n";
    return codigo;
}

std::string GeradorCodigoAssembly::gerarComentario(std::string comentario){
    std::string codigo;
    codigo = "\n\n\t; --- ";
    codigo += comentario;
    codigo += " ---\n";
    return codigo;
}

std::string GeradorCodigoAssembly::gerarOperacao(ENUMS::tipoToken tipo){
    std::string codigo;

    switch (tipo) {
    case ENUMS::SOMA:
        codigo = "\t\tfadd\t\t\t;desempilha dois valores, soma e empilha o resultado\n";
        break;
    case ENUMS::SUB:
        codigo = "\t\tfsub\t\t\t;pop st(0) e st(1). depois push st(1)-st(0)\n";
        break;
    case ENUMS::MUL:
        codigo = "\t\tfmul\t\t\t;pop st(0) e st(1). depois push st(0)*st(1)\n";
        break;
    case ENUMS::DIV:
        codigo = "\t\tfdiv\t\t\t;pop st(0) e st(1). depois push st(1)/st(0)\n";
        break;
    default:
        std::cout<<"Tipo de operador em não conformidade com metodo gerar operaçao"<<std::endl;
        exit(1);
        break;
    }

    return codigo;
}

std::string GeradorCodigoAssembly::gerarMacro(ENUMS::tipoToken tipo){
    std::string codigo;

    switch (tipo) {
    case ENUMS::SOMA:
        //gera macro para somar
        codigo = "\n\t%macro somar 0\t\t\t;macro para somar\n";
        codigo += "\t\tpop rcx\t\t\t;desempilha o segundo operador\n";
        codigo += "\t\tpop rbx\t\t\t;desempilha o primeiro operador\n";
        codigo += "\t\tadd rbx, rcx\t\t;soma rbx a rcx e guarda em rbx\n";
        codigo += "\t\tpush rbx\t\t;empilha o resultado\n";
        codigo += "\t\%endmacro \t\t\t;sai da macro\n";
        break;
    case ENUMS::SUB:
        //gera macro para subtrair
        codigo = "\n\t%macro subtrair 0\t\t;macro para subtrair\n";
        codigo += "\t\tpop rcx\t\t\t;desempilha o segundo operador\n";
        codigo += "\t\tpop rbx\t\t\t;desempilha o primeiro operador\n";
        codigo += "\t\tsub rbx, rcx\t\t;subtrai rbx a rcx e guarda em rbx\n";
        codigo += "\t\tpush rbx\t\t;empilha o resultado\n";
        codigo += "\t\%endmacro \t\t\t;sai da macro\n";
        break;
    case ENUMS::MUL:
        //gera macro para multiplicar
        codigo = "\n\t\%macro multiplicar 0\t\t;macro para multiplicar\n";
        codigo += "\t\tpop rdx\t\t\t;desempilha o segundo operador\n";
        codigo += "\t\tpop rax\t\t\t;desempilha o primeiro operador\n";
        codigo += "\t\tmul rdx\t\t\t;multiplica rax = rax * rdx\n";
        codigo += "\t\tpush rax\t\t;empilha o resultado\n";
        codigo += "\t\%endmacro \t\t\t;sai da macro\n";
        break;
    case ENUMS::DIV:
        //gera macro para dividir
        codigo = "\n\t\%macro dividir 0\t\t;macro para dividir\n";
        codigo += "\t\tpop rdx\t\t\t;desempilha o segundo operador\n";
        codigo += "\t\tpop rax\t\t\t;desempilha o primeiro operador\n";
        codigo += "\t\tdiv rdx\t\t\t;divide rax = rax / rdx\n";
        codigo += "\t\tpush rax\t\t;empilha o resultado\n";
        codigo += "\t\%endmacro \t\t\t;sai da macro\n";
        break;

    case ENUMS::INT:
        //gera macro para guardar o numero
        codigo = "\n\t\%macro empilhar 1\t\t;macro para empilhar recebe 1 parametro\n";
        codigo += "\tsection .data\t\t\t;define a variavel passada por parametro\n";
        codigo += "\t\t.valor dq %1\t\t;.valor = parametro\n";
        codigo += "\tsection .text\t\t\t;segmento de procedimentos da macro\n";
        codigo += "\t\tfld qword[.valor]\t;empilha o valor real\n";
        codigo += "\t\%endmacro \t\t\t;fim da macro\n";
        break;
    default:
        std::cout<<"Tipo de operador em não conformidade com metodo gerar macros"<<std::endl;
        exit(1);
        break;
    }



    return codigo;
}

std::string GeradorCodigoAssembly::gerarEmpilhaNumero(ENUMS::tipoToken tipo, ENUMS::numeroTipo valor){
    std::string codigo;
    //tem que criar label nova a cada empilhamento senao da pau quando declara 2 variaveis .valor na mesma label no .data
    std::string nomeLabel("lab");
    switch (tipo) {
    case ENUMS::INT:
        nomeLabel += std::to_string(contadorLabel++);
        codigo += this->gerarLabel(nomeLabel);
        codigo += "\t\tempilhar ";
        codigo += std::to_string(valor.inteiro);
        codigo += ".0\t\t;chama a macro para empilhar o valor passado\n";
        break;
    case ENUMS::DOUBLE:
        nomeLabel += std::to_string(contadorLabel++);
        codigo += this->gerarLabel(nomeLabel);
        codigo += "\t\tempilhar ";
        codigo += std::to_string(valor.real);
        codigo += "\t\t;chama a macro para empilhar o valor passado\n";
        break;
    default:
        std::cout<<"Tipo de operador em não conformidade com metodo gerar empilha numero"<<std::endl;
        exit(1);
        break;
    }
    return codigo;
}


}//FIM DA NAMESPACE COMPILADOR
