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
		if (node->score + node->loc_score < small_score || node == stack->first)
		{
			small = node->value;
			small_score = node->score + node->loc_score;
		}
		node = node->next;
	}
	return (small);
}

void 	get_to_a(t_env *env, int value)
{
	int i;
	int count;
	int rev_count;
	t_node *node;

	i = 0;
	count = 0;
	rev_count = stack_len(env->stack_a);
	node = env->stack_a->first;
	while (node && node->value != value)
	{
		count++;
		rev_count--;
		node = node->next;
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
}

int		get_min(t_stack *stack)
{
	int	min;
	int i;
	t_node	*node;

	min = 0;
	i = 0;
	node = stack->first;
	while(node)
	{
		if (node == stack->first || node->value < min)
			min = node->value;
		node = node->next;
		i++;
	}
	return (min);
}

int		get_max(t_stack *stack)
{
	int max;
	t_node *node;

	max = 0;
	node = stack->first;
	while (node)
	{
		if (node->value > max)
			max = node->value;
		node = node->next;
	}
	return (max);
}

void 	get_to_b(t_env *env, int value)
{
	int i;
	int count;
	int rev_count;
	t_node *node;

	count = 0;
	i = 0;
	node = env->stack_b->first;
	if (value <= get_min(env->stack_b) || value >= get_max(env->stack_b))
	{
		while (node && node->value != get_max(env->stack_b))
		{
			node = node->next;
			count++;
		}
	}
	else if (node && value > node->value)
	{
		count = stack_len(env->stack_b);
		node = env->stack_b->last;
		while (node && value > node->value && node->value != get_min(env->stack_b))
		{
			node = node->prev;
			count--;
		}
	}
	else
	{
		while (node && node->value > value && node->value != get_min(env->stack_b))
		{
			node = node->next;
			count++;
		}
	}
	rev_count = stack_len(env->stack_b) - count;
	while (i < count)
	{
		add_instr(env, "rb");
		rot_b(env);
		i++;
	}
	i = 0;
	while (i < rev_count)
	{
		add_instr(env, "rrb");
		i++;
	}
}

void 	push_smallest(t_env *env)
{
	int small;
	int i;
	int j;

	i = 0;
	j = 0;
	small = get_smallest(env->stack_a);
	// small = env->stack_a->first->value;
	get_to_a(env, small);
	get_to_b(env, small);
	add_instr(env, "pb");
	push_b(env);
}

int		get_score(t_env *env, int value)
{
	int i;
	int count;
	t_node *node;

	count = 0;
	i = 0;
	node = env->stack_b->first;
	if (value <= get_min(env->stack_b) || value >= get_max(env->stack_b))
	{
		while (node && node->value != get_max(env->stack_b))
		{
			node = node->next;
			count++;
		}
	}
	else if (node && value > node->value)
	{
		count = stack_len(env->stack_b);
		node = env->stack_b->last;
		while (node && value > node->value && node->value != get_min(env->stack_b))
		{
			node = node->prev;
			count--;
		}
	}
	else
	{
		while (node && node->value > value && node->value != get_min(env->stack_b))
		{
			node = node->next;
			count++;
		}
	}
	if (count > stack_len(env->stack_b) / 2)
		count = stack_len(env->stack_b) - count;
	return (count);
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
		if (i > stack_len(env->stack_a) / 2)
			node->loc_score = stack_len(env->stack_a) - i;
		else
			node->loc_score= i;
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
	env->instructions = NULL;
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
	// return (!env->stack_b->first ? 1 : 0);
	return (1);
}

void 	read_instr(t_env *env)
{
	char *buff;
	while (get_next_line(0, &buff))
	{

		if (ft_strequ(buff, "sa"))
			swap_a(env);
		else if (ft_strequ(buff, "sb"))
			swap_b(env);
		else if (ft_strequ(buff, "ss"))
			swap_swap(env);
		else if (ft_strequ(buff, "pa"))
			push_a(env);
		else if (ft_strequ(buff, "pb"))
			push_b(env);
		else if (ft_strequ(buff, "ra"))
			rot_a(env);
		else if (ft_strequ(buff, "rb"))
			rot_b(env);
		else if (ft_strequ(buff, "rr"))
			rot_rot(env);
		else if (ft_strequ(buff, "rra"))
			rev_rot_a(env);
		else if (ft_strequ(buff, "rrb"))
			rev_rot_b(env);
		else if (ft_strequ(buff, "rrr"))
			rev_rot_rot(env);
		else
		{
			ft_putstr("Error\n");
			exit(0);
		}
	}
	if (is_sort(env))
		printf("OK\n");
	else
		ft_putstr("KO\n");
}
