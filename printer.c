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
        printf("\tname_index: %d", cf->constant_pool[i].info.Class.name_index);
        /* imprimir referencia desse index */
				break;
			case CONSTANT_Fieldref:
        printf("[%d] CONSTANT_Fieldref_info\n", i+1);
        printf("\tclass_index: %d\n", cf->constant_pool[i].info.Fieldref.class_index);
        printf("\tname_and_type_index: %d", cf->constant_pool[i].info.Fieldref.name_and_type_index);
        /* imprimir referencia desse index */
				break;
			case CONSTANT_Methodref:
        printf("[%d] CONSTANT_Methodref_info\n", i+1);
        printf("\tclass_index: %d\n", cf->constant_pool[i].info.Methodref.class_index);
        printf("\tname_and_type_index: %d", cf->constant_pool[i].info.Methodref.name_and_type_index);
        /* imprimir referencia desse index */
				break;
			case CONSTANT_InterfaceMethodref:
        printf("[%d] CONSTANT_InterfaceMethodref_info\n", i+1);
        printf("\tclass_index: %d\n", cf->constant_pool[i].info.InterfaceMethodref.class_index);
        printf("\tname_and_type_index: %d", cf->constant_pool[i].info.InterfaceMethodref.name_and_type_index);
        /* imprimir referencia desse index */
				break;
			case CONSTANT_String:
        printf("[%d] CONSTANT_String_info\n", i+1);
        printf("\tstring_index: %d", cf->constant_pool[i].info.String.string_index);
        /* imprimir referencia desse index */
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
        printf("\tname_index: %d\n", cf->constant_pool[i].info.NameAndType.name_index);
        printf("\tdescriptor_index: %d", cf->constant_pool[i].info.NameAndType.descriptor_index);
				break;
			case CONSTANT_Utf8:
        printf("[%d] CONSTANT_Utf8_info\n", i+1);
        printf("\tlength: %d\n", cf->constant_pool[i].info.Utf8.length);
        printf("\tbytes: %s", cf->constant_pool[i].info.Utf8.bytes);
				break;
			case CONSTANT_MethodHandle:
        printf("[%d] CONSTANT_MethodHandle_info\n", i+1);
        printf("\treference_kind: %d\n", cf->constant_pool[i].info.MethodHandle.reference_kind);
        printf("\treference_index: %d", cf->constant_pool[i].info.MethodHandle.reference_index);
				break;
			case CONSTANT_MethodType:
        printf("[%d] CONSTANT_MethodType_info\n", i+1);
        printf("\tdescriptor_index: %d", cf->constant_pool[i].info.MethodType.descriptor_index);
				break;
			case CONSTANT_InvokeDynamic:
        printf("[%d] CONSTANT_InvokeDynamic_info\n", i+1);
        printf("\tbootstrap_method_attr_index: %d\n", cf->constant_pool[i].info.InvokeDynamic.bootstrap_method_attr_index);
        printf("\tname_and_type_index: %d", cf->constant_pool[i].info.InvokeDynamic.name_and_type_index);
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
	printf("This Class: cp_info #%d\n", cf->this_class);
	printf("Super Class: cp_info #%d\n", cf->super_class);

  /* Interfaces */
	printf("Interfaces Count: cp_info #%d\n", cf->interfaces_count);
  for (int i = 0; i < cf->interfaces_count; i++) {
    printf("[%d] Interface: cp_info #%d\n", i+1, cf->interfaces[i]);
  }

  /* Fields */
	printf("Fields Count: cp_info #%d\n",cf->fields_count);  
}