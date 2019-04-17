#include <stdlib.h>
#include <stdio.h>
#include "printer.h"
#include "reader.h"

int main() {
    classFile* cf;
	cf = classReader("tests/Array.class");
    classPrinter(cf);
    return 0; 
}