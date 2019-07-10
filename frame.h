///
///		@file frame.h
///		@class frame.c "frame.c"
///		@headerfile leitor.h "leitor.h"
///
///		@date 26/06/17.
///		@copyright Copyright © 2017 GrupoSB. All rights reserved.
///
///		@authors
///		Bruno Sanguinetti 18/0046063 \n
///		Gabriel Vasconcelos 16/0120781 \n
///		Leonardo de Almeida 15/0135491 \n
///		Lucas Mafra 12/0126443 \n
///		Wladimir Gramacho 15/0058718 \n
///
///		@brief 
///		Arquivo de definicao de das estruturas de um frame.

#ifndef FRAME_H
#define FRAME_H

#include <stdint.h>
#include <stdlib.h>
#include "leitor.h"

typedef struct PilhaOp {
  int depth;
  int32_t* operandos;
} PilhaOp;

typedef struct Frame {
	int32_t* localVariables;
	CpInfo* constantPool;
	ClassFile* classe;
	uint16_t maxStack;
	uint16_t maxLocals;
	uint32_t codeLength;
	uint8_t* code;
	uint32_t pc;
  PilhaOp* pilhaOp;
} Frame;

typedef struct StackFrame {
	Frame* refFrame;
	struct StackFrame* next;
} StackFrame;

typedef struct Vector {
	int32_t referencia;
	int32_t tamanho;
	int8_t tipo;
} Vector ;

int32_t retorno;
int32_t retAlta;
int32_t retBaixa;
int8_t flagRet;

int32_t popOp();

void criaFrame(ClassFile*, CodeAttribute*);
void desalocaFrame();
void pushOp(int32_t);
void dumpStack();
void dumpFields();
void pushFrame(ClassFile*, CodeAttribute*, StackFrame*);
void popFrame();
int checkaOverflowPilhaOp();
int checkaUnderflowPilhaOp();

#endif
