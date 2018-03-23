/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_pr_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbuy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 13:20:23 by dbuy              #+#    #+#             */
/*   Updated: 2018/03/14 13:20:25 by dbuy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"

int		not_only_label(char *in)
{
	int i;

	i = 0;
	while (is_label_char(in[i]) == 1)
		i++;
	if (in[i] == LABEL_CHAR)
		i++;
	i = skip_spaces(in, i);
	if (in[i] == '\0')
		return (1);
	return (0);
}

int		empty(t_list *code)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = code;
	while (tmp)
	{
		if (ft_strlen(tmp->str) > 0 && not_only_label(tmp->str) == 0)
			i++;
		tmp = tmp->next;
	}
	if (i > 2)
		return (0);
	clear_src(code);
	return (1);
}

int		find_s(char *in)
{
	int	i;

	i = 0;
	while (in[i++] != '\0')
	{
		if (in[i] == '.' && in[i + 1] == 's')
			if (in[i + 2] == '\0')
				return (1);
	}
	return (0);
}

int		find_comment(char *in)
{
	int i;

	i = 0;
	while (in[i] != '\0')
	{
		if (in[i] != COMMENT_CHAR)
			return (0);
		if (in[i] == COMMENT_CHAR)
			return (1);
		i++;
	}
	return (0);
}
