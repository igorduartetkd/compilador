Autor: Igor Duarte
Programas desenvolvidos na disciplina de compiladores na PUC-GOIÁS

N1 são os compiadores que compõem a nota do primeiro bimestre de 2018/1, portanto são mais básicos.

O primeiroCompilador é apenas um interpretador para expressões aritmeticas simples de soma, subtração, divisao e multiplicação para valores inteiros e reais com ou sem parenteses.
Para executar o primeiro compilador basta ir na pasta build... e lançar um: ./primeiroCompilador < teste.txt


O segundoCompilador possui as mesmas funções do primeiroCompilador, porém, ele gera código assembly.
Para executar o segundoCompilador:
	-edite a entrada desejada no arquivo "teste.txt" dentro da pasta build do segundo compiador.
	-pelo terminal execute o comando "./segundoCompilador < teste.txt" para gerar o arquivo "produzido.asm"
	-ainda no terminal execute "./executarNasm.sh produzido" para montar, linkeditar e executar o programa com nasm
obs. caso não possua o gcc-4.9 instalado na maquina, basta ir no arquivo executarNasm.sh e mudar a versão do gcc podendo deixar apenas gcc (caso o instalado nao for o 6.3.0)

