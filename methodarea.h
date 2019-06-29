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
* @brief  \n
* @section DESCRIPTION
* 
*/

#ifndef METHOD_AREA_H
#define METHOD_AREA_H

#include "reader.h"

typedef struct method_area{
  classFile** classes_array;
  int num_classes;
}method_area;

#endif