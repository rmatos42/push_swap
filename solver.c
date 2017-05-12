#include "push_swap.h"

void 	solve_three(t_env *env)
{
	t_node *node;

	node = env->stack_a->first;
	if (stack_len(env->stack_a) > 3)
		return ;
	while (!is_sort(env))
	{
		node = env->stack_a->first;
		if (node->value > node->next->value)
		{
			printf("sa\n");
			swap_a(env);
		}
		else if (node->next->next->value < node->next->value)
		{
			printf("rra\n");
			rev_rot_a(env);
		}
	}
}



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
	if (stack_len(env->stack_a) != 3)
	{
		while (env->stack_a->first)
		{
			set_scores(env);
			push_smallest(env);
		}
		while (env->stack_b->first)
		{
			add_instr(env, "pa");
			push_a(env);
		}
	}
	else
		solve_three(env);
	t_node *node = env->stack_a->first;
	int count = 0;
	int rev_count = stack_len(env->stack_a);
	while (node && node->value != get_min(env->stack_a))
	{
		node = node->next;
		count++;
		rev_count--;
	}
	while (i < count)
	{
		add_instr(env, "ra");
		rot_a(env);
		i++;
	}
	i = 0;
	while (i < rev_count)
	{
		add_instr(env, "rra");
		i++;
	}
	print_instr(env);
	// solve_five(env);
	// print_stack(env->stack_a);
	// print_stack(env->stack_b);
	return (0);
}
