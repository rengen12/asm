/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbuy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 17:19:06 by dbuy              #+#    #+#             */
/*   Updated: 2018/03/14 17:19:08 by dbuy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		skip_spaces(char *str, int i)
{
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	return (i);
}

int		skip_labelchar(char *str, int i)
{
	while (is_label_char(str[i]))
		i++;
	return (i);
}

int		skip_numeric(char *str, int i)
{
	if (str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	i = skip_spaces(str, i);
	return (i);
}

int		skip_math(char *str, int i)
{
	i = skip_spaces(str, i);
	if (str[i] == '-' || str[i] == '+')
		i++;
	i = skip_spaces(str, i);
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	i = skip_spaces(str, i);
	return (i);
}

int		skip_com(char *str, char *com)
{
	int ret;
	int j;

	ret = 0;
	j = 0;
	ret = skip_spaces(str, ret);
	while (str[ret] == com[j++])
		ret++;
	ret = skip_spaces(str, ret);
	return (ret);
}
