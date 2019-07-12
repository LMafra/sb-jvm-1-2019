///
///		@file decodificador.h
///		@class decodificador.c "decodificador.c"
///
///		@date 26/07/2019.
///
///		@authors
///	    Bruno Sanguinetti 18/0046063 \n
///	    Gabriel Vasconcelos 16/0120781 \n
///	    Leonardo de Almeida 15/0135491 \n
///	    Lucas Mafra 12/0126443 \n
///	    Wladimir Gramacho 15/0058718 \n
///
///  	@brief Recebe uma estrutura Decodificador vazia e preenche
///		com strings que sao as instrucoes presentes no bytecode.
///		Retorna uma estrutura Decodificador preenchida.

#ifndef DECODIFICADOR_H
#define DECODIFICADOR_H

#include <string.h> 

#define NOME_INSTRUCAO 30 

typedef struct Decodificador {
    char instrucao[NOME_INSTRUCAO];
    int bytes; 
} Decodificador; 

void inicializaDecodificador(Decodificador dec[]);

#endif 