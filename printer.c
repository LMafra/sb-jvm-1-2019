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
* @brief Responsavel por imprimir no terminal 
*        a estrutura do classfile lido. \n
* @section DESCRIPTION
* 
*/

#include "printer.h"
#include "reader.h"

void cpIndexReader(cp_info *cp, uint16_t cpIndex) {
		switch (cp[cpIndex-1].tag) { 
			case CONSTANT_Class:
        cpIndexReader(cp, cp[cpIndex-1].info.Class.name_index);
				break;
			case CONSTANT_Fieldref:
				cpIndexReader(cp, cp[cpIndex-1].info.Fieldref.class_index);
				cpIndexReader(cp, cp[cpIndex-1].info.Fieldref.name_and_type_index);
				break;
			case CONSTANT_Methodref:
				cpIndexReader(cp, cp[cpIndex-1].info.Methodref.class_index);
				cpIndexReader(cp, cp[cpIndex-1].info.Methodref.name_and_type_index);
				break;
			case CONSTANT_InterfaceMethodref:
				cpIndexReader(cp, cp[cpIndex-1].info.InterfaceMethodref.class_index);
				cpIndexReader(cp, cp[cpIndex-1].info.InterfaceMethodref.name_and_type_index);
				break;
			case CONSTANT_String:
				cpIndexReader(cp, cp[cpIndex-1].info.String.string_index);
				break;	
			case CONSTANT_NameAndType:
				cpIndexReader(cp, cp[cpIndex-1].info.NameAndType.name_index);
				cpIndexReader(cp, cp[cpIndex-1].info.NameAndType.descriptor_index);
				break;
			case CONSTANT_Utf8:
				printf("%s\n", (char *)cp[cpIndex-1].info.Utf8.bytes);
				break;
			case CONSTANT_MethodHandle:
				cpIndexReader(cp, cp[cpIndex-1].info.MethodHandle.reference_index);
				break;
			case CONSTANT_MethodType:
				cpIndexReader(cp, cp[cpIndex-1].info.MethodType.descriptor_index);
				break;
			case CONSTANT_InvokeDynamic:
				cpIndexReader(cp, cp[cpIndex-1].info.InvokeDynamic.bootstrap_method_attr_index);
				cpIndexReader(cp, cp[cpIndex-1].info.InvokeDynamic.name_and_type_index);
				break;
			default:
				break;
		}
}

