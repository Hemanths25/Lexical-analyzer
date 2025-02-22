#include <stdio.h>
#include "lexer.h"

int main(int argc, char *argv[]) {
    initializeLexer(argv[1]);
    tokens();
    return 0;
}
