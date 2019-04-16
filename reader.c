#include "reader.h"

classFile* classReader(char * className) {
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
		printf("Invalid .class!");
		printf("Finalizando");
		exit(0);
	}

	/* first info */
	cf->minor_version = read2bytes(file);
	cf->major_version = read2bytes(file);
	cf->constant_pool_count = read2bytes(file);

	/* constant pool read */
	cf->constant_pool = (cp_info* ) malloc((cf->constant_pool_count-1) * sizeof(cp_info));
	cp_info* cp = cf->constant_pool;

	for(int i = 0; i < cf->constant_pool_count-1; i++) {
		cp->tag = read1byte(file);
		switch (cp->tag) { /* adicionar checagem se constantes sao validas */
			case CONSTANT_Class:
				cp->info.Class.name_index = read2bytes(file);
				break;
			case CONSTANT_Fieldref:
				cp->info.Fieldref.class_index = read2bytes(file);
				cp->info.Fieldref.name_and_type_index = read2bytes(file);
				break;
			case CONSTANT_Methodref:
				cp->info.Methodref.class_index = read2bytes(file);
				cp->info.Methodref.name_and_type_index = read2bytes(file);
				break;
			case CONSTANT_InterfaceMethodref:
				cp->info.InterfaceMethodref.class_index = read2bytes(file);
				cp->info.InterfaceMethodref.name_and_type_index = read2bytes(file);
				break;
			case CONSTANT_String:
				cp->info.String.string_index = read2bytes(file);
				break;	
			case CONSTANT_Integer:
				cp->info.Integer.bytes = read4bytes(file);
				break;
			case CONSTANT_Float:
				cp->info.Float.bytes = read4bytes(file);
				break;
			case CONSTANT_Long:
				cp->info.Long.high_bytes = read4bytes(file);
				cp->info.Long.low_bytes = read4bytes(file);
				/* como tem o dobro do tamanho normal, aponta duas vezes o tamanho normal para pegar a proxima constant */
				cp++; i++;
			case CONSTANT_Double:
				cp->info.Double.high_bytes = read4bytes(file);
				cp->info.Double.low_bytes = read4bytes(file);
				cp++; i++;
				break;
			case CONSTANT_NameAndType:
				cp->info.NameAndType.name_index = read2bytes(file);
				cp->info.NameAndType.descriptor_index = read2bytes(file);
				break;
			case CONSTANT_Utf8:
				cp->info.Utf8.length = read2bytes(file);
				/* +1 para adicionar o \0 na string do C */
				cp->info.Utf8.bytes = (uint8_t* )malloc((cp->info.Utf8.length+1) * sizeof(uint8_t));
				uint8_t* bt = cp->info.Utf8.bytes;
				for(int j = 0; j < cp->info.Utf8.length; j++) {
					*bt = getc(file);
					bt++;
				}
				bt = '\0';
				break;
			default:
				break;
		}
		/* aponta para o proximo constant */
		cp++;
	}

	return cf;
}


static inline uint8_t read1byte(FILE * file) {
    uint8_t data = getc(file);
    return data;
}

static inline uint16_t read2bytes(FILE * file) {
    uint16_t data = getc(file);
    data = (data << 8) | (getc(file));
    return data;
}

static inline uint32_t read4bytes(FILE * file) {
    uint32_t data = getc(file);
    data = (data << 8) | (getc(file));
    data = (data << 8) | (getc(file));
    data = (data << 8) | (getc(file));
    return data;
}

int main(int argc, char* argv[]) {
	classReader("tests/Array.class");
	return 0;
}