/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_labels.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbuy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 13:39:55 by dbuy              #+#    #+#             */
/*   Updated: 2018/03/14 13:39:57 by dbuy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

t_lab	*save_address(int pos, char *str, t_lab *address, int indir)
{
	t_lab	*new;
	char	*label;
	int		i;

	i = 0;
	while (is_label_char(str[i]))
		i++;
	label = (char*)malloc(i + 1);
	label[i] = '\0';
	i = -1;
	while (is_label_char(str[++i]))
		label[i] = str[i];
	new = (t_lab*)malloc(sizeof(t_lab));
	new->lab = label;
	new->next = address;
	new->pos = pos;
	new->indir = (indir == 1 ? 1 : 0);
	return (new);
}

t_lab	*new_label(t_list *node, int pos, int i)
{
	t_lab	*ret;
	int		tmp;
	char	*label;
	int		j;

	j = 0;
	tmp = i;
	while (is_label_char(node->str[i]))
		i++;
	label = (char*)malloc(i - tmp + 1);
	label[i - tmp] = '\0';
	i = tmp;
	while (is_label_char(node->str[i]))
		label[j++] = node->str[i++];
	ret = (t_lab*)malloc(sizeof(t_lab));
	ret->lab = label;
	ret->pos = pos;
	ret->next = NULL;
	return (ret);
}

t_lab	*add_label(t_lab *head, t_lab *new)
{
	new->next = head;
	return (new);
}

void	add_links(char *champ, t_lab *label, t_lab *address)
{
	t_lab	*tmp;
	t_lab	*search;
	int		val;

	tmp = address;
	while (tmp)
	{
		search = label;
		while (search)
		{
			if (ft_strcmp(tmp->lab, search->lab) == 0)
			{
				val = search->pos - tmp->start + tmp->math;
				champ[tmp->pos + tmp->cor] = (char)((val << 16) >> 24);
				champ[tmp->pos + 1 + tmp->cor] = (char)((val << 24) >> 24);
				if (tmp->cor == 2)
				{
					champ[tmp->pos] = (char)(val >> 24);
					champ[tmp->pos + 1] = (char)((val << 8) >> 24);
				}
			}
			search = search->next;
		}
		tmp = tmp->next;
	}
}

int		test_label_repeat(t_lab *label)
{
	t_lab	*tmp;
	t_lab	*tmp2;

	tmp = label;
	while (tmp)
	{
		tmp2 = tmp->next;
		while (tmp2)
		{
			if (ft_strcmp(tmp->lab, tmp2->lab) == 0)
			{
				write(1, "ERROR: duplicated label: ", 25);
				write(1, tmp->lab, ft_strlen(tmp->lab));
				return (1);
			}
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
	return (0);
}
