#include "push_swap.h"

void 	free_stack(t_stack *stack)
{
	t_node *node;
	t_node *tmp;

	node = stack->first;
	while (node)
	{
		tmp = node;
		node = node->next;
		free(tmp);
	}
	free(stack);
}

void 	free_env(t_env *env)
{
	free_stack(env->stack_a);
	free_stack(env->stack_b);
	free(env);
}

void 	print_and_free(t_instr *instr)
{
	t_instr *tmp;

	while (instr)
	{
		tmp = instr;
		ft_putendl(instr->str);
		instr = instr->next;
		free(tmp);
	}
}

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

void 	push_min_util(t_env *env, int *i, int *count)
{
	while (*i < *count)
	{
		add_instr(env, "ra");
		rot_a(env);
		(*i)++;
	}
}

void 	push_min(t_env *env)
{
	int count;
	int i;

	count = 0;
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
			push_min_util(env, &i, &count);
		add_instr(env, "pb");
		push_b(env);
	}
}

void 	solve_five(t_env *env)
{
	t_node	*node;
	int 	i;
	int		count;

	if (stack_len(env->stack_a) != 5)
		return ;
	push_min(env);
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
	print_and_free(env->instructions);

}

void 	make_a_sort(t_env *env)
{
	int 	i;
	t_node	*node;
	int		count;

	i = -1;
	count = 0;
	node = env->stack_a->first;
	while (node && node->value != get_min(env->stack_a))
	{
		node = node->next;
		count++;
	}
	while (++i < count)
	{
		add_instr(env, "ra");
		rot_a(env);
	}
	i = -1;
	count = stack_len(env->stack_a) - count;
	while (++i < count)
		add_instr(env, "rra");
	free_env(env);
	print_instr(env);
}

void 	solve_three_and_five(t_env *env)
{
	t_instr		*instr;
	t_instr		*tmp;

	if (stack_len(env->stack_a) == 5)
	{
		solve_five(env);
		free_env(env);
	}
	else
	{
		solve_three(env);
		print_and_free(env->instructions);
		free_env(env);
	}
}

int		main(int argc, char **argv)
{
	t_env	*env;

	if (argc == 1)
		return (0);
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
	else
	{
		solve_three_and_five(env);
		return (0);
	}
	make_a_sort(env);
	return (0);
}
