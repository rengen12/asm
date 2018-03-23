/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dasm_list_link.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbuy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 17:27:05 by dbuy              #+#    #+#             */
/*   Updated: 2018/03/14 17:27:06 by dbuy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"

char	*find_lab(t_list *set)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	ret = NULL;
	while (set->str[i] == 32 || (set->str[i] >= 9 && set->str[i] <= 13))
		i++;
	while (is_label_char(set->str[i + j]))
		j++;
	if (set->str[i + j] == LABEL_CHAR)
	{
		ret = (char*)malloc(j + 1);
		ret[j] = '\0';
		j = -1;
		while (set->str[i + ++j] != LABEL_CHAR)
			ret[j] = set->str[i + j];
	}
	return (ret);
}

void	set_link2(char *label, char *a, t_list *call, char *tmp)
{
	char *buff;

	if (label == NULL)
	{
		buff = strconcat(call->str, ":label_");
		tmp = strconcat(buff, a);
		free(buff);
		buff = strconcat(tmp, "\n");
		free(tmp);
		call->str = ft_strcpy(call->str, buff);
		call->num = call->num++ + 9 + (int)ft_strlen(a);
		call->str[call->num++] = '\t';
	}
	else
	{
		buff = strconcat(call->str, ":");
		tmp = strconcat(buff, label);
		free(buff);
		buff = strconcat(tmp, "\n");
		free(tmp);
		call->str = ft_strcpy(call->str, buff);
		call->num = call->num++ + 2 + (int)ft_strlen(label);
		call->str[call->num++] = '\t';
	}
	free(buff);
}

void	set_link(t_list *set, t_list *call)
{
	static int	i;
	char		*a;
	char		*label;
	char		*buff;
	char		*tmp;

	tmp = NULL;
	if ((label = find_lab(set)) == NULL)
		i++;
	a = ft_itoa(i);
	if (label == NULL)
	{
		buff = strconcat("\nlabel_", a);
		tmp = strconcat(buff, ":\t");
		free(buff);
		buff = strconcat(tmp, set->str);
		free(tmp);
		set->str = ft_strcpy(set->str, buff);
		free(buff);
	}
	set->num = set->num + 9 + (int)ft_strlen(a);
	set_link2(label, a, call, tmp);
	free(a);
	free(label);
}

void	make_link(t_list *code, int i, int val)
{
	t_list	*tmp;
	t_list	*tmp2;

	tmp = code;
	while (tmp)
	{
		i = 0;
		while (tmp->str[i] != '\n' && tmp->str[i] != DIRECT_CHAR)
			i++;
		if (tmp->str[i] == DIRECT_CHAR)
		{
			tmp2 = (code->next ? code->next->next : NULL);
			val = ft_atoi(tmp->str + i + 1);
			while (tmp2)
			{
				if (val == tmp2->start - tmp->start && val != 0)
				{
					tmp->str[i + 1] = '\0';
					set_link(tmp2, tmp);
				}
				tmp2 = tmp2->next;
			}
		}
		tmp = tmp->next;
	}
}

void	print_list(t_list *code, int flag)
{
	t_list	*tmp;
	int		i;
	char	*num;

	i = 0;
	tmp = code;
	while (tmp)
	{
		i++;
		if ((flag & 8) == 8 && i > 2)
		{
			num = ft_itoa(tmp->start);
			write(1, num, ft_strlen(num));
			write(1, ":\t", 2);
		}
		write(1, tmp->str, ft_strlen(tmp->str));
		tmp = tmp->next;
	}
}
