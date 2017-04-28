#include "push_swap.h"
#include "get_next_line.h"

int		main(int argc, char **argv)
{
	int		i;
	t_env	*env;

	if (argc == 1)
		return (0);
	i = 0;
	env = env_init(argc, argv);
	read_instr(env);
	return (0);
}
