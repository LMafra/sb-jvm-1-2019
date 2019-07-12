///
///  @file exibidor.c
///  @headerfile exibidor.h "exibidor.h"
///
///  @authors
///	 Bruno Sanguinetti 18/0046063 \n
///	 Gabriel Vasconcelos 16/0120781 \n
///	 Leonardo de Almeida 15/0135491 \n
///	 Lucas Mafra 12/0126443 \n
///	 Wladimir Gramacho 15/0058718 \n
///
///  @date 01/06/2019
///
///
///  @brief Arquivo que exibe na tela uma estrutura ClassFile
///  imprimindo todos os dados armazenados.
///
///  Recebe um ponteiro para uma estrutura ClassFile, imprime
///  cada parte de acordo com seu formato e suas subestruturas,
///  isso tudo com uma interface semelhante ao programa
///  "jclasslib bytecode viewer".
///

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "exibidor.h"

///
/// Funcao principal que imprime as informacoes gerais
/// e coordena as chamadas das funcoes que imprimem
/// as demais estuturas do classfile
///
/// @param ClassFile* Ponteiro para a estrutura Classfile
/// @return @c void
/// @see printaCpInfo printaInterfaces printaFieldInfo printaMethodInfo printaAttributeInfo
/// @see imprimeStringPool printTopo printBase printBlank
void printaClassFile(ClassFile* classFile) {

    /* GENERAL INFORMATION */
    printf("CLASS FILE STRUCTURE\n\n");
    printf("CAFEBABE: 0x%0x \n", classFile->magic);
    printf("Minor Version: %d\n", classFile->minorVersion);
    printf("Major Version: %d\n", classFile->majorVersion);
    printf("Constant Pool Count: %d\n", classFile->constantPoolCount);
    printf("Access Flags: 0x%04X\n", classFile->accessFlags);
    printf("This Class: cp_info #%d ", classFile->thisClass);
    imprimeStringPool(classFile->constantPool, classFile->thisClass-1);
    printf("\n");
    printf("Super Class: cp_info #%d ", classFile->superClass);
    imprimeStringPool(classFile->constantPool, classFile->superClass-1);
    printf("\n");
    printf("Interfaces Count: %d\n", classFile->interfacesCount);
    printf("Fields Countd: %d\n", classFile->fieldsCount);
    printf("Methods Count: %d\n", classFile->methodsCount);
    printf("Attributes Count: %d\n", classFile->attributesCount);

    /* CONSTANT POOL */
    printf("\nCONSTANT POOL\n");
    printf("Constant Pool Count: %d\n", classFile->constantPoolCount);
    printaCpInfo(classFile);

    /* INTERFACES */
    printf("\nINTERFACES\n");
    printaInterfaces(classFile);

    /* FIELD INFO */
    printf("\nFIELD INFO\n");
    printaFieldInfo(classFile);

    /* METHOD INFO */
    printf("\nMETHODS\n");
    printaMethodInfo(classFile);

    /* ATTRIBUTE INFO */
    printf("\nATTRIBUTES\n");
    printaAttributeInfo(classFile);
}

