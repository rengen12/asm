/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_and_add.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbuy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 13:30:41 by dbuy              #+#    #+#             */
/*   Updated: 2018/03/14 13:30:43 by dbuy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

char	*test_add2(char *in, int i, t_list *tmp)
{
	char *error;

	error = NULL;
	i = skip_spaces(in, i);
	if (in[i] != 'r')
		return (strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white)));
	i++;
	if ((error = test_reg(in, i, tmp->num)) != NULL)
		return (error);
	i = skip_numeric(in, i);
	i = skip_spaces(in, i);
	if (in[i] != '\0')
		return (strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white)));
	return (error);
}

char	*test_add(char *com, char *in, t_list *tmp)
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
	while (j++ < 2)
	{
		i = skip_spaces(in, i);
		if (in[i] != 'r')
			return (strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white)));
		i++;
		if ((error = test_reg(in, i, tmp->num)) != NULL)
			return (error);
		i = skip_numeric(in, i);
		i = skip_spaces(in, i);
		if (in[i] != SEPARATOR_CHAR)
			return (strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white)));
		i++;
	}
	return (test_add2(in, i, tmp));
}

char	*test_and3(char *in, int *i, t_list *tmp, t_list *code)
{
	char *error;

	if (in[*i] == DIRECT_CHAR)
		*i = *i + 1;
	if (in[*i] == LABEL_CHAR)
	{
		if ((error = test_label(in, *i + 1, tmp, code)) != NULL)
			return (error);
		*i = skip_labelchar(in, (*i + 1));
		*i = skip_math(in, *i);
	}
	else if ((in[*i] >= '0' && in[*i] <= '9') || in[*i] == '-')
		*i = skip_numeric(in, *i);
	else
		return (strjoin(ft_itoa(tmp->num), ft_itoa(*i + tmp->white)));
	return (NULL);
}

char	*test_and2(char *in, int *i, t_list *tmp, t_list *code)
{
	int		j;
	char	*error;

	j = 0;
	while (j++ < 2)
	{
		*i = skip_spaces(in, *i);
		if (in[*i] == 'r')
		{
			*i = *i + 1;
			if ((error = test_reg(in, *i, tmp->num)) != NULL)
				return (error);
			*i = skip_numeric(in, *i);
		}
		else if ((error = test_and3(in, i, tmp, code)))
			return (error);
		*i = skip_spaces(in, *i);
		if (in[*i] != SEPARATOR_CHAR)
			return (strjoin(ft_itoa(tmp->num), ft_itoa(*i + tmp->white)));
		*i = *i + 1;
	}
	return (NULL);
}

char	*test_and(char *com, char *in, t_list *tmp, t_list *code)
{
	int		i;
	int		j;
	char	*error;

	i = 0;
	i = skip_spaces(in, i);
	j = -1;
	while (in[i] == com[++j])
		i++;
	if ((error = test_and2(in, &i, tmp, code)))
		return (error);
	i = skip_spaces(in, i);
	if (in[i] == 'r')
	{
		i++;
		if ((error = test_reg(in, i, tmp->num)) != NULL)
			return (error);
		i = skip_numeric(in, i);
	}
	else
		return (strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white)));
	i = skip_spaces(in, i);
	if (in[i] != '\0')
		return (strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white)));
	return (NULL);
}
