#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include <stdlib.h>
#include <stdio.h>
#include <libft.h>
#include <get_next_line.h>

typedef struct		s_node
{
	int				value;
	int				score;
	struct s_node	*prev;
	struct s_node	*next;
}					t_node;

typedef struct		s_stack
{
	struct s_node	*first;
	struct s_node	*last;
}					t_stack;

typedef struct		s_env
{
	t_stack			*stack_a;
	t_stack			*stack_b;
}					t_env;

t_node				*node_init(int value);
t_stack				*stack_init(void);
t_env				*env_init(void);

//stack functions
void				print_stack(t_stack *stack);
void				push_front(t_stack *stack, int value);
void				push_end(t_stack *stack, int value);
int					pop_front(t_stack *stack);
int					pop_end(t_stack *stack);

//push_swap functions
void				swap_int(int *nb1, int *nb2);
void				swap_a(t_env *env);
void				swap_b(t_env *env);
void				swap_swap(t_env *env);
void				push_a(t_env *env);
void				push_b(t_env *env);
void				rot_a(t_env *env);
void				rot_b(t_env *env);
void				rot_rot(t_env *env);
void				rev_rot_a(t_env *env);
void				rev_rot_b(t_env *env);
void				rev_rot_rot(t_env *env);

#endif