///
/// Funcao que imprime o Constant Pool, buscando os
/// valores UTF8 finais de cada constatnte e imprimindo
/// tambem suas referencias
///
/// @param ClassFile* Ponteiro para a estrutura Classfile
/// @return @c void
/// @see imprimeStringPool hexToDouble hexToLong
void printaCpInfo(ClassFile* classFile) {
    double valorDouble;
    float valorFloat;
    long valorLong;

    for (int i = 0; i < classFile->constantPoolCount-1; ++i) {

        switch (classFile->constantPool[i].tag) {
            case CONSTANT_Class:
                printf("[%d] CONSTANT_Class_Info: #%d ",i+1, classFile->constantPool[i].info.Class.nameIndex);
                imprimeStringPool(classFile->constantPool, classFile->constantPool[i].info.Class.nameIndex -1);
                printf("\n\n");
                break;
            case CONSTANT_Fieldref:
                printf("[%d] CONSTANT_Fieldref_Info", i+1);
                printf("\n");
                printf("\tClassIndex: %d ", classFile->constantPool[i].info.Fieldref.classIndex);
                imprimeStringPool(classFile->constantPool, classFile->constantPool[i].info.Fieldref.classIndex-1);
                printf("\n");
                printf("\tNameAndTypeIndex: %d ", classFile->constantPool[i].info.Fieldref.nameAndTypeIndex);
                imprimeStringPool(classFile->constantPool, classFile->constantPool[i].info.Fieldref.nameAndTypeIndex-1);
                printf("\n\n");
                break;

            case CONSTANT_NameAndType:
                printf("[%d] CONSTANT_NameAndType_Info", i+1);
                printf("\n");
                printf("\tNameIndex: %d ", classFile->constantPool[i].info.NameAndType.nameIndex);
                imprimeStringPool(classFile->constantPool, classFile->constantPool[i].info.NameAndType.nameIndex-1);
                printf("\n");
                printf("\tDescriptorIndex: %d ", classFile->constantPool[i].info.NameAndType.descriptorIndex);
                imprimeStringPool(classFile->constantPool, classFile->constantPool[i].info.NameAndType.descriptorIndex-1);
                printf("\n\n");
                break;
            case CONSTANT_Utf8:
                printf("[%d] CONSTANT_Utf8_Info", i+1);
                printf("\n");
                printf("\tLength: %d", classFile->constantPool[i].info.Utf8.length);
                printf("\n");
                printf("\tBytes: %s", classFile->constantPool[i].info.Utf8.bytes);
                printf("\n\n");
                break;
            case CONSTANT_Methodref:
                printf("[%d] CONSTANT_Methodref_Info",i+1);
                printf("\n");
                printf("\tClassIndex: %d ", classFile->constantPool[i].info.Methodref.classIndex);
                imprimeStringPool(classFile->constantPool, classFile->constantPool[i].info.Methodref.classIndex -1);
                printf("\n");
                printf("\tNameAndTypeIndex: %d ", classFile->constantPool[i].info.Methodref.nameAndTypeIndex);
                imprimeStringPool(classFile->constantPool, classFile->constantPool[i].info.Methodref.nameAndTypeIndex -1);
                printf("\n\n");
                break;
            case CONSTANT_InterfaceMethodref:
                printf("[%d] CONSTANT_InterfaceMethodref_Info",i+1);
                printf("\n");
                printf("\tClassIndex: %d ",classFile->constantPool[i].info.InterfaceMethodref.classIndex);
                imprimeStringPool(classFile->constantPool, classFile->constantPool[i].info.InterfaceMethodref.classIndex -1);
                printf("\n");
                printf("\tNameAndTypeIndex: #%d %u",i+1, classFile->constantPool[i].info.InterfaceMethodref.nameAndTypeIndex);
                imprimeStringPool(classFile->constantPool, classFile->constantPool[i].info.InterfaceMethodref.nameAndTypeIndex -1);
                printf("\n\n");
                break;
            case CONSTANT_String:
                printf("[%d] CONSTANT_String_Info", i+1);
                printf("\n");
                printf("\tStringIndex: #%d ", classFile->constantPool[i].info.String.stringIndex);
                imprimeStringPool(classFile->constantPool, classFile->constantPool[i].info.String.stringIndex -1);
                printf("\n\n");
                break;
            case CONSTANT_Integer:
                printf("[%d] CONSTANT_Integer_Info", i+1);
                printf("\n");
                printf("\tValor: %u", classFile->constantPool[i].info.Integer.bytes);
                printf("\n");
                break;
            case CONSTANT_Float:
                memcpy(&valorFloat, &classFile->constantPool[i].info.Float.bytes, sizeof(int32_t));
                printf("[%d] CONSTANT_Float_Info", i+1);
                printf("\n");
                printf("\tValor: %0.2f", valorFloat);
                printf("\n\n");
                break;
            case CONSTANT_Double:
                printf("[%d] CONSTANT_Double_Info", i+1);
                printf("\n");
                printf("\tHighBytes: 0x%08X", classFile->constantPool[i].info.Double.highBytes);
                printf("\n");
                printf("\tLowBytes: 0x%08X", classFile->constantPool[i].info.Double.lowBytes);
                printf("\n");
                valorDouble = hexToDouble(classFile->constantPool[i].info.Double.highBytes, classFile->constantPool[i].info.Double.lowBytes);
                printf("\tDouble: %.4f", valorDouble);
                printf("\n");
                printf("[%d] (large numeric continued)", i+2);
                printf("\n\n");
                i++;
                break;
            case CONSTANT_Long:
                printf("[%d] CONSTANT_Long_Info", i+1);
                printf("\n");
                printf("\tHighBytes: 0x%08X", classFile->constantPool[i].info.Long.highBytes);
                printf("\n");
                printf("\tLowBytes: 0x%08X", classFile->constantPool[i].info.Long.lowBytes);
                printf("\n");
                valorLong = hexToLong(classFile->constantPool[i].info.Long.highBytes, classFile->constantPool[i].info.Long.lowBytes);
                printf("\tLong: %ld", valorLong);
                printf("\n");
                printf("[%d] (large numeric continued)", i+2);
                printf("\n\n");
                i++;
                break;
            default:
                break;
        }
    }
}

