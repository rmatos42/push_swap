#include "push_swap.h"

t_node		*node_init(int value)
{
	t_node	*result;

	result = (t_node *)malloc(sizeof(t_node));
	result->value = value;
	result->prev = NULL;
	result->next = NULL;
	result->score = 0;
	return (result);
}

t_stack		*stack_init(void)
{
	t_stack	*result;

	result = (t_stack *)malloc(sizeof(t_stack));
	result->first = NULL;
	result->last = NULL;
	return (result);
}

void		push_front(t_stack *stack, int value)
{
	t_node *node;

	node = node_init(value);
	if (!stack->first)
	{
		stack->first = node;
		stack->last = node;
	}
	else
	{
		stack->first->prev = node;
		node->next = stack->first;
		stack->first = node;
	}
}

void		push_end(t_stack *stack, int value)
{
	t_node	*node;

	node = node_init(value);
	if (!stack->first)
	{
		stack->first = node;
		stack->last = node;
	}
	else
	{
		stack->last->next = node;
		node->prev = stack->last;
		stack->last = node;
	}
}

int			pop_front(t_stack *stack)
{
	int	result;

	result = stack->first->value;
	if (!stack->first->next)
	{
		free(stack->first);
		stack->first = NULL;
		stack->last = NULL;
		return (result);
	}
	stack->first = stack->first->next;
	free(stack->first->prev);
	stack->first->prev = NULL;
	return (result);
}

int			pop_end(t_stack *stack)
{
	int	result;

	result = stack->last->value;
	if (!stack->last->prev)
	{
		free(stack->last);
		stack->first = NULL;
		stack->last = NULL;
		return (result);
	}
	stack->last = stack->last->prev;
	free(stack->last->next);
	stack->last->next = NULL;
	return (result);
}

void		print_stack(t_stack *stack)
{
	t_node *node;

	node = stack->first;
	while (node)
	{
		printf("%i ", node->value);
		node = node->next;
	}
	printf("\n");
}
