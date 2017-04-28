#include "push_swap.h"



int		main(int argc, char **argv)
{
	int		i;
	int		tmp;
	t_env	*env;

	if (argc == 1)
		return (0);
	i = 0;
	tmp = -1;
	env = env_init(argc, argv);
	set_scores(env);
	while (env->stack_a->first)
	{
		set_scores(env);
		push_smallest(env);
	}
	while (env->stack_b->first)
	{
		printf("pa\n");
		push_a(env);
	}
	print_stack(env->stack_a);
	// while (!is_sort(env))
	// {
	// 	printf("ra\n");
	// 	rot_a(env);
	// }
	// printf("argc%i\n", argc);
	return (0);
}
