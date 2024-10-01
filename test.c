#include "minishell.h"

int	main(void) {
	while (1) {
		char	*str = readline("> ");
		t_cmdli	*cmdli = tokenize(str);
		
	}
}