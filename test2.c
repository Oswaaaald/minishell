#include "src/minishell.h"

int main() {
    char    *buff = getenv("PWD");
    printf("%s\n", buff);
}