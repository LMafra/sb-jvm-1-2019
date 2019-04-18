/* @file 
 * @section DESCRIPTION
 * Universidade de Brasilia
 *
 * Bruno Sanguinetti \n
 * Gabriel Vasconcelos \n
 * Leonardo de Almeida \n
 * Lucas Mafra 12/0126443 \n
 * Wladimir Gramacho \n
 * 
 * Função responsável pelo processamento do arquivo .class
 *  e execução das instruções da JVM
 */


#include <stdlib.h>
#include <stdio.h>
#include "printer.h"
#include "reader.h"

int main() {
  classFile* cf;

	cf = classReader("tests/Array.class");
  classPrinter(cf);

  return 0;
}