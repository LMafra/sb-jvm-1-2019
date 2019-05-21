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
* @brief Responsavel por imprimir no terminal 
*        a estrutura do classfile lido. \n
* @section DESCRIPTION
* 
*/

#include "printer.h"
#include "reader.h"
#include "instructions.h"

const char *VERIFICATION_TYPE_TAG[9] = {"TOP", "INTEGER", "FLOAT", "DOUBLE", "LONG", "NULL", "UNINITIALIZEDTHIS", "OBJECT", "UNINITIALIZED"};

int goHorse = 0;

void cpIndexReader(cp_info *cp, uint16_t cpIndex) {
  uint64_t long_value, double_value;
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
    case CONSTANT_Integer:
      printf("%d ", cp[cpIndex-1].info.Integer.bytes);
      break;
    case CONSTANT_Float:
      printf("%f ", *(float *)&cp[cpIndex-1].info.Float.bytes);
      break;
    case CONSTANT_Long:
      long_value = ((uint64_t)cp[cpIndex-1].info.Long.high_bytes << 32) | cp[cpIndex-1].info.Long.low_bytes;
      printf("%ld ", (long)long_value);
      break;
    case CONSTANT_Double:
      double_value = ((uint64_t)cp[cpIndex-1].info.Double.high_bytes << 32) | cp[cpIndex-1].info.Double.low_bytes;
      printf("%f ", *(double *)&double_value);
      break;
    case CONSTANT_NameAndType:
      cpIndexReader(cp, cp[cpIndex-1].info.NameAndType.name_index);
      if (!goHorse) {
        cpIndexReader(cp, cp[cpIndex-1].info.NameAndType.descriptor_index);
        goHorse = 0;
      }
      break;
    case CONSTANT_Utf8:
      printf("%s ", (char *)cp[cpIndex-1].info.Utf8.bytes);
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

void classPrinter( classFile* cf) { /*! Funcao responavel por ler o arquivo class descrito pela documentacao da JVM. */
  printf("CLASS FILE STRUCTURE\n\n");

  /* General Information */
  printf("CAFEBABE: 0x%0x \n", cf->magic);
  printf("Minor version: %d \n", cf->minor_version);
  printf("Major version: %d \n", cf->major_version);
  printf("Constant Pool Count: %d \n", cf->constant_pool_count);
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
  printf("\n");
	printf("Super Class: cp_info #%d ", cf->super_class);
  cpIndexReader(cf->constant_pool, cf->super_class);
  printf("\n");
  printf("Interfaces Count: %d\n", cf->interfaces_count);
	printf("Fields Count: %d\n",cf->fields_count);  
  printf("Methods Count: %d\n",cf->methods_count);
  printf("Attributes Count: %d\n",cf->attributes_count);

  /* Constant Pool Information */
  printf("\nCONSTANT POOL\n");
  printf("Constant Pool Count: %d \n", cf->constant_pool_count);
  uint8_t tag;
  for (int i = 0; i < cf->constant_pool_count - 1; i++) {
    uint64_t long_value, double_value;
    tag = cf->constant_pool[i].tag;
    switch (tag) {
      case CONSTANT_Class:
        printf("[%d] CONSTANT_Class_info\n", i+1);
        printf("\tname_index: #%d ", cf->constant_pool[i].info.Class.name_index);
        cpIndexReader(cf->constant_pool, cf->constant_pool[i].info.Class.name_index);
        printf("\n");
				break;
			case CONSTANT_Fieldref:
        printf("[%d] CONSTANT_Fieldref_info\n", i+1);
        printf("\tclass_index: %d ", cf->constant_pool[i].info.Fieldref.class_index);
        cpIndexReader(cf->constant_pool, cf->constant_pool[i].info.Fieldref.class_index);
        printf("\n");
        printf("\tname_and_type_index: %d ", cf->constant_pool[i].info.Fieldref.name_and_type_index);
        cpIndexReader(cf->constant_pool, cf->constant_pool[i].info.Fieldref.name_and_type_index);
        printf("\n");
				break;
			case CONSTANT_Methodref:
        printf("[%d] CONSTANT_Methodref_info\n", i+1);
        printf("\tclass_index: %d ", cf->constant_pool[i].info.Methodref.class_index);
        cpIndexReader(cf->constant_pool, cf->constant_pool[i].info.Methodref.class_index);
        printf("\n");
        printf("\tname_and_type_index: %d ", cf->constant_pool[i].info.Methodref.name_and_type_index);
        cpIndexReader(cf->constant_pool, cf->constant_pool[i].info.Methodref.name_and_type_index);
        printf("\n");
				break;
			case CONSTANT_InterfaceMethodref:
        printf("[%d] CONSTANT_InterfaceMethodref_info\n", i+1);
        printf("\tclass_index: %d ", cf->constant_pool[i].info.InterfaceMethodref.class_index);
        cpIndexReader(cf->constant_pool, cf->constant_pool[i].info.InterfaceMethodref.class_index);
        printf("\n");
        printf("\tname_and_type_index: %d ", cf->constant_pool[i].info.InterfaceMethodref.name_and_type_index);
        cpIndexReader(cf->constant_pool, cf->constant_pool[i].info.InterfaceMethodref.name_and_type_index);
        printf("\n");
				break;
			case CONSTANT_String:
        printf("[%d] CONSTANT_String_info\n", i+1);
        printf("\tstring_index: %d ", cf->constant_pool[i].info.String.string_index);
        cpIndexReader(cf->constant_pool, cf->constant_pool[i].info.String.string_index);
        printf("\n");
				break;	
			case CONSTANT_Integer:
        printf("[%d] CONSTANT_Integer_info\n", i+1);
        printf("\tbytes: %d", cf->constant_pool[i].info.Integer.bytes);
				break;
			case CONSTANT_Float:
        printf("[%d] CONSTANT_Float_info\n", i+1);
        printf("\tbytes: 0x%08x\n", cf->constant_pool[i].info.Float.bytes);
        printf("\tfloat: %f", *(float *)&cf->constant_pool[i].info.Float.bytes);
				break;
			case CONSTANT_Long:
        printf("[%d] CONSTANT_Long_info\n", i+1);
        printf("\thigh_bytes: %d\n", cf->constant_pool[i].info.Long.high_bytes);
        printf("\tlow_bytes: %d\n", cf->constant_pool[i].info.Long.low_bytes);
        long_value = ((uint64_t)cf->constant_pool[i].info.Long.high_bytes << 32) | cf->constant_pool[i].info.Long.low_bytes;
        printf("\nlong: %ld", (long)long_value);
				break;
			case CONSTANT_Double:
        printf("[%d] CONSTANT_Double_info\n", i+1);
        printf("\thigh_bytes: %d\n", cf->constant_pool[i].info.Double.high_bytes);
        printf("\tlow_bytes: %d\n", cf->constant_pool[i].info.Double.low_bytes);
        double_value = ((uint64_t)cf->constant_pool[i].info.Double.high_bytes << 32) | cf->constant_pool[i].info.Double.low_bytes;
        printf("\ndouble: %f", *(double *)&double_value);
				break;
			case CONSTANT_NameAndType:
        printf("[%d] CONSTANT_NameAndType_info\n", i+1);
        printf("\tname_index: %d ", cf->constant_pool[i].info.NameAndType.name_index);
        cpIndexReader(cf->constant_pool, cf->constant_pool[i].info.NameAndType.name_index);
        printf("\n");
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
        printf("\n");
				break;
			case CONSTANT_MethodType:
        printf("[%d] CONSTANT_MethodType_info\n", i+1);
        printf("\tdescriptor_index: %d ", cf->constant_pool[i].info.MethodType.descriptor_index);
        cpIndexReader(cf->constant_pool, cf->constant_pool[i].info.MethodType.descriptor_index);
        printf("\n");
				break;
			case CONSTANT_InvokeDynamic:
        printf("[%d] CONSTANT_InvokeDynamic_info\n", i+1);
        printf("\tbootstrap_method_attr_index: %d ", cf->constant_pool[i].info.InvokeDynamic.bootstrap_method_attr_index);
        cpIndexReader(cf->constant_pool, cf->constant_pool[i].info.InvokeDynamic.bootstrap_method_attr_index);
        printf("\n");
        printf("\tname_and_type_index: %d ", cf->constant_pool[i].info.InvokeDynamic.name_and_type_index);
        cpIndexReader(cf->constant_pool, cf->constant_pool[i].info.InvokeDynamic.name_and_type_index);
        printf("\n");
				break;
			default:
				break;
    }
    printf("\n");
  }

  /* Interfaces Information */
  printf("\nINTERFACES\n");
	printf("Interfaces Count: %d\n", cf->interfaces_count);
  for (int i = 0; i < cf->interfaces_count; i++) {
    printf("[%d] Interface: cp_info #%d ", i+1, cf->interfaces[i]);
    cpIndexReader(cf->constant_pool, cf->interfaces[i]);
    printf("\n");
  }

  /* Fields Information */
  printf("\nFIELDS\n");
	printf("Fields Count: %d\n",cf->fields_count);  
  for (int i = 0; i < cf->fields_count; i++) {
    printf("[%d] Field: ", i+1);
    cpIndexReader(cf->constant_pool, cf->fields[i].name_index);
    printf("\n");
    printf("\taccess_flags: %d\n", cf->fields[i].access_flags);
    printf("\tname_index: cp_info #%d ", cf->fields[i].name_index);
    cpIndexReader(cf->constant_pool, cf->fields[i].name_index);
    printf("\n");
    printf("\tdescriptor_index: cp_info #%d ", cf->fields[i].descriptor_index);
    cpIndexReader(cf->constant_pool, cf->fields[i].descriptor_index);
    printf("\n");
    printf("\tattributes_count: %d\n", cf->fields[i].attributes_count);
    for (int j = 0; j < cf->fields->attributes_count; j++) {
      printf("\t[%d] Attribute: ", j+1);
      cpIndexReader(cf->constant_pool, cf->fields[i].attributes[j].attribute_name_index);
      printf("\n");
      printf("\t\tattribute_name_index: cp_info #%d ", cf->fields[i].attributes[j].attribute_name_index);
      cpIndexReader(cf->constant_pool, cf->fields[i].attributes[j].attribute_name_index);
      printf("\n");
      printf("\t\tattribute_length: %d\n", cf->fields[i].attributes[j].attribute_length);
      uint16_t cp_index = cf->fields[i].attributes[j].attribute_name_index;
      if (!strcmp((char*)cf->constant_pool[cp_index].info.Utf8.bytes, "ConstantValue")) {
        printf("\t\tconstantvalue_index: cp_info #%d ", cf->fields[i].attributes[j].att_info.ConstantValue.constantvalue_index);
        cpIndexReader(cf->constant_pool, cf->fields[i].attributes[j].att_info.ConstantValue.constantvalue_index);
        printf("\n");
      } else if (!strcmp((char*)cf->constant_pool[cp_index].info.Utf8.bytes, "Deprecated")) {
        printf("\t\tDeprecated\n");
      }
    }
  }

  /* Methods Information */
  printf("\nMETHODS\n");
  printf("Methods Count: %d\n",cf->methods_count);
  printf("Methods:\n");
  for (int i = 0; i < cf->methods_count; i++) {
    printf("[%d] Method: ", i);
    cpIndexReader(cf->constant_pool, cf->methods[i].name_index);
    printf("\n");
    printf("\taccess_flags: %d\n", cf->methods[i].access_flags);
    printf("\tname_index: cp_info #%d ", cf->methods[i].name_index);
    cpIndexReader(cf->constant_pool, cf->methods[i].name_index);
    printf("\n");
    printf("\tdescriptor_index: cp_info #%d ", cf->methods[i].descriptor_index);
    cpIndexReader(cf->constant_pool, cf->methods[i].descriptor_index);
    printf("\n");
    printf("\tattributes_count: %d\n", cf->methods[i].attributes_count);
    printf("\tMethod Attributes:\n");
    for (int j = 0; j < cf->methods->attributes_count; j++) {
      printf("\t[%d] Attribute: ",j+1);
      cpIndexReader(cf->constant_pool, cf->methods[i].attributes[j].attribute_name_index);
      printf("\n");
      printf("\t\tattribute_name_index: cp_info #%d ", cf->methods[i].attributes[j].attribute_name_index);
      cpIndexReader(cf->constant_pool, cf->methods[i].attributes[j].attribute_name_index);
      printf("\n");
      printf("\t\tattribute_length: %d\n", cf->methods[i].attributes[j].attribute_length);
      uint16_t cp_index = cf->methods[i].attributes[j].attribute_name_index - 1;
      if (!strcmp((char*)cf->constant_pool[cp_index].info.Utf8.bytes, "Code")) {
        printf("\t\tmax_stack: %d\n", cf->methods[i].attributes[j].att_info.Code.max_stack);
        printf("\t\tmax_locals: %d\n", cf->methods[i].attributes[j].att_info.Code.max_locals);
        printf("\t\tcode_length: %d\n", cf->methods[i].attributes[j].att_info.Code.code_length);
        if (cf->methods[i].attributes[j].att_info.Code.code_length > 0) printf("\t\tCode:\n");
        uint16_t pc = 0;
        for(int k = 0; k < cf->methods[i].attributes[j].att_info.Code.code_length; k++) {
          uint8_t opcode_index = cf->methods[i].attributes[j].att_info.Code.code[k];
          printf("\t\t\t%d", pc);
          printf("\t%s ", instructions[opcode_index].name);
          if (instructions[opcode_index].arguments == 4) {
            k++;
            uint32_t branchbyte1 = cf->methods[i].attributes[j].att_info.Code.code[k];
            k++;
            uint32_t branchbyte2 = cf->methods[i].attributes[j].att_info.Code.code[k];
            k++;
            uint32_t branchbyte3 = cf->methods[i].attributes[j].att_info.Code.code[k];
            k++;
            uint32_t branchbyte4 = cf->methods[i].attributes[j].att_info.Code.code[k];
            int32_t branchbyte = (branchbyte1 << 24) | (branchbyte2 << 16)| (branchbyte3 << 8) | branchbyte4;
            printf("%d ", pc + branchbyte);
            if (branchbyte > 0) printf("+");
            printf("%d ", branchbyte);
          } else if (instructions[opcode_index].arguments == 2) {
            if (instructions[opcode_index].key == inst_goto){
              k++;
              uint16_t branchbyte1 = cf->methods[i].attributes[j].att_info.Code.code[k];
              k++;
              uint16_t branchbyte2 = cf->methods[i].attributes[j].att_info.Code.code[k];
              int16_t branchbyte = (branchbyte1 << 8) | branchbyte2;
              printf("%d ", pc + branchbyte);
              if (branchbyte > 0) printf("+");
              printf("%d ", branchbyte);
            } else if (instructions[opcode_index].key == iinc) {
              k++;
              printf("%d by ", cf->methods[i].attributes[j].att_info.Code.code[k]);
              k++;
              printf("%d", cf->methods[i].attributes[j].att_info.Code.code[k]);
            } else {
              k++;
              uint16_t indexbyte1 = cf->methods[i].attributes[j].att_info.Code.code[k];
              k++;
              uint16_t indexbyte2 = cf->methods[i].attributes[j].att_info.Code.code[k];
              uint16_t arg_res = (indexbyte1 << 8) | indexbyte2;
              if ((instructions[opcode_index].key >= 153 && instructions[opcode_index].key <= 166) || 
                  (instructions[opcode_index].key >= 198 && instructions[opcode_index].key <= 199) ) {
                printf("%d +", pc + arg_res);
              } else if (instructions[opcode_index].reference) {
                printf("#");
              }
              printf("%d ", arg_res);
              if (instructions[opcode_index].reference) {
                goHorse = 1;
                cpIndexReader(cf->constant_pool, arg_res);
              }
            }
          } else if (instructions[opcode_index].arguments == 1) {
            if (instructions[opcode_index].key == bipush) {
              k++;
              int8_t arg1 = cf->methods[i].attributes[j].att_info.Code.code[k];
              printf("%d", arg1);
            } else {
              k++;
              uint8_t arg1 = cf->methods[i].attributes[j].att_info.Code.code[k];
              if (instructions[opcode_index].key == ldc) printf("#");
              printf("%d ", arg1);
              if (instructions[opcode_index].key == newarray) {
                switch (cf->methods[i].attributes[j].att_info.Code.code[k]) {
                  case T_BOOLEAN:
                    printf("bool");
                    break;
                  case T_CHAR:
                    printf("char");
                    break;
                  case T_FLOAT:
                    printf("float");
                    break;
                  case T_DOUBLE:
                    printf("double");
                    break;
                  case T_BYTE:
                    printf("byte");
                    break;
                  case T_SHORT:
                    printf("short");
                    break;
                  case T_INT:
                    printf("int");
                    break;
                  case T_LONG:
                    printf("long");
                    break;
                  default:
                    break;
                }
              } else if (instructions[opcode_index].key == ldc) {
                cpIndexReader(cf->constant_pool, arg1);
              }
            }
          }
          pc += 1 + instructions[opcode_index].arguments;
          printf("\n");
        }
        printf("\n");
        printf("\t\texception_table_length: %d\n", cf->methods[i].attributes[j].att_info.Code.exception_table_length);
        if (cf->methods[i].attributes[j].att_info.Code.exception_table_length > 0) {
          printf("\t\tException Table:\n");
          printf("\t\t\t i\tstart_pc\tend_pc\thandler_pc\tcatch_type\n");
        }
        for (int k = 0; k < cf->methods[i].attributes[j].att_info.Code.exception_table_length; k++) {
          printf("\t\t\t[%d]",k);
          printf("\t%d", cf->methods[i].attributes[j].att_info.Code.exception_table_array[k].start_pc);
          printf("\t\t%d", cf->methods[i].attributes[j].att_info.Code.exception_table_array[k].end_pc);
          printf("\t\t%d", cf->methods[i].attributes[j].att_info.Code.exception_table_array[k].handler_pc);
          printf("\t\t%d\n", cf->methods[i].attributes[j].att_info.Code.exception_table_array[k].catch_type);
        }
        printf("\t\tattributes_count: %d\n", cf->methods[i].attributes[j].att_info.Code.attributes_count);
        printf("\t\tCode Attributes:\n");
        for (int k = 0; k < cf->methods[i].attributes[j].att_info.Code.attributes_count; k++){
          printf("\t\t[%d] Attribute: ", k+1);
          cpIndexReader(cf->constant_pool, cf->methods[i].attributes[j].att_info.Code.attributes[k].attribute_name_index);
          printf("\n");
          printf("\t\t\tattribute_name_index: cp_info #%d ", cf->methods[i].attributes[j].att_info.Code.attributes[k].attribute_name_index);
          cpIndexReader(cf->constant_pool, cf->methods[i].attributes[j].att_info.Code.attributes[k].attribute_name_index);
          printf("\n");
          printf("\t\t\tattribute_length: %d\n", cf->methods[i].attributes[j].att_info.Code.attributes[k].attribute_length);
					uint16_t cp_indexao = cf->methods[i].attributes[j].att_info.Code.attributes[k].attribute_name_index - 1;
					if (!strcmp((char*)cf->constant_pool[cp_indexao].info.Utf8.bytes, "LineNumberTable")) {
            printf("\t\t\tline_number_table_length: %d\n", cf->methods[i].attributes[j].att_info.Code.attributes[k].att_info.LineNumberTable.line_number_table_length);
            printf("\t\t\tLine Number Table:\n");
            printf("\t\t\t\t i\tstart_pc\tline_number\n");
						for(int w = 0; w < cf->methods[i].attributes[j].att_info.Code.attributes[k].att_info.LineNumberTable.line_number_table_length; w++) {
              printf("\t\t\t\t[%d] ", w);
							printf("\t%d", cf->methods[i].attributes[j].att_info.Code.attributes[k].att_info.LineNumberTable.line_number_table_array[w].start_pc);
							printf("\t\t%d\n", cf->methods[i].attributes[j].att_info.Code.attributes[k].att_info.LineNumberTable.line_number_table_array[w].line_number);
						}
					} else if (!strcmp((char*)cf->constant_pool[cp_indexao].info.Utf8.bytes, "StackMapTable")) {
            printf("\t\t\tnumber_of_entries: %d\n", cf->methods[i].attributes[j].att_info.Code.attributes[k].att_info.StackMapTable.number_of_entries);
            stack_map_frame *smt = cf->methods[i].attributes[j].att_info.Code.attributes[k].att_info.StackMapTable.entries;
            printf("\t\t\tFrames:\n");
            for (int w = 0; w < cf->methods[i].attributes[j].att_info.Code.attributes[k].att_info.StackMapTable.number_of_entries; w++) {
              printf("\t\t\t\tframe_type: %d\n", smt[w].frame_type);
              if (smt[w].frame_type < 64) {
              } else if (smt[w].frame_type >= 64 && smt[w].frame_type <= 127) {
                verification_type_info *vti = smt[w].map_frame_type.same_locals_1_stack_item_frame.stack;
                printf("\t\t\t\t\ttag: %d\n", vti[0].tag);
                if (vti[0].tag == 7) {
                  printf(" cp_info #%d ", vti[0].verification_type.Object_variable_info.cpool_index);
                  cpIndexReader(cf->constant_pool, vti[0].verification_type.Object_variable_info.cpool_index);
                } else if (vti[0].tag == 8) {
                  printf(" offset: %d", vti[0].verification_type.Uninitialized_variable_info.offset);
                }
                printf("\n");
              } else if (smt[w].frame_type == 247) {
                printf("\t\t\t\t\toffset_delta: %d\n", smt[w].map_frame_type.same_locals_1_stack_item_frame_extended.offset_delta);
                verification_type_info *vti = smt[w].map_frame_type.same_locals_1_stack_item_frame_extended.stack;
                printf("\t\t\t\t\ttag: %s", VERIFICATION_TYPE_TAG[vti[0].tag]);
                if (vti[0].tag == 7) {
                  printf(" cpool_index: cp_info #%d ", vti[0].verification_type.Object_variable_info.cpool_index);
                  cpIndexReader(cf->constant_pool, vti[0].verification_type.Object_variable_info.cpool_index);
                } else if (vti[0].tag == 8) {
                  printf(" offset: %d", vti[0].verification_type.Uninitialized_variable_info.offset);
                }
                printf("\n");
              } else if (smt[w].frame_type >= 248 && smt[w].frame_type <= 250 ) {
                printf("\t\t\t\t\toffset_delta: %d\n", smt[w].map_frame_type.chop_frame.offset_delta);
              } else if (smt[w].frame_type == 251 ) {
                printf("\t\t\t\t\toffset_delta: %d\n", smt[w].map_frame_type.same_frame_extended.offset_delta);
              } else if (smt[w].frame_type >= 252 && smt[w].frame_type <= 254) {
                printf("\t\t\t\t\toffset_delta: %d\n", smt[w].map_frame_type.append_frame.offset_delta);
                verification_type_info *vti = smt[w].map_frame_type.append_frame.locals;
                printf("\t\t\t\t\tlocals:\n");
								for (int y = 0; y < smt[w].frame_type - 251; y++){
                  printf("\t\t\t\t\t\ttag: %s", VERIFICATION_TYPE_TAG[vti[y].tag]);
                  if (vti[y].tag == 7) {
                    printf(" cpool_index: cp_info #%d ", vti[y].verification_type.Object_variable_info.cpool_index);
                    cpIndexReader(cf->constant_pool, vti[y].verification_type.Object_variable_info.cpool_index);
                  } else if (vti[y].tag == 8) {
                    printf(" offset: %d", vti[y].verification_type.Uninitialized_variable_info.offset);
                  }
                  printf("\n");
								}
              } else if (smt[w].frame_type == 255) {
                printf("\t\t\t\t\toffset_delta: %d\n", smt[w].map_frame_type.full_frame.offset_delta);
                printf("\t\t\t\t\tnumber_of_locals: %d\n", smt[w].map_frame_type.full_frame.number_of_locals);
                verification_type_info *vti_loc = smt[w].map_frame_type.full_frame.locals;
                for (int y = 0; y < smt[w].map_frame_type.full_frame.number_of_locals; y++) {
                  printf("\t\t\t\t\t\ttag: %s", VERIFICATION_TYPE_TAG[vti_loc[y].tag]);
                  if (vti_loc[y].tag == 7) {
                    printf(" cpool_index: cp_info #%d ", vti_loc[y].verification_type.Object_variable_info.cpool_index);
                    cpIndexReader(cf->constant_pool, vti_loc[y].verification_type.Object_variable_info.cpool_index);
                  } else if (vti_loc[y].tag == 8) {
                    printf(" offset: %d", vti_loc[y].verification_type.Uninitialized_variable_info.offset);
                  }
                  printf("\n");
                }
                printf("\t\t\t\t\tnumber_of_stack_items: %d\n", smt[w].map_frame_type.full_frame.number_of_stack_items);
                verification_type_info *vti_stk = smt[w].map_frame_type.full_frame.stack;
                for (int y = 0; y < smt[w].map_frame_type.full_frame.number_of_stack_items; y++) {
                  printf("\t\t\t\t\t\ttag: %s", VERIFICATION_TYPE_TAG[vti_stk[y].tag]);
                  if (vti_stk[y].tag == 7) {
                    printf(" cpool_index: cp_info #%d ", vti_stk[y].verification_type.Object_variable_info.cpool_index);
                    cpIndexReader(cf->constant_pool, vti_stk[y].verification_type.Object_variable_info.cpool_index);
                  } else if (vti_stk[y].tag == 8) {
                    printf(" offset: %d", vti_stk[y].verification_type.Uninitialized_variable_info.offset);
                  }
                  printf("\n");
                }
              }
            }
          }
				}
      } else if (!strcmp((char*)cf->constant_pool[cp_index].info.Utf8.bytes, "Exceptions")) {
        printf("\t\tnumber_of_exceptions: %d\n", cf->methods[i].attributes[j].att_info.Exceptions.number_of_exceptions);
        printf("\t\texception_index_table:\n");
        for (int k = 0; k < cf->methods[i].attributes[j].att_info.Exceptions.number_of_exceptions; k++) {
          printf("\t\t\tcp_info #%d ", cf->methods[i].attributes[j].att_info.Exceptions.exception_index_table[k]);
          cpIndexReader(cf->constant_pool, cf->methods[i].attributes[j].att_info.Exceptions.exception_index_table[k]);
          printf("\n");
        }
      } else if (!strcmp((char*)cf->constant_pool[cp_index].info.Utf8.bytes, "Deprecated")) {
        printf("\t\tDeprecated\n");
      }
    }
  }

  /* Attributes Information*/
  printf("\nATTRIBUTES\n");
  printf("Attributes Count: %d\n",cf->attributes_count);
  for (int i = 0; i < 1; i++) {
    printf("[%d] Attribute: ", i);
    cpIndexReader(cf->constant_pool, cf->attributes[i].attribute_name_index);
    printf("\n");
    printf("\tattribute_name_index: cp_info #%d ", cf->attributes[i].attribute_name_index);
    cpIndexReader(cf->constant_pool, cf->attributes[i].attribute_name_index);
    printf("\n");
    printf("\tattribute_length: %d\n", cf->attributes[i].attribute_length);
    uint16_t cp_index = cf->attributes[i].attribute_name_index - 1;
    if (!strcmp((char*)cf->constant_pool[cp_index].info.Utf8.bytes, "Deprecated")) {
      printf("\t\tDeprecated\n");
    } else if (!strcmp((char*)cf->constant_pool[cp_index].info.Utf8.bytes, "BootstrapMethods")) {
      printf("\t\tbootstrap_methods_length: %d\n", cf->attributes[i].att_info.BootstrapMethods.bootstrap_methods_length);
      printf("\t\tBootstrap Methods:\n");
			for (int j = 0; j < cf->attributes[i].att_info.BootstrapMethods.bootstrap_methods_length; j++){
        printf("\t\t[%d] Bootstrap Method:\n", j+1);
        printf("\t\t\tbootstrap_method_ref: %d\n", cf->attributes[i].att_info.BootstrapMethods.bootstrap_methods_array[j].bootstrap_method_ref);
        printf("\t\t\tnum_bootstrap_arguments: %d\n", cf->attributes[i].att_info.BootstrapMethods.bootstrap_methods_array[j].num_bootstrap_arguments);
        printf("\t\t\tBootstrap Arguments:\n\t\t\t\t");
        for (int k = 0; k < cf->attributes[i].att_info.BootstrapMethods.bootstrap_methods_array[j].num_bootstrap_arguments; k++) {
          printf("%d ", cf->attributes[i].att_info.BootstrapMethods.bootstrap_methods_array[j].bootstrap_arguments[k]);
        }
        printf("\n");
			}
    } else if (!strcmp((char*)cf->constant_pool[cp_index].info.Utf8.bytes, "SourceFile")) {
      printf("\tsourcefile_index: cp_info #%d ", cf->attributes[i].att_info.SourceFile.sourcefile_index);
      cpIndexReader(cf->constant_pool, cf->attributes[i].att_info.SourceFile.sourcefile_index);
    }
  }
  printf("\n");
}