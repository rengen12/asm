/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbuy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 13:30:41 by dbuy              #+#    #+#             */
/*   Updated: 2018/03/14 13:30:43 by dbuy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

char	*test_reg(char *in, int i, int num)
{
	char	*tr;
	long	reg;

	tr = (char*)malloc(ft_strlen(in) + 1);
	tr = copy_index(tr, in, i, 1);
	reg = ft_atoi(tr);
	free(tr);
	if (reg < 1 || reg > REG_NUMBER)
		return (strjoin(ft_itoa(num), ft_itoa(i)));
	return (NULL);
}

int		is_label_char(char test)
{
	char	*label;
	int		i;

	i = -1;
	label = LABEL_CHARS;
	while (label[++i] != '\0')
		if (test == label[i])
			return (1);
	return (0);
}

int		find_label(char *label, t_list *code)
{
	t_list	*tmp;
	int		i;
	int		j;

	tmp = code;
	while (tmp)
	{
		j = 0;
		i = 0;
		i = skip_spaces(tmp->str, i);
		if (tmp->str[i] == label[0])
		{
			while (tmp->str[i] != '\0' && label[j] != '\0' \
			&& tmp->str[i] == label[j])
			{
				i++;
				j++;
			}
			if (label[j] == '\0' && tmp->str[i] == LABEL_CHAR)
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

char	*test_label(char *in, int i, t_list *tmp, t_list *code)
{
	int		size;
	char	*label;
	char	*a;
	char	*b;
	int		j;

	j = 0;
	size = 0;
	while (is_label_char(in[i++]) == 1)
		size++;
	i = i - size - 1;
	label = (char*)malloc(size + 1);
	label[size] = '\0';
	while (size-- > 0)
		label[j++] = in[i++];
	if (find_label(label, code) == 0)
	{
		a = ft_itoa(tmp->num);
		b = ft_itoa(i + tmp->white);
		free(label);
		label = strjoin(a, b);
		return (label);
	}
	free(label);
	return (NULL);
}