///
/// Funcao que imprime Interfaces da classe passada
/// parametro, alem das referencias das constantes
/// que contem as informacoes UTF8 de cada Interface 
///
/// @param ClassFile* Ponteiro para a estrutura Classfile
/// @return @c void
/// @see imprimeStringPool
void printaInterfaces(ClassFile* classFile) {
    if (classFile->interfacesCount) {
        for (int i = 0; i < classFile->interfacesCount; ++i) {

            int index = classFile->constantPool[classFile->interfaces[i]-1].info.Class.nameIndex;

            printf("\tInterface %d: #%d  %d", i, classFile->interfaces[i], index);
            imprimeStringPool(classFile->constantPool, classFile->interfaces[i]-1);
            printf("\n");
        }
    } else {
        printf("Interfaces Count: %d\n\n", classFile->interfacesCount);
    }
}

///
/// Funcao que imprime as informacoes de Fields da classe,
/// bem como suas referencias no Constant Pool.
///
/// @param ClassFile* Ponteiro para a estrutura Classfile
/// @return @c void
/// @see imprimeStringPool printAccessFlag printSingleLine
void printaFieldInfo(ClassFile* classFile) {

    if(classFile->fieldsCount != 0) {
        for (int i = 0; i < classFile->fieldsCount; i++) {

            printf("\tName:           cp_info_#%d   ", classFile->fields[i].nameIndex);
            imprimeStringPool(classFile->constantPool, classFile->fields[i].nameIndex - 1);
            printf("\n");
            printf("\tDescriptor:     cp_info_#%d   ", classFile->fields[i].descriptorIndex);
            imprimeStringPool(classFile->constantPool, classFile->fields[i].descriptorIndex - 1);
            printf("\n");
            printf("\tAccess Flag:    0x%04X        ", classFile->fields[i].accessFlags);
            printAccessFlag(classFile->fields[i].accessFlags);
            printf("\tNumero de Atributos:  %d", classFile->fields[i].attributesCount);
            printf("\n\n");

            for (int j = 0; j < classFile->fields[i].attributesCount; j++) {

                printf("\tGeneric Info ");
                printf("\t\tattribute_name_index:   cp_info_#%d  ", classFile->fields[i].attributes->attributeNameIndex);
                imprimeStringPool(classFile->constantPool, classFile->fields[i].attributes->attributeNameIndex - 1);
                printf("\n");
                printf("\t\tattribute_length:       %u\n", classFile->fields[i].attributes->attributeLength);
                printf("\n");
                printf("\tSpecific Info ");
                printf("\t\tconstant_value_index:   cp_info_#%d  ", classFile->fields[i].attributes->constantValueIndex);
                imprimeStringPool(classFile->constantPool, classFile->fields[i].attributes->constantValueIndex - 1);
                printf("\n\n\n");
            }
        }
    } else {
        printf("Fields Count: %d\n\n", classFile->fieldsCount);
    }
}

