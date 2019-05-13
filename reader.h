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
* @brief Cabeçalho do leitor do .class. \n 
* @section DESCRIPTION 
*/
 
#ifndef READER_H
#define READER_H

/* Includes */
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

/* Definitions/Constants type - Constant pool tags */
#define CONSTANT_Class 7                 /*!< \brief constante de Class definida como 7 */
#define CONSTANT_Fieldref 9              /*!< \brief constante de Fieldref definida como 9 */
#define CONSTANT_Methodref 10            /*!< \brief constante de Methodref definida como 10 */
#define CONSTANT_InterfaceMethodref 11   /*!< \brief constante de InterfaceMethodref definida como 11 */
#define CONSTANT_String 8                /*!< \brief constante de String como definida 8 */
#define CONSTANT_Integer 3               /*!< \brief constante de Integer definida como 3 */
#define CONSTANT_Float 4                 /*!< \brief constante de Float definida como 4 */
#define CONSTANT_Long 5                  /*!< \brief constante de Long definida como 5 */
#define CONSTANT_Double 6                /*!< \brief constante de Double definida como 6 */
#define CONSTANT_NameAndType 12          /*!< \brief constante de NameAndType definida como 12 */
#define CONSTANT_Utf8 1                  /*!< \brief constante de Utf8 definida como 1 */
#define CONSTANT_MethodHandle 15         /*!< \brief constante de MethodHandle definida como 15 */
#define CONSTANT_MethodType 16           /*!< \brief constante de MethodType definida como 16 */
#define CONSTANT_InvokeDynamic 18        /*!< \brief constante de InvokeDynamic definida como 18 */

/*! \brief A estrutura do cp_info ira compor 
*   a constant_pool do classFile 
*
*  cp_info varia de acordo com o byte lido em sua tag
* 
*/
typedef struct cp_info {                    
  uint8_t tag;                        /*!< \brief Valor de um byte que indica o tipo de entrada*/
  union{
    struct{ 
      uint16_t name_index;            /*!< \brief Detailed description after the member */
    } Class;                          /*!< Class
                                      Detailed description after the member
                                      \brief ALO */                       
    struct {  
      uint16_t class_index;           /*!< Detailed description after the member1 */
      uint16_t name_and_type_index;   /*!< Detailed description after the member2 */
    } Fieldref;                       /*!< \brief ALO */

    struct {   
      uint16_t class_index;           /*!< Detailed description after the member */
      uint16_t name_and_type_index;   /*!< Detailed description after the member */
    } Methodref;                      /*!< Methodref 
                                      Detailed description after the member
                                      \brief ALO */
    struct {  
      uint16_t class_index;           /*!< Detailed description after the member */
      uint16_t name_and_type_index;   /*!< Detailed description after the member */
    } InterfaceMethodref;             /*!< \struct InterfaceMethodref
                                      Detailed description after the member
                                      \brief ALO*/
    struct {  
      uint16_t string_index;          /*!< Detailed description after the member */
    } String;                         /*! \struct String 
                                      Detailed description after the member
                                      \brief ALO */
    struct {  
      uint32_t bytes;                 /*!< Detailed description after the member */
    } Integer;                        /*! \struct Integer
                                      Detailed description after the member
                                      \brief ALO*/
    struct {  
      uint32_t bytes;                 /*!< Detailed description after the member */
    } Float;                          /*! \struct Float 
                                      Detailed description after the member
                                      \brief ALO*/
    struct {  
      uint32_t high_bytes;            /*!< \var Detailed description after the member */
      uint32_t low_bytes;             /*!< \var Detailed description after the member */
    } Long;                           /*! \struct Long Detailed
                                      Detailed description after the member
                                      \brief ALO*/
    struct { 
      uint32_t high_bytes;            /*!< Detailed description after the member */
      uint32_t low_bytes;             /*!< Detailed description after the member */
    } Double;                         /*! \struct Double
                                      Detailed description after the member
                                      \brief ALO*/
    struct {  
      uint16_t name_index;            /*!< Detailed description after the member */
      uint16_t descriptor_index;      /*!< Detailed description after the member */
    } NameAndType;                    /*! \struct NameAndType
                                      Detailed description after the member
                                      \brief ALO*/
    struct {  
      uint16_t length;                /*!< Detailed description after the member */
      uint8_t* bytes;                 /*!< Detailed description after the member */
    } Utf8;                           /*! \struct Utf8
                                      Detailed description after the member
                                      \brief ALO*/
    struct { 
      uint8_t reference_kind;         /*!< Detailed description after the member */
      uint16_t reference_index;       /*!< Detailed description after the member */
    } MethodHandle;                   /*! \struct MethodHandle
                                      Detailed description after the member
                                      \brief ALO*/
    struct {  
      uint16_t descriptor_index;      /*!< Detailed description after the member */
    } MethodType;                     /*! \struct MethodType
                                      Detailed description after the member
                                      \brief ALO*/
    struct {  
      uint16_t bootstrap_method_attr_index;  /*!< Detailed description after the member */
      uint16_t name_and_type_index;          /*!< Detailed description after the member */
    } InvokeDynamic;                         /*!< \struct InvokeDynamic
                                             Detailed description after the member
                                             \brief ALO*/
  } info; /*!< \brief Tipo de dado retornado pela union*/
} cp_info;

