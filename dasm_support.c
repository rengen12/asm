/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dasm_support.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbuy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 17:27:05 by dbuy              #+#    #+#             */
/*   Updated: 2018/03/14 17:27:06 by dbuy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"

char	*ft_strcpy(char *out, char *in)
{
	int	i;

	i = 0;
	while (in[i++] != '\0')
		out[i - 1] = in[i - 1];
	out[i - 1] = '\0';
	return (out);
}

void	clear_list(t_list *in)
{
	t_list *tmp;
	t_list *buff;

	tmp = in;
	while (tmp)
	{
		buff = tmp;
		free(tmp->str);
		tmp = tmp->next;
		free(buff);
	}
}

int		ft_strcmp(char *a, char *b)
{
	int i;

	i = 0;
	while (a[i] == b[i] && a[i] != '\0' && b[i] != '\0')
		i++;
	return (a[i] - b[i]);
}
