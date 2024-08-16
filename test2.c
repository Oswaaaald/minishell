#include "src/minishell.h"
#include "stdlib.h"

int main() {
    putenv("TEMP");
    char    *buff = getenv("TEMP");
    printf("%s\n", buff);
}