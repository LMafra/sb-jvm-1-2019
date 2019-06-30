///
///		@file exibidor.h
///		@class exibidor.c "exibidor.c"
///		@headerfile leitor.h "leitor.h"
///
///
///		@date 28/06/17.
///		@copyright Copyright © 2017 GrupoSB. All rights reserved.
///
///		@authors
///	    Bruno Sanguinetti 18/0046063 \n
///	    Gabriel Vasconcelos 16/0120781 \n
///	    Leonardo de Almeida 15/0135491 \n
///	    Lucas Mafra 12/0126443 \n
///	    Wladimir Gramacho 15/0058718 \n
///
///		@brief 
///		Arquivo que exibe na tela uma estrutura ClassFile
///		imprimindo todos os dados armazenados.
///
///		Recebe um ponteiro para uma estrutura ClassFile, imprime
///		cada parte de acordo com seu formato e suas subestruturas,
///		isso tudo com uma interface semelhante ao programa
///		"jclasslib bytecode viewer".
///

#ifndef EXIBIDOR_h
#define EXIBIDOR_h

#include <stdio.h>

#include "leitor.h"

void printaClassFile(ClassFile*);
void printaCpInfo(ClassFile*);
void printaInterfaces(ClassFile*);
void printaFieldInfo(ClassFile*);
void printaMethodInfo(ClassFile*);
void printaAttributeInfo(ClassFile*);
void imprimeStringPool(CpInfo*, int);
void imprimeCode(ClassFile*, CodeAttribute*);
void imprimeExc(ClassFile*, ExceptionsAttribute*);
double hexToDouble(uint32_t, uint32_t);
long hexToLong(uint32_t, uint32_t);
void printAccessFlag(uint16_t);
void imprimeMajorVersion(uint16_t);
void printTopo();
void printBlank();
void printBase();
void printSingleLine();

#endif