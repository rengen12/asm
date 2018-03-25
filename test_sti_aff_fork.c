/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_sti_aff_fork.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbuy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 13:30:41 by dbuy              #+#    #+#             */
/*   Updated: 2018/03/14 13:30:43 by dbuy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

char	*test_sti3(char *in, int *i, t_list *tmp, t_list *code)
{
	char *error;

	*i = skip_spaces(in, *i);
	if (in[*i] == DIRECT_CHAR)
	{
		*i = *i + 1;
		if (in[*i] == LABEL_CHAR)
		{
			*i = *i + 1;
			if ((error = test_label(in, *i, tmp, code)) != NULL)
				return (error);
			*i = skip_labelchar(in, *i);
			*i = skip_math(in, *i);
		}
		else
			*i = skip_numeric(in, *i);
	}
	else if (in[*i] == 'r')
	{
		if ((error = test_skip_reg(in, i, tmp)) != NULL)
			return (error);
	}
	else
		return (strjoin(ft_itoa(tmp->num), ft_itoa(*i + tmp->white)));
	return (NULL);
}

char	*test_sti2(char *in, int *i, t_list *tmp, t_list *code)
{
	char		*e;

	e = NULL;
	*i = skip_spaces(in, *i);
	if (in[*i] == 'r')
	{
		if ((e = test_skip_reg(in, i, tmp)) != NULL)
			return (e);
	}
	else if (in[*i] == DIRECT_CHAR || (in[*i] == LABEL_CHAR) || in[*i] == '-' \
	|| ((in[*i] >= '0' && in[*i] <= '9')))
	{
		*i = (in[*i] == DIRECT_CHAR ? *i + 1 : *i);
		if (in[*i] == LABEL_CHAR)
			if ((e = test_label(in, (++*i), tmp, code)))
				return (e);
		*i = (in[--*i] == LABEL_CHAR ? skip_labelchar(in, ++*i) \
													: skip_numeric(in, ++*i));
	}
	*i = skip_spaces(in, *i);
	if (in[*i] != SEPARATOR_CHAR)
		return (strjoin(ft_itoa(tmp->num), ft_itoa(*i + tmp->white)));
	*i = *i + 1;
	return (e);
}

char	*test_sti(char *com, char *in, t_list *tmp, t_list *code)
{
	int		i;
	char	*error;

	i = skip_com(in, com);
	if (in[i] != 'r')
		return (strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white)));
	if ((error = test_reg(in, ++i, tmp->num)) != NULL)
		return (error);
	i = skip_numeric(in, i);
	if (in[i++] != SEPARATOR_CHAR)
		return (strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white)));
	if ((error = test_sti2(in, &i, tmp, code)) != NULL)
		return (error);
	if ((error = test_sti3(in, &i, tmp, code)) != NULL)
		return (error);
	i = skip_spaces(in, i);
	if (in[i] != '\0' && in[i] != COMMENT_CHAR)
		return (strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white)));
	return (error);
}

char	*test_aff(char *com, char *in, t_list *tmp)
{
	int		i;
	int		j;
	char	*error;

	i = 0;
	i = skip_spaces(in, i);
	j = -1;
	while (in[i] == com[++j])
		i++;
	j = 0;
	while (in[i] == 32 || (in[i] >= 9 && in[i] <= 13))
		i++;
	if (in[i] != 'r')
		return (strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white)));
	i++;
	if ((error = test_reg(in, i, tmp->num)) != NULL)
		return (error);
	i = skip_numeric(in, i);
	i = skip_spaces(in, i);
	if (in[i] != '\0' && in[i] != COMMENT_CHAR)
		return (strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white)));
	return (error);
}

char	*test_fork(char *com, char *in, t_list *tmp, t_list *code)
{
	int		i;
	int		j;
	char	*error;

	i = 0;
	j = -1;
	while (in[i] == com[++j])
		i++;
	i = skip_spaces(in, i);
	if (in[i] != DIRECT_CHAR)
		return (strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white + 1)));
	i++;
	if (in[i] == LABEL_CHAR)
	{
		if ((error = test_label(in, ++i, tmp, code)) != NULL)
			return (error);
		i = skip_labelchar(in, i);
		i = skip_math(in, i);
	}
	else if ((in[i] >= '0' && in[i] <= '9') || in[i] == '-')
		i = skip_numeric(in, i);
	i = skip_spaces(in, i);
	return (in[i] != '\0' ? strjoin(ft_itoa(tmp->num), \
	ft_itoa(i + tmp->white)) : NULL);
}
