///
///		@file metodo.h
///		@class metodo.c "metodo.c"
///		@headerfile carregador.h "carregador.h"
///
///		@date 28/06/19.
///
///		@authors
///	    Bruno Sanguinetti 18/0046063 \n
///	    Gabriel Vasconcelos 16/0120781 \n
///	    Leonardo de Almeida 15/0135491 \n
///	    Lucas Mafra 12/0126443 \n
///	    Wladimir Gramacho 15/0058718 \n
///
///		@brief
///		Define as funcoes que implementam a execucao de um 
///     metodo e instanciacao de objetos.

#ifndef METODO_H
#define METODO_H

#include "carregador.h"

AreaMetodos areaMetodos;

MethodInfo* buscaMetodoMain();
void empilhaMetodo(MethodInfo*, ClassFile*);
void executaFrameCorrente();
Objeto* criaObjeto(ClassFile*);
MethodInfo* buscaMetodo(ClassFile*, ClassFile*, uint16_t);
int32_t retornaNumeroParametros(ClassFile*, MethodInfo*);
ClassFile* retornaClassePorNome(char*);
int retornaIndiceDaClassePorNome(char*);
int32_t buscaCampo(char*, char*, char*);

#endif
