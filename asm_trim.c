/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_trim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbuy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 13:20:23 by dbuy              #+#    #+#             */
/*   Updated: 2018/03/14 13:20:25 by dbuy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"

char	*trim_label(char *in, t_list *tmp)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	i = skip_spaces(in, i);
	j = i;
	ret = (char*)malloc(ft_strlen(in) + 1);
	while (is_label_char(in[i]))
		i++;
	if (in[i] != LABEL_CHAR)
		return (ft_memmove(ret, in, ft_strlen(in) + 1));
	else
	{
		i++;
		i = skip_spaces(in, i);
		tmp->white = tmp->white + i - j;
		ret = ft_memmove(ret, in + i, ft_strlen(in + i) + 1);
		return (ret);
	}
}

char	*trim_space(char *in, t_list *tmp)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ret = (char*)malloc(ft_strlen(in) + 1);
	while (in[i] != '\0' && (in[i] == 32 || (in[i] >= 9 && in[i] <= 13)))
		i++;
	tmp->white = tmp->white + i;
	while (in[i] != '\0')
		ret[j++] = in[i++];
	ret[j] = '\0';
	free(in);
	in = NULL;
	return (ret);
}

t_list	*trim_comment(t_list *code)
{
	t_list	*tmp;
	int		i;

	tmp = code;
	while (tmp)
	{
		i = 0;
		while (tmp->str[i] != COMMENT_CHAR && tmp->str[i] != '\0')
			i++;
		tmp->str[i] = '\0';
		tmp = tmp->next;
	}
	return (code);
}

t_list	*trim_white(t_list *code)
{
	t_list	*tmp;
	int		i;

	tmp = code;
	while (tmp)
	{
		i = 0;
		i = skip_spaces(tmp->str, i);
		tmp->str = ft_memmove(tmp->str, tmp->str + i, \
		ft_strlen(tmp->str) - i + 1);
		tmp->white = i;
		tmp = tmp->next;
	}
	return (code);
}

t_list	*src_modif(t_list *src)
{
	src = lstrev(src);
	src = trim_comment(src);
	src = trim_white(src);
	return (src);
}
