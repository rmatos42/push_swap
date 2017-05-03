#include "push_swap.h"

void 	add_instr(t_env *env, char *instr)
{
	t_instr *list;

	list = env->instructions;
	if (env->instructions == NULL)
	{
		env->instructions = (t_instr *)malloc(sizeof(t_instr));
		env->instructions->str = instr;
		env->instructions->next = NULL;
	}
	else
	{
		while (list->next)
			list = list->next;
		list->next = (t_instr *)malloc(sizeof(t_instr));
		list->next->str = instr;
		list->next->next = NULL;
	}
}

void 	print_instr(t_env *env)
{
	t_instr *list;
	int		ra;
	int		rb;
	int		rra;
	int		rrb;

	ra = 0;
	rb = 0;
	rra = 0;
	rrb = 0;
	list = env->instructions;
	while (list)
	{
		while (list && !ft_strequ(list->str, "pa") && !ft_strequ(list->str, "pb"))
		{
			ra += (ft_strequ(list->str, "ra")) ? 1 : 0;
			rb += (ft_strequ(list->str, "rb")) ? 1 : 0;
			rra += (ft_strequ(list->str, "rra")) ? 1 : 0;
			rrb += (ft_strequ(list->str, "rrb")) ? 1 : 0;
			list = list->next;
		}
		while (ra > 0 && rb > 0)
		{
			printf("rr\n");
			ra--;
			rb--;
		}
		while (rra > 0 && rrb > 0)
		{
			printf("rrr\n");
			rra--;
			rrb--;
		}
		while (ra > 0)
		{
			printf("ra\n");
			ra--;
		}
		while (rb > 0)
		{
			printf("rb\n");
			rb--;
		}
		while (rra > 0)
		{
			printf("rra\n");
			rra--;
		}
		while (rrb > 0)
		{
			printf("rrb\n");
			rrb--;
		}
		if (list)
		{
			printf("%s\n", list->str);
			list = list->next;
		}
	}
}

// void 	print_instr(t_env *env)
// {
// 	t_instr *list;
// 	int		ra;
// 	int		rb;
// 	int		rra;
// 	int		rrb;
//
// 	ra = 0;
// 	rb = 0;
// 	rra = 0;
// 	rrb = 0;
// 	int ra_rb = 0;
// 	int ra_rrb = 0;
// 	int rra_rb = 0;
// 	int rra_rrb = 0;
// 	list = env->instructions;
// 	while (list)
// 	{
// 		while (list && !ft_strequ(list->str, "pa") && !ft_strequ(list->str, "pb"))
// 		{
// 			ra += (ft_strequ(list->str, "ra")) ? 1 : 0;
// 			rb += (ft_strequ(list->str, "rb")) ? 1 : 0;
// 			rra += (ft_strequ(list->str, "rra")) ? 1 : 0;
// 			rrb += (ft_strequ(list->str, "rrb")) ? 1 : 0;
// 			list = list->next;
// 		}
// 		ra_rb = abs(ra - rb);
// 		ra_rrb = ra + rrb;
// 		rra_rb = rra + rb;
// 		rra_rrb = abs(rra - rrb);
// 		if (ra_rb <= ra_rrb && ra_rb <= rra_rb && ra_rb <= rra_rrb)
// 		{
// 			while (ra)
// 			{
// 				printf("ra\n");
// 				ra--;
// 			}
// 			while (rb)
// 			{
// 				printf("rb\n");
// 				rb--;
// 			}
// 		}
// 		else if (ra_rrb <= ra_rb && ra_rrb <= rra_rb && ra_rrb <= rra_rrb)
// 		{
// 			while (ra)
// 			{
// 				printf("ra\n");
// 				ra--;
// 			}
// 			while (rrb)
// 			{
// 				printf("rrb\n");
// 				rrb--;
// 			}
// 		}
// 		else if (rra_rb <= ra_rb && rra_rb <= ra_rrb && rra_rb <= rra_rrb)
// 		{
// 			while (rra)
// 			{
// 				printf("rra\n");
// 				rra--;
// 			}
// 			while (rb)
// 			{
// 				printf("rb\n");
// 				rb--;
// 			}
// 		}
// 		else
// 		{
// 			while (rra)
// 			{
// 				printf("rra\n");
// 				rra--;
// 			}
// 			while (rrb)
// 			{
// 				printf("rrb\n");
// 				rrb--;
// 			}
// 		}
// 		ra = 0;
// 		rb = 0;
// 		rra = 0;
// 		rrb = 0;
// 		if (list)
// 		{
// 			printf("%s\n", list->str);
// 			list = list->next;
// 		}
// 	}
// }
