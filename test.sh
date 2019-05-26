gcc -o main main.c reader.c printer.c freemem.c instructions.c -Wall -std=c99 -ggdb3
cppcheck --enable=warning .
valgrind --leak-check=full --leak-resolution=high --track-origins=yes ./main ./tests/Delta.class