///
/// Funcao que imprime as informacoes dos Metodos da classe,
/// suas instrucoes (mnemonicos) e suas referencias no Constant Pool.
///
/// @param ClassFile* Ponteiro para a estrutura Classfile
/// @return @c void
/// @see imprimeStringPool imprimeCode imprimeExc
void printaMethodInfo(ClassFile* classFile) {
    uint16_t methodsCount = classFile->methodsCount;
    printf("Methods Count: %d\n", methodsCount);
    printf("Methods:\n");

    if(methodsCount == 0)
        return;
    else{
        MethodInfo* cp = classFile->methods;
        for(int i = 0; i < methodsCount; cp++){
            printf("[%d] Method: ", i);
            imprimeStringPool(classFile->constantPool, cp->nameIndex - 1);
            printf("\n");

            printf("\tAccess Flag: 0x%04X ",cp->accessFlags);
            printAccessFlag(cp->accessFlags);
            printf("\tName Index: cp_info #%d ",cp->nameIndex);
            imprimeStringPool(classFile->constantPool, cp->nameIndex - 1);
            printf("\n");
            printf("\tDescriptor Index: cp_info #%d ",cp->descriptorIndex);
            imprimeStringPool(classFile->constantPool, cp->descriptorIndex - 1);
            printf("\n");
            
            printf("\tAttributes Count: %d\n",cp->attributesCount);

            imprimeCode(classFile, cp->cdAtrb);

            if (cp->attributesCount == 2) {
                imprimeExc(classFile, cp->excAtrb);
            }
            i++;
        }
    }
}

///
/// Funcao que imprime as informacoes dos Atributos da classe,
/// bem como suas referencias no Constant Pool.
///
/// @param ClassFile* Ponteiro para a estrutura Classfile
/// @return @c void
/// @see imprimeStringPool printSingleLine
void printaAttributeInfo(ClassFile* classFile) {

    if (classFile->attributesCount) {
        printf("Attributes Count: %d\n", classFile->attributesCount);

        AttributeInfo* attrInfo = classFile->attributes;

        for(int i = 0; i < classFile->attributesCount; attrInfo++){
            printf("[%d] Attribute: ", i);
            imprimeStringPool(classFile->constantPool, attrInfo->attributeNameIndex-1);

            printf("\n");
            printf("\tAttribute name index:  cp_info #%d  ", attrInfo->attributeNameIndex);
            imprimeStringPool(classFile->constantPool, attrInfo->attributeNameIndex-1);
            printf("\n");
            printf("\tAttribute length:  %u\n", attrInfo->attributeLength);
            for(uint32_t j = 0; j < attrInfo->attributeLength; attrInfo->info++){
                if(*(attrInfo->info)){
                    printf("\tsourcefile_index:  cp_info #%d ",*(attrInfo->info));
                    imprimeStringPool(classFile->constantPool, *(attrInfo->info) - 1);
                    printf("\n");
                }
                j++;
            }
            i++;
            printf("\n\n");
        }
    } else {
        printf("Atributtes Count: %d\n\n", classFile->attributesCount);
    }
}

