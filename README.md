![alt text](http://www.unb.br/images/Imagens/logo_unb.png)

# Software Básico - 1/2019

# Informações

## Cabeçalho

* 18/04/2019
* Brasília, DF, Brasil
* Software Básico
* Turma: A - 01/2019
* Professor: Marcelo Ladeira

## Autores

* **Bruno Sanguinetti R. Barros** |    *18/0046063*     |     [GitHub](https://github.com/BrunoSNT)
* **Gabriel Vasconcelos**         |    *16/0120781*     |     [GitHub](https://github.com/gcvasconcelos)
* **Leonardo de Almeida**         |    *15/0135491*     |     [GitHub](https://github.com/leodealmeida)
* **Lucas Mafra**                 |    *12/0126443*     |     [GitHub](https://github.com/LMafra)
* **Wladimir Gramacho**           |    *15/0048718*     |     [GitHub](https://github.com/wladimirgramacho)

## Getting Started

Essas instruções farão com que você tenha uma cópia deste projeto em sua máquina local para fins de desenvolvimento e teste.

```

~dir/ user$ git clone https://github.com/LMafra/sb-jvm-1-2019.git
~dir/ user$ cd sb-jvm-1-2019

```

### Compilando e Executando

Como compilar `gcc -o main main.c reader.c printer.c instructions.c freemem.c -Wall -std=c99 -ggdb3`:

```

~dir/sb-jvm-1-2019 user$ gcc -o main main.c reader.c printer.c instructions.c freemem.c -Wall -std=c99 -ggdb3

```

Como  executar `./main`:

```

~dir/sb-jvm-1-2019 user$ ./main

```

## Testes

Todos os testes foram feitos com classes fornecidas pelo professor ou baixadas da internet para fins de testes.


## Testes de Coding Style

Durante todo o projeto, após cada aprovaçao nos teste, foram executados os comandos

```

cppcheck --enable=warning main.c reader.c printer.c memcheck.c instructions.c
valgrind --leak-check=full --leak-resolution=high --track-origins=yes ./main

```

E em seguida feitas as devidas alterações para enquadrar o código nos padrões delimitados se nescessário

## Built With

* [Valgrind](http://www.valgrind.org/) - Dymanic Code Analysis Tool
* [CPPCheck](cppcheck.sourceforge.net) - Static Code Analysis Tool
* [VSCode](https://code.visualstudio.com) - Code Editor

## License

This project is licensed under the MIT License - see the [LICENSE](https://opensource.org/licenses/MIT) file for details

