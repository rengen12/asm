/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbuy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 13:39:55 by dbuy              #+#    #+#             */
/*   Updated: 2018/03/14 13:39:57 by dbuy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

void	add_args2(t_list *tmp, char *in, int *pos)
{
	int arg;

	arg = (int)ft_atoi(tmp->str + tmp->i + 1);
	if ((tmp->op >= 9 && tmp->op <= 12) || tmp->op == 14 || tmp->op == 15)
	{
		in[*pos] = (char)((arg << 16) >> 24);
		*pos = *pos + 1;
		in[*pos] = (char)((arg << 24) >> 24);
		*pos = *pos + 1;
	}
	else
	{
		in[*pos] = (char)(arg >> 24);
		*pos = *pos + 1;
		in[*pos] = (char)((arg << 8) >> 24);
		*pos = *pos + 1;
		in[*pos] = (char)((arg << 16) >> 24);
		*pos = *pos + 1;
		in[*pos] = (char)((arg << 24) >> 24);
		*pos = *pos + 1;
	}
	tmp->i = skip_numeric(tmp->str, tmp->i + 1);
}

int		add_args3(t_list *tmp, char *in, int *pos, t_lab **add)
{
	char	*t;
	int		arg;

	t = tmp->str + tmp->i;
	if (t[0] == LABEL_CHAR)
	{
		*add = save_address(*pos, t + 1, *add, 1);
		(*add)->cor = 0;
		(*add)->start = tmp->start;
		*pos = *pos + 2;
		tmp->i = skip_labelchar(t, tmp->i + 2);
		tmp->i = skip_spaces(t, tmp->i);
		(*add)->math = set_math(tmp, tmp->i);
		tmp->i = skip_math(t, tmp->i);
	}
	else
	{
		arg = (int)ft_atoi(t);
		in[(*pos)++] = (char)((arg << 16) >> 24);
		in[(*pos)++] = (char)((arg << 24) >> 24);
		tmp->i = skip_numeric(t, tmp->i);
	}
	return (tmp->i);
}

int		add_args4(t_list *tmp, int *pos, t_lab **add)
{
	*add = save_address(*pos, tmp->str + tmp->i + 2, *add, 0);
	if (tmp->op == 1 || tmp->op == 2 || tmp->op == 6 || tmp->op == 7 \
									|| tmp->op == 8 || tmp->op == 13)
		(*add)->cor = 2;
	else
		(*add)->cor = 0;
	(*add)->start = tmp->start;
	*pos = ((tmp->op >= 9 && tmp->op <= 12) || tmp->op == 14 || \
									tmp->op == 15 ? *pos + 2 : *pos + 4);
	tmp->i = skip_labelchar(tmp->str, tmp->i + 2);
	tmp->i = skip_spaces(tmp->str, tmp->i);
	(*add)->math = set_math(tmp, tmp->i);
	tmp->i = skip_math(tmp->str, tmp->i);
	return (tmp->i);
}

void	add_args5(t_list *tmp, int *pos, char *in, t_lab **add)
{
	tmp->i = (tmp->str[tmp->i] == SEPARATOR_CHAR ? tmp->i + 1 : tmp->i);
	tmp->i = skip_spaces(tmp->str, tmp->i);
	if (tmp->str[tmp->i] == 'r')
	{
		in[(*pos)++] = (char)ft_atoi(tmp->str + tmp->i++ + 1);
		tmp->i = skip_numeric(tmp->str, tmp->i);
	}
	else if (tmp->str[tmp->i] == DIRECT_CHAR)
	{
		if (tmp->str[tmp->i + 1] == LABEL_CHAR)
			tmp->i = add_args4(tmp, pos, add);
		else
			add_args2(tmp, in, pos);
	}
	else
		tmp->i = add_args3(tmp, in, pos, add);
}

int		add_args(char *in, int pos, t_list *tmp, t_lab **add)
{
	int		j;
	int		n;

	n = 0;
	tmp->i = skip_spaces(tmp->str, 0);
	j = skip_labelchar(tmp->str, tmp->i) - tmp->i;
	tmp->i = (tmp->str[tmp->i + j] == LABEL_CHAR ? tmp->i + j + 1 : tmp->i);
	tmp->i = skip_spaces(tmp->str, tmp->i);
	while (tmp->str[tmp->i] != 32 && (tmp->str[tmp->i] < 9 || \
							tmp->str[tmp->i] > 13) && tmp->str[tmp->i] != '\0')
		tmp->i++;
	while (n++ < 3 && tmp->str[tmp->i] != '\0' && tmp->str[tmp->i] \
															!= COMMENT_CHAR)
	{
		add_args5(tmp, &pos, in, add);
		while (tmp->str[tmp->i] != SEPARATOR_CHAR && tmp->str[tmp->i] != '\0' \
											&& tmp->str[tmp->i] != COMMENT_CHAR)
			tmp->i++;
	}
	return (pos);
}
