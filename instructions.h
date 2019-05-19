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

#ifndef INSTR_H
#define INSTR_H

/* Includes */
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

/* Definições */
enum {
  newarray = 188, anewarray = 189, multianewarray = 197, checkcast = 192, getfield = 180, getstatic = 178, instanceofg = 193, invokedynamic = 186, invokeinterface = 185, invokespecial = 183, invokestatic = 184, invokevirtual = 182, ldc = 18, ldc_w = 19, ldc2_w = 20, NEW = 187, putfield = 181, putstatic = 179, GOTO = 167, if_acmpeq = 165, if_acmpne = 166, if_icmpeq = 159, if_icmpne = 160, if_icmplt = 161, if_icmpge = 162, if_icmpgt = 163, if_icmple = 164, iifeq = 153, ifne = 154, iflt = 155, ifge = 156, ifgt = 157, ifle = 158, ifnonull = 199, ifnull = 198, jsr = 168, aload = 25, aload_0 = 42, aload_1 = 43, aload_2 = 44, aload_3 = 45, areturn = 176, return_original = 177
} instructions_opcode;


/* Estruturas */
typedef struct Opcode{
  char name[50];
  uint8_t key;
  uint8_t arguments;
  uint16_t references;
} opcode;

/* Funções */
void initializeInstructions();

/* para usar na main */
extern opcode instructions[300];

#endif