/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbuy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 13:37:18 by dbuy              #+#    #+#             */
/*   Updated: 2018/03/14 13:37:20 by dbuy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_list	*listn(char *in)
{
	t_list		*ret;
	static int	num;

	num++;
	ret = (t_list *)malloc(sizeof(t_list));
	ret->next = NULL;
	ret->white = 1;
	ret->op = 0;
	ret->num = num;
	ret->str = (char*)malloc(ft_strlen(in) + 1);
	ret->str = ft_memmove(ret->str, in, ft_strlen(in) + 1);
	return (ret);
}

t_list	*listadd(t_list *head, t_list *new)
{
	new->next = head;
	return (new);
}

char	*strjoin(char *a, char *b)
{
	size_t	len;
	char	*er;
	int		i;
	int		j;
	char	*out;

	er = "Syntax error at token [";
	len = ft_strlen(er) + ft_strlen(a) + ft_strlen(b) + 2;
	out = (char*)malloc(len + 1);
	out[len] = 0;
	i = -1;
	while (er[++i] != '\0')
		out[i] = er[i];
	j = 0;
	while (a[j] != '\0')
		out[i++] = a[j++];
	out[i] = ':';
	j = 0;
	while (b[j] != '\0')
		out[++i] = b[j++];
	out[++i] = ']';
	free(a);
	free(b);
	return (out);
}

char	*strconcat(char *a, char *b)
{
	char	*ret;
	int		i;
	int		j;

	ret = (char*)malloc(ft_strlen(a) + ft_strlen(b) + 1);
	i = -1;
	while (a[++i] != '\0')
		ret[i] = a[i];
	j = -1;
	while (b[++j] != '\0')
		ret[i++] = b[j];
	ret[i] = '\0';
	return (ret);
}

t_list	*lstrev(t_list *com)
{
	t_list *tmp;
	t_list *link;

	if (!com)
		return (NULL);
	tmp = com->next;
	com->next = NULL;
	while (tmp)
	{
		link = tmp->next;
		tmp->next = com;
		com = tmp;
		tmp = link;
	}
	return (com);
}
