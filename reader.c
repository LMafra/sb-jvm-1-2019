#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

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
    exceptions_attribute* exceptions; // não fica muito claro na doc como isso funciona
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

classFile* classReader(char * className) {
    
    FILE* file;
    file = fopen(className, "rb");

    if (file == NULL) {
        printf("Error opening file.\n");
        return -1;
    }

    
}

uint8_t read1byte(FILE * file) {
    uint8_t data = getc(file);
    return data;
}

uint16_t read2bytes(FILE * file) {
    uint16_t data = getc(file);
    data = (data << 8) | (getc(file));
    return data;
}

uint8_t read4bytes(FILE * file) {
    uint8_t data = getc(file);
    data = (data << 8) | (getc(file));
    data = (data << 8) | (getc(file));
    data = (data << 8) | (getc(file));
    return data;
}

