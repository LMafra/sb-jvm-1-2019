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
* @brief  \n
* @section DESCRIPTION
* 
*/

#include "instructions.h"

opcode instructions[300];

void initializeInstructions() {
  strcpy(instructions[0].name, "nop");
  instructions[0].arguments = 0;

  strcpy(instructions[1].name, "aconst_null");
  instructions[1].arguments = 0;
  instructions[1].references = 0;

  strcpy(instructions[2].name, "iconst_m1");
  instructions[2].arguments = 0;
  instructions[2].references = 0;

  strcpy(instructions[3].name, "iconst_0");
  instructions[3].arguments = 0;
  instructions[3].references = 0;

  strcpy(instructions[4].name, "iconst_1");
  instructions[4].arguments = 0;
  instructions[4].references = 0;

  strcpy(instructions[5].name, "iconst_2");
  instructions[5].arguments = 0;
  instructions[5].references = 0;

  strcpy(instructions[6].name, "iconst_3");
  instructions[6].arguments = 0;
  instructions[6].references = 0;

  strcpy(instructions[7].name, "iconst_4");
  instructions[7].arguments = 0;
  instructions[7].references = 0;

  strcpy(instructions[8].name, "iconst_5");
  instructions[8].arguments = 0;
  instructions[8].references = 0;

  strcpy(instructions[9].name, "lconst_0");
  instructions[9].arguments = 0;
  instructions[9].references = 0;

  strcpy(instructions[10].name, "lconst_1");
  instructions[10].arguments = 0;
  instructions[10].references = 0;

  strcpy(instructions[11].name, "fconst_0");
  instructions[11].arguments = 0;
  instructions[11].references = 0;

  strcpy(instructions[12].name, "fconst_1");
  instructions[12].arguments = 0;
  instructions[12].references = 0;

  strcpy(instructions[13].name, "fconst_2");
  instructions[13].arguments = 0;
  instructions[13].references = 0;

  strcpy(instructions[14].name, "dconst_0");
  instructions[14].arguments = 0;
  instructions[14].references = 0;

  strcpy(instructions[15].name, "dconst_1");
  instructions[15].arguments = 0;
  instructions[15].references = 0;

  strcpy(instructions[16].name, "bipush");
  instructions[16].arguments = 1;
  instructions[16].references = 0;

  strcpy(instructions[17].name, "sipush");
  instructions[17].arguments = 2;
  instructions[17].references = 0;

  strcpy(instructions[18].name, "ldc");
  instructions[18].arguments = 1;
  instructions[18].references = 1;

  strcpy(instructions[19].name, "ldc_w");
  instructions[19].arguments = 2;
  instructions[19].references = 1;

  strcpy(instructions[20].name, "ldc2_w");
  instructions[20].arguments = 2;
  instructions[20].references = 1;

  strcpy(instructions[21].name, "iload");
  instructions[21].arguments = 1;
  instructions[21].references = 0;

  strcpy(instructions[22].name, "lload");
  instructions[22].arguments = 1;
  instructions[22].references = 0;

  strcpy(instructions[23].name, "fload");
  instructions[23].arguments = 1;
  instructions[23].references = 0;

  strcpy(instructions[24].name, "dload");
  instructions[24].arguments = 1;
  instructions[24].references = 0;

  strcpy(instructions[25].name, "aload");
  instructions[25].arguments = 1;
  instructions[25].references = 0;

  strcpy(instructions[26].name, "iload_0");
  instructions[26].arguments = 0;
  instructions[26].references = 0;

  strcpy(instructions[27].name, "iload_1");
  instructions[27].arguments = 0;
  instructions[27].references = 0;

  strcpy(instructions[28].name, "iload_2");
  instructions[28].arguments = 0;
  instructions[28].references = 0;

  strcpy(instructions[29].name, "iload_3");
  instructions[29].arguments = 0;
  instructions[29].references = 0;

  strcpy(instructions[30].name, "lload_0");
  instructions[30].arguments = 0;
  instructions[30].references = 0;

  strcpy(instructions[31].name, "lload_1");
  instructions[31].arguments = 0;
  instructions[31].references = 0;

  strcpy(instructions[32].name, "lload_2");
  instructions[32].arguments = 0;
  instructions[32].references = 0;

  strcpy(instructions[33].name, "lload_3");
  instructions[33].arguments = 0;
  instructions[33].references = 0;

  strcpy(instructions[34].name, "fload_0");
  instructions[34].arguments = 0;
  instructions[34].references = 0;

  strcpy(instructions[35].name, "fload_1");
  instructions[35].arguments = 0;
  instructions[35].references = 0;

  strcpy(instructions[36].name, "fload_2");
  instructions[36].arguments = 0;
  instructions[36].references = 0;

  strcpy(instructions[37].name, "fload_3");
  instructions[37].arguments = 0;
  instructions[37].references = 0;

  strcpy(instructions[38].name, "dload_0");
  instructions[38].arguments = 0;
  instructions[38].references = 0;

  strcpy(instructions[39].name, "dload_1");
  instructions[39].arguments = 0;
  instructions[39].references = 0;

  strcpy(instructions[40].name, "dload_2");
  instructions[40].arguments = 0;
  instructions[40].references = 0;

  strcpy(instructions[41].name, "dload_3");
  instructions[41].arguments = 0;
  instructions[41].references = 0;

  strcpy(instructions[42].name, "aload_0");
  instructions[42].arguments = 0;
  instructions[42].references = 0;

  strcpy(instructions[43].name, "aload_1");
  instructions[43].arguments = 0;
  instructions[43].references = 0;

  strcpy(instructions[44].name, "aload_2");
  instructions[44].arguments = 0;
  instructions[40].references = 0;

  strcpy(instructions[45].name, "aload_3");
  instructions[45].arguments = 0;
  instructions[45].references = 0;

  strcpy(instructions[46].name, "iaload");
  instructions[46].arguments = 0;
  instructions[46].references = 0;

  strcpy(instructions[47].name, "laload");
  instructions[47].arguments = 0;
  instructions[47].references = 0;

  strcpy(instructions[48].name, "faload");
  instructions[48].arguments = 0;
  instructions[48].references = 0;

  strcpy(instructions[49].name, "daload");
  instructions[49].arguments = 0;
  instructions[49].references = 0;

  strcpy(instructions[50].name, "aaload");
  instructions[50].arguments = 0;
  instructions[50].references = 0;

  strcpy(instructions[51].name, "baload");
  instructions[51].arguments = 0;
  instructions[51].references = 0;

  strcpy(instructions[52].name, "caload");
  instructions[52].arguments = 0;
  instructions[52].references = 0;

  strcpy(instructions[53].name, "saload");
  instructions[53].arguments = 0;
  instructions[53].references = 0;

  strcpy(instructions[54].name, "istore");
  instructions[54].arguments = 1;
  instructions[54].references = 0;

  strcpy(instructions[55].name, "lstore");
  instructions[55].arguments = 1;
  instructions[55].references = 0;

  strcpy(instructions[56].name, "fstore");
  instructions[56].arguments = 1;
  instructions[56].references = 0;

  strcpy(instructions[57].name, "dstore");
  instructions[57].arguments = 1;
  instructions[57].references = 0;

  strcpy(instructions[58].name, "astore");
  instructions[58].arguments = 1;
  instructions[58].references = 0;

  strcpy(instructions[59].name, "istore_0");
  instructions[59].arguments = 0;
  instructions[59].references = 0;

  strcpy(instructions[60].name, "istore_1");
  instructions[60].arguments = 0;
  instructions[60].references = 0;

  strcpy(instructions[61].name, "istore_2");
  instructions[61].arguments = 0;
  instructions[61].references = 0;

  strcpy(instructions[62].name, "istore_3");
  instructions[62].arguments = 0;
  instructions[62].references = 0;

  strcpy(instructions[63].name, "lstore_0");
  instructions[63].arguments = 0;
  instructions[63].references = 0;

  strcpy(instructions[64].name, "lstore_1");
  instructions[64].arguments = 0;
  instructions[64].references = 0;

  strcpy(instructions[65].name, "lstore_2");
  instructions[65].arguments = 0;
  instructions[65].references = 0;

  strcpy(instructions[66].name, "lstore_3");
  instructions[66].arguments = 0;
  instructions[66].references = 0;

  strcpy(instructions[67].name, "fstore_0");
  instructions[67].arguments = 0;
  instructions[67].references = 0;

  strcpy(instructions[68].name, "fstore_1");
  instructions[68].arguments = 0;
  instructions[68].references = 0;

  strcpy(instructions[69].name, "fstore_2");
  instructions[69].arguments = 0;
  instructions[69].references = 0;

  strcpy(instructions[70].name, "fstore_3");
  instructions[70].arguments = 0;
  instructions[70].references = 0;

  strcpy(instructions[71].name, "dstore_0");
  instructions[71].arguments = 0;
  instructions[71].references = 0;

  strcpy(instructions[72].name, "dstore_1");
  instructions[72].arguments = 0;
  instructions[72].references = 0;

  strcpy(instructions[73].name, "dstore_2");
  instructions[73].arguments = 0;
  instructions[73].references = 0;

  strcpy(instructions[74].name, "dstore_3");
  instructions[74].arguments = 0;
  instructions[74].references = 0;

  strcpy(instructions[75].name, "astore_0");
  instructions[75].arguments = 0;
  instructions[75].references = 0;

  strcpy(instructions[76].name, "astore_1");
  instructions[76].arguments = 0;
  instructions[76].references = 0;

  strcpy(instructions[77].name, "astore_2");
  instructions[77].arguments = 0;
  instructions[77].references = 0;

  strcpy(instructions[78].name, "astore_3");
  instructions[78].arguments = 0;
  instructions[78].references = 0;

  strcpy(instructions[79].name, "iastore");
  instructions[79].arguments = 0;
  instructions[79].references = 0;

  strcpy(instructions[80].name, "lastore");
  instructions[80].arguments = 0;
  instructions[80].references = 0;

  strcpy(instructions[81].name, "fastore");
  instructions[81].arguments = 0;
  instructions[81].references = 0;

  strcpy(instructions[82].name, "dastore");
  instructions[82].arguments = 0;
  instructions[82].references = 0;

  strcpy(instructions[83].name, "aastore");
  instructions[83].arguments = 0;
  instructions[83].references = 0;

  strcpy(instructions[84].name, "bastore");
  instructions[84].arguments = 0;
  instructions[84].references = 0;

  strcpy(instructions[85].name, "castore");
  instructions[85].arguments = 0;
  instructions[85].references = 0;

  strcpy(instructions[86].name, "sastore");
  instructions[86].arguments = 0;
  instructions[86].references = 0;

  strcpy(instructions[87].name, "pop");
  instructions[87].arguments = 0;
  instructions[87].references = 0;

  strcpy(instructions[88].name, "pop2");
  instructions[88].arguments = 0;
  instructions[88].references = 0;

  strcpy(instructions[89].name, "dup");
  instructions[89].arguments = 0;
  instructions[89].references = 0;

  strcpy(instructions[90].name, "dup_x1");
  instructions[90].arguments = 0;
  instructions[90].references = 0;

  strcpy(instructions[91].name, "dup_x2");
  instructions[91].arguments = 0;
  instructions[91].references = 0;

  strcpy(instructions[92].name, "dup2");
  instructions[92].arguments = 0;
  instructions[92].references = 0;

  strcpy(instructions[93].name, "dup2_x1");
  instructions[93].arguments = 0;
  instructions[93].references = 0;

  strcpy(instructions[94].name, "dup2_x2");
  instructions[94].arguments = 0;
  instructions[94].references = 0;

  strcpy(instructions[95].name, "swap");
  instructions[95].arguments = 0;
  instructions[95].references = 0;

  strcpy(instructions[96].name, "iadd");
  instructions[96].arguments = 0;
  instructions[96].references = 0;

  strcpy(instructions[97].name, "ladd");
  instructions[97].arguments = 0;
  instructions[97].references = 0;

  strcpy(instructions[98].name, "fadd");
  instructions[98].arguments = 0;
  instructions[98].references = 0;

  strcpy(instructions[99].name, "dadd");
  instructions[99].arguments = 0;
  instructions[99].references = 0;

  strcpy(instructions[100].name, "isub");
  instructions[100].arguments = 0;
  instructions[100].references = 0;

  strcpy(instructions[101].name, "lsub");
  instructions[101].arguments = 0;
  instructions[101].references = 0;

  strcpy(instructions[102].name, "fsub");
  instructions[102].arguments = 0;
  instructions[102].references = 0;

  strcpy(instructions[103].name, "dsub");
  instructions[103].arguments = 0;
  instructions[103].references = 0;

  strcpy(instructions[104].name, "imul");
  instructions[104].arguments = 0;
  instructions[104].references = 0;

  strcpy(instructions[105].name, "lmul");
  instructions[105].arguments = 0;
  instructions[105].references = 0;

  strcpy(instructions[106].name, "fmul");
  instructions[106].arguments = 0;
  instructions[106].references = 0;

  strcpy(instructions[107].name, "dmul");
  instructions[107].arguments = 0;
  instructions[107].references = 0;

  strcpy(instructions[108].name, "idiv");
  instructions[108].arguments = 0;
  instructions[108].references = 0;

  strcpy(instructions[109].name, "ldiv");
  instructions[109].arguments = 0;
  instructions[109].references = 0;

  strcpy(instructions[110].name, "fdiv");
  instructions[110].arguments = 0;
  instructions[110].references = 0;

  strcpy(instructions[111].name, "ddiv");
  instructions[111].arguments = 0;
  instructions[111].references = 0;

  strcpy(instructions[112].name, "irem");
  instructions[112].arguments = 0;
  instructions[112].references = 0;

  strcpy(instructions[113].name, "lrem");
  instructions[113].arguments = 0;
  instructions[113].references = 0;

  strcpy(instructions[114].name, "frem");
  instructions[114].arguments = 0;
  instructions[114].references = 0;

  strcpy(instructions[115].name, "drem");
  instructions[115].arguments = 0;
  instructions[115].references = 0;

  strcpy(instructions[116].name, "ineg");
  instructions[116].arguments = 0;
  instructions[116].references = 0;

  strcpy(instructions[117].name, "lneg");
  instructions[117].arguments = 0;
  instructions[117].references = 0;

  strcpy(instructions[118].name, "fneg");
  instructions[118].arguments = 0;
  instructions[118].references = 0;

  strcpy(instructions[119].name, "dneg");
  instructions[119].arguments = 0;
  instructions[119].references = 0;

  strcpy(instructions[120].name, "ishl");
  instructions[120].arguments = 0;
  instructions[120].references = 0;

  strcpy(instructions[121].name, "lshl");
  instructions[121].arguments = 0;
  instructions[121].references = 0;

  strcpy(instructions[122].name, "ishr");
  instructions[122].arguments = 0;
  instructions[122].references = 0;

  strcpy(instructions[123].name, "lshr");
  instructions[123].arguments = 0;
  instructions[123].references = 0;

  strcpy(instructions[124].name, "iushr");
  instructions[124].arguments = 0;
  instructions[124].references = 0;

  strcpy(instructions[125].name, "lushr");
  instructions[125].arguments = 0;
  instructions[125].references = 0;

  strcpy(instructions[126].name, "iand");
  instructions[126].arguments = 0;
  instructions[126].references = 0;

  strcpy(instructions[127].name, "land");
  instructions[127].arguments = 0;
  instructions[127].references = 0;

  strcpy(instructions[128].name, "ior");
  instructions[128].arguments = 0;
  instructions[128].references = 0;

  strcpy(instructions[129].name, "lor");
  instructions[129].arguments = 0;
  instructions[129].references = 0;

  strcpy(instructions[130].name, "ixor");
  instructions[130].arguments = 0;
  instructions[130].references = 0;

  strcpy(instructions[131].name, "lxor");
  instructions[131].arguments = 0;
  instructions[131].references = 0;

  strcpy(instructions[132].name, "iinc");
  instructions[132].arguments = 2;
  instructions[132].references = 0;

  strcpy(instructions[133].name, "i2l");
  instructions[133].arguments = 0;
  instructions[133].references = 0;

  strcpy(instructions[134].name, "i2f");
  instructions[134].arguments = 0;
  instructions[134].references = 0;

  strcpy(instructions[135].name, "i2d");
  instructions[135].arguments = 0;
  instructions[135].references = 0;

  strcpy(instructions[136].name, "l2i");
  instructions[136].arguments = 0;
  instructions[136].references = 0;

  strcpy(instructions[137].name, "l2f");
  instructions[137].arguments = 0;
  instructions[137].references = 0;

  strcpy(instructions[138].name, "l2d");
  instructions[138].arguments = 0;
  instructions[138].references = 0;

  strcpy(instructions[139].name, "f2i");
  instructions[139].arguments = 0;
  instructions[139].references = 0;

  strcpy(instructions[140].name, "f2l");
  instructions[140].arguments = 0;
  instructions[140].references = 0;

  strcpy(instructions[141].name, "f2d");
  instructions[141].arguments = 0;
  instructions[141].references = 0;

  strcpy(instructions[142].name, "d2i");
  instructions[142].arguments = 0;
  instructions[142].references = 0;

  strcpy(instructions[143].name, "d2l");
  instructions[143].arguments = 0;
  instructions[143].references = 0;

  strcpy(instructions[144].name, "d2f");
  instructions[144].arguments = 0;
  instructions[144].references = 0;

  strcpy(instructions[145].name, "i2b");
  instructions[145].arguments = 0;
  instructions[145].references = 0;

  strcpy(instructions[146].name, "i2c");
  instructions[146].arguments = 0;
  instructions[146].references = 0;

  strcpy(instructions[147].name, "i2s");
  instructions[147].arguments = 0;
  instructions[146].references = 0;

  strcpy(instructions[148].name, "lcmp");
  instructions[148].arguments = 0;
  instructions[148].references = 0;

  strcpy(instructions[149].name, "fcmpl");
  instructions[149].arguments = 0;
  instructions[149].references = 0;

  strcpy(instructions[150].name, "fcmpg");
  instructions[150].arguments = 0;
  instructions[150].references = 0;

  strcpy(instructions[151].name, "dcmpl");
  instructions[151].arguments = 0;
  instructions[151].references = 0;

  strcpy(instructions[152].name, "dcmpg");
  instructions[152].arguments = 0;
  instructions[152].references = 0;

  strcpy(instructions[153].name, "ifeq");
  instructions[153].arguments = 2;
  instructions[153].references = 0;

  strcpy(instructions[154].name, "ifne");
  instructions[154].arguments = 2;
  instructions[154].references = 0;

  strcpy(instructions[155].name, "iflt");
  instructions[155].arguments = 2;
  instructions[155].references = 0;

  strcpy(instructions[156].name, "ifge");
  instructions[156].arguments = 2;
  instructions[156].references = 0;

  strcpy(instructions[157].name, "ifgt");
  instructions[157].arguments = 2;
  instructions[157].references = 0;

  strcpy(instructions[158].name, "ifle");
  instructions[158].arguments = 2;
  instructions[158].references = 0;

  strcpy(instructions[159].name, "if_icmpeq");
  instructions[159].arguments = 2;
  instructions[159].references = 0;

  strcpy(instructions[160].name, "if_icmpne");
  instructions[160].arguments = 2;
  instructions[160].references = 0;

  strcpy(instructions[161].name, "if_icmplt");
  instructions[161].arguments = 2;
  instructions[161].references = 0;

  strcpy(instructions[162].name, "if_icmpg2");
  instructions[162].arguments = 2;
  instructions[162].references = 0;

  strcpy(instructions[163].name, "if_icmpgt");
  instructions[163].arguments = 2;
  instructions[163].references = 0;

  strcpy(instructions[164].name, "if_icmple");
  instructions[164].arguments = 2;
  instructions[164].references = 0;

  strcpy(instructions[165].name, "if_acmpeq");
  instructions[165].arguments = 2;
  instructions[165].references = 0;

  strcpy(instructions[166].name, "if_acmpne");
  instructions[166].arguments = 2;
  instructions[166].references = 0;

  strcpy(instructions[167].name, "goto");
  instructions[167].arguments = 2;
  instructions[167].references = 0;

  strcpy(instructions[168].name, "jsr");
  instructions[168].arguments = 2;
  instructions[168].references = 0;

  strcpy(instructions[169].name, "ret");
  instructions[169].arguments = 1;
  instructions[169].references = 0;

  strcpy(instructions[170].name, "tableswitch");
  // instrução tem tamanho variável
  instructions[170].arguments = 34;
  instructions[170].references = 0;

  strcpy(instructions[171].name, "lookupswitch");
  // instrução tem tamanho variável
  instructions[171].arguments = 26;
  instructions[171].references = 0;

  strcpy(instructions[172].name, "ireturn");
  instructions[172].arguments = 0;
  instructions[172].references = 0;

  strcpy(instructions[173].name, "lreturn");
  instructions[173].arguments = 0;
  instructions[173].references = 0;

  strcpy(instructions[174].name, "freturn");
  instructions[174].arguments = 0;
  instructions[174].references = 0;

  strcpy(instructions[175].name, "dreturn");
  instructions[175].arguments = 0;
  instructions[175].references = 0;

  strcpy(instructions[176].name, "areturn");
  instructions[176].arguments = 0;
  instructions[176].references = 0;

  strcpy(instructions[177].name, "return");
  instructions[177].arguments = 0;
  instructions[177].references = 0;

  strcpy(instructions[178].name, "getstatic");
  instructions[178].arguments = 2;
  instructions[178].references = 1;

  strcpy(instructions[179].name, "putstatic");
  instructions[179].arguments = 2;
  instructions[179].references = 1;

  strcpy(instructions[180].name, "getfield");
  instructions[180].arguments = 2;
  instructions[180].references = 1;

  strcpy(instructions[181].name, "putfield");
  instructions[181].arguments = 2;
  instructions[181].references = 1;

  strcpy(instructions[182].name, "invokevirtual");
  instructions[182].arguments = 2;
  instructions[182].references = 1;

  strcpy(instructions[183].name, "invokespecial");
  instructions[183].arguments = 2;
  instructions[183].references = 1;

  strcpy(instructions[184].name, "invokestatic");
  instructions[184].arguments = 2;
  instructions[184].references = 1;

  strcpy(instructions[185].name, "invokeinterface");
  instructions[185].arguments = 4;
  instructions[185].references = 1;

  strcpy(instructions[186].name, "invokedynamic");
  instructions[186].arguments = 4;
  instructions[186].references = 1;

  strcpy(instructions[187].name, "new");
  instructions[187].arguments = 2;
  instructions[187].references = 1;

  strcpy(instructions[188].name, "newarray");
  instructions[188].arguments = 1;
  instructions[188].references = 0;

  strcpy(instructions[189].name, "anewarray");
  instructions[189].arguments = 2;
  instructions[189].references = 1;

  strcpy(instructions[190].name, "arraylength");
  instructions[190].arguments = 0;
  instructions[190].references = 0;

  strcpy(instructions[191].name, "athrow");
  instructions[191].arguments = 0;
  instructions[191].references = 0;

  strcpy(instructions[192].name, "checkcast");
  instructions[192].arguments = 2;
  instructions[192].references = 1;

  strcpy(instructions[193].name, "instanceof");
  instructions[193].arguments = 2;
  instructions[193].references = 1;

  strcpy(instructions[194].name, "monitorenter");
  instructions[194].arguments = 0;
  instructions[194].references = 0;

  strcpy(instructions[195].name, "monitorexit");
  instructions[195].arguments = 0;
  instructions[195].references = 0;

  strcpy(instructions[196].name, "wide");
  instructions[196].arguments = 3;
  instructions[196].references = 0;

  strcpy(instructions[197].name, "multianewarray");
  instructions[197].arguments = 3;
  instructions[197].references = 1;

  strcpy(instructions[198].name, "ifnull");
  instructions[198].arguments = 2;
  instructions[198].references = 0;

  strcpy(instructions[199].name, "ifnonnull");
  instructions[199].arguments = 2;
  instructions[199].references = 0;

  strcpy(instructions[200].name, "goto_w");
  instructions[200].arguments = 4;
  instructions[200].references = 0;

  strcpy(instructions[201].name, "jsr_w");
  instructions[201].arguments = 4;
  instructions[201].references = 0;

  // reservados
  strcpy(instructions[202].name, "breakpoint");
  instructions[200].arguments = 0;

  strcpy(instructions[254].name, "impdep1");
  instructions[254].arguments = 0;

  strcpy(instructions[255].name, "impdep2");
  instructions[255].arguments = 0;
}