///
/// Funcao que imprime na tela o UTF8 final de uma constante
/// a partir de sua posicao. O UTF8 eh encontrado recursivamente.
///
/// @param ClassFile* Ponteiro para a estrutura Classfile
/// @param int Posicao da costante que sera impressa
/// @return @c void
void imprimeStringPool(CpInfo* cp, int pos) {
    int tag;

    tag = cp[pos].tag;

    if (tag == CONSTANT_Utf8) {
        printf("%s ", cp[pos].info.Utf8.bytes);
        return;
    }

    switch(tag) {
        case CONSTANT_Class:
            imprimeStringPool(cp, cp[pos].info.Class.nameIndex - 1);
            break;

        case CONSTANT_Fieldref:
            imprimeStringPool(cp, cp[pos].info.Fieldref.classIndex - 1);
            imprimeStringPool(cp, cp[pos].info.Fieldref.nameAndTypeIndex - 1);
            break;

        case CONSTANT_NameAndType:
            imprimeStringPool(cp, cp[pos].info.NameAndType.nameIndex - 1 );
            imprimeStringPool(cp, cp[pos].info.NameAndType.descriptorIndex - 1);
            break;

        case CONSTANT_Methodref:
            imprimeStringPool(cp, cp[pos].info.Methodref.classIndex - 1);
            imprimeStringPool(cp, cp[pos].info.Methodref.nameAndTypeIndex - 1);
            break;

        case CONSTANT_InterfaceMethodref:
            imprimeStringPool(cp, cp[pos].info.InterfaceMethodref.classIndex - 1);
            imprimeStringPool(cp, cp[pos].info.InterfaceMethodref.nameAndTypeIndex - 1);
            break;

        case CONSTANT_String:
            imprimeStringPool(cp, cp[pos].info.String.stringIndex - 1);
            break;

        case CONSTANT_Integer:
            printf("%u", cp[pos].info.Integer.bytes);
            break;

        case CONSTANT_Float:
            printf("%u", cp[pos].info.Float.bytes);
            break;

        default:
            break;
    }
}

///
/// Funcao converte um valor Hexademical lido em bytes para
/// uma variavel double (tipada de acordo com C99).
///
/// @param uint32_t Parte alta dos 64 bits
/// @param uint32_t Parte baixa dos 64 bits
/// @return @c double O valor Hexadecimal de entrada salvo numa variavel do tipo double
double hexToDouble(uint32_t highBytes, uint32_t lowBytes){

    double retorno;
    uint64_t valorDouble;

    valorDouble = highBytes;
    valorDouble <<= 32;
    valorDouble |= lowBytes;

    memcpy(&retorno, &valorDouble, sizeof(uint64_t));

    return retorno;
}

///
/// Funcao converte um valor Hexademical lido em bytes para
/// uma variavel long (tipada de acordo com C99).
///
/// @param uint32_t Parte alta dos 64 bits
/// @param uint32_t Parte baixa dos 64 bits
/// @return @c long O valor Hexadecimal de entrada salvo numa variavel do tipo long
long hexToLong(uint32_t highBytes, uint32_t lowBytes){
    long retorno;
    long negativo;

    highBytes &= 0x80000000;
    negativo = pow(-1, highBytes);
    memcpy(&retorno, &lowBytes, sizeof(uint32_t));

    return retorno * negativo;
}

///
/// Funcao que imprime o tipo de Access Flag de acordo
/// com o parametro Hexadecimal passado. Se o valor for
//  uma combinacao de flags, tambem eh reconhecido e uma
/// string com todas as flags eh impressa na tela.
///
/// @param uint16_t Valor Hexadecimal referente a uma flag ou combinacao de flags
/// @param uint32_t Parte baixa dos 64 bits
/// @return @c void
void printAccessFlag(uint16_t accessFlags){

    switch(accessFlags){
        case 0x0001:
            printf("[Public]\n");
        break;
        case 0x0009:
            printf("[Public Static]\n");
        break;
        case 0x0041:
            printf("[Public Volatile]\n");
        break;
        case 0x00019:
            printf("[Public Static Final]\n");
        break;
        case 0x0002:
            printf("[Private]\n");
        break;
        case 0x000A:
            printf("[Private Static]\n");
        break;
        case 0x0042:
            printf("[Private Volatile]\n");
        break;
        case 0x0001A:
            printf("[Private Static Final]\n");
        break;
        case 0x0004:
            printf("[Protected]\n");
        break;
        case 0x000C:
            printf("[Protected Static]\n");
        break;
        case 0x0044:
            printf("[Protected Volatile]\n");
        break;
        case 0x0001C:
            printf("[Protected Static Final]\n");
        break;
        case 0x0008:
            printf("[Static]\n");
        break;
        case 0x0010:
            printf("[Final]\n");
        break;
        case 0x0040:
            printf("[Volatile]\n");
        break;
        case 0x0080:
            printf("[Transient]\n");
        break;

    }
}

