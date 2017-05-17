#include "push_swap.h"

void 	solve_three(t_env *env)
{
	t_node *node;

	if (stack_len(env->stack_a) != 3)
		return ;
	while (!is_sort(env))
	{
		node = env->stack_a->first;
		if (node->value > node->next->value)
		{
			add_instr(env, "sa");
			swap_a(env);
		}
		else if (node->next->next->value < node->next->value)
		{
			add_instr(env, "rra");
			rev_rot_a(env);
		}
	}
}

int 	get_min_i(t_stack *stack)
{
	int		min;
	int 	min_i;
	int 	i;
	t_node	*node;

	min = 0;
	i = 0;
	min_i = 0;
	node = stack->first;
	while (node)
	{
		if (i == 0 || node->value < min)
		{
			min = node->value;
			min_i = i;
		}
		i++;
		node = node->next;
	}
	return (min_i);
}

void 	solve_five(t_env *env)
{
	t_node	*node;
	int 	i;
	int		count;

	if (stack_len(env->stack_a) != 5)
		return ;
	while (stack_len(env->stack_a) != 3)
	{
		i = 0;
		count = get_min_i(env->stack_a);
		if (count > stack_len(env->stack_a) / 2)
		{
			count = stack_len(env->stack_a) - count;
			while (i < count)
			{
				add_instr(env, "rra");
				rev_rot_a(env);
				i++;
			}
		}
		else
		{
			while (i < count)
			{
				add_instr(env, "ra");
				rot_a(env);
				i++;
			}
		}
		add_instr(env, "pb");
		push_b(env);
	}
	solve_three(env);
	while (env->stack_b->first)
	{
		add_instr(env, "pa");
		push_a(env);
	}
	if (env->stack_a->first->value > env->stack_a->first->next->value)
	{
		add_instr(env, "sa");
		swap_a(env);
	}
	t_instr *instr = env->instructions;
	while (instr)
	{
		printf("%s\n", instr->str);
		instr = instr->next;
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
	if (stack_len(env->stack_a) != 3 && stack_len(env->stack_a) != 5)
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
	else if (stack_len(env->stack_a) == 5)
	{
		solve_five(env);
		return (0);
	}
	else
	{
		solve_three(env);
		t_instr *instr = env->instructions;
		while (instr)
		{
			printf("%s\n", instr->str);
			instr = instr->next;
		}
		return (0);
	}
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
	return (0);
}
