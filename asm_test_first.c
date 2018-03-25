/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_test_first.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbuy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 13:20:23 by dbuy              #+#    #+#             */
/*   Updated: 2018/03/14 13:20:25 by dbuy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"

int		ft_findstr(char *in, t_list *code)
{
	int		ret;
	t_list	*tmp;

	tmp = code;
	ret = 1;
	while (tmp)
	{
		if (ft_strcmp(in, tmp->str) == 0)
			break ;
		tmp = tmp->next;
		ret++;
	}
	return (ret);
}

char	*make_error(char *error, char *in, int i, t_list *code)
{
	char *a;
	char *b;

	a = ft_itoa(i);
	b = ft_itoa(ft_findstr(in, code));
	error = strjoin(b, a);
	return (error);
}

char	*clear_src(t_list *src)
{
	t_list *tmp;
	t_list *buff;

	tmp = src;
	while (tmp)
	{
		buff = tmp;
		free(tmp->str);
		tmp = tmp->next;
		free(buff);
	}
	return (NULL);
}

char	*test_first2(int i, int rew)
{
	if (rew == 1 && i > PROG_NAME_LENGTH + 5)
		return (strconcat("Too long name/comment", ""));
	if (rew == 2 && i > COMMENT_LENGTH + 8)
		return (strconcat("Too long comment", ""));
	return (NULL);
}

char	*test_first(char *in, t_list *code, char *error, char *name)
{
	static int	rew;
	int			i;
	int			j;

	j = 0;
	rew++;
	i = skip_spaces(in, 0);
	if (in[i] != name[0])
		return (make_error(error, in, i, code));
	while (in[i] != '\0' && name[j] != '\0')
		if (in[i++] != name[j++])
			return (make_error(error, in, i, code));
	i = skip_spaces(in, i);
	if (in[i++] != '"')
		return (make_error(error, in, i, code));
	if (in[i] == '"' && rew == 1)
		return (make_error(error, in, i, code));
	while (in[i] != '"' && in[i] != '\0')
		i++;
	if (in[i++] != '"')
		return (make_error(error, in, i, code));
	i = skip_spaces(in, i);
	if (in[i] != '\0' && in[i] != COMMENT_CHAR)
		return (make_error(error, in, i, code));
	return (test_first2(i, rew));
}
