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
* @brief Responsavel por ler o .class e 
*        montar as estruturas. \n
* @section DESCRIPTION
*/

#include "reader.h"

classFile* classReader(char * className) {  /*! O método classReader(arg*) é responsavel
por ler e carregar em memoria as informacoes do classfile. A leitura é por blocos de bytes
que sao percorridos pelas funcoes read1byte(arg*), read2bytes(arg*) e read4bytes(arg*) e sem seguida 
carregados em memoria por alocamento da estrutura abstrata cf. */
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
    field_info fi = cf->fields[i];
    fi.access_flags = read2bytes(file);
    fi.name_index = read2bytes(file);
    fi.descriptor_index = read2bytes(file);

    fi.attributes_count = read2bytes(file);
    fi.attributes = (attribute_info* )malloc(fi.attributes_count * sizeof(attribute_info));
    for(int j = 0; j < fi.attributes_count; j++) {
      attribute_info fi_ai = fi.attributes[j];
      fi_ai.attribute_name_index = read2bytes(file);
      fi_ai.attribute_length = read4bytes(file);
      
      uint16_t cp_index = fi_ai.attribute_name_index - 1; 
      if (strcmp((char*)cf->constant_pool[cp_index].info.Utf8.bytes, "ConstantValue")) {
        fi_ai.att_info.ConstantValue.constantvalue_index = read1byte(file);
      } else if (!strcmp((char*)cf->constant_pool[cp_index].info.Utf8.bytes, "Deprecated")) {
        printf("Deprecated\n");
      }
    }
  }

	/* methods */
	cf->methods_count = read2bytes(file);
  cf->methods = (method_info* )malloc(cf->methods_count * sizeof(method_info));
  method_info *mi = cf->methods;
  for(int i = 0; i < 1; i++){
    mi[i].access_flags = read2bytes(file);
    mi[i].name_index = read2bytes(file);
    mi[i].descriptor_index = read2bytes(file);
    mi[i].attributes_count = read2bytes(file);
    printf("WWW attribute_count: %d\n", mi[i].attributes_count);
    mi[i].attributes = (attribute_info* )malloc(mi[i].attributes_count * sizeof(attribute_info));
    attribute_info *mi_ai = mi[i].attributes;
    for(int j = 0; j < 1; j++) {
      mi_ai[j].attribute_name_index = read2bytes(file);
      printf("WWW attribute_name_index: %d\n", mi_ai[j].attribute_name_index);
      mi_ai[j].attribute_length = read4bytes(file);
      uint16_t cp_index = mi_ai[j].attribute_name_index - 1;
			printf("Resultado strcmp %d\n", strcmp((char*)cf->constant_pool[cp_index].info.Utf8.bytes, "Code"));
			if (!strcmp((char*)cf->constant_pool[cp_index].info.Utf8.bytes, "Code")) {
        mi_ai[j].att_info.Code.max_stack = read2bytes(file);
        mi_ai[j].att_info.Code.max_locals = read2bytes(file);
        mi_ai[j].att_info.Code.code_length = read4bytes(file);
        mi_ai[j].att_info.Code.code = (uint8_t*) malloc(mi_ai[j].att_info.Code.code_length * sizeof(uint8_t));
        for (int k = 0; k < mi_ai[j].att_info.Code.code_length; k++) {
          mi_ai[j].att_info.Code.code[k] = read1byte(file);
        }
        mi_ai[j].att_info.Code.exception_table_length = read2bytes(file);
        mi_ai[j].att_info.Code.exception_table_array = (exception_table*) malloc(mi_ai[j].att_info.Code.exception_table_length * sizeof(exception_table));
        for(int k = 0; k < mi_ai[j].att_info.Code.exception_table_length; k++) {
          mi_ai[j].att_info.Code.exception_table_array[k].start_pc = read2bytes(file);
          mi_ai[j].att_info.Code.exception_table_array[k].end_pc = read2bytes(file);
          mi_ai[j].att_info.Code.exception_table_array[k].handler_pc = read2bytes(file);
          mi_ai[j].att_info.Code.exception_table_array[k].catch_type = read2bytes(file);
        }
        mi_ai[j].att_info.Code.attributes_count = read2bytes(file);
        mi_ai[j].att_info.Code.attributes = (attribute_info *)malloc(mi_ai[j].att_info.Code.attributes_count * sizeof(attribute_info));
				for (int k = 0; k < mi_ai[j].att_info.Code.attributes_count; k++){
					mi_ai[j].att_info.Code.attributes[k].attribute_name_index = read2bytes(file);
					printf("%d", mi_ai[j].att_info.Code.attributes[k].attribute_name_index);
					mi_ai[j].att_info.Code.attributes[k].attribute_length = read4bytes(file);
					uint16_t cp_indexao = mi_ai[j].att_info.Code.attributes[k].attribute_name_index - 1;
					printf("cp_index = %u .", cp_indexao);
					if (!strcmp((char*)cf->constant_pool[cp_indexao].info.Utf8.bytes, "LineNumberTable")) {
						mi_ai[j].att_info.Code.attributes[k].att_info.LineNumberTable.line_number_table_length = read2bytes(file);
						printf("%d\n", mi_ai[j].att_info.Code.attributes[k].att_info.LineNumberTable.line_number_table_length);
						mi_ai[j].att_info.Code.attributes[k].att_info.LineNumberTable.line_number_table_array = (line_number_table*)malloc(mi_ai[j].att_info.Code.attributes[k].att_info.LineNumberTable.line_number_table_length * sizeof(line_number_table));
						for(int w = 0; w < mi_ai[j].att_info.Code.attributes[k].att_info.LineNumberTable.line_number_table_length; w++) {
							mi_ai[j].att_info.Code.attributes[k].att_info.LineNumberTable.line_number_table_array[w].start_pc = read2bytes(file);
							printf("start_pc %d\n", mi_ai[j].att_info.Code.attributes[k].att_info.LineNumberTable.line_number_table_array[w].start_pc);
							mi_ai[j].att_info.Code.attributes[k].att_info.LineNumberTable.line_number_table_array[w].line_number = read2bytes(file);
							printf("line_number %d\n", mi_ai[j].att_info.Code.attributes[k].att_info.LineNumberTable.line_number_table_array[w].line_number);
						}
					}
				}
      } else if (!strcmp((char*)cf->constant_pool[cp_index].info.Utf8.bytes, "Exceptions")) {
        mi_ai[j].att_info.Exceptions.number_of_exceptions = read2bytes(file);
        mi_ai[j].att_info.Exceptions.exception_index_table = (uint16_t *)malloc(mi_ai[j].att_info.Exceptions.number_of_exceptions * sizeof(uint16_t));
        for (int k = 0; k < mi_ai[j].att_info.Exceptions.number_of_exceptions; k++) {
          mi_ai[j].att_info.Exceptions.exception_index_table[k] = read2bytes(file);
        }
      } else if (!strcmp((char*)cf->constant_pool[cp_index].info.Utf8.bytes, "Deprecated")) {
				printf("Deprecated\n");
      }
    }
  }

	/* attributes */
  // cf->attributes_count = read2bytes(file);
  // cf->attributes = (attribute_info *)malloc(cf->attributes_count * sizeof(attribute_info));
  // for (int i = 0; i < cf->attributes_count; i++) {
  //   attribute_info ai = cf->attributes[i];
  //   ai.attribute_name_index = read2bytes(file);
  //   ai.attribute_length = read4bytes(file);
  //   uint16_t cp_index = ai.attribute_name_index - 1;
  //   if (!strcmp((char*)cf->constant_pool[cp_index].info.Utf8.bytes, "Deprecated")) {
  //     printf("Deprecated\n");
  //   }
  // }
  
	fclose(file);
	return cf;
}

uint8_t read1byte(FILE * file) {  /*!< Usa a funcao getc para ler um byte de um arquivo  */
  uint8_t data = getc(file);
  return data;
}

/* Precisa ser assim porque é big-endian */
uint16_t read2bytes(FILE * file) {    /*! Usa a funcao getc para ler dois bytes de 
                                       um arquivo, por meio de um right-shift para a 
                                       leitura do segundo byte */
  uint16_t data = getc(file);       
  data = (data << 8) | (getc(file)); 
  return data;
}

/* Precisa ser assim porque é big-endian */
uint32_t read4bytes(FILE * file) {  /*! Usa a funcao getc para ler quatro bytes de
                                       um arquivo por meio de um right-shift para a
                                       leitura do segundo, terceiro e quarto byte */
  uint32_t data = getc(file);
  data = (data << 8) | (getc(file));
  data = (data << 8) | (getc(file));
  data = (data << 8) | (getc(file));
  return data;
}
