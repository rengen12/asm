/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_support2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbuy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 13:20:23 by dbuy              #+#    #+#             */
/*   Updated: 2018/03/14 13:20:25 by dbuy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"

int		find_op2(char *in)
{
	if (is_substr(in, "add") == 1)
		return (4);
	else if (is_substr(in, "aff") == 1)
		return (16);
	else if (is_substr(in, "and") == 1)
		return (6);
	else if (is_substr(in, "xor") == 1)
		return (8);
	else if (is_substr(in, "or") == 1)
		return (7);
	else if (is_substr(in, "zjmp") == 1)
		return (9);
	else if (is_substr(in, "fork") == 1)
		return (12);
	else if (is_only_spaces(in) == 1)
		return (0);
	return (-1);
}

int		find_op(char *in)
{
	if (is_substr(in, "lldi") == 1)
		return (14);
	if (is_substr(in, "ldi") == 1)
		return (10);
	else if (is_substr(in, "lld") == 1)
		return (13);
	else if (is_substr(in, "ld") == 1)
		return (2);
	else if (is_substr(in, "lfork") == 1)
		return (15);
	else if (is_substr(in, "live") == 1)
		return (1);
	else if (is_substr(in, "sti") == 1)
		return (11);
	else if (is_substr(in, "st") == 1)
		return (3);
	else if (is_substr(in, "sub") == 1)
		return (5);
	else
		return (find_op2(in));
}

char	*copy_index(char *ret, char *in, int i, int numeric)
{
	int j;

	j = -1;
	if (numeric == 0)
		while (in[++j + i] != '\0')
			ret[j] = in[j + i];
	else
		while (in[++j + i] != '\0' && (in[i] == 32 || (in[i] >= 9 && \
		in[i] <= 13) || (in[i] >= '0' && in[i] <= '9')\
		|| in[i] == '+' || in[i] == '-'))
			ret[j] = in[j + i];
	ret[j] = '\0';
	return (ret);
}

int		is_only_spaces(char *in)
{
	int i;

	i = 0;
	while (in[i] == 32 || (in[i] >= 9 && in[i] <= 13))
		i++;
	if (in[i] == '\0')
		return (1);
	return (0);
}

int		is_substr(char *a, char *b)
{
	int i;

	i = 0;
	while (a[i] != 0 && b[i] != 0 && a[i] == b[i])
		i++;
	if (b[i] == '\0')
		return (1);
	return (0);
}
