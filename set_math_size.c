/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_math_size.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbuy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 13:39:55 by dbuy              #+#    #+#             */
/*   Updated: 2018/03/14 13:39:57 by dbuy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

int		set_math(t_list *tmp, int i)
{
	int sign;
	int val;

	i = skip_spaces(tmp->str, i);
	if (tmp->str[i] == '-')
		sign = -1;
	else if (tmp->str[i] == '+')
		sign = 1;
	else
		return (0);
	if (tmp->str[i] == '-' || tmp->str[i] == '+')
		i++;
	i = skip_spaces(tmp->str, i);
	val = sign * ft_atoi(tmp->str + i);
	return (val);
}

void	add_size(char *in, int size)
{
	in[PROG_NAME_LENGTH + 10] = (char)(size >> 8);
	in[PROG_NAME_LENGTH + 11] = (char)size;
}
