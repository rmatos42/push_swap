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

void 	solve_five(t_env *env)
{
	t_node *node;

	while (!is_sort(env))
	{
		node = env->stack_a->first;
		if (node->value > node->next->value)
		{
			printf("sa\n");
			swap_a(env);
			rot_a(env);
			rot_a(env);
		}
		else if ( < node->next->value)
		{
			printf("rra\n");
			rot_a(env);
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
	// while (env->stack_a->first)
	// {
	// 	set_scores(env);
	// 	push_smallest(env);
	// }
	// while (env->stack_b->first)
	// {
	// 	add_instr(env, "pa");
	// 	push_a(env);
	// }
	// t_node *node = env->stack_a->first;
	// int count = 0;
	// while (node && node->value != get_min(env->stack_a))
	// {
	// 	node = node->next;
	// 	count++;
	// }
	// if (count >= stack_len(env->stack_a) / 2)
	// {
	// 	count = stack_len(env->stack_a) - count;
	// 	while (i < count)
	// 	{
	// 		add_instr(env, "rra");
	// 		rev_rot_a(env);
	// 		i++;
	// 	}
	// }
	// else
	// {
	// 	while (i < count)
	// 	{
	// 		add_instr(env, "ra");
	// 		rot_a(env);
	// 		i++;
	// 	}
	// }
	// print_instr(env);
	solve_five(env);
	print_stack(env->stack_a);
	print_stack(env->stack_b);
	return (0);
}