void classPrinter( classFile* cf) { /*! Long Detailed description after the member */
  /* General Information */
  printf("# Class file Structure\n");
  printf("CAFEBABE: 0x%0x \n", cf->magic);
  printf("Minor version: %d \n", cf->minor_version);
  printf("Major version: %d \n", cf->major_version);
  printf("Constant Pool Count: %d \n", cf->constant_pool_count);

  /* Constant Pool Information */
  uint8_t tag;
  for (int i = 0; i < cf->constant_pool_count - 1; i++) {
    tag = cf->constant_pool[i].tag;
    switch (tag) {
      case CONSTANT_Class:
        printf("[%d] CONSTANT_Class_info\n", i+1);
        printf("\tname_index: #%d ", cf->constant_pool[i].info.Class.name_index);
        cpIndexReader(cf->constant_pool, cf->constant_pool[i].info.Class.name_index);
				break;
			case CONSTANT_Fieldref:
        printf("[%d] CONSTANT_Fieldref_info\n", i+1);
        printf("\tclass_index: %d ", cf->constant_pool[i].info.Fieldref.class_index);
        cpIndexReader(cf->constant_pool, cf->constant_pool[i].info.Fieldref.class_index);
        printf("\tname_and_type_index: %d ", cf->constant_pool[i].info.Fieldref.name_and_type_index);
        cpIndexReader(cf->constant_pool, cf->constant_pool[i].info.Fieldref.name_and_type_index);
				break;
			case CONSTANT_Methodref:
        printf("[%d] CONSTANT_Methodref_info\n", i+1);
        printf("\tclass_index: %d ", cf->constant_pool[i].info.Methodref.class_index);
        cpIndexReader(cf->constant_pool, cf->constant_pool[i].info.Methodref.class_index);
        printf("\tname_and_type_index: %d ", cf->constant_pool[i].info.Methodref.name_and_type_index);
        cpIndexReader(cf->constant_pool, cf->constant_pool[i].info.Methodref.name_and_type_index);
				break;
			case CONSTANT_InterfaceMethodref:
        printf("[%d] CONSTANT_InterfaceMethodref_info\n", i+1);
        printf("\tclass_index: %d ", cf->constant_pool[i].info.InterfaceMethodref.class_index);
        cpIndexReader(cf->constant_pool, cf->constant_pool[i].info.InterfaceMethodref.class_index);
        printf("\tname_and_type_index: %d ", cf->constant_pool[i].info.InterfaceMethodref.name_and_type_index);
        cpIndexReader(cf->constant_pool, cf->constant_pool[i].info.InterfaceMethodref.name_and_type_index);
				break;
			case CONSTANT_String:
        printf("[%d] CONSTANT_String_info\n", i+1);
        printf("\tstring_index: %d ", cf->constant_pool[i].info.String.string_index);
        cpIndexReader(cf->constant_pool, cf->constant_pool[i].info.String.string_index);
				break;	
			case CONSTANT_Integer:
        printf("[%d] CONSTANT_Integer_info\n", i+1);
        printf("\tbytes: %d", cf->constant_pool[i].info.Integer.bytes);
				break;
			case CONSTANT_Float:
        printf("[%d] CONSTANT_Float_info\n", i+1);
        printf("\tbytes: %d", cf->constant_pool[i].info.Float.bytes);
				break;
			case CONSTANT_Long:
        printf("[%d] CONSTANT_Long_info\n", i+1);
        printf("\thigh_bytes: %d\n", cf->constant_pool[i].info.Long.high_bytes);
        printf("\tlow_bytes: %d", cf->constant_pool[i].info.Long.low_bytes);
				break;
			case CONSTANT_Double:
        printf("[%d] CONSTANT_Double_info\n", i+1);
        printf("\thigh_bytes: %d\n", cf->constant_pool[i].info.Double.high_bytes);
        printf("\tlow_bytes: %d", cf->constant_pool[i].info.Double.low_bytes);
				break;
			case CONSTANT_NameAndType:
        printf("[%d] CONSTANT_NameAndType_info\n", i+1);
        printf("\tname_index: %d ", cf->constant_pool[i].info.NameAndType.name_index);
        cpIndexReader(cf->constant_pool, cf->constant_pool[i].info.NameAndType.name_index);
        printf("\tdescriptor_index: %d ", cf->constant_pool[i].info.NameAndType.descriptor_index);
        cpIndexReader(cf->constant_pool, cf->constant_pool[i].info.NameAndType.descriptor_index);
				break;
			case CONSTANT_Utf8:
        printf("[%d] CONSTANT_Utf8_info\n", i+1);
        printf("\tlength: %d\n", cf->constant_pool[i].info.Utf8.length);
        printf("\tbytes: %s", cf->constant_pool[i].info.Utf8.bytes);
				break;
			case CONSTANT_MethodHandle:
        printf("[%d] CONSTANT_MethodHandle_info\n", i+1);
        printf("\treference_kind: %d\n", cf->constant_pool[i].info.MethodHandle.reference_kind);
        printf("\treference_index: %d ", cf->constant_pool[i].info.MethodHandle.reference_index);
        cpIndexReader(cf->constant_pool, cf->constant_pool[i].info.MethodHandle.reference_index);
				break;
			case CONSTANT_MethodType:
        printf("[%d] CONSTANT_MethodType_info\n", i+1);
        printf("\tdescriptor_index: %d ", cf->constant_pool[i].info.MethodType.descriptor_index);
        cpIndexReader(cf->constant_pool, cf->constant_pool[i].info.MethodType.descriptor_index);
				break;
			case CONSTANT_InvokeDynamic:
        printf("[%d] CONSTANT_InvokeDynamic_info\n", i+1);
        printf("\tbootstrap_method_attr_index: %d ", cf->constant_pool[i].info.InvokeDynamic.bootstrap_method_attr_index);
        cpIndexReader(cf->constant_pool, cf->constant_pool[i].info.InvokeDynamic.bootstrap_method_attr_index);
        printf("\tname_and_type_index: %d ", cf->constant_pool[i].info.InvokeDynamic.name_and_type_index);
        cpIndexReader(cf->constant_pool, cf->constant_pool[i].info.InvokeDynamic.name_and_type_index);
				break;
			default:
				break;
    }
    printf("\n");
  }
  
  /* General Information */
  printf("----Second General Info----\n");
	printf("Access Flags: 0x%0x ", cf->access_flags);
  switch (cf->access_flags) {
    case ACC_PUBLIC:
      printf("[public]\n");
      break;  
    case ACC_FINAL:
      printf("[final]\n");
      break;  
    case ACC_SUPER:
      printf("[super]\n");
      break;  
    case ACC_INTERFACE:
      printf("[interface]\n");
      break;  
    case ACC_ABSTRACT:
      printf("[abstract]\n");
      break;  
    case ACC_SYNTHETIC:
      printf("[synthetic]\n");
      break;  
    case ACC_ANNOTATION:
      printf("[annotation]\n");
      break;  
    case ACC_ENUM:
      printf("[enum]\n");
      break;  
    default:
      printf("\n");
      break;
  }
	printf("This Class: cp_info #%d ", cf->this_class);
  cpIndexReader(cf->constant_pool, cf->this_class);
	printf("Super Class: cp_info #%d ", cf->super_class);
  cpIndexReader(cf->constant_pool, cf->super_class);

  /* Interfaces */
	printf("Interfaces Count: cp_info #%d ", cf->interfaces_count);
  cpIndexReader(cf->constant_pool, cf->interfaces_count);
  for (int i = 0; i < cf->interfaces_count; i++) {
    printf("[%d] Interface: cp_info #%d ", i+1, cf->interfaces[i]);
    cpIndexReader(cf->constant_pool, cf->interfaces[i]);
  }

  /* Fields */
	printf("Fields Count: #%d\n",cf->fields_count);  
  for (int i = 0; i < cf->fields_count; i++) {
    printf("[%d] Field:\n", i+1);
    printf("\taccess_flags: %d\n", cf->fields[i].access_flags);
    printf("\tname_index: cp_info #%d ", cf->fields[i].name_index);
    cpIndexReader(cf->constant_pool, cf->fields[i].name_index);
    printf("\tdescriptor_index: cp_info #%d ", cf->fields[i].descriptor_index);
    cpIndexReader(cf->constant_pool, cf->fields[i].descriptor_index);
    printf("\tattributes_count: %d\n", cf->fields[i].attributes_count);
    for (int j = 0; j < cf->fields->attributes_count; j++) {
      printf("\t[%d] Attribute:\n", j+1);
      printf("\t\tattribute_name_index: cp_info #%d ", cf->fields[i].attributes[j].attribute_name_index);
      cpIndexReader(cf->constant_pool, cf->fields[i].attributes[j].attribute_name_index);
      printf("\t\tattribute_length: %d\n", cf->fields[i].attributes[j].attribute_length);
      uint16_t cp_index = cf->fields[i].attributes[j].attribute_name_index;
      if (!strcmp((char*)cf->constant_pool[cp_index].info.Utf8.bytes, "ConstantValue")) {
        printf("\t\tconstantvalue_index: cp_info #%d ", cf->fields[i].attributes[j].att_info.ConstantValue.constantvalue_index);
        cpIndexReader(cf->constant_pool, cf->fields[i].attributes[j].att_info.ConstantValue.constantvalue_index);
      } else if (!strcmp((char*)cf->constant_pool[cp_index].info.Utf8.bytes, "Deprecated")) {
        printf("\t\tDeprecated\n");
      }
    }
  }

  /* Methods */
  printf("Methods Count: %d\n",cf->methods_count);
  for (int i = 0; i < cf->methods_count; i++) {
    printf("[%d] Method:\n", i+1);
    printf("\taccess_flags: %d\n", cf->methods[i].access_flags);
    printf("\tname_index: cp_info %d ", cf->methods[i].name_index);
    cpIndexReader(cf->constant_pool, cf->methods[i].name_index);
    printf("\tdescriptor_index: cp_info %d ", cf->methods[i].descriptor_index);
    cpIndexReader(cf->constant_pool, cf->methods[i].descriptor_index);
    printf("\tattributes_count: %d\n", cf->methods[i].attributes_count);
    for (int j = 0; j < cf->methods->attributes_count; j++) {
      printf("\t[%d] Attribute:\n",j+1);
      printf("\t\tattribute_name_index: cp_info #%d ", cf->methods[i].attributes[j].attribute_name_index);
      cpIndexReader(cf->constant_pool, cf->methods[i].attributes[j].attribute_name_index);
      printf("\t\tattribute_length: %d\n", cf->methods[i].attributes[j].attribute_length);
      uint16_t cp_index = cf->methods[i].attributes[j].attribute_name_index - 1;
      if (!strcmp((char*)cf->constant_pool[cp_index].info.Utf8.bytes, "Code")) {
        printf("\t\tmax_stack: %d\n", cf->methods[i].attributes[j].att_info.Code.max_stack);
        printf("\t\tmax_locals: %d\n", cf->methods[i].attributes[j].att_info.Code.max_locals);
        printf("\t\tcode_length: %d\n", cf->methods[i].attributes[j].att_info.Code.code_length);
        printf("\t\tCode:");
        for(int k = 0; k < cf->methods[i].attributes[j].att_info.Code.code_length; k++) {
          printf(" %d", cf->methods[i].attributes[j].att_info.Code.code[k]);
        }
        printf("\n");
        printf("\t\texception_table_length: %d\n", cf->methods[i].attributes[j].att_info.Code.exception_table_length);
        printf("\t\texception_table:\n");
        for (int k = 0; k < cf->methods[i].attributes[j].att_info.Code.exception_table_length; k++) {
          printf("\t\t\tstart_pc: %d\n", cf->methods[i].attributes[j].att_info.Code.exception_table_array[k].start_pc);
          printf("\t\t\tend_pc: %d\n", cf->methods[i].attributes[j].att_info.Code.exception_table_array[k].end_pc);
          printf("\t\t\thandler_pc: %d\n", cf->methods[i].attributes[j].att_info.Code.exception_table_array[k].handler_pc);
          printf("\t\t\tcatch_type: %d\n", cf->methods[i].attributes[j].att_info.Code.exception_table_array[k].catch_type);
        }
        printf("\t\tattributes_count: %d\n", cf->methods[i].attributes[j].att_info.Code.attributes_count);
        printf("\t\tattributes_count:\n");
        for (int k = 0; k < cf->methods[i].attributes[j].att_info.Code.attributes_count; k++){
          printf("\t\t\tattribute_name_index: cp_info #%d ", cf->methods[i].attributes[j].att_info.Code.attributes[k].attribute_name_index);
          cpIndexReader(cf->constant_pool, cf->methods[i].attributes[j].att_info.Code.attributes[k].attribute_name_index);
          printf("\t\t\tattribute_length: %d\n", cf->methods[i].attributes[j].att_info.Code.attributes[k].attribute_length);
					uint16_t cp_indexao = cf->methods[i].attributes[j].att_info.Code.attributes[k].attribute_name_index - 1;
					if (!strcmp((char*)cf->constant_pool[cp_indexao].info.Utf8.bytes, "LineNumberTable")) {
            printf("\t\t\tLineNumberTable:\n");
            printf("\t\t\tline_number_table_length: %d\n", cf->methods[i].attributes[j].att_info.Code.attributes[k].att_info.LineNumberTable.line_number_table_length);
						for(int w = 0; w < cf->methods[i].attributes[j].att_info.Code.attributes[k].att_info.LineNumberTable.line_number_table_length; w++) {
							printf("\t\t\t\tstart_pc %d\n", cf->methods[i].attributes[j].att_info.Code.attributes[k].att_info.LineNumberTable.line_number_table_array[w].start_pc);
							printf("\t\t\t\tline_number %d\n", cf->methods[i].attributes[j].att_info.Code.attributes[k].att_info.LineNumberTable.line_number_table_array[w].line_number);
						}
					}
				}
      } else if (!strcmp((char*)cf->constant_pool[cp_index].info.Utf8.bytes, "Exceptions")) {
        printf("\t\tnumber_of_exceptions: %d\n", cf->methods[i].attributes[j].att_info.Exceptions.number_of_exceptions);
        printf("\t\texception_index_table:\n");
        for (int k = 0; k < cf->methods[i].attributes[j].att_info.Exceptions.number_of_exceptions; k++) {
          printf("\t\t\tcp_info #%d ", cf->methods[i].attributes[j].att_info.Exceptions.exception_index_table[k]);
          cpIndexReader(cf->constant_pool, cf->methods[i].attributes[j].att_info.Exceptions.exception_index_table[k]);
        }
      } else if (!strcmp((char*)cf->constant_pool[cp_index].info.Utf8.bytes, "Deprecated")) {
        printf("\t\tDeprecated\n");
      }
    }
  }

  /* attributes */
  printf("Attributes Count: %d\n",cf->attributes_count);
  for (int i = 0; i < 1; i++) {
    printf("[%d] Attribute:\n", i+1);
    printf("\tattribute_name_index: cp_info #%d ", cf->attributes[i].attribute_name_index);
    cpIndexReader(cf->constant_pool, cf->attributes[i].attribute_name_index);
    printf("\tattribute_length: %d\n", cf->attributes[i].attribute_length);
    uint16_t cp_index = cf->attributes[i].attribute_name_index - 1;
    if (!strcmp((char*)cf->constant_pool[cp_index].info.Utf8.bytes, "Deprecated")) {
      printf("\t\tDeprecated\n");
    }
  }
}