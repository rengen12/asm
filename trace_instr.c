/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_instr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbuy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 13:39:55 by dbuy              #+#    #+#             */
/*   Updated: 2018/03/14 13:39:57 by dbuy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

void	add_instr3(int tm, int *pos, char *champ)
{
	char *t;

	while (tm++ != *pos)
	{
		t = hexa(champ[tm - 1]);
		write(1, t, ft_strlen(t));
		free(t);
		write(1, " ", 1);
	}
	write(1, "\n", 1);
}

void	add_instr2(t_list *tmp, int acb, int start, int *pos)
{
	char *t;

	write(1, "\n", 1);
	t = ft_itoa(start - COMMENT_LENGTH - PROG_NAME_LENGTH - 16);
	write(1, t, ft_strlen(t));
	free(t);
	write(1, " (", 2);
	t = ft_itoa(*pos - start);
	write(1, t, ft_strlen(t));
	free(t);
	write(1, ")\t", 2);
	write(1, tmp->str, ft_strlen(tmp->str));
	write(1, "\n\t\tOP = ", 8);
	t = ft_itoa(tmp->op);
	write(1, t, ft_strlen(t));
	free(t);
	write(1, "\n\t\tacb = ", 9);
	if (tmp->op == 1 || tmp->op == 9 || tmp->op == 12 || tmp->op == 15)
		t = "NULL";
	else
		t = binary(acb);
	write(1, t, ft_strlen(t));
	if (ft_strcmp(t, "NULL") != 0)
		free(t);
	write(1, "\n\t\targs = ", 10);
}

int		add_instr(char **champ, int pos, t_list *tmp, t_lab **address)
{
	int			tm;
	int			acb;
	int			start;
	static int	max;

	max = (max == 0 ? 2800 : max);
	start = pos;
	tmp->start = pos;
	(*champ)[pos] = (char)tmp->op;
	pos++;
	acb = (tmp->op == 12 || tmp->op == 15 || tmp->op == 1 || tmp->op == 9 ? 0 \
														: find_acb(tmp->str));
	if (tmp->op != 12 && tmp->op != 15 && tmp->op != 1 && tmp->op != 9)
		(*champ)[pos++] = (char)acb;
	tm = pos;
	pos = add_args(*champ, pos, tmp, address);
	if (tmp->j == 2)
	{
		add_instr2(tmp, acb, start, &pos);
		add_instr3(tm, &pos, *champ);
	}
	if (pos > max)
		*champ = expand(champ, pos, max);
	max = (pos > max ? max * 2 : max);
	return (pos);
}

int		first_trace2(t_list *tmp, t_list *code, t_lab **label, int *i)
{
	while (is_label_char(tmp->str[*i]))
	{
		code->j = 0;
		while (is_label_char(tmp->str[*i + code->j]))
			code->j++;
		if (tmp->str[*i + code->j] == LABEL_CHAR)
		{
			*label = add_label(*label, new_label(tmp, code->pos, *i));
			if (test_label_repeat(*label) == 1)
				return (-1);
			*i = *i + code->j + 1;
			*i = skip_spaces(tmp->str, *i);
		}
		else
			break ;
	}
	return (0);
}

int		first_trace(char **champ, int pos, t_list *code, int flag)
{
	t_list		*tmp;
	t_lab		*label;
	t_lab		*address;
	int			i;

	tmp = code;
	label = NULL;
	address = NULL;
	while ((tmp = tmp->next))
	{
		i = skip_spaces(tmp->str, 0);
		if (tmp->str[i] == COMMENT_CHAR || tmp->str[i] == '.' || !tmp->str[i])
			continue ;
		code->pos = pos;
		if (first_trace2(tmp, code, &label, &i) == -1)
			return (free_lab_add(label, address));
		if (tmp->str[i] == '\0' || tmp->str[i] == COMMENT_CHAR)
			continue ;
		tmp->j = flag;
		pos = (tmp->op > 0 ? add_instr(champ, pos, tmp, &address) : pos);
	}
	add_links(*champ, label, address);
	clear_links(label, address);
	return (pos);
}
