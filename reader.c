/* @file 
 * @section DESCRIPTION
 * Universidade de Brasilia
 *
 * Bruno Sanguinetti \n
 * Gabriel Vasconcelos 16/0120781 \n
 * Leonardo de Almeida \n
 * Lucas Mafra 12/0126443 \n
 * Wladimir Gramacho \n
 * 
 * Responsavel por ler o .class e 
 * montar as estruturas. \n
 *  
 */

#include "reader.h"

classFile* classReader(char * className) {
  FILE* file;
  file = fopen(className, "rb");

  if (file == NULL) {
    printf("Error opening file.\n");
    return NULL;
  }

	classFile* cf = NULL;
	cf = (classFile *)malloc (sizeof(classFile));

	cf->magic = read4bytes(file);

	if (cf->magic != 0xCAFEBABE) {
		printf("Invalid .class! Terminated.");
		exit(0);
	}

	/* info */
	cf->minor_version = read2bytes(file);
	cf->major_version = read2bytes(file);

	/* constant pool */
	cf->constant_pool_count = read2bytes(file);
	cf->constant_pool = (cp_info* ) malloc((cf->constant_pool_count-1) * sizeof(cp_info));
	cp_info* cp = cf->constant_pool;

	for(int i = 0; i < cf->constant_pool_count-1; i++) { 
		cp[i].tag = read1byte(file);
		switch (cp[i].tag) { /* adicionar checagem se constantes sao validas */
			case CONSTANT_Class:
				cp[i].info.Class.name_index = read2bytes(file);
				break;
			case CONSTANT_Fieldref:
				cp[i].info.Fieldref.class_index = read2bytes(file);
				cp[i].info.Fieldref.name_and_type_index = read2bytes(file);
				break;
			case CONSTANT_Methodref:
				cp[i].info.Methodref.class_index = read2bytes(file);
				cp[i].info.Methodref.name_and_type_index = read2bytes(file);
				break;
			case CONSTANT_InterfaceMethodref:
				cp[i].info.InterfaceMethodref.class_index = read2bytes(file);
				cp[i].info.InterfaceMethodref.name_and_type_index = read2bytes(file);
				break;
			case CONSTANT_String:
				cp[i].info.String.string_index = read2bytes(file);
				break;	
			case CONSTANT_Integer:
				cp[i].info.Integer.bytes = read4bytes(file);
				break;
			case CONSTANT_Float:
				cp[i].info.Float.bytes = read4bytes(file);
				break;
			case CONSTANT_Long:
				cp[i].info.Long.high_bytes = read4bytes(file);
				cp[i].info.Long.low_bytes = read4bytes(file);
				/* como tem o dobro do tamanho normal, ocupa duas posições no vetor */
				i++;
        break;
			case CONSTANT_Double:
				cp[i].info.Double.high_bytes = read4bytes(file);
				cp[i].info.Double.low_bytes = read4bytes(file);
				i++;
				break;
			case CONSTANT_NameAndType:
				cp[i].info.NameAndType.name_index = read2bytes(file);
				cp[i].info.NameAndType.descriptor_index = read2bytes(file);
				break;
			case CONSTANT_Utf8:
				cp[i].info.Utf8.length = read2bytes(file);
				/* +1 para adicionar o \0 na string do C */
				cp[i].info.Utf8.bytes = (uint8_t* )malloc((cp[i].info.Utf8.length+1) * sizeof(uint8_t));
				/* fiz diferente pode dar merda */
				uint8_t* bt = cp[i].info.Utf8.bytes;
				for(int j = 0; j < cp[i].info.Utf8.length; j++, bt++) {
					*bt = getc(file);
				}
				bt = '\0';
				break;
			/* essa parte nao tem no do mesquita, mas tem na documentação */
			case CONSTANT_MethodHandle:
				cp[i].info.MethodHandle.reference_kind = read1byte(file);
				cp[i].info.MethodHandle.reference_index = read2bytes(file);
				break;
			case CONSTANT_MethodType:
				cp[i].info.MethodType.descriptor_index = read2bytes(file);
				break;
			case CONSTANT_InvokeDynamic:
				cp[i].info.InvokeDynamic.bootstrap_method_attr_index = read2bytes(file);
				cp[i].info.InvokeDynamic.name_and_type_index = read2bytes(file);
				break;
			default:
				break;
		}
	}

	/* info */
	cf->access_flags = read2bytes(file);
	cf->this_class = read2bytes(file);
	cf->super_class = read2bytes(file);

	/* interfaces */
	cf->interfaces_count = read2bytes(file);
  cf->interfaces = (uint16_t* )malloc(cf->interfaces_count * sizeof(uint16_t));
  for (int i = 0; i < cf->interfaces_count; i++) {
    cf->interfaces[i] = read2bytes(file);
  }

	/* fields */
	cf->fields_count = read2bytes(file);
  cf->fields = (field_info* )malloc(cf->fields_count * sizeof(field_info));
  for(int i = 0; i < cf->fields_count; i++) {
    cf->fields[i].access_flags = read2bytes(file);
    cf->fields[i].name_index = read2bytes(file);
    cf->fields[i].descriptor_index = read2bytes(file);

    cf->fields[i].attributes_count = read2bytes(file);
    cf->fields[i].attributes = (attribute_info* )malloc(cf->fields[i].attributes_count * sizeof(attribute_info));
    for(int j = 0; j < cf->fields->attributes_count; j++) {
      cf->fields[i].attributes[j].attribute_name_index = read2bytes(file);
      cf->fields[i].attributes[j].attribute_length = read4bytes(file);
      
      uint16_t cp_index = cf->fields[i].attributes[j].attribute_name_index; 
      if (strcmp((char*)cf->constant_pool[cp_index].info.Utf8.bytes, "ConstantValue")) {
        cf->fields[i].attributes[j].att_info.ConstantValue.constantvalue_index = read1byte(file);
      } else if (strcmp((char*)cf->constant_pool[cp_index].info.Utf8.bytes, "Exceptions")) {
        cf->fields[i].attributes[j].att_info.Exceptions.number_of_exceptions = read2bytes(file);
        cf->fields[i].attributes[j].att_info.Exceptions.exception_index_table = (uint16_t *)malloc(cf->fields[i].attributes[j].att_info.Exceptions.number_of_exceptions * sizeof(uint16_t));
      }
    }
  }

	/* methods */
	cf->methods_count = read2bytes(file);
  cf->methods = (method_info* )malloc(cf->methods_count * sizeof(method_info));
  for(int i = 0; i < cf->methods_count; i++){
    cf->methods[i].access_flags = read2bytes(file);
    cf->methods[i].name_index = read2bytes(file);
    cf->methods[i].descriptor_index = read2bytes(file);
    cf->methods[i].attributes_count = read2bytes(file);
    cf->methods[i].attributes = (attribute_info* )malloc(cf->methods[i].attributes_count * sizeof(attribute_info));
    for(int j = 0; j < cf->methods->attributes_count; j++) {
      cf->methods[i].attributes[j].attribute_name_index = read2bytes(file);
      cf->methods[i].attributes[j].attribute_length = read4bytes(file);
      uint16_t cp_index = cf->methods[i].attributes[j].attribute_name_index; 
      if (strcmp((char*)cf->constant_pool[cp_index].info.Utf8.bytes, "ConstantValue")) {
        cf->methods[i].attributes[j].att_info.ConstantValue.constantvalue_index = read1byte(file);
      } else if (strcmp((char*)cf->constant_pool[cp_index].info.Utf8.bytes, "Exceptions")) {
        cf->methods[i].attributes[j].att_info.Exceptions.number_of_exceptions = read2bytes(file);
        cf->methods[i].attributes[j].att_info.Exceptions.exception_index_table = (uint16_t *)malloc(cf->methods[i].attributes[j].att_info.Exceptions.number_of_exceptions * sizeof(uint16_t));
      }
    }
  }

	/* attributes */
  cf->attributes_count = read2bytes(file);
  cf->attributes = (attribute_info *)malloc(cf->attributes_count * sizeof(attribute_info));
  for (int i = 0; i < cf->attributes_count; i++) {
    
  }
  
	fclose(file);
	return cf;
}

uint8_t read1byte(FILE * file) {
  uint8_t data = getc(file);
  return data;
}

/* Precisa ser assim porque é big-endian */
uint16_t read2bytes(FILE * file) {
  uint16_t data = getc(file);
  data = (data << 8) | (getc(file));
  return data;
}

/* Precisa ser assim porque é big-endian */
uint32_t read4bytes(FILE * file) {
  uint32_t data = getc(file);
  data = (data << 8) | (getc(file));
  data = (data << 8) | (getc(file));
  data = (data << 8) | (getc(file));
  return data;
}