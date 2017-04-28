#include "push_swap.h"

int		stack_len(t_stack *stack)
{
	int i;
	t_node *node;

	i = 0;
	node = stack->first;
	while (node)
	{
		node = node->next;
		i++;
	}
	return (i);
}

int		get_smallest(t_stack *stack)
{
	t_node	*node;
	int		small;
	int		small_score;

	node = stack->first;
	small = 0;
	small_score = 0;
	while (node)
	{
		if (node->score < small_score || node == stack->first)
		{
			small = node->value;
			small_score = node->score;
		}
		node = node->next;
	}
	return (small);
}

void 	get_to_a(t_env *env, int value)
{
	int i;
	int j;
	t_node *node;

	i = 0;
	j = 0;
	node = env->stack_a->first;
	while (node && node->value != value)
	{
		i++;
		node = node->next;
	}
	node = env->stack_a->last;
	while (node && node->value != value)
	{
		j++;
		node = node->prev;
	}
	while (env->stack_a->first->value != value)
	{
		if (i <= j)
		{
			printf("ra\n");
			rot_a(env);
		}
		else
		{
			printf("rra\n");
			rev_rot_a(env);
		}
	}
}

int		b_is_sort(t_env *env)
{
	int big;
	int bigs;
	t_node *node;

	big = 0;
	bigs = 0;
	node = env->stack_b->first;
	while (node)
	{
		if (node->value > big)
		{
			big = node->value;
			bigs++;
		}
	}
	if (bigs == 0 || bigs == 1)
		return (1);
	return (0);
}

void 	get_to_b(t_env *env, int value)
{

}

void 	push_smallest(t_env *env)
{
	int small;
	int i;
	int j;

	i = 0;
	j = 0;
	small = get_smallest(env->stack_a);
	get_to_a(env, small);
	// while (i < env->stack_a->first->score)
	// {
	// 	printf("rb\n");
	// 	rot_b(env);
	// 	i++;
	// }
	get_to_b(env, small);
	printf("pb\n");
	push_b(env);
}

int		get_score(t_env *env, int value)
{
	t_node	*node;
	int		i;

	node = env->stack_b->first;
	i = 0;
	while (node && node->value > value)
	{
		node = node->next;
		i++;
	}
	return (i);
}

void 	set_scores(t_env *env)
{
	t_node *node;
	int i;

	i = 0;
	node = env->stack_a->first;
	while (node)
	{
		node->score = get_score(env, node->value);
		node = node->next;
		i++;
	}
}

t_env	*env_init(int argc, char **argv)
{
	t_env	*env;
	int		i;
	char	**split;

	i = 0;
	env = (t_env *)malloc(sizeof(t_env));
	env->stack_a = stack_init();
	env->stack_b = stack_init();
	if (argc == 2)
	{
		split = ft_strsplit(argv[1], ' ');
		while (split[i])
			push_end(env->stack_a, atoi(split[i++]));
	}
	else
		while (argv[++i])
			push_end(env->stack_a, atoi(argv[i]));
	return (env);
}

void	swap_int(int *nb1, int *nb2)
{
	int tmp;

	tmp = *nb2;
	*nb2 = *nb1;
	*nb1 = tmp;
}

void	swap_a(t_env *env)
{
	if (env->stack_a->first->next)
		swap_int(&env->stack_a->first->value, &env->stack_a->first->next->value);
}

void	swap_b(t_env *env)
{
	if (env->stack_b->first->next)
		swap_int(&env->stack_b->first->value, &env->stack_b->first->next->value);
}

void	swap_swap(t_env *env)
{
	swap_a(env);
	swap_b(env);
}

void	push_a(t_env *env)
{
	if (env->stack_b->first)
		push_front(env->stack_a, pop_front(env->stack_b));
}

void	push_b(t_env *env)
{
	if (env->stack_a->first)
		push_front(env->stack_b, pop_front(env->stack_a));
}

void	rot_a(t_env *env)
{
	if (env->stack_a->first)
		push_end(env->stack_a, pop_front(env->stack_a));
}

void	rot_b(t_env *env)
{
	if (env->stack_b->first)
		push_end(env->stack_b, pop_front(env->stack_b));
}

void	rot_rot(t_env *env)
{
	rot_a(env);
	rot_b(env);
}

void	rev_rot_a(t_env *env)
{
	if (env->stack_a->first)
		push_front(env->stack_a, pop_end(env->stack_a));
}

void	rev_rot_b(t_env *env)
{
	if (env->stack_b->first)
		push_front(env->stack_b, pop_end(env->stack_b));
}

void	rev_rot_rot(t_env *env)
{
	rev_rot_a(env);
	rev_rot_b(env);
}

int		is_sort(t_env *env)
{
	t_node *node;

	node = env->stack_a->first;
	while (node)
	{
		if (node->prev && node->prev->value > node->value)
			return (0);
		node = node->next;
	}
	return (!env->stack_b->first ? 1 : 0);
}

void 	read_instr(t_env *env)
{
	char *buff;
	while (get_next_line(0, &buff))
	{
		if (ft_strequ(buff, "sa"))
			swap_a(env);
		if (ft_strequ(buff, "sb"))
			swap_b(env);
		if (ft_strequ(buff, "ss"))
			swap_swap(env);
		if (ft_strequ(buff, "pa"))
			push_a(env);
		if (ft_strequ(buff, "pb"))
			push_b(env);
		if (ft_strequ(buff, "ra"))
			rot_a(env);
		if (ft_strequ(buff, "rb"))
			rot_b(env);
		if (ft_strequ(buff, "rr"))
			rot_rot(env);
		if (ft_strequ(buff, "rra"))
			rev_rot_a(env);
		if (ft_strequ(buff, "rrb"))
			rev_rot_b(env);
		if (ft_strequ(buff, "rrr"))
			rev_rot_rot(env);
		printf("stack_a");
		print_stack(env->stack_a);
		printf("stack_b");
		print_stack(env->stack_b);
		if (env->stack_a->first)
			printf("score%i\n", get_score(env, env->stack_a->first->value));
	}
	if (is_sort(env))
		printf("ok\n");
}
