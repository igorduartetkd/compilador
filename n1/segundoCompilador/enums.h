#ifndef ENUMS_H
#define ENUMS_H
namespace ENUMS {
enum tipoToken{
    INT,
    DOUBLE,
    SOMA,
    SUB,
    MUL,
    DIV,
    EPSILON,
    ABREPARENTESE,
    FECHAPARENTESE,
    ERRO
};

union numeroTipo{
    int inteiro;
    double real;
};

}//FIM DA NAMESPACE ENUMS
#endif // ENUMS_H
