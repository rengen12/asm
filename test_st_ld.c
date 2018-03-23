/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_st_ld.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbuy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 13:30:41 by dbuy              #+#    #+#             */
/*   Updated: 2018/03/14 13:30:43 by dbuy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

char	*test_ld2(char *in, int i, t_list *tmp)
{
	char *error;

	i = skip_spaces(in, i);
	if (in[i] != SEPARATOR_CHAR)
		return (strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white)));
	i++;
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
	return (NULL);
}

char	*test_ld(char *com, char *in, t_list *tmp, t_list *code)
{
	int		i;
	int		j;
	char	*error;

	i = 0;
	j = -1;
	while (in[i] == com[++j])
		i++;
	i = skip_spaces(in, i);
	if (in[i] == DIRECT_CHAR)
		i++;
	if (in[i] == LABEL_CHAR)
	{
		if ((error = test_label(in, ++i, tmp, code)) != NULL)
			return (error);
		i = skip_labelchar(in, i);
		i = skip_math(in, i);
	}
	else if (in[i] == '-' || (in[i] >= '0' && in[i] <= '9'))
		i = skip_numeric(in, i);
	return (test_ld2(in, i, tmp));
}

char	*test_st3(char *in, int i, t_list *tmp, t_list *code)
{
	char *error;

	if (in[i] == LABEL_CHAR)
	{
		if ((error = test_label(in, i + 1, tmp, code)) != NULL)
			return (error);
		i++;
		while (is_label_char(in[i]) == 1)
			i++;
		i = skip_math(in, i);
		if (in[i] != '\0')
			return (strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white)));
	}
	else if ((in[i] >= '0' && in[i] <= '9') || in[i] == '-')
	{
		i = skip_numeric(in, i);
		i = skip_spaces(in, i);
		if (in[i] != '\0')
			return (strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white)));
	}
	else
		return (strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white)));
	return (NULL);
}

char	*test_st2(char *in, int i, t_list *tmp, t_list *code)
{
	char *error;

	if (in[i] == 'r')
	{
		if ((error = test_reg(in, i + 1, tmp->num)) != NULL)
			return (error);
		i++;
		while (in[i] >= '0' && in[i] <= '9')
			i++;
		i = skip_spaces(in, i);
		if (in[i] != '\0')
			return (strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white)));
	}
	else
		return (test_st3(in, i, tmp, code));
	return (NULL);
}

char	*test_st(char *in, char *error, t_list *tmp, t_list *code)
{
	int		i;
	int		j;
	char	*com;

	com = "st";
	i = 0;
	i = skip_spaces(in, i);
	j = -1;
	while (in[i] == com[++j])
		i++;
	i = skip_spaces(in, i);
	if (in[i] != 'r')
		return (strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white)));
	i++;
	if ((error = test_reg(in, i, tmp->num)) != NULL)
		return (error);
	while (in[i] >= '0' && in[i] <= '9')
		i++;
	i = skip_spaces(in, i);
	if (in[i] != SEPARATOR_CHAR)
		return (strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white)));
	i++;
	i = skip_spaces(in, i);
	return (test_st2(in, i, tmp, code));
}