typedef struct ExceptionTable{
  uint16_t start_pc;
  uint16_t end_pc;
  uint16_t handler_pc;
  uint16_t catch_type;
} exception_table;

typedef struct LineNumberTable {
  uint16_t start_pc;
  uint16_t line_number;
} line_number_table;

/*! Detailed description after the member \brief ALO */
typedef struct attribute_info {
  uint16_t attribute_name_index;          /*!< Detailed description after the member */
  uint32_t attribute_length;              /*!< Detailed description after the member */
  union {
    struct { 
      uint8_t constantvalue_index;;       /*!< Detailed description after the member */
    } ConstantValue;                      /*!< Detailed description after the member */
    struct {  
      uint16_t number_of_exceptions;      /*!< Detailed description after the member */
      uint16_t* exception_index_table;    /*!< Detailed description after the member */
    } Exceptions;  /*!< Detailed description after the member */
    struct {
      uint16_t max_stack;
      uint16_t max_locals;
      uint32_t code_length;
      uint8_t* code;
      uint16_t exception_table_length;
      exception_table *exception_table_array;
      uint16_t attributes_count;
      struct attribute_info* attributes;
    } Code;
    struct {

    } Deprecated;

    struct {
      uint16_t line_number_table_length;
      line_number_table *line_number_table_array;
    } LineNumberTable; 
  } att_info;      /*!< Detailed description after the member */
  
} attribute_info;

/*! Detailed description after the member \brief ALO */
typedef struct field_info {
  uint16_t access_flags;       /*!< Detailed description after the member */
  uint16_t name_index;         /*!< Detailed description after the member */
  uint16_t descriptor_index;   /*!< Detailed description after the member */
  uint16_t attributes_count;   /*!< Detailed description after the member */
  attribute_info* attributes;  /*!< Detailed description after the member */
} field_info;               

/*! Detailed description after the member \brief ALO */
typedef struct method_info{           
  uint16_t access_flags;              /*!< Detailed description after the member */
  uint16_t name_index;                /*!< Detailed description after the member */
  uint16_t descriptor_index;          /*!< Detailed description after the member */
  uint16_t attributes_count;          /*!< Detailed description after the member */
  attribute_info* attributes;         /*!< Detailed description after the member */
} method_info;                        


/*! \brief A estrutura de um classFile 
 *         em bytes (8-bits).
 *
 * A estrutura de um classFile 
 * baseado em bytes de 8-bits. Todos os 16-bit, 32-bit, 
 * e 64-bit sao construidos por leituras de dois, 
 * quatro, e oito bytes (8bits) consecutivos. 
 * Dados de multibyte sao armazenados em ordem big-endian, 
 * onde o high-byte vem primeiro.
 */
typedef struct classFile {           
  uint32_t magic;                     /*!< \brief Magic fornece o 'numero magico' que intentifica
                                          o formato classfile e tem valor 0xCAFEBABE */
  uint16_t minor_version;             /*!< \brief Minor version do classfile denotado como 'm' em M.m */
  uint16_t major_version;             /*!< \brief Majot version do classfile denotado como 'M' em M.m */
  uint16_t constant_pool_count;       /*!< \brief Numero de entradas em constant_pool mais um */
  cp_info* constant_pool;             /*!< \brief Tábela de estruturas */
  uint16_t access_flags;              /*!< \brief Flags usadas para denotar permissoes e propriedades da classe */
  uint16_t this_class;                /*!< \brief Valor que corresponde a um index valido na constant_pool */
  uint16_t super_class;               /*!< \brief Valor que corresponde a 0 ou um index valido na constant_pool */
  uint16_t interfaces_count;          /*!< \brief Numero de interfaces e superinterfaces da classe */
  uint16_t* interfaces;               /*!< \brief Valor que corresponde a um index valido na constant_pool*/
  uint16_t fields_count;              /*!< \brief Numero de estruturas fields na tabela de fields*/
  field_info* fields;                 /*!< \brief Descricao de um field desta classe */
  uint16_t methods_count;             /*!< \brief Numero de estruturas methods na tabela de methods */
  method_info* methods;               /*!< \brief Descricao de um method desta classe */
  uint16_t attributes_count;          /*!< \brief Numero de estruturas attributes na tabela de attributes */
  attribute_info* attributes;         /*!< \brief Aributos da descritos pela tabela do classfile*/
} classFile;                          

/* Function headers */
uint8_t read1byte(FILE* fp);                /*!< \brief Lê um byte (8bits) de um arquivo. */
uint16_t read2bytes(FILE* fp);              /*!< \brief Lê dois bytes (16bits) de um arquivo. */
uint32_t read4bytes(FILE* fp);              /*!< \brief Lê quatro bytes (32bits) de um arquivo. */
classFile* classReader(char * className);   /*!< \brief O método classReader(arg*) é responsavel
                                                        por ler e carregar em memoria as informacoes 
                                                        do classfile */

#endif