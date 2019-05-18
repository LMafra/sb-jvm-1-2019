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

int main() { /*! Long Detailed description after the member */
  classFile* cf;

	cf = classReader("tests/Array.class");
  classPrinter(cf);

  return 0;
}