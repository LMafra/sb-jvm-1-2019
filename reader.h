 /********************************************//**
 * Universidade de Brasilia
 *
 * Bruno Sanguinetti \n
 * Gabriel Vasconcelos \n
 * Leonardo de Almeida \n
 * Lucas Mafra 12/0126443 \n
 * Wladimir Gramacho \n
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

/* Definitions */
#define CONSTANT_Class 7                 /*!< Detailed description after the member */
#define CONSTANT_Fieldref 9              /*!< Detailed description after the member */
#define CONSTANT_Methodref 10            /*!< Detailed description after the member */
#define CONSTANT_InterfaceMethodref 11   /*!< Detailed description after the member */
#define CONSTANT_String 8                /*!< Detailed description after the member */
#define CONSTANT_Integer 3               /*!< Detailed description after the member */
#define CONSTANT_Float 4                 /*!< Detailed description after the member */
#define CONSTANT_Long 5                  /*!< Detailed description after the member */
#define CONSTANT_Double 6                /*!< Detailed description after the member */
#define CONSTANT_NameAndType 12          /*!< Detailed description after the member */
#define CONSTANT_Utf8 1                  /*!< Detailed description after the member */
#define CONSTANT_MethodHandle 15         /*!< Detailed description after the member */
#define CONSTANT_MethodType 16           /*!< Detailed description after the member */
#define CONSTANT_InvokeDynamic 18        /*!< Detailed description after the member */

/* .class Structure */
typedef struct cp_info {  /*!< Detailed description after the member */        
  uint8_t tag;
  union{
    struct {  /*!< Detailed description after the member */
      uint16_t name_index; /*!< Detailed description after the member */
    } Class; /*!< Detailed description after the member */
    struct {  
      uint16_t class_index; /*!< Detailed description after the member */
      uint16_t name_and_type_index; /*!< Detailed description after the member */
    } Fieldref; /*!< Detailed description after the member */
    struct {  
      uint16_t class_index;  /*!< Detailed description after the member */
      uint16_t name_and_type_index;  /*!< Detailed description after the member */
    } Methodref; /*!< \typedef Detailed description after the member */
    struct {  
      uint16_t class_index;  /*!< Detailed description after the member */
      uint16_t name_and_type_index;  /*!< Detailed description after the member */
    } InterfaceMethodref;  /*!< Detailed description after the member */
    struct {  
      uint16_t string_index;  /*!< Detailed description after the member */
    } String;  /*!< Detailed description after the member */
    struct {  
      uint32_t bytes; /*!< Detailed description after the member */
    } Integer;   /*!< Detailed description after the member */
    struct {  
      uint32_t bytes;  /*!< Detailed description after the member */
    } Float;  /*!< Detailed description after the member */
    struct {  
      uint32_t high_bytes;  /*!< Detailed description after the member */
      uint32_t low_bytes; /*!< Detailed description after the member */
    } Long;  /*!< Detailed description after the member */
    struct { 
      uint32_t high_bytes;   /*!< Detailed description after the member */
      uint32_t low_bytes;  /*!< Detailed description after the member */
    } Double;  /*!< Detailed description after the member */
    struct {  
      uint16_t name_index;   /*!< Detailed description after the member */
      uint16_t descriptor_index;  /*!< Detailed description after the member */
    } NameAndType;   /*!< Detailed description after the member */
    struct {  
      uint16_t length;  /*!< Detailed description after the member */
      uint8_t* bytes;  /*!< Detailed description after the member */
    } Utf8;  /*!< Detailed description after the member */
    struct { 
      uint8_t reference_kind; /*!< Detailed description after the member */
      uint16_t reference_index; /*!< Detailed description after the member */
    } MethodHandle;  /*!< Detailed description after the member */
    struct {  
      uint16_t descriptor_index;
    } MethodType;  /*!< Detailed description after the member */
    struct {  
      uint16_t bootstrap_method_attr_index;  /*!< Detailed description after the member */
      uint16_t name_and_type_index;  /*!< Detailed description after the member */
    } InvokeDynamic;   /*!< Detailed description after the member */
  } info; 
} cp_info;   /*!< Detailed description after the member */

