#include "push_swap.h"

void 	ft_swap(int *n1, int *n2)
{
	int x;

	x = *n2;
	*n2 = *n1;
	*n1 = x;
}

int		partition(int *arr, int left, int right, int pivot)
{
	while (left <= right)
	{
		while (arr[left] < arr[pivot])
			left++;
		while (arr[right] > arr[pivot])
			right--;
		if (left <= right)
		{
			ft_swap(&arr[left], &arr[right]);
			left++;
			right--;
		}
	}
	return (left);
}

void 	ft_qsort(int *arr, int left, int right)
{
	int pivot;
	int index;

	if (left >= right)
		return;
	pivot = left;
	index = partition(arr, left, right, pivot);
	ft_qsort(arr, left, index - 1);
	ft_qsort(arr, index, right);
}

int		get_sorted_loc(int *arr, int len, int value)
{
	int i;

	i = 0;
	while (i < len)
	{
		if (arr[i] == value)
			return (i);
		i++;
	}
	return (-1);
}

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

int		*make_array(t_stack *stack)
{
	int		*result;
	int		len;
	t_node	*node;
	int		i;

	len = stack_len(stack);
	result = (int *)malloc(sizeof(int) * len);
	node = stack->first;
	i = 0;
	while (i < len)
	{
		result[i] = node->value;
		node = node->next;
		i++;
	}
	ft_qsort(result, 0, len - 1);
	return (result);
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

void 	get_to(t_env *env, int value)
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

void 	push_smallest(t_env *env)
{
	int small;
	t_stack *stack;

	small = get_smallest(env->stack_a);
	stack = env->stack_a;
	get_to(env, small);
	printf("pb\n");
	push_b(env);
}

void 	set_scores(t_stack *stack)
{
	t_node	*node;
	int		*arr;
	int i;
	int	len;

	i = 0;
	node = stack->first;
	arr = make_array(stack);
	len = stack_len(stack);
	while (node)
	{
		node->score = get_sorted_loc(arr, len, node->value);
		node = node->next;
		i++;
	}
}

int		not_main(int argc, char **argv)
{
	int		i;
	t_env	*env;

	if (argc == 1)
		return (0);
	i = 0;
	env = env_init();
	while (argv[++i])
		push_end(env->stack_a, atoi(argv[i]));
	i = 0;
	set_scores(env->stack_a);
	while (env->stack_a->first)
		push_smallest(env);
	while (env->stack_b->first)
	{
		printf("pa\n");
		push_a(env);
	}
	return (0);
}
