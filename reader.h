#ifndef READER_H
#define READER_H

/* Includes */
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

/* Definitions */
#define CONSTANT_Class 7
#define CONSTANT_Fieldref 9
#define CONSTANT_Methodref 10
#define CONSTANT_InterfaceMethodref 11
#define CONSTANT_String 8
#define CONSTANT_Integer 3
#define CONSTANT_Float 4
#define CONSTANT_Long 5
#define CONSTANT_Double 6
#define CONSTANT_NameAndType 12
#define CONSTANT_Utf8 1
#define CONSTANT_MethodHandle 15
#define CONSTANT_MethodType 16
#define CONSTANT_InvokeDynamic 18

/* .class Structure */
typedef struct cp_info {
  uint8_t tag;
  union{
    struct {
      uint16_t name_index;
    } Class;
    struct {
      uint16_t class_index;
      uint16_t name_and_type_index;
    } Fieldref;
    struct {
      uint16_t class_index;
      uint16_t name_and_type_index;
    } Methodref;
    struct {
      uint16_t class_index;
      uint16_t name_and_type_index;
    } InterfaceMethodref;
    struct {
      uint16_t string_index;
    } String;
    struct {
      uint32_t bytes;
    } Integer;
    struct {
      uint32_t bytes;
    } Float;
    struct {
      uint32_t high_bytes;
      uint32_t low_bytes;
    } Long;
    struct {
      uint32_t high_bytes;
      uint32_t low_bytes;
    } Double;
    struct {
      uint16_t name_index;
      uint16_t descriptor_index;
    } NameAndType;
    struct {
      uint16_t length;
      uint8_t* bytes;
    } Utf8;
    struct {
      uint8_t reference_kind;
      uint16_t reference_index;
    } MethodHandle;
    struct {
      uint16_t descriptor_index;
    } MethodType;
    struct {
      uint16_t bootstrap_method_attr_index;
      uint16_t name_and_type_index;
    } InvokeDynamic;
  } info;
} cp_info;

typedef struct attribute_info {    
  uint16_t attribute_name_index;
  uint32_t attribute_length;
  uint8_t* info;
} attribute_info;

typedef struct field_info {
  uint16_t access_flags;
  uint16_t name_index;
  uint16_t descriptor_index;
  uint16_t attributes_count;
  attribute_info* attributes;
} field_info;

typedef struct exceptions_attribute {
  uint16_t attribute_name_index;
  uint32_t attribute_length;
  uint16_t number_of_exceptions;
  uint16_t* exception_index_table;
} exceptions_attribute; 

typedef struct method_info{
  uint16_t access_flags;
  uint16_t name_index;
  uint16_t descriptor_index;
  uint16_t attributes_count;
  attribute_info* attributes;
  /* não fica muito claro na doc como isso funciona */
  exceptions_attribute* exceptions;
} method_info;

typedef struct classFile {
  uint32_t magic;
  uint16_t minor_version;
  uint16_t major_version;
  uint16_t constant_pool_count;
  cp_info* constant_pool;
  uint16_t access_flags;
  uint16_t this_class;
  uint16_t super_class;
  uint16_t interfaces_count;
  uint16_t* interfaces;
  uint16_t fields_count;
  field_info* fields;
  uint16_t methods_count;
  method_info* methods;
  uint16_t attributes_count;
  attribute_info* attributes;
} classFile;

/* Function headers */
static inline uint8_t read1byte(FILE* fp);
static inline uint16_t read2bytes(FILE* fp);
static inline uint32_t read4bytes(FILE* fp);
classFile* classReader(char * className);

#endif 