typedef struct attribute_info {    /*!< Detailed description after the member */
  uint16_t attribute_name_index;   /*!< Detailed description after the member */
  uint32_t attribute_length;   /*!< Detailed description after the member */
  union {
    struct {  /*!< Detailed description after the member */
      uint8_t constantvalue_index;;  /*!< Detailed description after the member */
    } ConstantValue;   /*!< Detailed description after the member */
    struct {  /*!< Detailed description after the member */
      uint16_t number_of_exceptions;   /*!< Detailed description after the member */
      uint16_t* exception_index_table;   /*!< Detailed description after the member */
    } Exceptions;  /*!< Detailed description after the member */
  } att_info;  /*!< Detailed description after the member */
  
} attribute_info;  /*!< Detailed description after the member */

typedef struct field_info {   /*!< Detailed description after the member */
  uint16_t access_flags;   /*!< Detailed description after the member */
  uint16_t name_index;   /*!< Detailed description after the member */
  uint16_t descriptor_index;   /*!< Detailed description after the member */
  uint16_t attributes_count;   /*!< Detailed description after the member */
  attribute_info* attributes;  /*!< Detailed description after the member */
} field_info;  /*!< Detailed description after the member */

typedef struct exceptions_attribute {   /*!< Detailed description after the member */
  uint16_t attribute_name_index;   /*!< Detailed description after the member */
  uint32_t attribute_length;   /*!< Detailed description after the member */
  uint16_t number_of_exceptions;   /*!< Detailed description after the member */
  uint16_t* exception_index_table;   /*!< Detailed description after the member */
} exceptions_attribute;    /*!< Detailed description after the member */

typedef struct method_info{   /*!< Detailed description after the member */
  uint16_t access_flags;   /*!< Detailed description after the member */
  uint16_t name_index;   /*!< Detailed description after the member */
  uint16_t descriptor_index;   /*!< Detailed description after the member */
  uint16_t attributes_count;   /*!< Detailed description after the member */
  attribute_info* attributes;  /*!< Detailed description after the member */
  /* não fica muito claro na doc como isso funciona */
  exceptions_attribute* exceptions;  /*!< Detailed description after the member */
} method_info;   /*!< Detailed description after the member */

typedef struct classFile {  /*!< Detailed description after the member */
  uint32_t magic; /*!< Detailed description after the member */
  uint16_t minor_version; /*!< Detailed description after the member */
  uint16_t major_version; /*!< Detailed description after the member */
  uint16_t constant_pool_count; /*!< Detailed description after the member */
  cp_info* constant_pool; /*!< Detailed description after the member */
  uint16_t access_flags;  /*!< Detailed description after the member */
  uint16_t this_class;  /*!< Detailed description after the member */
  uint16_t super_class; /*!< Detailed description after the member */
  uint16_t interfaces_count;  /*!< Detailed description after the member */
  uint16_t* interfaces; /*!< Detailed description after the member */
  uint16_t fields_count;  /*!< Detailed description after the member */
  field_info* fields; /*!< Detailed description after the member */
  uint16_t methods_count; /*!< Detailed description after the member */
  method_info* methods; /*!< Detailed description after the member */
  uint16_t attributes_count;  /*!< Detailed description after the member */
  attribute_info* attributes; /*!< Detailed description after the member */
} classFile;   /*!< Detailed description after the member */

/* Function headers */
uint8_t read1byte(FILE* fp);  /*!< Detailed description after the member */
uint16_t read2bytes(FILE* fp);  /*!< Detailed description after the member */
uint32_t read4bytes(FILE* fp);  /*!< Detailed description after the member */
classFile* classReader(char * className); /*!< Detailed description after the member */

#endif 