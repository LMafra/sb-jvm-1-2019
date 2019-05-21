/********************************************//**
 * Universidade de Brasilia
 *
 * Bruno Sanguinetti \n
 * Gabriel Vasconcelos \n
 * Leonardo de Almeida \n
 * Lucas Mafra 12/0126443 \n
 * Wladimir Gramacho \n
 ***********************************************/

/**
* @file
* @brief Responsável pelo processamento do arquivo 
*        .class e execução das instruções da JVM
* @section DESCRIPTION
*/

#include <stdlib.h>
#include <stdio.h>
#include "printer.h"
#include "reader.h"
#include "freemem.h"
#include "instructions.h"

int main(int argc, char **argv) { /*! funcao princial que executa o codigo. Inici */
  classFile* cf;

  initializeInstructions();

  if(argc != 2){
    printf("You must pass the name of the file as an argument!\n");
    return 0;
  }
	cf = classReader(argv[1]);
  classPrinter(cf);
  freeMemory(cf);

  return 0;
}