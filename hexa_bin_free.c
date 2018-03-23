/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexa_bin_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbuy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 13:39:55 by dbuy              #+#    #+#             */
/*   Updated: 2018/03/14 13:39:57 by dbuy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

char	*binary(int a)
{
	char *ret;
	char *hex;

	hex = "0123456789abcdef";
	ret = (char*)malloc(19);
	ret[0] = ((a >> 7 > 0) ? '1' : '0');
	ret[1] = ((a >> 6) % 2 > 0 ? '1' : '0');
	ret[2] = ' ';
	ret[3] = ((a >> 5) % 2 > 0 ? '1' : '0');
	ret[4] = ((a >> 4) % 2 > 0 ? '1' : '0');
	ret[5] = ' ';
	ret[6] = ((a >> 3) % 2 > 0 ? '1' : '0');
	ret[7] = ((a >> 2) % 2 > 0 ? '1' : '0');
	ret[8] = ' ';
	ret[9] = '0';
	ret[10] = '0';
	ret[18] = '\0';
	ret[11] = ' ';
	ret[12] = '(';
	ret[13] = '0';
	ret[14] = 'x';
	ret[15] = (hex[a / 16]);
	ret[16] = (hex[a % 16]);
	ret[17] = ')';
	return (ret);
}

char	*hexa(unsigned char i)
{
	char *hex;
	char *ret;

	ret = (char*)malloc(3);
	ret[2] = '\0';
	hex = "0123456789abcdef";
	ret[0] = hex[(i >> 4)];
	ret[1] = hex[i % 16];
	return (ret);
}

char	*expand(char **ch, int pos, int max)
{
	char *ret;

	ret = (char*)malloc(max * 2 + 10);
	ft_bzero(ret, max * 2 + 10);
	while (pos-- > 0)
		ret[pos] = (*ch)[pos];
	free(*ch);
	return (ret);
}

void	clear_links(t_lab *label, t_lab *address)
{
	t_lab *tmp;
	t_lab *buff;

	tmp = label;
	while (tmp)
	{
		buff = tmp;
		free(tmp->lab);
		free(buff);
		tmp = tmp->next;
	}
	tmp = address;
	while (tmp)
	{
		buff = tmp;
		free(tmp->lab);
		free(buff);
		tmp = tmp->next;
	}
}

int		free_lab_add(t_lab *label, t_lab *address)
{
	t_lab *tmp;
	t_lab *tm;

	tmp = label;
	while (tmp)
	{
		tm = tmp;
		free(tmp->lab);
		tmp = tmp->next;
		free(tm);
	}
	tmp = address;
	while (tmp)
	{
		tm = tmp;
		free(tmp->lab);
		tmp = tmp->next;
		free(tm);
	}
	return (-1);
}
