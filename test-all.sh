gcc -o main *.c -Wall -std=c99 -ggdb3
cppcheck --enable=warning .
valgrind --leak-check=full --leak-resolution=high --track-origins=yes ./main
