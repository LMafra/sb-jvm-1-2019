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
#define ACC_PUBLIC      0x0001  /*!< \brief Declaracao: publico; pode ser acessada de fora do pacote. */
#define ACC_PRIVADO     0x0002  /*!< \brief Declaracao: privado; usavel apenas dentro da classe. */
#define ACC_PROTECTED   0x0004  /*!< \brief Declaracao: protected; usavel pela classe e subclasses. */
#define ACC_STATIC      0x0008  /*!< \brief Declaracao: statico. */
#define ACC_FINAL       0x0010  /*!< \brief Declaracao: final; after the member */
#define ACC_SUPER       0x0020  /*!< \brief Declaracao: superclass */
#define ACC_INTERFACE   0x0200  /*!< \brief Declaracao: interface */
#define ACC_ABSTRACT    0x0400  /*!< \brief Declaracao: classe abstrata */
#define ACC_SYNTHETIC   0x1000  /*!< \brief Declaracao: synthetic */  
#define ACC_ANNOTATION  0x2000  /*!< \brief Declaracao: annotation */
#define ACC_ENUM        0x4000  /*!< \brief Declaracao: enum*/

/* Functions */
void classPrinter( classFile* cf); /*!< \brief Detailed description after the member */

#endif