///
/// Funcao que imprime as instrucoes (mnemonicos) de um metodo, alem
/// das informacoes sobre o Code do metodo e das referencias de cada
/// valor no Constant Pool.
///
/// @param ClassFile* Ponteiro para a estrutura Classfile
/// @param CodeAttributte* Ponteiro para a estrutura CodeAttribute
/// @return @c void
/// @see printSingleLine imprimeStringPool inicializaDecodificador
void imprimeCode(ClassFile* classFile, CodeAttribute* cdAtrb) {
    int opcode, posReferencia;
    int bytesPreench, offsets;
    uint32_t defautV, low, high, npairs, temp;

    printf("\n\tAttribute: Code\n");
    printf("\t\tAttribute Name Index: %d ",cdAtrb->attributeNameIndex);
    imprimeStringPool(classFile->constantPool, cdAtrb->attributeNameIndex - 1);
    printf("\n");
    printf("\t\tAttribute Length: %u\n   ",cdAtrb->attributeLength);
    printf("\t\tMax Stack: %d\n", cdAtrb->maxStack);
    printf("\t\tMax Locals: %d\n",cdAtrb->maxLocals);
    printf("\t\tCode Length: %u\n", cdAtrb->codeLength);
    printf("\t\tCode:\n");


    Decodificador dec[NUM_INSTRUCAO];
    inicializaDecodificador(dec);

    for(uint32_t k = 0; k < cdAtrb->codeLength; ) {
        opcode = cdAtrb->code[k];
        printf("\t\t\t%u: %s  ", k, dec[opcode].instrucao);
        k++;

        if (opcode == TABLESWITCH) {
            posReferencia = k - 1;
            bytesPreench = (4 - (k % 4)) % 4;
            for (int j = 0; j < bytesPreench; j++) {
                k++;
            }

            defautV = 0;
            for (int j = 0; j < 4; j++) {
                defautV = (defautV << 4) + cdAtrb->code[k];
                k++;
            }

            low = 0;
            for (int j = 0; j < 4; j++) {
                low = (low << 4) + cdAtrb->code[k];
                k++;
            }

            high = 0;
            for (int j = 0; j < 4; j++) {
                high = (high << 4) + cdAtrb->code[k];
                k++;
            }
 
            printf("  %u to %u\n", low, high);

            offsets = 1 + high - low;
            for (int j = 0; j < offsets; j++) {
                temp = 0;
                for (int i = 0; i < 4; i++) {
                    temp = (temp << 4) + cdAtrb->code[k];
                    k++;
                }
                printf("\t\t%d: %u (+%u)\n", j, (posReferencia + temp), temp);
            }
            printf("\t\tdefault: %u (+%u)\n", (defautV + posReferencia), defautV);
        } else if (opcode == LOOKUPSWITCH) {
            posReferencia = k - 1;
            bytesPreench = (4 - (k % 4)) % 4;
            for (int j = 0; j < bytesPreench; j++) {
                k++;
            }

            defautV = 0;
            for (int j = 0; j < 4; j++) {
                defautV = (defautV << 4) + cdAtrb->code[k];
                k++;
            }

            npairs = 0;
            for (int j = 0; j < 4; j++) {
                npairs = (npairs << 4) + cdAtrb->code[k];
                k++;
            }

            printf("  %u\n", npairs);

            for (int j = 0; j < npairs; j++) {
                temp = 0;
                for (int i = 0; i < 4; i++) {
                    temp = (temp << 8) + cdAtrb->code[k];
                    k++;
                }
                printf("\t%u:  ", temp);

                temp = 0;
                for (int i = 0; i < 4; i++) {
                    temp = (temp << 8) + cdAtrb->code[k];
                    k++;
                }
                printf("%u (+%u)\n", temp + posReferencia, temp);

            }
            printf("\tdefault: %u (+%u)\n", defautV + posReferencia, defautV);
        } else if (opcode == WIDE) {
            printf("\n");

            opcode = cdAtrb->code[k];
            k++;

            if (opcode == ILOAD || opcode == FLOAD || opcode == ALOAD || opcode == LLOAD ||
                opcode == DLOAD || opcode == ISTORE || opcode == FSTORE || opcode == ASTORE ||
                opcode == LSTORE || opcode == DSTORE || opcode == RET) {

                printf("%u: %s  ", k - 1, dec[opcode].instrucao);
                k+=2;
                temp = cdAtrb->code[k-2] << 8;
                temp += cdAtrb->code[k-1];
                printf(" %u \n", temp);
                printf("%u: iinc ", k - 1);
                k+=2;
                temp = cdAtrb->code[k-2] << 8;
                temp += cdAtrb->code[k-1];
                printf(" %u ", temp);
                k+=2;
                temp = cdAtrb->code[k-2] << 8;
                temp += cdAtrb->code[k-1];
                printf(" por  %u \n", temp);

            } else {
                printf("Arquivo .class invalido na instrucao wide");
                exit(1);
            }
        } else if (opcode == LDC) {

            int8_t index = cdAtrb->code[k];
            uint32_t valor;
            float valorFloat;
            int valorInt;

            
            if (classFile->constantPool[index-1].tag == CONSTANT_Float) {
                printf("%d  ", index);
                valor = classFile->constantPool[index-1].info.Float.bytes;
                memcpy(&valorFloat, &valor, sizeof(int32_t));
                printf("%.4f\n", valorFloat);
            } else if (classFile->constantPool[index-1].tag == CONSTANT_Integer) {
                printf("%d  ", index);
                valor = classFile->constantPool[index-1].info.Integer.bytes;
                memcpy(&valorInt, &valor, sizeof(uint32_t));
                printf("%d\n", valorInt);
            } else if (classFile->constantPool[index-1].tag == CONSTANT_String) {
                printf("%d  ", index);
                imprimeStringPool(classFile->constantPool, index-1);
                printf("\n");
            }
            k++;
        } else if (opcode == LDC_W || opcode == LDC2_W) {

            int16_t index = cdAtrb->code[k+1];
            
            if (classFile->constantPool[index-1].tag == CONSTANT_Long) {
                uint32_t parteAlta = classFile->constantPool[index-1].info.Long.highBytes;
                uint32_t parteBaixa = classFile->constantPool[index-1].info.Long.lowBytes;
                long resultado = hexToLong(parteAlta, parteBaixa);
                printf("%d  ", index);
                printf("%ld", resultado);
                printf("\n");
                
            } else if (classFile->constantPool[index-1].tag == CONSTANT_Double) {
                uint32_t parteAlta = classFile->constantPool[index-1].info.Long.highBytes;
                uint32_t parteBaixa = classFile->constantPool[index-1].info.Long.lowBytes;
                double resultado = hexToDouble(parteAlta, parteBaixa);
                printf("%d  ", index);
                printf("%.4f", resultado);
                printf("\n");
            }
            k+=2;
        } else if (opcode == IINC){
            int numBytes = dec[opcode].bytes;
            for (int j = 0; j < numBytes; j++) {
                
                if(cdAtrb->code[k] != 0){
                    int8_t byteSigned;
                    memcpy(&byteSigned, &cdAtrb->code[k], sizeof(uint8_t));
                    printf("%d", byteSigned);
                }
                if(j != numBytes - 1){
                    printf(" by ");    
                }
                k++;
            }
            printf("\n");
        } else if (opcode == ILOAD  || opcode == FLOAD  || opcode == ALOAD  || opcode == LLOAD  ||
                   opcode == DLOAD  || opcode == ISTORE || opcode == FSTORE || opcode == ASTORE ||
                   opcode == LSTORE || opcode == DSTORE || opcode == BIPUSH || opcode == SIPUSH) {

                    uint8_t byteUnsigned;
                    
                    if(cdAtrb->code[k] != 0){
                        memcpy(&byteUnsigned, &cdAtrb->code[k], sizeof(uint8_t));
                    
                    }
                    printf("%d ", byteUnsigned);                    
                    printf("\n");
                    k++;        
        } else  if (opcode == IFEQ || opcode == IFNE || opcode == IFLT || opcode == IFGE ||
                    opcode == IFGT || opcode == IFLE || opcode == IF_ACMPEQ || opcode == IF_ACMPNE || 
                    opcode == IF_ICMPEQ || opcode == IF_ICMPNE || opcode == IF_ICMPLT || opcode == IF_ICMPGE || 
                    opcode == IF_ICMPGT || opcode == IF_ICMPLE || opcode == IFNONNULL || opcode == IFNULL ||
                    opcode == GOTO) {
            
                    int8_t byteSigned;
                    
                    if(cdAtrb->code[k+1] != 0){
                        memcpy(&byteSigned, &cdAtrb->code[k+1], sizeof(uint8_t));
                    
                    }
                    printf("%d ", (k-1) + byteSigned);
                    if (byteSigned > 0){
                        printf("(+%d)", byteSigned);
                    } else {
                        printf("(%d)", byteSigned);
                    }
                    
                    printf("\n");
                    k += 2;
        } else  if (opcode == NEWARRAY) {
                    
                    switch(cdAtrb->code[k]){
                        case 4:
                            printf("4  (boolean)\n");
                            break;
                        case 5:
                            printf("5  (char)\n");
                            break;
                        case 6:
                            printf("6  (float)\n");
                            break;
                        case 7:
                            printf("7  (double)\n");
                            break;
                        case 8:
                            printf("8  (byte)\n");
                            break;            
                        case 9:
                            printf("9  (short)\n");
                            break;
                        case 10:
                            printf("10  (int)\n");
                            break;
                        case 11:
                            printf("11  (long)\n");
                            break;
                        default:
                            break;
                    }
                    k++;
        } else {
            int numBytes = dec[opcode].bytes;
            for (int j = 0; j < numBytes; j++) {

                
                if(cdAtrb->code[k] != 0){
                    printf("%d  ", cdAtrb->code[k]);
                    imprimeStringPool(classFile->constantPool, cdAtrb->code[k] - 1);
                }
                k++;
            }
            printf("\n");
        }
    }
    printf("\n\n");
}

