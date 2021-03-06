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
	cf = (classFile *)calloc(1, sizeof(classFile));

	cf->magic = read4bytes(file);

	if (cf->magic != 0xCAFEBABE) {
		printf("Invalid .class! Terminated.");
		exit(0);
	}

	/* info */
	cf->minor_version = read2bytes(file);
	cf->major_version = read2bytes(file);

  if(cf->major_version > 52) {
    printf(".class with invalid version. Terminated.");
    exit(0);
  }

	/* constant pool */
	cf->constant_pool_count = read2bytes(file);
	cf->constant_pool = (cp_info* ) calloc((cf->constant_pool_count-1), sizeof(cp_info));
	cp_info* cp = cf->constant_pool;

	for(int i = 0; i < cf->constant_pool_count-1; i++) { 
		cp[i].tag = read1byte(file);
		switch (cp[i].tag) {
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
				cp[i].info.Utf8.bytes = (uint8_t* )calloc((cp[i].info.Utf8.length+1), sizeof(uint8_t));
				uint8_t* bt = cp[i].info.Utf8.bytes;
				for(int j = 0; j < cp[i].info.Utf8.length; j++, bt++) {
					*bt = getc(file);
				}
				bt = '\0';
				break;
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
  cf->interfaces = (uint16_t* )calloc(cf->interfaces_count, sizeof(uint16_t));
  for (int i = 0; i < cf->interfaces_count; i++) {
    cf->interfaces[i] = read2bytes(file);
  }

	/* fields */
	cf->fields_count = read2bytes(file);
  cf->fields = (field_info* )calloc(cf->fields_count, sizeof(field_info));
  field_info *fi = cf->fields;
  for(int i = 0; i < cf->fields_count; i++) {
    fi[i].access_flags = read2bytes(file);
    fi[i].name_index = read2bytes(file);
    fi[i].descriptor_index = read2bytes(file);

    fi[i].attributes_count = read2bytes(file);
    fi[i].attributes = (attribute_info* )calloc(fi[i].attributes_count, sizeof(attribute_info));
    attribute_info *fi_ai = fi[i].attributes;
    for(int j = 0; j < fi[i].attributes_count; j++) {
      fi_ai[j].attribute_name_index = read2bytes(file);
      fi_ai[j].attribute_length = read4bytes(file);
      
      uint16_t cp_index = fi_ai[j].attribute_name_index - 1;
      if (strcmp((char*)cf->constant_pool[cp_index].info.Utf8.bytes, "ConstantValue")) {
        fi_ai[j].att_info.ConstantValue.constantvalue_index = read1byte(file);
      } else { // le o espaço de um atributo não implementado
				for (int w = 0; w < fi_ai[j].attribute_length; w++) read1byte(file);
			}
    }
  }

	/* methods */
	cf->methods_count = read2bytes(file);
  cf->methods = (method_info* )calloc(cf->methods_count, sizeof(method_info));
  method_info *mi = cf->methods;
  for(int i = 0; i < cf->methods_count; i++){
    mi[i].access_flags = read2bytes(file);
    mi[i].name_index = read2bytes(file);
    mi[i].descriptor_index = read2bytes(file);
    mi[i].attributes_count = read2bytes(file);
    mi[i].attributes = (attribute_info* )calloc(mi[i].attributes_count, sizeof(attribute_info));
    attribute_info *mi_ai = mi[i].attributes;
    for(int j = 0; j < mi[i].attributes_count; j++) {
      mi_ai[j].attribute_name_index = read2bytes(file);
      mi_ai[j].attribute_length = read4bytes(file);
      uint16_t cp_index = mi_ai[j].attribute_name_index - 1;
			if (!strcmp((char*)cf->constant_pool[cp_index].info.Utf8.bytes, "Code")) {
        mi_ai[j].att_info.Code.max_stack = read2bytes(file);
        mi_ai[j].att_info.Code.max_locals = read2bytes(file);
        mi_ai[j].att_info.Code.code_length = read4bytes(file);
        mi_ai[j].att_info.Code.code = (uint8_t*) calloc(mi_ai[j].att_info.Code.code_length, sizeof(uint8_t));
        for (int k = 0; k < mi_ai[j].att_info.Code.code_length; k++) {
          mi_ai[j].att_info.Code.code[k] = read1byte(file);
        }
        mi_ai[j].att_info.Code.exception_table_length = read2bytes(file);
        mi_ai[j].att_info.Code.exception_table_array = (exception_table*) calloc(mi_ai[j].att_info.Code.exception_table_length, sizeof(exception_table));
        for(int k = 0; k < mi_ai[j].att_info.Code.exception_table_length; k++) {
          mi_ai[j].att_info.Code.exception_table_array[k].start_pc = read2bytes(file);
          mi_ai[j].att_info.Code.exception_table_array[k].end_pc = read2bytes(file);
          mi_ai[j].att_info.Code.exception_table_array[k].handler_pc = read2bytes(file);
          mi_ai[j].att_info.Code.exception_table_array[k].catch_type = read2bytes(file);
        }
        mi_ai[j].att_info.Code.attributes_count = read2bytes(file);
        mi_ai[j].att_info.Code.attributes = (attribute_info *)calloc(mi_ai[j].att_info.Code.attributes_count, sizeof(attribute_info));
				for (int k = 0; k < mi_ai[j].att_info.Code.attributes_count; k++){
					mi_ai[j].att_info.Code.attributes[k].attribute_name_index = read2bytes(file);
					mi_ai[j].att_info.Code.attributes[k].attribute_length = read4bytes(file);
					uint16_t cp_indexao = mi_ai[j].att_info.Code.attributes[k].attribute_name_index - 1;
					if (!strcmp((char*)cf->constant_pool[cp_indexao].info.Utf8.bytes, "LineNumberTable")) {
						mi_ai[j].att_info.Code.attributes[k].att_info.LineNumberTable.line_number_table_length = read2bytes(file);
						mi_ai[j].att_info.Code.attributes[k].att_info.LineNumberTable.line_number_table_array = (line_number_table*)calloc(mi_ai[j].att_info.Code.attributes[k].att_info.LineNumberTable.line_number_table_length, sizeof(line_number_table));
						for(int w = 0; w < mi_ai[j].att_info.Code.attributes[k].att_info.LineNumberTable.line_number_table_length; w++) {
							mi_ai[j].att_info.Code.attributes[k].att_info.LineNumberTable.line_number_table_array[w].start_pc = read2bytes(file);
							mi_ai[j].att_info.Code.attributes[k].att_info.LineNumberTable.line_number_table_array[w].line_number = read2bytes(file);
						}
					} else if (!strcmp((char*)cf->constant_pool[cp_indexao].info.Utf8.bytes, "LocalVariableTable")) {
						mi_ai[j].att_info.Code.attributes[k].att_info.LocalVariableTable.local_variable_table_length = read2bytes(file);
						mi_ai[j].att_info.Code.attributes[k].att_info.LocalVariableTable.local_variable_table_array = (local_variable_table*)calloc(mi_ai[j].att_info.Code.attributes[k].att_info.LocalVariableTable.local_variable_table_length, sizeof(local_variable_table));
						for(int w = 0; w < mi_ai[j].att_info.Code.attributes[k].att_info.LocalVariableTable.local_variable_table_length; w++) {
							mi_ai[j].att_info.Code.attributes[k].att_info.LocalVariableTable.local_variable_table_array[w].start_pc = read2bytes(file);
							mi_ai[j].att_info.Code.attributes[k].att_info.LocalVariableTable.local_variable_table_array[w].length = read2bytes(file);
							mi_ai[j].att_info.Code.attributes[k].att_info.LocalVariableTable.local_variable_table_array[w].name_index = read2bytes(file);
							mi_ai[j].att_info.Code.attributes[k].att_info.LocalVariableTable.local_variable_table_array[w].descriptor_index = read2bytes(file);
							mi_ai[j].att_info.Code.attributes[k].att_info.LocalVariableTable.local_variable_table_array[w].index = read2bytes(file);
						}
					} else if (!strcmp((char*)cf->constant_pool[cp_indexao].info.Utf8.bytes, "StackMapTable")) {
            mi_ai[j].att_info.Code.attributes[k].att_info.StackMapTable.number_of_entries = read2bytes(file);
            mi_ai[j].att_info.Code.attributes[k].att_info.StackMapTable.entries = (stack_map_frame *)calloc(mi_ai[j].att_info.Code.attributes[k].att_info.StackMapTable.number_of_entries, sizeof(stack_map_frame));
            stack_map_frame *smt = mi_ai[j].att_info.Code.attributes[k].att_info.StackMapTable.entries;
            for (int w = 0; w < mi_ai[j].att_info.Code.attributes[k].att_info.StackMapTable.number_of_entries; w++) {
              smt[w].frame_type = read1byte(file);
              if (smt[w].frame_type < 64) {

              } else if (smt[w].frame_type >= 64 && smt[w].frame_type <= 127) {
                smt[w].map_frame_type.same_locals_1_stack_item_frame.stack = (verification_type_info *)calloc(1,sizeof(verification_type_info));
                verification_type_info *vti = smt[w].map_frame_type.same_locals_1_stack_item_frame.stack;
                vti[0].tag = read1byte(file);
                if (vti[0].tag == 7) {
                  vti[0].verification_type.Object_variable_info.cpool_index = read2bytes(file);
                } else if (vti[0].tag == 8) {
                  vti[0].verification_type.Uninitialized_variable_info.offset = read2bytes(file);
                }
              } else if (smt[w].frame_type == 247) {
                smt[w].map_frame_type.same_locals_1_stack_item_frame_extended.offset_delta = read2bytes(file);
                smt[w].map_frame_type.same_locals_1_stack_item_frame_extended.stack = (verification_type_info *)calloc(1,sizeof(verification_type_info));
                verification_type_info *vti = smt[w].map_frame_type.same_locals_1_stack_item_frame_extended.stack;
                vti[0].tag = read1byte(file);
                if (vti[0].tag == 7) {
                  vti[0].verification_type.Object_variable_info.cpool_index = read2bytes(file);
                } else if (vti[0].tag == 8) {
                  vti[0].verification_type.Uninitialized_variable_info.offset = read2bytes(file);
                }
              } else if (smt[w].frame_type >= 248 && smt[w].frame_type <= 250 ) {
								smt[w].map_frame_type.chop_frame.offset_delta = read2bytes(file);
              } else if (smt[w].frame_type == 251 ) {
								smt[w].map_frame_type.same_frame_extended.offset_delta = read2bytes(file);
              } else if (smt[w].frame_type >= 252 && smt[w].frame_type <= 254) {
								smt[w].map_frame_type.append_frame.offset_delta = read2bytes(file);
								smt[w].map_frame_type.append_frame.locals = (verification_type_info *)calloc(smt[w].frame_type - 251,sizeof(verification_type_info));
                verification_type_info *vti = smt[w].map_frame_type.append_frame.locals;
								for (int y = 0; y < smt[w].frame_type - 251; y++){
									vti[y].tag = read1byte(file);
                  if (vti[y].tag == 7) {
                    vti[y].verification_type.Object_variable_info.cpool_index = read2bytes(file);
                  } else if (vti[y].tag == 8) {
                    vti[y].verification_type.Uninitialized_variable_info.offset = read2bytes(file);
                  }
								}

              } else if (smt[w].frame_type == 255) {
                smt[w].map_frame_type.full_frame.offset_delta = read2bytes(file);
                smt[w].map_frame_type.full_frame.number_of_locals = read2bytes(file);
                smt[w].map_frame_type.full_frame.locals = (verification_type_info *)calloc(smt[w].map_frame_type.full_frame.number_of_locals, sizeof(verification_type_info));
                verification_type_info *vti_loc = smt[w].map_frame_type.full_frame.locals;
                for (int y = 0; y < smt[w].map_frame_type.full_frame.number_of_locals; y++) {
                  vti_loc[y].tag = read1byte(file);
                  if (vti_loc[y].tag == 7) {
                    vti_loc[y].verification_type.Object_variable_info.cpool_index = read2bytes(file);
                  } else if (vti_loc[y].tag == 8) {
                    vti_loc[y].verification_type.Uninitialized_variable_info.offset = read2bytes(file);
                  }
                }
                smt[w].map_frame_type.full_frame.number_of_stack_items = read2bytes(file);
                smt[w].map_frame_type.full_frame.stack = (verification_type_info *)calloc(smt[w].map_frame_type.full_frame.number_of_stack_items, sizeof(verification_type_info));
                verification_type_info *vti_stk = smt[w].map_frame_type.full_frame.stack;
                for (int y = 0; y < smt[w].map_frame_type.full_frame.number_of_stack_items; y++) {
                  vti_stk[y].tag = read1byte(file);
                  if (vti_stk[y].tag == 7) {
                    vti_stk[y].verification_type.Object_variable_info.cpool_index = read2bytes(file);
                  } else if (vti_stk[y].tag == 8) {
                    vti_stk[y].verification_type.Uninitialized_variable_info.offset = read2bytes(file);
                  }
                }
              }
            }
          } else { // le o espaço de um atributo não implementado
						for (int w = 0; w < mi_ai[j].att_info.Code.attributes[k].attribute_length; w++) read1byte(file);
					}
				}
      } else if (!strcmp((char*)cf->constant_pool[cp_index].info.Utf8.bytes, "Exceptions")) {
        mi_ai[j].att_info.Exceptions.number_of_exceptions = read2bytes(file);
        mi_ai[j].att_info.Exceptions.exception_index_table = (uint16_t *)calloc(mi_ai[j].att_info.Exceptions.number_of_exceptions, sizeof(uint16_t));
        for (int k = 0; k < mi_ai[j].att_info.Exceptions.number_of_exceptions; k++) {
          mi_ai[j].att_info.Exceptions.exception_index_table[k] = read2bytes(file);
        }
      } else { // le o espaço de um atributo não implementado
				for (int w = 0; w < mi_ai[j].attribute_length; w++) read1byte(file);
			}
    }
  }

	/* attributes */
  cf->attributes_count = read2bytes(file);
  cf->attributes = (attribute_info *)calloc(cf->attributes_count, sizeof(attribute_info));
  attribute_info *ai = cf->attributes;
  for (int i = 0; i < cf->attributes_count; i++) {
    ai[i].attribute_name_index = read2bytes(file);
    ai[i].attribute_length = read4bytes(file);
    uint16_t cp_index = ai[i].attribute_name_index - 1;
    if (!strcmp((char*)cf->constant_pool[cp_index].info.Utf8.bytes, "BootstrapMethods")) {
			ai[i].att_info.BootstrapMethods.bootstrap_methods_length = read2bytes(file);
			ai[i].att_info.BootstrapMethods.bootstrap_methods_array = (bootstrap_methods *)calloc(ai[i].att_info.BootstrapMethods.bootstrap_methods_length, sizeof(bootstrap_methods));
			bootstrap_methods *ai_bm = ai[i].att_info.BootstrapMethods.bootstrap_methods_array;
			for (int j = 0; j < ai[i].att_info.BootstrapMethods.bootstrap_methods_length; j++){
				ai_bm[j].bootstrap_method_ref = read2bytes(file);
				ai_bm[j].num_bootstrap_arguments = read2bytes(file);
				ai_bm[j].bootstrap_arguments = (uint16_t*) calloc(ai_bm[j].num_bootstrap_arguments, sizeof(uint16_t));
        for (int k = 0; k < ai_bm[j].num_bootstrap_arguments; k++) {
          ai_bm[j].bootstrap_arguments[k] = read2bytes(file);
        }
			}
		} else if (!strcmp((char*)cf->constant_pool[cp_index].info.Utf8.bytes, "SourceFile")) {
      ai[i].att_info.SourceFile.sourcefile_index = read2bytes(file);
    } else if (!strcmp((char*)cf->constant_pool[cp_index].info.Utf8.bytes, "InnerClasses")) {
      ai[i].att_info.InnerClasses.number_of_classes = read2bytes(file);
      ai[i].att_info.InnerClasses.classes_array = (inner_classes *)calloc(ai[i].att_info.InnerClasses.number_of_classes, sizeof(inner_classes));
      inner_classes *ai_ic = ai[i].att_info.InnerClasses.classes_array;
      for(int j = 0; j < ai[i].att_info.InnerClasses.number_of_classes; j++){
        ai_ic[j].inner_class_info_index = read2bytes(file);
        ai_ic[j].outer_class_info_index = read2bytes(file);
        ai_ic[j].inner_name_index = read2bytes(file);
        ai_ic[j].inner_class_access_flags = read2bytes(file);
      }
    } else { // le o espaço de um atributo não implementado
      for (int w = 0; w < ai[i].attribute_length; w++) read1byte(file);
    }
  }
  
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
