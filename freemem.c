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
* @brief \n
* @section DESCRIPTION
*/

#include "reader.h"

void freeMemory(classFile* cf) {
	free(cf->interfaces);

  for(int i = 0; i < cf->fields_count; i++) {
    free(cf->fields[i].attributes);
  }
  free(cf->fields);

  for(int i = 0; i < cf->methods_count; i++){
    for(int j = 0; j < cf->methods[i].attributes_count; j++) {
      uint16_t cp_index = cf->methods[i].attributes[j].attribute_name_index - 1;
			if (!strcmp((char*)cf->constant_pool[cp_index].info.Utf8.bytes, "Code")) {
				for (int k = 0; k < cf->methods[i].attributes[j].att_info.Code.attributes_count; k++){
					uint16_t cp_indexao = cf->methods[i].attributes[j].att_info.Code.attributes[k].attribute_name_index - 1;
					if (!strcmp((char*)cf->constant_pool[cp_indexao].info.Utf8.bytes, "LineNumberTable")) {
						free(cf->methods[i].attributes[j].att_info.Code.attributes[k].att_info.LineNumberTable.line_number_table_array);
          }
				}
      } else if (!strcmp((char*)cf->constant_pool[cp_index].info.Utf8.bytes, "Exceptions")) {
        free(cf->methods[i].attributes[j].att_info.Exceptions.exception_index_table);
      }
      free(cf->methods[i].attributes[j].att_info.Code.code);
      free(cf->methods[i].attributes[j].att_info.Code.exception_table_array);
      free(cf->methods[i].attributes[j].att_info.Code.attributes);
    }
    free(cf->methods[i].attributes);
  }
  free(cf->methods);

  for (int i = 0; i < cf->attributes_count; i++) {
    uint16_t cp_index = cf->attributes[i].attribute_name_index - 1;
    if (!strcmp((char*)cf->constant_pool[cp_index].info.Utf8.bytes, "BootstrapMethods")) {
			for (int j = 0; j < cf->attributes[i].att_info.BootstrapMethods.bootstrap_methods_length; j++){
				free(cf->attributes[i].att_info.BootstrapMethods.bootstrap_methods_array[j].bootstrap_arguments);
			}
    free(cf->attributes[i].att_info.BootstrapMethods.bootstrap_methods_array);
		}
  }
  free(cf->attributes);

  for(int i = 0; i < cf->constant_pool_count-1; i++) { 
    switch (cf->constant_pool[i].tag) { 
      case CONSTANT_Long:
        i++;
        break;
      case CONSTANT_Double:
        i++;
        break;
      case CONSTANT_Utf8:
        free(cf->constant_pool[i].info.Utf8.bytes);
        break;
      default:
        break;
    }
  }

	free(cf->constant_pool); 
  free(cf);
}