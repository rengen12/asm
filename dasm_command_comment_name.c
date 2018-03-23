/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dasm_command_comment_name.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbuy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 17:27:05 by dbuy              #+#    #+#             */
/*   Updated: 2018/03/14 17:27:06 by dbuy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"

t_list	*add_op(char *com, t_list *out, int pos, int *j)
{
	int i;

	i = 0;
	while (com[i] != 0)
		out->str[pos++] = com[i++];
	out->start = j[0] - PROG_NAME_LENGTH - COMMENT_LENGTH - 16;
	out->num = pos;
	return (out);
}

t_list	*add_command2(t_list **new, char *in, int *i, int pos)
{
	if (in[*i] == 8)
		*new = add_op("xor", *new, pos, i);
	else if (in[*i] == 9)
		*new = add_op("zjmp", *new, pos, i);
	else if (in[*i] == 10)
		*new = add_op("ldi", *new, pos, i);
	else if (in[*i] == 11)
		*new = add_op("sti", *new, pos, i);
	else if (in[*i] == 12)
		*new = add_op("fork", *new, pos, i);
	else if (in[*i] == 13)
		*new = add_op("lld", *new, pos, i);
	else if (in[*i] == 14)
		*new = add_op("lldi", *new, pos, i);
	else if (in[*i] == 15)
		*new = add_op("lfork", *new, pos, i);
	else if (in[*i] == 16)
		*new = add_op("aff", *new, pos, i);
	else
		pos++;
	return (*new);
}

t_list	*add_command(t_list *out, char *in, int *i, int pos)
{
	t_list *new;

	new = (t_list*)malloc(sizeof(t_list));
	new->next = out;
	new->str = (char*)malloc(1000);
	if (in[*i] == 1)
		new = add_op("live", new, pos, i);
	else if (in[*i] == 2)
		new = add_op("ld", new, pos, i);
	else if (in[*i] == 3)
		new = add_op("st", new, pos, i);
	else if (in[*i] == 4)
		new = add_op("add", new, pos, i);
	else if (in[*i] == 5)
		new = add_op("aub", new, pos, i);
	else if (in[*i] == 6)
		new = add_op("and", new, pos, i);
	else if (in[*i] == 7)
		new = add_op("or", new, pos, i);
	else
		new = add_command2(&new, in, i, pos);
	*i = *i + 1;
	pos = new->num;
	pos = add_arg(new, in, i, in[*i - 1]);
	return (new);
}

t_list	*add_comment(t_list *out, char *in, int max, int pos)
{
	int		i;
	int		j;
	char	*name;
	t_list	*new;

	new = (t_list*)malloc(sizeof(t_list));
	new->next = out;
	new->str = (char*)malloc(1000);
	name = ".comment";
	i = PROG_NAME_LENGTH + 12;
	j = 0;
	while (name[j] != '\0')
		new->str[pos++] = name[j++];
	new->str[pos++] = ' ';
	new->str[pos++] = '"';
	while (in[i] != '\0' && i <= max)
		new->str[pos++] = in[i++];
	new->str[pos++] = '"';
	new->str[pos++] = '\n';
	new->str[pos] = '\n';
	return (new);
}

t_list	*add_name(t_list *out, char *in, int max, int pos)
{
	int		i;
	int		j;
	char	*name;

	out = (t_list*)malloc(sizeof(t_list));
	out->next = NULL;
	out->str = (char*)malloc(1000);
	name = ".name";
	i = 4;
	j = 0;
	while (name[j] != '\0')
		out->str[pos++] = name[j++];
	out->str[pos++] = ' ';
	out->str[pos++] = '"';
	while (in[i] != '\0' && i <= max)
		out->str[pos++] = in[i++];
	out->str[pos++] = '"';
	out->str[pos++] = '\n';
	return (out);
}
