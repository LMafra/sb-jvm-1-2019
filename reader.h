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
typedef struct CPInfo {                    
  uint8_t tag;                        /*!< \brief Valor de um byte que indica o tipo de entrada*/
  union Info{
    struct Class{ 
      uint16_t name_index;            /*!< \brief Um item valido da tabela constant_pool */
    } Class;                          /*!< Class
                                      Detailed description after the member
                                      \brief um index valido da constant_pool . */                       
    struct FieldRef{  
      uint16_t class_index;           /*!< represanta a classe ou a interface */
      uint16_t name_and_type_index;   /*!< indica nome e descritor do field ou method */
    } Fieldref;                       /*!< \brief  */

    struct MethodRef{   
      uint16_t class_index;           /*!< represanta a classe ou a interface */
      uint16_t name_and_type_index;   /*!< indica nome e descritor do field ou method */
    } Methodref;                      /*!< Methodref 
                                      Detailed description after the member
                                      \brief  */
    struct InterfaceMethodRef{  
      uint16_t class_index;           /*!< represanta a classe ou a interface */
      uint16_t name_and_type_index;   /*!< indica nome e descritor do field ou method */
    } InterfaceMethodref;             /*!< \struct InterfaceMethodref
                                      Detailed description after the member
                                      \brief ALO*/
    struct String{  
      uint16_t string_index;          /*!< representa a sequencia de unicode em que a string sera inicializada */
    } String;                         /*! \struct String 
                                      Detailed description after the member
                                      \brief representa objetos contantes do tipo string */
    struct Integer{  
      uint32_t bytes;                 /*!< representa o valor do int*/
    } Integer;                        /*! \struct Integer
                                      Detailed description after the member
                                      \brief representa numericos de 4-bytes */
    struct Float{  
      uint32_t bytes;                 /*!< representa o valor do float em formato IEEE 754 */
    } Float;                          /*! \struct Float 
                                      Detailed description after the member
                                      \brief representa numericos de 4-bytes */
    struct Long{  
      uint32_t high_bytes;            /*!< \var representa uma parte do long e soma-se ao low_byte para representa-lo */
      uint32_t low_bytes;             /*!< \var Detailed representa uma parte do long e soma-se ao high_byte para representa-lo */
    } Long;                           /*! \struct Long Detailed
                                      Detailed description after the member
                                      \brief representa numericos de 8-bytes*/
    struct Double{ 
      uint32_t high_bytes;            /*!< representa uma parte do double e soma-se ao low_byte para representalo */
      uint32_t low_bytes;             /*!< representa uma parte do double e soma-se ao low_byte para representalor */
    } Double;                         /*! \struct Double
                                      Detailed description after the member
                                      \brief representa numericos de 8-bytes*/
    struct NameAndType{  
      uint16_t name_index;            /*!< Um item valido da tabela constant_pool */
      uint16_t descriptor_index;      /*!< um descritor de field ou method valido */
    } NameAndType;                    /*! \struct NameAndType
                                      Detailed description after the member
                                      \brief usando para representar um field ou method sem indicar uma classe ou interface*/
    struct Utf8{  
      uint16_t length;                /*!< o tamanho do array de byte */
      uint8_t* bytes;                 /*!< os bytes da string */
    } Utf8;                           /*! \struct Utf8
                                      Detailed description after the member
                                      \brief representar valores constantes de string*/
    struct MethodHandle{ 
      uint8_t reference_kind;         /*!< o tipo do methodhanlder */
      uint16_t reference_index;       /*!< endtrada da constant_pool */
    } MethodHandle;                   /*! \struct MethodHandle
                                      Detailed description after the member
                                      \brief */
    struct MethodType{  
      uint16_t descriptor_index;      /*!< representa o descritor do metodo */
    } MethodType;                     /*! \struct MethodType
                                      Detailed description after the member
                                      \brief representa um tipo de metodo*/
    struct InvokeDynamic{  
      uint16_t bootstrap_method_attr_index;  /*!< item valido da tabela de boostrap */
      uint16_t name_and_type_index;          /*!< representa o nome e o tipo do descritor */
    } InvokeDynamic;                         /*!< \struct InvokeDynamic
                                              Detailed description after the member
                                              \brief usado para indicar o metodo de boostrap*/            
  } info; /*!< \brief Tipo de dado retornado pela union*/
} cp_info;

typedef struct ExceptionTableStruct {
  uint16_t start_pc;
  uint16_t end_pc;
  uint16_t handler_pc;
  uint16_t catch_type;
} exception_table;

typedef struct LineNumberTableStruct {
  uint16_t start_pc;
  uint16_t line_number;
} line_number_table;

