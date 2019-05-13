 /********************************************//**
 * Universidade de Brasilia
 *
 * Bruno Sanguinetti 18/0046063 \n
 * Gabriel Vasconcelos 16/0120781 \n
 * Leonardo de Almeida 15/0135491 \n
 * Lucas Mafra 12/0126443 \n
 * Wladimir Gramacho 15/0058718 \n
 ***********************************************/

/**
* @file 
* @brief Cabeçalho do exibidor do classfile no terminal. \n
* @section DESCRIPTION
* 
*  
*/

#ifndef PRINTER_H
#define PRINTER_H

/* Includes */
#include <stdlib.h>
#include <stdio.h>
#include "reader.h"

/* Definitions */
#define ACC_PUBLIC      0x0001
#define ACC_FINAL       0x0010
#define ACC_SUPER       0x0020
#define ACC_INTERFACE   0x0200
#define ACC_ABSTRACT    0x0400
#define ACC_SYNTHETIC   0x1000
#define ACC_ANNOTATION  0x2000
#define ACC_ENUM        0x4000

/* Functions */
void classPrinter( classFile* cf); /*!< \brief Detailed description after the member */

#endif