///
/// Funcao que imprime as excecoes (quando especificadas) e
/// as referencias de cada ao Constant Pool.
///
/// @param ClassFile* Ponteiro para a estrutura Classfile
/// @param ExceptionsAttribute* Ponteiro para a estrutura ExceptionsAttribute
/// @return @c void
/// @see printSingleLine imprimeStringPool
void imprimeExc(ClassFile* classFile, ExceptionsAttribute* excAtrb) {
    printf("\n\tException Info\n");
    printf("\tattribute_name_index: cp_info #%d ", excAtrb->attributeNameIndex);
    imprimeStringPool(classFile->constantPool, excAtrb->attributeNameIndex - 1);
    printf("\n");
    printf("\t# - Excecao\n");
    for (int k = 0; k < excAtrb->numberExceptions; k++) {
        printf("\t\t%d - %d\n", k, excAtrb->exceptionIndexTable[k]);
    }
}

///
/// Recebe os bytes de minor version lidos
/// do ClassFile e converte para a versao Java.
///
/// @param uint16_t 2bytes do minor version
/// @return @c void
void imprimeMajorVersion(uint16_t minor){

  switch(minor){

        case 45:
          printf("45 [1.1]\n");
          break;
        case 46:
            printf("46 [1.2]\n");
            break;
        case 47:
            printf("47 [1.3]\n");
            break;
        case 48:
            printf("48 [1.4]\n");
            break;
        case 49:
            printf("49 [1.5]\n");
            break;
        case 50:
            printf("50 [1.6]\n");
            break;
        case 51:
            printf("51 [1.7]\n");
            break;
        case 52:
            printf("52 [1.8]\n");
            break;
        default:
            printf("%u\n", minor);
            break;
    }

}