typedef struct LocalVariableTableStruct {
  uint16_t start_pc;
  uint16_t length;
  uint16_t name_index;
  uint16_t descriptor_index;
  uint16_t index;
} local_variable_table;


typedef struct InnerClassesStruct {
  uint16_t inner_class_info_index;
  uint16_t outer_class_info_index;
  uint16_t inner_name_index;
  uint16_t inner_class_access_flags;
} inner_classes;

typedef struct BootstrapMethodsStruct {
  uint16_t bootstrap_method_ref;
  uint16_t num_bootstrap_arguments;
  uint16_t* bootstrap_arguments;
} bootstrap_methods;

typedef struct VerificationTypeInfo{
  uint8_t tag;
  union VerificationType{
    struct TopVariableInfo{
      /* 0 */
    } Top_variable_info;
    struct IntegerVariableInfo{
      /* 1 */
    } Integer_variable_info;
    struct FloatVariableInfo{
      /* 2 */
    } Float_variable_info;
    struct DoubleVariableInfo{
      /* 3 */
    } Double_variable_info;
    struct LongVariableInfo{
      /* 4 */
    } Long_variable_info;
    struct NullVariableInfo{
      /* 5 */
    } Null_variable_info;
    struct UninitializedThisVariableInfo{
      /* 6 */
    } UninitializedThis_variable_info;
    struct ObjectVariableInfo{
      /* 7 */
      uint16_t cpool_index;
    } Object_variable_info;
    struct UninitializedVariableInfo{
      /* 8 */
      uint16_t offset;
    } Uninitialized_variable_info;
  }verification_type;
} verification_type_info;

/*! \brief Usado pela StackMapTable 
*   
*
*  especifica o bytecode offset que aplica, 
* e o tipo de verificacao das variaveis locais e pilha de operandos.
* 
*/
typedef struct StackMapFrame{
    uint8_t frame_type; 
    union MapFrameType{   
      struct SameFrame {
        /* 0-63 */
      } same_frame;
      struct SameLocals1StackItemFrame {
        /* 64-127 */
        verification_type_info *stack; /* 1 */
      } same_locals_1_stack_item_frame;
      struct SameLocals1StackItemFrameExtended {
        /* 247 */
        uint16_t offset_delta;
        verification_type_info *stack; /* 1 */
      } same_locals_1_stack_item_frame_extended;
      struct ChopFrame{
           /* 248-250 */
        uint16_t offset_delta;
      } chop_frame;
      struct SameFrameExtended{
        /* 251 */
        uint16_t offset_delta;
      } same_frame_extended;
      struct AppendFrame{
        /* 252-254 */
        uint16_t offset_delta;
        verification_type_info *locals; /* frame_type - 251 */
      } append_frame;
      struct FullFrame {
        /* 255 */
        uint16_t offset_delta;
        uint16_t number_of_locals;
        verification_type_info *locals;
        uint16_t number_of_stack_items;
        verification_type_info *stack;
      } full_frame;
    } map_frame_type;
} stack_map_frame;

/*! Detailed description after the member \brief ALO */
typedef struct attribute_info {
  uint16_t attribute_name_index;          /*!< Detailed description after the member */
  uint32_t attribute_length;              /*!< Detailed description after the member */
  union AttInfo{
    struct ConstantValue{ 
      uint8_t constantvalue_index;;       /*!< Detailed description after the member */
    } ConstantValue;                      /*!< Detailed description after the member */
    struct Exceptions{  
      uint16_t number_of_exceptions;      /*!< Detailed description after the member */
      uint16_t* exception_index_table;    /*!< Detailed description after the member */
    } Exceptions;                         /*!< Detailed description after the member */
    struct Code{
      uint16_t max_stack;
      uint16_t max_locals;
      uint32_t code_length;
      uint8_t* code;
      uint16_t exception_table_length;
      exception_table *exception_table_array;
      uint16_t attributes_count;
      struct attribute_info* attributes;
    } Code;
    struct SourceFile{
      uint16_t sourcefile_index;
    } SourceFile; 
    struct LineNumberTable{
      uint16_t line_number_table_length;
      line_number_table *line_number_table_array;
    } LineNumberTable;
    struct LocalVariableTable{
      uint16_t local_variable_table_length;
      local_variable_table *local_variable_table_array;
    } LocalVariableTable;
    struct InnerClasses{
      uint16_t number_of_classes;
      inner_classes *classes_array;
    } InnerClasses;
    struct BootstrapMethods{
      uint16_t bootstrap_methods_length;
      bootstrap_methods* bootstrap_methods_array;
    } BootstrapMethods;
    struct StackMapTable{
      uint16_t number_of_entries;
      stack_map_frame *entries;
    } StackMapTable;
  } att_info;     /*!< Detailed description after the member */
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
typedef struct ClassFile {           
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