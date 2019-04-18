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
 * Responsavel por imprimir no terminal 
 * a estrutura do classfile lido. \n
 *  
 */


#include "printer.h"

void classPrinter( classFile* cf) {
  printf("# Class file Structure\n");
	printf("CAFEBABE: 0x%0x \n",cf->magic);
	printf("Minor version: %d \n",cf->minor_version);
	printf("Major version: %d \n",cf->major_version);
	printf("Constant Pool Count: %d \n",cf->constant_pool_count);
}