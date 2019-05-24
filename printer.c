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
      printf("%d ", (int32_t)cp[cpIndex-1].info.Integer.bytes);
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
  printf("Major version: %d", cf->major_version);
  if (cf->major_version == 52) {
    printf(" [1.8]\n");
  } else {
    printf("\nVersion is not supported! This JVM implementation works only for Java 1.8.\n");
    exit(1);
  }
  printf("Constant Pool Count: %d \n", cf->constant_pool_count);
	printf("Access Flags: 0x%04x ", cf->access_flags);
  if (cf->access_flags & ACC_PUBLIC) printf("[public] ");
  if (cf->access_flags & ACC_PRIVATE) printf("[private] ");
  if (cf->access_flags & ACC_PROTECTED) printf("[protected] ");
  if (cf->access_flags & ACC_STATIC) printf("[static] ");
  if (cf->access_flags & ACC_FINAL) printf("[final] ");
  if (cf->access_flags & ACC_VOLATILE) printf("[volatile] ");
  if (cf->access_flags & ACC_TRANSIENT) printf("[transient] ");
  if (cf->access_flags & ACC_SYNTHETIC) printf("[synthetic] ");
  if (cf->access_flags & ACC_ENUM) printf("[enum] ");
  printf("\n");

  printf("This Class: cp_info #%u ", cf->this_class);
  cpIndexReader(cf->constant_pool, cf->this_class);
  printf("\n");
	printf("Super Class: cp_info #%u ", cf->super_class);
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
        printf("\tname_index: #%u ", cf->constant_pool[i].info.Class.name_index);
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
        printf("\tbytes: %d", (int32_t)cf->constant_pool[i].info.Integer.bytes);
				break;
			case CONSTANT_Float:
        printf("[%d] CONSTANT_Float_info\n", i+1);
        printf("\tbytes: 0x%08x\n", cf->constant_pool[i].info.Float.bytes);
        printf("\tfloat: %.2f", *(float *)&cf->constant_pool[i].info.Float.bytes);
				break;
			case CONSTANT_Long:
        printf("[%d] CONSTANT_Long_info\n", i+1);
        printf("\thigh_bytes: %u\n", cf->constant_pool[i].info.Long.high_bytes);
        printf("\tlow_bytes: %u\n", cf->constant_pool[i].info.Long.low_bytes);
        long_value = ((uint64_t)cf->constant_pool[i].info.Long.high_bytes << 32) | cf->constant_pool[i].info.Long.low_bytes;
        printf("\nlong: %ld", (long)long_value);
				break;
			case CONSTANT_Double:
        printf("[%d] CONSTANT_Double_info\n", i+1);
        printf("\thigh_bytes: %u\n", cf->constant_pool[i].info.Double.high_bytes);
        printf("\tlow_bytes: %u\n", cf->constant_pool[i].info.Double.low_bytes);
        double_value = ((uint64_t)cf->constant_pool[i].info.Double.high_bytes << 32) | cf->constant_pool[i].info.Double.low_bytes;
        printf("\ndouble: %.2f", *(double *)&double_value);
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
        printf("\tlength: %u\n", cf->constant_pool[i].info.Utf8.length);
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
    printf("[%d] Interface: cp_info #%u ", i+1, cf->interfaces[i]);
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
    printf("\taccess_flags: 0x%04x ", cf->fields[i].access_flags);
    if (cf->fields[i].access_flags & ACC_PUBLIC) printf("[public] ");
    if (cf->fields[i].access_flags & ACC_PRIVATE) printf("[private] ");
    if (cf->fields[i].access_flags & ACC_PROTECTED) printf("[protected] ");
    if (cf->fields[i].access_flags & ACC_STATIC) printf("[static] ");
    if (cf->fields[i].access_flags & ACC_FINAL) printf("[final] ");
    if (cf->fields[i].access_flags & ACC_VOLATILE) printf("[volatile] ");
    if (cf->fields[i].access_flags & ACC_TRANSIENT) printf("[transient] ");
    if (cf->fields[i].access_flags & ACC_SYNTHETIC) printf("[synthetic] ");
    if (cf->fields[i].access_flags & ACC_ENUM) printf("[enum] ");
    printf("\n");
    printf("\tname_index: cp_info #%u ", cf->fields[i].name_index);
    cpIndexReader(cf->constant_pool, cf->fields[i].name_index);
    printf("\n");
    printf("\tdescriptor_index: cp_info #%u ", cf->fields[i].descriptor_index);
    cpIndexReader(cf->constant_pool, cf->fields[i].descriptor_index);
    printf("\n");
    printf("\tattributes_count: %d\n", cf->fields[i].attributes_count);
    for (int j = 0; j < cf->fields->attributes_count; j++) {
      printf("\t[%d] Attribute: ", j+1);
      cpIndexReader(cf->constant_pool, cf->fields[i].attributes[j].attribute_name_index);
      printf("\n");
      printf("\t\tattribute_name_index: cp_info #%u ", cf->fields[i].attributes[j].attribute_name_index);
      cpIndexReader(cf->constant_pool, cf->fields[i].attributes[j].attribute_name_index);
      printf("\n");
      printf("\t\tattribute_length: %u\n", cf->fields[i].attributes[j].attribute_length);
      uint16_t cp_index = cf->fields[i].attributes[j].attribute_name_index;
      if (!strcmp((char*)cf->constant_pool[cp_index].info.Utf8.bytes, "ConstantValue")) {
        printf("\t\tconstantvalue_index: cp_info #%u ", cf->fields[i].attributes[j].att_info.ConstantValue.constantvalue_index);
        cpIndexReader(cf->constant_pool, cf->fields[i].attributes[j].att_info.ConstantValue.constantvalue_index);
        printf("\n");
      } else if (!strcmp((char*)cf->constant_pool[cp_index].info.Utf8.bytes, "Deprecated")) {
        printf("\t\tDeprecated\n");
      } else if (!strcmp((char*)cf->constant_pool[cp_index].info.Utf8.bytes, "Synthetic")) {
        printf("\t\tSynthetic\n");
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
    printf("\taccess_flags: 0x%04x ", cf->methods[i].access_flags);
    if (cf->methods[i].access_flags & ACC_PUBLIC) printf("[public] ");
    if (cf->methods[i].access_flags & ACC_PRIVATE) printf("[private] ");
    if (cf->methods[i].access_flags & ACC_PROTECTED) printf("[protected] ");
    if (cf->methods[i].access_flags & ACC_STATIC) printf("[static] ");
    if (cf->methods[i].access_flags & ACC_FINAL) printf("[final] ");
    if (cf->methods[i].access_flags & ACC_VOLATILE) printf("[volatile] ");
    if (cf->methods[i].access_flags & ACC_TRANSIENT) printf("[transient] ");
    if (cf->methods[i].access_flags & ACC_SYNTHETIC) printf("[synthetic] ");
    if (cf->methods[i].access_flags & ACC_ENUM) printf("[enum] ");
    printf("\n");
    printf("\tname_index: cp_info #%u ", cf->methods[i].name_index);
    cpIndexReader(cf->constant_pool, cf->methods[i].name_index);
    printf("\n");
    printf("\tdescriptor_index: cp_info #%u ", cf->methods[i].descriptor_index);
    cpIndexReader(cf->constant_pool, cf->methods[i].descriptor_index);
    printf("\n");
    printf("\tattributes_count: %d\n", cf->methods[i].attributes_count);
    printf("\tMethod Attributes:\n");
    for (int j = 0; j < cf->methods->attributes_count; j++) {
      printf("\t[%d] Attribute: ",j+1);
      cpIndexReader(cf->constant_pool, cf->methods[i].attributes[j].attribute_name_index);
      printf("\n");
      printf("\t\tattribute_name_index: cp_info #%u ", cf->methods[i].attributes[j].attribute_name_index);
      cpIndexReader(cf->constant_pool, cf->methods[i].attributes[j].attribute_name_index);
      printf("\n");
      printf("\t\tattribute_length: %u\n", cf->methods[i].attributes[j].attribute_length);
      uint16_t cp_index = cf->methods[i].attributes[j].attribute_name_index - 1;
      if (!strcmp((char*)cf->constant_pool[cp_index].info.Utf8.bytes, "Code")) {
        printf("\t\tmax_stack: %d\n", cf->methods[i].attributes[j].att_info.Code.max_stack);
        printf("\t\tmax_locals: %d\n", cf->methods[i].attributes[j].att_info.Code.max_locals);
        printf("\t\tcode_length: %u\n", cf->methods[i].attributes[j].att_info.Code.code_length);
        if (cf->methods[i].attributes[j].att_info.Code.code_length > 0) printf("\t\tCode:\n");
        uint16_t pc = 0;
        for(int k = 0; k < cf->methods[i].attributes[j].att_info.Code.code_length; k++) {
          uint8_t opcode_index = cf->methods[i].attributes[j].att_info.Code.code[k];
          printf("\t\t\t%d", pc);
          printf("\t%s ", instructions[opcode_index].name);
          if (instructions[opcode_index].key == tableswitch) {
            // calcula padding para que proximo endereço seja multiplo de 4 bytes
            uint32_t bytes_padding = (4 - (pc % 4)) % 4; // ultimo módulo garante que que resultado é de 0-3
            uint32_t defaultbyte = cf->methods[i].attributes[j].att_info.Code.code[k += bytes_padding];
            for (int w = 0; w < 3; w++) defaultbyte = (defaultbyte << 8) | cf->methods[i].attributes[j].att_info.Code.code[++k];
            uint32_t low = cf->methods[i].attributes[j].att_info.Code.code[++k];
            for (int w = 0; w < 3; w++) low = (low << 8) | cf->methods[i].attributes[j].att_info.Code.code[++k];
            uint32_t high = cf->methods[i].attributes[j].att_info.Code.code[++k];
            for (int w = 0; w < 3; w++) high = (high << 8) | cf->methods[i].attributes[j].att_info.Code.code[++k];
            printf("%d to %d\n", (int32_t)low, (int32_t)high);
            int32_t jump_offsets = (int32_t)high - (int32_t)low + 1;
            uint32_t offset;
            for (int w = 0; w < jump_offsets; w++) {
              offset = cf->methods[i].attributes[j].att_info.Code.code[++k];
              for (int y = 0; y < 3; y++) offset = (offset << 4) | cf->methods[i].attributes[j].att_info.Code.code[++k];
              printf("\t\t\t\t\t%d: %d (%s%d)\n", w, pc + (int32_t)offset, (int32_t)offset>0 ? "+" : "", (int32_t)offset); //trivial
            }
            printf("\t\t\t\t  default: %d (%s%d)", pc + (int32_t)defaultbyte, (int32_t)defaultbyte>0 ? "+" : "", (int32_t)defaultbyte);
            instructions[opcode_index].arguments = k - pc;
          } else if (instructions[opcode_index].key == lookupswitch) {
            uint32_t bytes_padding = (4 - (opcode_index % 4)) % 4;
            instructions[opcode_index].arguments += bytes_padding;
            uint32_t defaultbyte = cf->methods[i].attributes[j].att_info.Code.code[k += bytes_padding];
            for (int w = 0; w < 4; w++) defaultbyte = (defaultbyte << 8) | cf->methods[i].attributes[j].att_info.Code.code[++k];
            uint32_t npairs = cf->methods[i].attributes[j].att_info.Code.code[++k];
            for (int w = 0; w < 4; w++) npairs = (npairs << 8) | cf->methods[i].attributes[j].att_info.Code.code[++k];
            instructions[opcode_index].arguments += 8;
            printf("%d:\n", (int32_t)npairs);

            uint32_t match, offset;
            for (int w = 0; w < npairs; w++) {
              match = cf->methods[i].attributes[j].att_info.Code.code[++k];
              // pega os 4 proximos bytes, alinhando eles
              for (int y = 0; y < 4; y++) match = (match << 4) | cf->methods[i].attributes[j].att_info.Code.code[++k];
              printf("\t\t\t\t%d: ",(int32_t)match);
              offset = cf->methods[i].attributes[j].att_info.Code.code[++k];
              for (int y = 0; y < 4; y++) offset = (offset << 4) | cf->methods[i].attributes[j].att_info.Code.code[++k];
              printf("%d (%s%d)\n", pc + (int32_t)offset, (int32_t)offset>0 ? "+" : "", (int32_t)offset); //trivial

              instructions[opcode_index].arguments += 8;
            }
            printf("\t\t\t\tdefault: %d (%s%d)", pc + (int32_t)defaultbyte, (int32_t)defaultbyte>0 ? "+" : "", (int32_t)defaultbyte);
          } else if (instructions[opcode_index].key == wide) {
              uint8_t opcode = cf->methods[i].attributes[j].att_info.Code.code[++k];
              uint16_t indexbyte1 = cf->methods[i].attributes[j].att_info.Code.code[++k];
              uint16_t indexbyte2 = cf->methods[i].attributes[j].att_info.Code.code[++k];
              uint16_t result = (indexbyte1 << 8) | indexbyte2;
              printf("%d ", opcode);
              printf("%d", result);
              if (opcode == iinc) {
                uint16_t constbyte1 = cf->methods[i].attributes[j].att_info.Code.code[++k];
                uint16_t constbyte2 = cf->methods[i].attributes[j].att_info.Code.code[++k];
                result = (constbyte1 << 8) | constbyte2;
                printf(" by %d", (int16_t)result);
              }
          } else if (instructions[opcode_index].arguments == 1) {
            uint8_t operand1 = cf->methods[i].attributes[j].att_info.Code.code[++k];
            if (instructions[opcode_index].key == bipush) {
              printf("%d", (int8_t)operand1);
            } else if (instructions[opcode_index].key == newarray) {
              printf("%d ", operand1);
              switch (operand1) {
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
            } else if (instructions[opcode_index].reference) {
              printf("#%u ", operand1);
              goHorse = 1;
              cpIndexReader(cf->constant_pool, operand1);
            } else {
              printf("%d", operand1);
            }
          } else if (instructions[opcode_index].arguments == 2) {
            uint16_t operand1 = cf->methods[i].attributes[j].att_info.Code.code[++k];
            uint16_t operand2 = cf->methods[i].attributes[j].att_info.Code.code[++k];
            uint16_t result = (operand1 << 8) | operand2;
            if (instructions[opcode_index].key == jsr || instructions[opcode_index].key == inst_goto || (instructions[opcode_index].key >= ifeq && instructions[opcode_index].key <= if_acmpne) || (instructions[opcode_index].key == ifnull) || (instructions[opcode_index].key == ifnonnull)) {
              printf("%d (%s%d)", pc + (int16_t)result, (int16_t)result>0 ? "+" : "", (int16_t)result);
            } else if (instructions[opcode_index].key == iinc) {
              printf("%d by %d", operand1, (int16_t)operand2);
            } else if (instructions[opcode_index].reference) {
              printf("#%u ", result);
              goHorse = 1;
              cpIndexReader(cf->constant_pool, result);
            } else if (instructions[opcode_index].key == sipush) {
              printf("%d", (int16_t)result);
            } else {
              printf("%d", result);
            }
          } else if (instructions[opcode_index].arguments == 3) {
            uint16_t operand1 = cf->methods[i].attributes[j].att_info.Code.code[++k];
            uint16_t operand2 = cf->methods[i].attributes[j].att_info.Code.code[++k];
            uint16_t operand3 = cf->methods[i].attributes[j].att_info.Code.code[++k];
            uint16_t result = (operand1 << 8) | operand2;
            if (instructions[opcode_index].key == multianewarray) {
              printf("#%u ", result);
              goHorse = 1;
              cpIndexReader(cf->constant_pool, result);
              printf("%u", operand3);
            } else {
              printf("%u ", result);
              printf("%u", operand3);
            }
          } else if (instructions[opcode_index].arguments == 4) {
            uint32_t operand1 = cf->methods[i].attributes[j].att_info.Code.code[++k];
            uint32_t operand2 = cf->methods[i].attributes[j].att_info.Code.code[++k];
            uint32_t operand3 = cf->methods[i].attributes[j].att_info.Code.code[++k];
            uint32_t operand4 = cf->methods[i].attributes[j].att_info.Code.code[++k];
            uint32_t result = (operand1 << 24) | (operand2 << 16) | (operand3 << 8) | operand4;
            if (instructions[opcode_index].key == jsr_w || instructions[opcode_index].key == goto_w) {
              printf("%d (%s%d)", pc + (int32_t)result, (int32_t)result>0 ? "+" : "", (int32_t)result);
            } else if (instructions[opcode_index].key == invokedynamic) {
              result = (operand1 << 8) | operand2;
              printf("#%u ", result);
              goHorse = 1;
              cpIndexReader(cf->constant_pool, result);
            } else if (instructions[opcode_index].key == invokeinterface) {
              result = (operand1 << 8) | operand2;
              printf("#%u ", result);
              goHorse = 1;
              cpIndexReader(cf->constant_pool, result);
              printf("%u", operand3);
            } else {
              printf("%u", result);
            }
          } 
          pc += 1 + instructions[opcode_index].arguments;
          printf("\n");
        }
        printf("\n");
        printf("\t\texception_table_length: %u\n", cf->methods[i].attributes[j].att_info.Code.exception_table_length);
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
        for (int k = 0; k < cf->methods[i].attributes[j].att_info.Code.attributes_count; k++) {
          printf("\t\t[%d] Attribute: ", k+1);
          cpIndexReader(cf->constant_pool, cf->methods[i].attributes[j].att_info.Code.attributes[k].attribute_name_index);
          printf("\n");
          printf("\t\t\tattribute_name_index: cp_info #%u ", cf->methods[i].attributes[j].att_info.Code.attributes[k].attribute_name_index);
          cpIndexReader(cf->constant_pool, cf->methods[i].attributes[j].att_info.Code.attributes[k].attribute_name_index);
          printf("\n");
          printf("\t\t\tattribute_length: %u\n", cf->methods[i].attributes[j].att_info.Code.attributes[k].attribute_length);
					uint16_t cp_indexao = cf->methods[i].attributes[j].att_info.Code.attributes[k].attribute_name_index - 1;
					if (!strcmp((char*)cf->constant_pool[cp_indexao].info.Utf8.bytes, "LineNumberTable")) {
            printf("\t\t\tline_number_table_length: %u\n", cf->methods[i].attributes[j].att_info.Code.attributes[k].att_info.LineNumberTable.line_number_table_length);
            printf("\t\t\tLine Number Table:\n");
            printf("\t\t\t\tnr.\tstart_pc\tline_number\n");
						for(int w = 0; w < cf->methods[i].attributes[j].att_info.Code.attributes[k].att_info.LineNumberTable.line_number_table_length; w++) {
              printf("\t\t\t\t[%d] ", w);
							printf("\t%d", cf->methods[i].attributes[j].att_info.Code.attributes[k].att_info.LineNumberTable.line_number_table_array[w].start_pc);
							printf("\t\t%d\n", cf->methods[i].attributes[j].att_info.Code.attributes[k].att_info.LineNumberTable.line_number_table_array[w].line_number);
						}
					} else if (!strcmp((char*)cf->constant_pool[cp_indexao].info.Utf8.bytes, "LocalVariableTable")) {
            printf("\t\t\tlocal_variable_table_length: %u\n", cf->methods[i].attributes[j].att_info.Code.attributes[k].att_info.LocalVariableTable.local_variable_table_length);
            printf("\t\t\tLocal Variable Table:\n");
            printf("\t\t\t\tnr.\tstart_pc\tlength\tname_index\tdescriptor_index\tindex\n");
						for(int w = 0; w < cf->methods[i].attributes[j].att_info.Code.attributes[k].att_info.LocalVariableTable.local_variable_table_length; w++) {
              printf("\t\t\t\t[%d] ", w);
							printf("\t%d", cf->methods[i].attributes[j].att_info.Code.attributes[k].att_info.LocalVariableTable.local_variable_table_array[w].start_pc);
							printf("\t\t%d", cf->methods[i].attributes[j].att_info.Code.attributes[k].att_info.LocalVariableTable.local_variable_table_array[w].length);
							printf("\t\t%d", cf->methods[i].attributes[j].att_info.Code.attributes[k].att_info.LocalVariableTable.local_variable_table_array[w].name_index);
							printf("\t\t%d", cf->methods[i].attributes[j].att_info.Code.attributes[k].att_info.LocalVariableTable.local_variable_table_array[w].descriptor_index);
							printf("\t\t%d\n", cf->methods[i].attributes[j].att_info.Code.attributes[k].att_info.LocalVariableTable.local_variable_table_array[w].index);
						}
					} else if (!strcmp((char*)cf->constant_pool[cp_indexao].info.Utf8.bytes, "StackMapTable")) {  
            printf("\t\t\tnumber_of_entries: %d\n", cf->methods[i].attributes[j].att_info.Code.attributes[k].att_info.StackMapTable.number_of_entries);
            stack_map_frame *smt = cf->methods[i].attributes[j].att_info.Code.attributes[k].att_info.StackMapTable.entries;
            printf("\t\t\tFrames:\n");
            uint32_t offset = 0;
            for (int w = 0; w < cf->methods[i].attributes[j].att_info.Code.attributes[k].att_info.StackMapTable.number_of_entries; w++) {
              printf("\t\t\t[%d] ", w);
              if (smt[w].frame_type < 64) {
                printf("SAME (%d)\n", smt[w].frame_type);
              } else if (smt[w].frame_type >= 64 && smt[w].frame_type <= 127) {
                printf("SAME LOCALS (%d)\n", smt[w].frame_type);
                verification_type_info *vti = smt[w].map_frame_type.same_locals_1_stack_item_frame.stack;
                printf("\t\t\t\t%d \n", vti[0].tag);
                if (vti[0].tag == 7) {
                  printf(" cp_info #%u ", vti[0].verification_type.Object_variable_info.cpool_index);
                  cpIndexReader(cf->constant_pool, vti[0].verification_type.Object_variable_info.cpool_index);
                } else if (vti[0].tag == 8) {
                  printf(" offset: %d", vti[0].verification_type.Uninitialized_variable_info.offset);
                }
                printf("\n");
              } else if (smt[w].frame_type == 247) {
                printf("SAME EXTENDED (%d), ", smt[w].frame_type);
                offset += smt[w].map_frame_type.same_locals_1_stack_item_frame_extended.offset_delta;
                printf("Offset: %d (+%d)\n", offset, smt[w].map_frame_type.same_locals_1_stack_item_frame_extended.offset_delta);
                verification_type_info *vti = smt[w].map_frame_type.same_locals_1_stack_item_frame_extended.stack;
                printf("\t\t\t\t%s ", VERIFICATION_TYPE_TAG[vti[0].tag]);
                if (vti[0].tag == 7) {
                  printf("cp_info #%u ", vti[0].verification_type.Object_variable_info.cpool_index);
                  cpIndexReader(cf->constant_pool, vti[0].verification_type.Object_variable_info.cpool_index);
                } else if (vti[0].tag == 8) {
                  printf(" offset: %d", vti[0].verification_type.Uninitialized_variable_info.offset);
                }
                printf("\n");
              } else if (smt[w].frame_type >= 248 && smt[w].frame_type <= 250 ) {
                printf("CHOP (%d), ", smt[w].frame_type);
                offset += smt[w].map_frame_type.chop_frame.offset_delta;
                printf("Offset: %d (+%d)\n", offset, smt[w].map_frame_type.chop_frame.offset_delta);
              } else if (smt[w].frame_type == 251 ) {
                printf("SAME (%d), ", smt[w].frame_type);
                offset += smt[w].map_frame_type.same_frame_extended.offset_delta;
                printf("Offset: %d (+%d)\n", offset, smt[w].map_frame_type.same_frame_extended.offset_delta);
              } else if (smt[w].frame_type >= 252 && smt[w].frame_type <= 254) {
                printf("APPEND (%d), ", smt[w].frame_type);
                offset += smt[w].map_frame_type.append_frame.offset_delta;
                printf("Offset: %d (+%d)\n", offset, smt[w].map_frame_type.append_frame.offset_delta);
                verification_type_info *vti = smt[w].map_frame_type.append_frame.locals;
                printf("\t\t\t\tlocals:\n");
								for (int y = 0; y < smt[w].frame_type - 251; y++) {
                  printf("\t\t\t\t\t%s ", VERIFICATION_TYPE_TAG[vti[y].tag]);
                  if (vti[y].tag == 7) {
                    printf("cp_info #%u ", vti[y].verification_type.Object_variable_info.cpool_index);
                    cpIndexReader(cf->constant_pool, vti[y].verification_type.Object_variable_info.cpool_index);
                  } else if (vti[y].tag == 8) {
                    printf(" offset: %d", vti[y].verification_type.Uninitialized_variable_info.offset);
                  }
                  printf("\n");
								}
              } else if (smt[w].frame_type == 255) {
                printf("FULL (%d), ", smt[w].frame_type);
                offset += smt[w].map_frame_type.full_frame.offset_delta;
                printf("Offset: %d (+%d)\n", offset, smt[w].map_frame_type.full_frame.offset_delta);
                printf("\t\t\t\tnumber_of_locals: %d\n", smt[w].map_frame_type.full_frame.number_of_locals);
                printf("\t\t\t\tLocals:\n");
                verification_type_info *vti_loc = smt[w].map_frame_type.full_frame.locals;
                for (int y = 0; y < smt[w].map_frame_type.full_frame.number_of_locals; y++) {
                  printf("\t\t\t\t\t%s ", VERIFICATION_TYPE_TAG[vti_loc[y].tag]);
                  if (vti_loc[y].tag == 7) {
                    printf("cp_info #%u ", vti_loc[y].verification_type.Object_variable_info.cpool_index);
                    cpIndexReader(cf->constant_pool, vti_loc[y].verification_type.Object_variable_info.cpool_index);
                  } else if (vti_loc[y].tag == 8) {
                    printf(" offset: %d", vti_loc[y].verification_type.Uninitialized_variable_info.offset);
                  }
                  printf("\n");
                }
                printf("\t\t\t\tnumber_of_stack_items: %d\n", smt[w].map_frame_type.full_frame.number_of_stack_items);
                verification_type_info *vti_stk = smt[w].map_frame_type.full_frame.stack;
                for (int y = 0; y < smt[w].map_frame_type.full_frame.number_of_stack_items; y++) {
                  printf("\t\t\t\t\t%s ", VERIFICATION_TYPE_TAG[vti_stk[y].tag]);
                  if (vti_stk[y].tag == 7) {
                    printf("cp_info #%u ", vti_stk[y].verification_type.Object_variable_info.cpool_index);
                    cpIndexReader(cf->constant_pool, vti_stk[y].verification_type.Object_variable_info.cpool_index);
                  } else if (vti_stk[y].tag == 8) {
                    printf(" offset: %d", vti_stk[y].verification_type.Uninitialized_variable_info.offset);
                  }
                  printf("\n");
                }
              }
              offset++;
            }
          }
				}
      } else if (!strcmp((char*)cf->constant_pool[cp_index].info.Utf8.bytes, "Exceptions")) {
        printf("\t\tnumber_of_exceptions: %d\n", cf->methods[i].attributes[j].att_info.Exceptions.number_of_exceptions);
        printf("\t\texception_index_table:\n");
        for (int k = 0; k < cf->methods[i].attributes[j].att_info.Exceptions.number_of_exceptions; k++) {
          printf("\t\t\tcp_info #%u ", cf->methods[i].attributes[j].att_info.Exceptions.exception_index_table[k]);
          cpIndexReader(cf->constant_pool, cf->methods[i].attributes[j].att_info.Exceptions.exception_index_table[k]);
          printf("\n");
        }
      } else if (!strcmp((char*)cf->constant_pool[cp_index].info.Utf8.bytes, "Deprecated")) {
        printf("\t\tDeprecated\n");
      } else if (!strcmp((char*)cf->constant_pool[cp_index].info.Utf8.bytes, "Synthetic")) {
        printf("\t\tSynthetic\n");
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
    printf("\tattribute_name_index: cp_info #%u ", cf->attributes[i].attribute_name_index);
    cpIndexReader(cf->constant_pool, cf->attributes[i].attribute_name_index);
    printf("\n");
    printf("\tattribute_length: %u\n", cf->attributes[i].attribute_length);
    uint16_t cp_index = cf->attributes[i].attribute_name_index - 1;
    if (!strcmp((char*)cf->constant_pool[cp_index].info.Utf8.bytes, "Deprecated")) {
      printf("\t\tDeprecated\n");
    } else if (!strcmp((char*)cf->constant_pool[cp_index].info.Utf8.bytes, "BootstrapMethods")) {
      printf("\t\tbootstrap_methods_length: %u\n", cf->attributes[i].att_info.BootstrapMethods.bootstrap_methods_length);
      printf("\t\tBootstrap Methods:\n");
			for (int j = 0; j < cf->attributes[i].att_info.BootstrapMethods.bootstrap_methods_length; j++) {
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
      printf("\tsourcefile_index: cp_info #%u ", cf->attributes[i].att_info.SourceFile.sourcefile_index);
      cpIndexReader(cf->constant_pool, cf->attributes[i].att_info.SourceFile.sourcefile_index);
    }
  }
  printf("\n");
}