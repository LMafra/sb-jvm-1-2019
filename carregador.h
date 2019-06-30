///
///		@file carregador.h
///		@class carregador.c "carregador.c"
///		@headerfile leitor.h "leitor.h"
///		@headerfile areaMetodos.h "areaMetodos.h"
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
///		Carrega, inicializa e aloca um ClassFile e associa com a estrutura do AreaMetodos.
///

#ifndef CARREGADOR_H
#define CARREGADOR_H

#include "leitor.h"
#include "areaMetodos.h"

int32_t carregaClasseParaMemoria(char*);
void inicializaPrimeiraVez();
void carregaClasse(char*);
char* retornaNomeClass(ClassFile*);
ClassFile* buscaClassPorIndice(int);
char* retornaNome(ClassFile*, uint16_t);
void validaClassFile(ClassFile*, char*);
void validaVersaoJava(ClassFile*);
void validaNomeClasseArquivo(ClassFile*, char*);

#endif
