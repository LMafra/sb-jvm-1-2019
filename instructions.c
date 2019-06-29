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
* @brief Instrucoes assembly
* @section DESCRIPTION
* 
*/

#include "instructions.h"

opcode instructions[300];

void initializeInstructions() {

  /**
   * @brief Não faz nada, só incrementa pc.
   * param 
   * @return void
   */

  strcpy(instructions[nop].name, "nop");
  instructions[nop].key = nop;
  instructions[nop].arguments = 0;

  strcpy(instructions[aconst_null].name, "aconst_null");
  instructions[aconst_null].key = aconst_null;
  instructions[aconst_null].arguments = 0;
  instructions[aconst_null].reference = 0;

  strcpy(instructions[iconst_m1].name, "iconst_m1");
  instructions[iconst_m1].key = iconst_m1;
  instructions[iconst_m1].arguments = 0;
  instructions[iconst_m1].reference = 0;

  strcpy(instructions[iconst_0].name, "iconst_0");
  instructions[iconst_0].key = iconst_0;
  instructions[iconst_0].arguments = 0;
  instructions[iconst_0].reference = 0;

  strcpy(instructions[iconst_1].name, "iconst_1");
  instructions[iconst_1].key = iconst_1;
  instructions[iconst_1].arguments = 0;
  instructions[iconst_1].reference = 0;

  strcpy(instructions[iconst_2].name, "iconst_2");
  instructions[iconst_2].key = iconst_2;
  instructions[iconst_2].arguments = 0;
  instructions[iconst_2].reference = 0;

  strcpy(instructions[iconst_3].name, "iconst_3");
  instructions[iconst_3].key = iconst_3;
  instructions[iconst_3].arguments = 0;
  instructions[iconst_3].reference = 0;

  strcpy(instructions[iconst_4].name, "iconst_4");
  instructions[iconst_4].key = iconst_4;
  instructions[iconst_4].arguments = 0;
  instructions[iconst_4].reference = 0;

  strcpy(instructions[iconst_5].name, "iconst_5");
  instructions[iconst_5].key = iconst_5;
  instructions[iconst_5].arguments = 0;
  instructions[iconst_5].reference = 0;

  strcpy(instructions[lconst_0].name, "lconst_0");
  instructions[lconst_0].key = lconst_0;
  instructions[lconst_0].arguments = 0;
  instructions[lconst_0].reference = 0;

  strcpy(instructions[lconst_1].name, "lconst_1");
  instructions[lconst_1].key = lconst_1;
  instructions[lconst_1].arguments = 0;
  instructions[lconst_1].reference = 0;

  strcpy(instructions[fconst_0].name, "fconst_0");
  instructions[fconst_0].key = fconst_0;
  instructions[fconst_0].arguments = 0;
  instructions[fconst_0].reference = 0;

  strcpy(instructions[fconst_1].name, "fconst_1");
  instructions[fconst_1].key = fconst_1;
  instructions[fconst_1].arguments = 0;
  instructions[fconst_1].reference = 0;

  strcpy(instructions[fconst_2].name, "fconst_2");
  instructions[fconst_2].key = fconst_2;
  instructions[fconst_2].arguments = 0;
  instructions[fconst_2].reference = 0;

  strcpy(instructions[dconst_0].name, "dconst_0");
  instructions[dconst_0].key = dconst_0;
  instructions[dconst_0].arguments = 0;
  instructions[dconst_0].reference = 0;

  strcpy(instructions[dconst_1].name, "dconst_1");
  instructions[dconst_1].key = dconst_1;
  instructions[dconst_1].arguments = 0;
  instructions[dconst_1].reference = 0;

  strcpy(instructions[bipush].name, "bipush");
  instructions[bipush].key = bipush;
  instructions[bipush].arguments = 1;
  instructions[bipush].reference = 0;

  strcpy(instructions[sipush].name, "sipush");
  instructions[sipush].key = sipush;
  instructions[sipush].arguments = 2;
  instructions[sipush].reference = 0;

  strcpy(instructions[ldc].name, "ldc");
  instructions[ldc].key = ldc;
  instructions[ldc].arguments = 1;
  instructions[ldc].reference = 1;

  strcpy(instructions[ldc_w].name, "ldc_w");
  instructions[ldc_w].key = ldc_w;
  instructions[ldc_w].arguments = 2;
  instructions[ldc_w].reference = 1;

  strcpy(instructions[ldc2_w].name, "ldc2_w");
  instructions[ldc2_w].key = ldc2_w;
  instructions[ldc2_w].arguments = 2;
  instructions[ldc2_w].reference = 1;

  strcpy(instructions[iload].name, "iload");
  instructions[iload].key = iload;
  instructions[iload].arguments = 1;
  instructions[iload].reference = 0;

  strcpy(instructions[lload].name, "lload");
  instructions[lload].key = lload;
  instructions[lload].arguments = 1;
  instructions[lload].reference = 0;

  strcpy(instructions[fload].name, "fload");
  instructions[fload].key = fload;
  instructions[fload].arguments = 1;
  instructions[fload].reference = 0;

  strcpy(instructions[dload].name, "dload");
  instructions[dload].key = dload;
  instructions[dload].arguments = 1;
  instructions[dload].reference = 0;

  strcpy(instructions[aload].name, "aload");
  instructions[aload].key = aload;
  instructions[aload].arguments = 1;
  instructions[aload].reference = 0;

  strcpy(instructions[iload_0].name, "iload_0");
  instructions[iload_0].key = iload_0;
  instructions[iload_0].arguments = 0;
  instructions[iload_0].reference = 0;

  strcpy(instructions[iload_1].name, "iload_1");
  instructions[iload_1].key = iload_1;
  instructions[iload_1].arguments = 0;
  instructions[iload_1].reference = 0;

  strcpy(instructions[iload_2].name, "iload_2");
  instructions[iload_2].key = iload_2;
  instructions[iload_2].arguments = 0;
  instructions[iload_2].reference = 0;

  strcpy(instructions[iload_3].name, "iload_3");
  instructions[iload_3].key = iload_3;
  instructions[iload_3].arguments = 0;
  instructions[iload_3].reference = 0;

  strcpy(instructions[lload_0].name, "lload_0");
  instructions[lload_0].key = lload_0;
  instructions[lload_0].arguments = 0;
  instructions[lload_0].reference = 0;

  strcpy(instructions[lload_1].name, "lload_1");
  instructions[lload_1].key = lload_1;
  instructions[lload_1].arguments = 0;
  instructions[lload_1].reference = 0;

  strcpy(instructions[lload_2].name, "lload_2");
  instructions[lload_2].key = lload_2;
  instructions[lload_2].arguments = 0;
  instructions[lload_2].reference = 0;

  strcpy(instructions[lload_3].name, "lload_3");
  instructions[lload_3].key = lload_3;
  instructions[lload_3].arguments = 0;
  instructions[lload_3].reference = 0;

  strcpy(instructions[fload_0].name, "fload_0");
  instructions[fload_0].key = fload_0;
  instructions[fload_0].arguments = 0;
  instructions[fload_0].reference = 0;

  strcpy(instructions[fload_1].name, "fload_1");
  instructions[fload_1].key = fload_1;
  instructions[fload_1].arguments = 0;
  instructions[fload_1].reference = 0;

  strcpy(instructions[fload_2].name, "fload_2");
  instructions[fload_2].key = fload_2;
  instructions[fload_2].arguments = 0;
  instructions[fload_2].reference = 0;

  strcpy(instructions[fload_3].name, "fload_3");
  instructions[fload_3].key = fload_3;
  instructions[fload_3].arguments = 0;
  instructions[fload_3].reference = 0;

  strcpy(instructions[dload_0].name, "dload_0");
  instructions[dload_0].key = dload_0;
  instructions[dload_0].arguments = 0;
  instructions[dload_0].reference = 0;

  strcpy(instructions[dload_1].name, "dload_1");
  instructions[dload_1].key = dload_1;
  instructions[dload_1].arguments = 0;
  instructions[dload_1].reference = 0;

  strcpy(instructions[dload_2].name, "dload_2");
  instructions[dload_2].key = dload_2;
  instructions[dload_2].arguments = 0;
  instructions[dload_2].reference = 0;

  strcpy(instructions[dload_3].name, "dload_3");
  instructions[dload_3].key = dload_3;
  instructions[dload_3].arguments = 0;
  instructions[dload_3].reference = 0;

  strcpy(instructions[aload_0].name, "aload_0");
  instructions[aload_0].key = aload_0;
  instructions[aload_0].arguments = 0;
  instructions[aload_0].reference = 0;

  strcpy(instructions[aload_1].name, "aload_1");
  instructions[aload_1].key = aload_1;
  instructions[aload_1].arguments = 0;
  instructions[aload_1].reference = 0;

  strcpy(instructions[aload_2].name, "aload_2");
  instructions[aload_2].key = aload_2;
  instructions[aload_2].arguments = 0;
  instructions[aload_2].reference = 0;

  strcpy(instructions[aload_3].name, "aload_3");
  instructions[aload_3].key = aload_3;
  instructions[aload_3].arguments = 0;
  instructions[aload_3].reference = 0;

  strcpy(instructions[iaload].name, "iaload");
  instructions[iaload].key = iaload;
  instructions[iaload].arguments = 0;
  instructions[iaload].reference = 0;

  strcpy(instructions[laload].name, "laload");
  instructions[laload].key = laload;
  instructions[laload].arguments = 0;
  instructions[laload].reference = 0;

  strcpy(instructions[faload].name, "faload");
  instructions[faload].key = faload;
  instructions[faload].arguments = 0;
  instructions[faload].reference = 0;

  strcpy(instructions[daload].name, "daload");
  instructions[daload].key = daload;
  instructions[daload].arguments = 0;
  instructions[daload].reference = 0;

  strcpy(instructions[aaload].name, "aaload");
  instructions[aaload].key = aaload;
  instructions[aaload].arguments = 0;
  instructions[aaload].reference = 0;

  strcpy(instructions[baload].name, "baload");
  instructions[baload].key = baload;
  instructions[baload].arguments = 0;
  instructions[baload].reference = 0;

  strcpy(instructions[caload].name, "caload");
  instructions[caload].key = caload;
  instructions[caload].arguments = 0;
  instructions[caload].reference = 0;

  strcpy(instructions[saload].name, "saload");
  instructions[saload].key = saload;
  instructions[saload].arguments = 0;
  instructions[saload].reference = 0;

  strcpy(instructions[istore].name, "istore");
  instructions[istore].key = istore;
  instructions[istore].arguments = 1;
  instructions[istore].reference = 0;

  strcpy(instructions[lstore].name, "lstore");
  instructions[lstore].key = lstore;
  instructions[lstore].arguments = 1;
  instructions[lstore].reference = 0;

  strcpy(instructions[fstore].name, "fstore");
  instructions[fstore].key = fstore;
  instructions[fstore].arguments = 1;
  instructions[fstore].reference = 0;

  strcpy(instructions[dstore].name, "dstore");
  instructions[dstore].key = dstore;
  instructions[dstore].arguments = 1;
  instructions[dstore].reference = 0;

  strcpy(instructions[astore].name, "astore");
  instructions[astore].key = astore;
  instructions[astore].arguments = 1;
  instructions[astore].reference = 0;

  strcpy(instructions[istore_0].name, "istore_0");
  instructions[istore_0].key = istore_0;
  instructions[istore_0].arguments = 0;
  instructions[istore_0].reference = 0;

  strcpy(instructions[istore_1].name, "istore_1");
  instructions[istore_1].key = istore_1;
  instructions[istore_1].arguments = 0;
  instructions[istore_1].reference = 0;

  strcpy(instructions[istore_2].name, "istore_2");
  instructions[istore_2].key = istore_2;
  instructions[istore_2].arguments = 0;
  instructions[istore_2].reference = 0;

  strcpy(instructions[istore_3].name, "istore_3");
  instructions[istore_3].key = istore_3;
  instructions[istore_3].arguments = 0;
  instructions[istore_3].reference = 0;

  strcpy(instructions[lstore_0].name, "lstore_0");
  instructions[lstore_0].key = lstore_0;
  instructions[lstore_0].arguments = 0;
  instructions[lstore_0].reference = 0;

  strcpy(instructions[lstore_1].name, "lstore_1");
  instructions[lstore_1].key = lstore_1;
  instructions[lstore_1].arguments = 0;
  instructions[lstore_1].reference = 0;

  strcpy(instructions[lstore_2].name, "lstore_2");
  instructions[lstore_2].key = lstore_2;
  instructions[lstore_2].arguments = 0;
  instructions[lstore_2].reference = 0;

  strcpy(instructions[lstore_3].name, "lstore_3");
  instructions[lstore_3].key = lstore_3;
  instructions[lstore_3].arguments = 0;
  instructions[lstore_3].reference = 0;

  strcpy(instructions[fstore_0].name, "fstore_0");
  instructions[fstore_0].key = fstore_0;
  instructions[fstore_0].arguments = 0;
  instructions[fstore_0].reference = 0;

  strcpy(instructions[fstore_1].name, "fstore_1");
  instructions[fstore_1].key = fstore_1;
  instructions[fstore_1].arguments = 0;
  instructions[fstore_1].reference = 0;

  strcpy(instructions[fstore_2].name, "fstore_2");
  instructions[fstore_2].key = fstore_2;
  instructions[fstore_2].arguments = 0;
  instructions[fstore_2].reference = 0;

  strcpy(instructions[fstore_3].name, "fstore_3");
  instructions[fstore_3].key = fstore_3;
  instructions[fstore_3].arguments = 0;
  instructions[fstore_3].reference = 0;

  strcpy(instructions[dstore_0].name, "dstore_0");
  instructions[dstore_0].key = dstore_0;
  instructions[dstore_0].arguments = 0;
  instructions[dstore_0].reference = 0;

  strcpy(instructions[dstore_1].name, "dstore_1");
  instructions[dstore_1].key = dstore_1;
  instructions[dstore_1].arguments = 0;
  instructions[dstore_1].reference = 0;

  strcpy(instructions[dstore_2].name, "dstore_2");
  instructions[dstore_2].key = dstore_2;
  instructions[dstore_2].arguments = 0;
  instructions[dstore_2].reference = 0;

  strcpy(instructions[dstore_3].name, "dstore_3");
  instructions[dstore_3].key = dstore_3;
  instructions[dstore_3].arguments = 0;
  instructions[dstore_3].reference = 0;

  strcpy(instructions[astore_0].name, "astore_0");
  instructions[astore_0].key = astore_0;
  instructions[astore_0].arguments = 0;
  instructions[astore_0].reference = 0;

  strcpy(instructions[astore_1].name, "astore_1");
  instructions[astore_1].key = astore_1;
  instructions[astore_1].arguments = 0;
  instructions[astore_1].reference = 0;

  strcpy(instructions[astore_2].name, "astore_2");
  instructions[astore_2].key = astore_2;
  instructions[astore_2].arguments = 0;
  instructions[astore_2].reference = 0;

  strcpy(instructions[astore_3].name, "astore_3");
  instructions[astore_3].key = astore_3;
  instructions[astore_3].arguments = 0;
  instructions[astore_3].reference = 0;

  strcpy(instructions[iastore].name, "iastore");
  instructions[iastore].key = iastore;
  instructions[iastore].arguments = 0;
  instructions[iastore].reference = 0;

  strcpy(instructions[lastore].name, "lastore");
  instructions[lastore].key = lastore;
  instructions[lastore].arguments = 0;
  instructions[lastore].reference = 0;

  strcpy(instructions[fastore].name, "fastore");
  instructions[fastore].key = fastore;
  instructions[fastore].arguments = 0;
  instructions[fastore].reference = 0;

  strcpy(instructions[dastore].name, "dastore");
  instructions[dastore].key = dastore;
  instructions[dastore].arguments = 0;
  instructions[dastore].reference = 0;

  strcpy(instructions[aastore].name, "aastore");
  instructions[aastore].key = aastore;
  instructions[aastore].arguments = 0;
  instructions[aastore].reference = 0;

  strcpy(instructions[bastore].name, "bastore");
  instructions[bastore].key = bastore;
  instructions[bastore].arguments = 0;
  instructions[bastore].reference = 0;

  strcpy(instructions[castore].name, "castore");
  instructions[castore].key = castore;
  instructions[castore].arguments = 0;
  instructions[castore].reference = 0;

  strcpy(instructions[sastore].name, "sastore");
  instructions[sastore].key = sastore;
  instructions[sastore].arguments = 0;
  instructions[sastore].reference = 0;

  strcpy(instructions[pop].name, "pop");
  instructions[pop].key = pop;
  instructions[pop].arguments = 0;
  instructions[pop].reference = 0;

  strcpy(instructions[pop2].name, "pop2");
  instructions[pop2].key = pop2;
  instructions[pop2].arguments = 0;
  instructions[pop2].reference = 0;

  strcpy(instructions[dup].name, "dup");
  instructions[dup].key = dup;
  instructions[dup].arguments = 0;
  instructions[dup].reference = 0;

  strcpy(instructions[dup_x1].name, "dup_x1");
  instructions[dup_x1].key = dup_x1;
  instructions[dup_x1].arguments = 0;
  instructions[dup_x1].reference = 0;

  strcpy(instructions[dup_x2].name, "dup_x2");
  instructions[dup_x2].key = dup_x2;
  instructions[dup_x2].arguments = 0;
  instructions[dup_x2].reference = 0;

  strcpy(instructions[dup2].name, "dup2");
  instructions[dup2].key = dup2;
  instructions[dup2].arguments = 0;
  instructions[dup2].reference = 0;

  strcpy(instructions[dup2_x1].name, "dup2_x1");
  instructions[dup2_x1].key = dup2_x1;
  instructions[dup2_x1].arguments = 0;
  instructions[dup2_x1].reference = 0;

  strcpy(instructions[dup2_x2].name, "dup2_x2");
  instructions[dup2_x2].key = dup2_x2;
  instructions[dup2_x2].arguments = 0;
  instructions[dup2_x2].reference = 0;

  strcpy(instructions[swap].name, "swap");
  instructions[swap].key = swap;
  instructions[swap].arguments = 0;
  instructions[swap].reference = 0;

  strcpy(instructions[iadd].name, "iadd");
  instructions[iadd].key = iadd;
  instructions[iadd].arguments = 0;
  instructions[iadd].reference = 0;

  strcpy(instructions[ladd].name, "ladd");
  instructions[ladd].key = ladd;
  instructions[ladd].arguments = 0;
  instructions[ladd].reference = 0;

  strcpy(instructions[fadd].name, "fadd");
  instructions[fadd].key = fadd;
  instructions[fadd].arguments = 0;
  instructions[fadd].reference = 0;

  strcpy(instructions[dadd].name, "dadd");
  instructions[dadd].key = dadd;
  instructions[dadd].arguments = 0;
  instructions[dadd].reference = 0;

  strcpy(instructions[isub].name, "isub");
  instructions[isub].key = isub;
  instructions[isub].arguments = 0;
  instructions[isub].reference = 0;

  strcpy(instructions[lsub].name, "lsub");
  instructions[lsub].key = lsub;
  instructions[lsub].arguments = 0;
  instructions[lsub].reference = 0;

  strcpy(instructions[fsub].name, "fsub");
  instructions[fsub].key = fsub;
  instructions[fsub].arguments = 0;
  instructions[fsub].reference = 0;

  strcpy(instructions[dsub].name, "dsub");
  instructions[dsub].key = dsub;
  instructions[dsub].arguments = 0;
  instructions[dsub].reference = 0;

  strcpy(instructions[imul].name, "imul");
  instructions[imul].key = imul;
  instructions[imul].arguments = 0;
  instructions[imul].reference = 0;

  strcpy(instructions[lmul].name, "lmul");
  instructions[lmul].key = lmul;
  instructions[lmul].arguments = 0;
  instructions[lmul].reference = 0;

  strcpy(instructions[fmul].name, "fmul");
  instructions[fmul].key = fmul;
  instructions[fmul].arguments = 0;
  instructions[fmul].reference = 0;

  strcpy(instructions[dmul].name, "dmul");
  instructions[dmul].key = dmul;
  instructions[dmul].arguments = 0;
  instructions[dmul].reference = 0;

  strcpy(instructions[idiv].name, "idiv");
  instructions[idiv].key = idiv;
  instructions[idiv].arguments = 0;
  instructions[idiv].reference = 0;

  strcpy(instructions[inst_ldiv].name, "ldiv");
  instructions[inst_ldiv].key = inst_ldiv;
  instructions[inst_ldiv].arguments = 0;
  instructions[inst_ldiv].reference = 0;

  strcpy(instructions[fdiv].name, "fdiv");
  instructions[fdiv].key = fdiv;
  instructions[fdiv].arguments = 0;
  instructions[fdiv].reference = 0;

  strcpy(instructions[ddiv].name, "ddiv");
  instructions[ddiv].key = ddiv;
  instructions[ddiv].arguments = 0;
  instructions[ddiv].reference = 0;

  strcpy(instructions[irem].name, "irem");
  instructions[irem].key = irem;
  instructions[irem].arguments = 0;
  instructions[irem].reference = 0;

  strcpy(instructions[lrem].name, "lrem");
  instructions[lrem].key = lrem;
  instructions[lrem].arguments = 0;
  instructions[lrem].reference = 0;

  strcpy(instructions[frem].name, "frem");
  instructions[frem].key = frem;
  instructions[frem].arguments = 0;
  instructions[frem].reference = 0;

  strcpy(instructions[drem].name, "drem");
  instructions[drem].key = drem;
  instructions[drem].arguments = 0;
  instructions[drem].reference = 0;

  strcpy(instructions[ineg].name, "ineg");
  instructions[ineg].key = ineg;
  instructions[ineg].arguments = 0;
  instructions[ineg].reference = 0;

  strcpy(instructions[lneg].name, "lneg");
  instructions[lneg].key = lneg;
  instructions[lneg].arguments = 0;
  instructions[lneg].reference = 0;

  strcpy(instructions[fneg].name, "fneg");
  instructions[fneg].key = fneg;
  instructions[fneg].arguments = 0;
  instructions[fneg].reference = 0;

  strcpy(instructions[dneg].name, "dneg");
  instructions[dneg].key = dneg;
  instructions[dneg].arguments = 0;
  instructions[dneg].reference = 0;

  strcpy(instructions[ishl].name, "ishl");
  instructions[ishl].key = ishl;
  instructions[ishl].arguments = 0;
  instructions[ishl].reference = 0;

  strcpy(instructions[lshl].name, "lshl");
  instructions[lshl].key = lshl;
  instructions[lshl].arguments = 0;
  instructions[lshl].reference = 0;

  strcpy(instructions[ishr].name, "ishr");
  instructions[ishr].key = ishr;
  instructions[ishr].arguments = 0;
  instructions[ishr].reference = 0;

  strcpy(instructions[lshr].name, "lshr");
  instructions[lshr].key = lshr;
  instructions[lshr].arguments = 0;
  instructions[lshr].reference = 0;

  strcpy(instructions[iushr].name, "iushr");
  instructions[iushr].key = iushr;
  instructions[iushr].arguments = 0;
  instructions[iushr].reference = 0;

  strcpy(instructions[lushr].name, "lushr");
  instructions[lushr].key = lushr;
  instructions[lushr].arguments = 0;
  instructions[lushr].reference = 0;

  strcpy(instructions[iand].name, "iand");
  instructions[iand].key = iand;
  instructions[iand].arguments = 0;
  instructions[iand].reference = 0;

  strcpy(instructions[land].name, "land");
  instructions[land].key = land;
  instructions[land].arguments = 0;
  instructions[land].reference = 0;

  strcpy(instructions[ior].name, "ior");
  instructions[ior].key = ior;
  instructions[ior].arguments = 0;
  instructions[ior].reference = 0;

  strcpy(instructions[lor].name, "lor");
  instructions[lor].key = lor;
  instructions[lor].arguments = 0;
  instructions[lor].reference = 0;

  strcpy(instructions[ixor].name, "ixor");
  instructions[ixor].key = ixor;
  instructions[ixor].arguments = 0;
  instructions[ixor].reference = 0;

  strcpy(instructions[lxor].name, "lxor");
  instructions[lxor].key = lxor;
  instructions[lxor].arguments = 0;
  instructions[lxor].reference = 0;

  strcpy(instructions[iinc].name, "iinc");
  instructions[iinc].key = iinc;
  instructions[iinc].arguments = 2;
  instructions[iinc].reference = 0;

  strcpy(instructions[i2l].name, "i2l");
  instructions[i2l].key = i2l;
  instructions[i2l].arguments = 0;
  instructions[i2l].reference = 0;

  strcpy(instructions[i2f].name, "i2f");
  instructions[i2f].key = i2f;
  instructions[i2f].arguments = 0;
  instructions[i2f].reference = 0;

  strcpy(instructions[i2d].name, "i2d");
  instructions[i2d].key = i2d;
  instructions[i2d].arguments = 0;
  instructions[i2d].reference = 0;

  strcpy(instructions[l2i].name, "l2i");
  instructions[l2i].key = l2i;
  instructions[l2i].arguments = 0;
  instructions[l2i].reference = 0;

  strcpy(instructions[l2f].name, "l2f");
  instructions[l2f].key = l2f;
  instructions[l2f].arguments = 0;
  instructions[l2f].reference = 0;

  strcpy(instructions[l2d].name, "l2d");
  instructions[l2d].key = l2d;
  instructions[l2d].arguments = 0;
  instructions[l2d].reference = 0;

  strcpy(instructions[f2i].name, "f2i");
  instructions[f2i].key = f2i;
  instructions[f2i].arguments = 0;
  instructions[f2i].reference = 0;

  strcpy(instructions[f2l].name, "f2l");
  instructions[f2l].key = f2l;
  instructions[f2l].arguments = 0;
  instructions[f2l].reference = 0;

  strcpy(instructions[f2d].name, "f2d");
  instructions[f2d].key = f2d;
  instructions[f2d].arguments = 0;
  instructions[f2d].reference = 0;

  strcpy(instructions[d2i].name, "d2i");
  instructions[d2i].key = d2i;
  instructions[d2i].arguments = 0;
  instructions[d2i].reference = 0;

  strcpy(instructions[d2l].name, "d2l");
  instructions[d2l].key = d2l;
  instructions[d2l].arguments = 0;
  instructions[d2l].reference = 0;

  strcpy(instructions[d2f].name, "d2f");
  instructions[d2f].key = d2f;
  instructions[d2f].arguments = 0;
  instructions[d2f].reference = 0;

  strcpy(instructions[i2b].name, "i2b");
  instructions[i2b].key = i2b;
  instructions[i2b].arguments = 0;
  instructions[i2b].reference = 0;

  strcpy(instructions[i2c].name, "i2c");
  instructions[i2c].key = i2c;
  instructions[i2c].arguments = 0;
  instructions[i2c].reference = 0;

  strcpy(instructions[i2s].name, "i2s");
  instructions[i2s].key = i2s;
  instructions[i2s].arguments = 0;
  instructions[i2s].reference = 0;

  strcpy(instructions[lcmp].name, "lcmp");
  instructions[lcmp].key = lcmp;
  instructions[lcmp].arguments = 0;
  instructions[lcmp].reference = 0;

  strcpy(instructions[fcmpl].name, "fcmpl");
  instructions[fcmpl].key = fcmpl;
  instructions[fcmpl].arguments = 0;
  instructions[fcmpl].reference = 0;

  strcpy(instructions[fcmpg].name, "fcmpg");
  instructions[fcmpg].key = fcmpg;
  instructions[fcmpg].arguments = 0;
  instructions[fcmpg].reference = 0;

  strcpy(instructions[dcmpl].name, "dcmpl");
  instructions[dcmpl].key = dcmpl;
  instructions[dcmpl].arguments = 0;
  instructions[dcmpl].reference = 0;

  strcpy(instructions[dcmpg].name, "dcmpg");
  instructions[dcmpg].key = dcmpg;
  instructions[dcmpg].arguments = 0;
  instructions[dcmpg].reference = 0;

  strcpy(instructions[ifeq].name, "ifeq");
  instructions[ifeq].key = ifeq;
  instructions[ifeq].arguments = 2;
  instructions[ifeq].reference = 0;

  strcpy(instructions[ifne].name, "ifne");
  instructions[ifne].key = ifne;
  instructions[ifne].arguments = 2;
  instructions[ifne].reference = 0;

  strcpy(instructions[iflt].name, "iflt");
  instructions[iflt].key = iflt;
  instructions[iflt].arguments = 2;
  instructions[iflt].reference = 0;

  strcpy(instructions[ifge].name, "ifge");
  instructions[ifge].key = ifge;
  instructions[ifge].arguments = 2;
  instructions[ifge].reference = 0;

  strcpy(instructions[ifgt].name, "ifgt");
  instructions[ifgt].key = ifgt;
  instructions[ifgt].arguments = 2;
  instructions[ifgt].reference = 0;

  strcpy(instructions[ifle].name, "ifle");
  instructions[ifle].key = ifle;
  instructions[ifle].arguments = 2;
  instructions[ifle].reference = 0;

  strcpy(instructions[if_icmpeq].name, "if_icmpeq");
  instructions[if_icmpeq].key = if_icmpeq;
  instructions[if_icmpeq].arguments = 2;
  instructions[if_icmpeq].reference = 0;

  strcpy(instructions[if_icmpne].name, "if_icmpne");
  instructions[if_icmpne].key = if_icmpne;
  instructions[if_icmpne].arguments = 2;
  instructions[if_icmpne].reference = 0;

  strcpy(instructions[if_icmplt].name, "if_icmplt");
  instructions[if_icmplt].key = if_icmplt;
  instructions[if_icmplt].arguments = 2;
  instructions[if_icmplt].reference = 0;

  strcpy(instructions[if_icmpge].name, "if_icmpge");
  instructions[if_icmpge].key = if_icmpge;
  instructions[if_icmpge].arguments = 2;
  instructions[if_icmpge].reference = 0;

  strcpy(instructions[if_icmpgt].name, "if_icmpgt");
  instructions[if_icmpgt].key = if_icmpgt;
  instructions[if_icmpgt].arguments = 2;
  instructions[if_icmpgt].reference = 0;

  strcpy(instructions[if_icmple].name, "if_icmple");
  instructions[if_icmple].key = if_icmple;
  instructions[if_icmple].arguments = 2;
  instructions[if_icmple].reference = 0;

  strcpy(instructions[if_acmpeq].name, "if_acmpeq");
  instructions[if_acmpeq].key = if_acmpeq;
  instructions[if_acmpeq].arguments = 2;
  instructions[if_acmpeq].reference = 0;

  strcpy(instructions[if_acmpne].name, "if_acmpne");
  instructions[if_acmpne].key = if_acmpne;
  instructions[if_acmpne].arguments = 2;
  instructions[if_acmpne].reference = 0;

  strcpy(instructions[inst_goto].name, "goto");
  instructions[inst_goto].key = inst_goto;
  instructions[inst_goto].arguments = 2;
  instructions[inst_goto].reference = 0;

  strcpy(instructions[jsr].name, "jsr");
  instructions[jsr].key = jsr;
  instructions[jsr].arguments = 2;
  instructions[jsr].reference = 0;

  strcpy(instructions[ret].name, "ret");
  instructions[ret].key = ret;
  instructions[ret].arguments = 1;
  instructions[ret].reference = 0;

  strcpy(instructions[170].name, "tableswitch");
  // instrução tem tableswitcho tableswitchl
  instructions[tableswitch].key = tableswitch;
  instructions[tableswitch].arguments = 34;
  instructions[tableswitch].reference = 0;

  strcpy(instructions[171].name, "lookupswitch");
  // instrução tem lookupswitcho lookupswitchl
  instructions[lookupswitch].key = lookupswitch;
  instructions[lookupswitch].arguments = 0;
  instructions[lookupswitch].reference = 0;

  strcpy(instructions[ireturn].name, "ireturn");
  instructions[ireturn].key = ireturn;
  instructions[ireturn].arguments = 0;
  instructions[ireturn].reference = 0;

  strcpy(instructions[lreturn].name, "lreturn");
  instructions[lreturn].key = lreturn;
  instructions[lreturn].arguments = 0;
  instructions[lreturn].reference = 0;

  strcpy(instructions[freturn].name, "freturn");
  instructions[freturn].key = freturn;
  instructions[freturn].arguments = 0;
  instructions[freturn].reference = 0;

  strcpy(instructions[dreturn].name, "dreturn");
  instructions[dreturn].key = dreturn;
  instructions[dreturn].arguments = 0;
  instructions[dreturn].reference = 0;

  strcpy(instructions[areturn].name, "areturn");
  instructions[areturn].key = areturn;
  instructions[areturn].arguments = 0;
  instructions[areturn].reference = 0;

  strcpy(instructions[inst_return].name, "return");
  instructions[inst_return].key = inst_return;
  instructions[inst_return].arguments = 0;
  instructions[inst_return].reference = 0;

  strcpy(instructions[getstatic].name, "getstatic");
  instructions[getstatic].key = getstatic;
  instructions[getstatic].arguments = 2;
  instructions[getstatic].reference = 1;

  strcpy(instructions[putstatic].name, "putstatic");
  instructions[putstatic].key = putstatic;
  instructions[putstatic].arguments = 2;
  instructions[putstatic].reference = 1;

  strcpy(instructions[getfield].name, "getfield");
  instructions[getfield].key = getfield;
  instructions[getfield].arguments = 2;
  instructions[getfield].reference = 1;

  strcpy(instructions[putfield].name, "putfield");
  instructions[putfield].key = putfield;
  instructions[putfield].arguments = 2;
  instructions[putfield].reference = 1;

  strcpy(instructions[invokevirtual].name, "invokevirtual");
  instructions[invokevirtual].key = invokevirtual;
  instructions[invokevirtual].arguments = 2;
  instructions[invokevirtual].reference = 1;

  strcpy(instructions[invokespecial].name, "invokespecial");
  instructions[invokespecial].key = invokespecial;
  instructions[invokespecial].arguments = 2;
  instructions[invokespecial].reference = 1;

  strcpy(instructions[invokestatic].name, "invokestatic");
  instructions[invokestatic].key = invokestatic;
  instructions[invokestatic].arguments = 2;
  instructions[invokestatic].reference = 1;

  strcpy(instructions[invokeinterface].name, "invokeinterface");
  instructions[invokeinterface].key = invokeinterface;
  instructions[invokeinterface].arguments = 4;
  instructions[invokeinterface].reference = 1;

  strcpy(instructions[invokedynamic].name, "invokedynamic");
  instructions[invokedynamic].key = invokedynamic;
  instructions[invokedynamic].arguments = 4;
  instructions[invokedynamic].reference = 1;

  strcpy(instructions[inst_new].name, "new");
  instructions[inst_new].key = inst_new;
  instructions[inst_new].arguments = 2;
  instructions[inst_new].reference = 1;

  strcpy(instructions[newarray].name, "newarray");
  instructions[newarray].key = newarray;
  instructions[newarray].arguments = 1;
  instructions[newarray].reference = 0;

  strcpy(instructions[anewarray].name, "anewarray");
  instructions[anewarray].key = anewarray;
  instructions[anewarray].arguments = 2;
  instructions[anewarray].reference = 1;

  strcpy(instructions[arraylength].name, "arraylength");
  instructions[arraylength].key = arraylength;
  instructions[arraylength].arguments = 0;
  instructions[arraylength].reference = 0;

  strcpy(instructions[athrow].name, "athrow");
  instructions[athrow].key = athrow;
  instructions[athrow].arguments = 0;
  instructions[athrow].reference = 0;

  strcpy(instructions[checkcast].name, "checkcast");
  instructions[checkcast].key = checkcast;
  instructions[checkcast].arguments = 2;
  instructions[checkcast].reference = 1;

  strcpy(instructions[instanceof].name, "instanceof");
  instructions[instanceof].key = instanceof;
  instructions[instanceof].arguments = 2;
  instructions[instanceof].reference = 1;

  strcpy(instructions[monitorenter].name, "monitorenter");
  instructions[monitorenter].key = monitorenter;
  instructions[monitorenter].arguments = 0;
  instructions[monitorenter].reference = 0;

  strcpy(instructions[monitorexit].name, "monitorexit");
  instructions[monitorexit].key = monitorexit;
  instructions[monitorexit].arguments = 0;
  instructions[monitorexit].reference = 0;

  strcpy(instructions[wide].name, "wide");
  instructions[wide].key = wide;
  instructions[wide].arguments = 5;
  instructions[wide].reference = 0;

  strcpy(instructions[multianewarray].name, "multianewarray");
  instructions[multianewarray].key = multianewarray;
  instructions[multianewarray].arguments = 3;
  instructions[multianewarray].reference = 1;

  strcpy(instructions[ifnull].name, "ifnull");
  instructions[ifnull].key = ifnull;
  instructions[ifnull].arguments = 2;
  instructions[ifnull].reference = 0;

  strcpy(instructions[ifnonnull].name, "ifnonnull");
  instructions[ifnonnull].key = ifnonnull;
  instructions[ifnonnull].arguments = 2;
  instructions[ifnonnull].reference = 0;

  strcpy(instructions[goto_w].name, "goto_w");
  instructions[goto_w].key = goto_w;
  instructions[goto_w].arguments = 4;
  instructions[goto_w].reference = 0;

  strcpy(instructions[jsr_w].name, "jsr_w");
  instructions[jsr_w].key = jsr_w;
  instructions[jsr_w].arguments = 4;
  instructions[jsr_w].reference = 0;
}