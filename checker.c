#include "push_swap.h"
#include "get_next_line.h"

t_env	*env_init(void)
{
	t_env *env;

	env = (t_env *)malloc(sizeof(t_env));
	env->stack_a = stack_init();
	env->stack_b = stack_init();
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
	}
	if (is_sort(env))
		printf("ok\n");
}

int		main(int argc, char **argv)
{
	int		i;
	t_env	*env;

	if (argc == 1)
		return (0);
	i = 0;
	env = env_init();
	while (argv[++i])
		push_end(env->stack_a, atoi(argv[i]));
	read_instr(env);
	return (0);
}
