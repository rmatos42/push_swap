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

void 	calc_direction(t_combo *var, t_instr **list)
{
	t_instr *tmp;

	var->ra = 0;
	var->rb = 0;
	var->rra = 0;
	var->rrb = 0;
	while (*list && !ft_strequ((*list)->str, "pa")
		&& !ft_strequ((*list)->str, "pb"))
	{
		tmp = *list;
		var->ra += (ft_strequ((*list)->str, "ra")) ? 1 : 0;
		var->rb += (ft_strequ((*list)->str, "rb")) ? 1 : 0;
		var->rra += (ft_strequ((*list)->str, "rra")) ? 1 : 0;
		var->rrb += (ft_strequ((*list)->str, "rrb")) ? 1 : 0;
		*list = (*list)->next;
		free(tmp);
	}
	var->ra_rb = abs(var->ra - var->rb)
		+ (var->ra < var->rb ? var->ra : var->rb);
	var->ra_rrb = var->ra + var->rrb;
	var->rra_rrb = abs(var->rra - var->rrb)
		+ (var->rra < var->rrb ? var->rra : var->rrb);
	var->rra_rb = var->rra + var->rb;
}

void 	print_ra_rb(t_combo *var)
{
	while (var->ra > 0 && var->rb > 0)
	{
		ft_putstr("rr\n");
		var->ra--;
		var->rb--;
	}
	while (var->ra > 0)
	{
		ft_putstr("ra\n");
		var->ra--;
	}
	while (var->rb > 0)
	{
		ft_putstr("rb\n");
		var->rb--;
	}
}

void 	print_ra_rrb(t_combo *var)
{
	while (var->ra > 0)
	{
		ft_putstr("ra\n");
		var->ra--;
	}
	while (var->rrb > 0)
	{
		ft_putstr("rrb\n");
		var->rrb--;
	}
}

void 	print_rra_rrb(t_combo *var)
{
	while (var->rra > 0 && var->rrb > 0)
	{
		ft_putstr("rrr\n");
		var->rra--;
		var->rrb--;
	}
	while (var->rra > 0)
	{
		ft_putstr("rra\n");
		var->rra--;
	}
	while (var->rrb > 0)
	{
		ft_putstr("rrb\n");
		var->rrb--;
	}
}

void 	print_rra_rb(t_combo *var)
{
	while (var->rra > 0)
	{
		ft_putstr("rra\n");
		var->rra--;
	}
	while (var->rb > 0)
	{
		ft_putstr("rb\n");
		var->rb--;
	}
}

void 	print_instr(t_env *env)
{
	t_instr	*list;
	t_instr	*tmp;
	t_combo	var;

	list = env->instructions;
	while (list)
	{
		calc_direction(&var, &list);
		if (var.ra_rb <= var.ra_rrb && var.ra_rb <= var.rra_rrb && var.ra <= var.rra_rb)
			print_ra_rb(&var);
		else if (var.ra_rrb <= var.ra_rb && var.ra_rrb <= var.rra_rrb && var.ra_rrb <= var.rra_rb)
			print_ra_rrb(&var);
		else if (var.rra_rrb <= var.ra_rb && var.rra_rrb <= var.ra_rrb && var.rra_rrb <= var.rra_rb)
			print_rra_rrb(&var);
		else
			print_rra_rb(&var);
		if (list)
		{
			tmp = list;
			ft_putendl(list->str);
			list = list->next;
			free(tmp);
		}
	}
}
