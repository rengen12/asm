/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ldi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbuy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 13:30:41 by dbuy              #+#    #+#             */
/*   Updated: 2018/03/14 13:30:43 by dbuy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

char	*test_ldi3(char *in, int *i, t_list *tmp)
{
	char	*error;

	*i = skip_spaces(in, *i);
	if (in[*i] != SEPARATOR_CHAR)
		return (strjoin(ft_itoa(tmp->num), ft_itoa(*i + tmp->white)));
	*i = *i + 1;
	*i = skip_spaces(in, *i);
	if (in[*i] != 'r')
		return (strjoin(ft_itoa(tmp->num), ft_itoa(*i + tmp->white)));
	if ((error = test_skip_reg(in, i, tmp)))
		return (error);
	*i = skip_spaces(in, *i);
	if (in[*i] != '\0' && in[*i] != COMMENT_CHAR)
		return (strjoin(ft_itoa(tmp->num), ft_itoa(*i + tmp->white)));
	return (NULL);
}

char	*test_ldi2(char *in, int *i, t_list *tmp, t_list *code)
{
	char	*error;

	*i = skip_spaces(in, *i);
	if (in[*i] != SEPARATOR_CHAR)
		return (strjoin(ft_itoa(tmp->num), ft_itoa(*i + tmp->white)));
	*i = skip_spaces(in, ++(*i));
	if (in[*i] == 'r')
	{
		if ((error = test_skip_reg(in, i, tmp)))
			return (error);
	}
	else if (in[*i] == DIRECT_CHAR)
	{
		if (in[++(*i)] == LABEL_CHAR)
		{
			if ((error = test_sk_label(in, i, tmp, code)))
				return (error);
			*i = skip_spaces(in, *i);
		}
		else
			*i = skip_numeric(in, *i);
	}
	else
		return (strjoin(ft_itoa(tmp->num), ft_itoa(*i + tmp->white)));
	return (NULL);
}

char	*test_ldi01(int *i, char *in, t_list *tmp, t_list *code)
{
	char *error;

	if (in[*i] == '-' || (in[*i] >= '0' && in[*i] <= '9'))
		*i = skip_numeric(in, *i);
	else if (in[*i] == LABEL_CHAR)
	{
		if ((error = test_sk_label(in, i, tmp, code)))
			return (error);
	}
	else
		return (strjoin(ft_itoa(tmp->num), ft_itoa(*i + tmp->white)));
	return (NULL);
}

char	*test_ldi(char *com, char *in, t_list *tmp, t_list *code)
{
	int		i;
	char	*error;

	i = skip_com(in, com);
	if (in[i] == 'r')
	{
		if ((error = test_skip_reg(in, &i, tmp)))
			return (error);
	}
	else if (in[i] == DIRECT_CHAR)
	{
		if (in[i++] == LABEL_CHAR && (error = \
										test_sk_label(in, &(i), tmp, code)))
			return (error);
		i = (in[i] == LABEL_CHAR ? skip_labelchar(in, ++i) \
													: skip_numeric(in, i));
	}
	else if ((error = test_ldi01(&i, in, tmp, code)))
		return (error);
	if ((error = test_ldi2(in, &i, tmp, code)) != NULL)
		return (error);
	if ((error = test_ldi3(in, &i, tmp)) != NULL)
		return (error);
	return (error);
}
