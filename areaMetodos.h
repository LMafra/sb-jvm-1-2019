///
///	@file areaMetodos.h
///	@headerfile leitor.h "leitor.h"
///
///	@date 28/06/19.
///
///	@authors
///	Bruno Sanguinetti 18/0046063 \n
///	Gabriel Vasconcelos 16/0120781 \n
///	Leonardo de Almeida 15/0135491 \n
///	Lucas Mafra 12/0126443 \n
///	Wladimir Gramacho 15/0058718 \n
///
///	@brief
///	Define as estruturas Area de Metodos e Objeto.
///

#ifndef AREA_METODOS_H
#define AREA_METODOS_H

#include "leitor.h"

///
/// @brief Estrutura geral que contem todas as demais estruturas
///
/// Aqui ficam guaradas as classes carregadas e todas as subestrutures
/// dessas classes.
typedef struct AreaMetodos {
  ClassFile** arrayClasses;			
  int numClasses;								
} AreaMetodos;

///
/// @brief Estrutura para um objeto java
///
/// Essa estrutura guarda todas as informacoes especificas de cada
/// objeto instanciado.
typedef struct Objeto {
  ClassFile* classe;						
  struct Objeto* superClasse;		
  uint32_t* campos;							
  uint32_t* indiceCampos;				
} Objeto;

#endif
