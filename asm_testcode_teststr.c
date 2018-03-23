/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_testcode_teststr.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbuy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 13:20:23 by dbuy              #+#    #+#             */
/*   Updated: 2018/03/14 13:20:25 by dbuy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"

char	*test_str3(int op, char *tr, t_list *tmp, t_list *code)
{
	char *error;

	error = NULL;
	if (op == 7)
		error = test_and("or", tr, tmp, code);
	else if (op == 8)
		error = test_and("xor", tr, tmp, code);
	else if (op == 9)
		error = test_fork("zjmp", tr, tmp, code);
	else if (op == 12)
		error = test_fork("fork", tr, tmp, code);
	else if (op == 15)
		error = test_fork("lfork", tr, tmp, code);
	else if (op == 10)
		error = test_ldi("ldi", tr, tmp, code);
	else if (op == 14)
		error = test_ldi("lldi", tr, tmp, code);
	else if (op == 11)
		error = test_sti("sti", tr, tmp, code);
	else if (op == 16)
		error = test_aff("aff", tr, tmp);
	return (error);
}

char	*test_str2(int op, char *tr, t_list *tmp, t_list *code)
{
	char *error;

	error = NULL;
	if (op == 1)
		error = test_fork("live", tr, tmp, code);
	else if (op == 2)
		error = test_ld("ld", tr, tmp, code);
	else if (op == 13)
		error = test_ld("lld", tr, tmp, code);
	else if (op == 3)
		error = test_st(tr, error, tmp, code);
	else if (op == 4)
		error = test_add("add", tr, tmp);
	else if (op == 5)
		error = test_add("sub", tr, tmp);
	else if (op == 6)
		error = test_and("and", tr, tmp, code);
	else
		error = test_str3(op, tr, tmp, code);
	return (error);
}

char	*test_str(t_list *tmp, t_list *code)
{
	int		op;
	char	*tr;
	char	*error;

	tr = trim_label(tmp->str, tmp);
	tr = trim_space(tr, tmp);
	op = find_op(tr);
	tmp->op = op;
	if (op < 0)
		error = strconcat("Invalid comand ", tmp->str);
	else
		error = test_str2(op, tr, tmp, code);
	free(tr);
	tmp->op = op;
	return (error);
}

char	*test_code2(t_list *tmp, int i, t_list *code, char *error)
{
	if (i == 0)
		error = test_first(tmp->str, code, error, NAME_CMD_STRING);
	else if (i == 1)
		error = test_first(tmp->str, code, error, COMMENT_CMD_STRING);
	else
		error = test_str(tmp, code);
	if (error)
	{
		clear_src(code);
		return (error);
	}
	return (NULL);
}

char	*test_code(t_list *code, char *error)
{
	t_list	*tmp;
	int		i;
	int		num;

	tmp = code;
	i = 0;
	num = 1;
	while (tmp)
	{
		if (find_comment(tmp->str) == 1 || ft_strlen(tmp->str) == 0 ||\
		is_only_spaces(tmp->str) == 1)
		{
			tmp = tmp->next;
			num++;
			continue ;
		}
		if ((error = test_code2(tmp, i, code, error)))
			return (error);
		tmp = tmp->next;
		num++;
		i++;
	}
	if (error)
		clear_src(code);
	return (error);
}
