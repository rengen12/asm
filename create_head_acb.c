/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_head_acb.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbuy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 13:39:55 by dbuy              #+#    #+#             */
/*   Updated: 2018/03/14 13:39:57 by dbuy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

int		init_header(char *header)
{
	int		head;
	int		pos;
	char	tmp;

	pos = 0;
	head = COREWAR_EXEC_MAGIC;
	tmp = head >> 24;
	header[pos++] = tmp;
	tmp = (head << 8) >> 24;
	header[pos++] = tmp;
	tmp = (head << 16) >> 24;
	header[pos++] = tmp;
	tmp = (head << 24) >> 24;
	header[pos] = tmp;
	return (pos + 1);
}

int		init_name(char *champ, int pos, t_list *code)
{
	int		i;
	int		j;
	t_list	*tmp;

	i = 0;
	j = 0;
	tmp = code;
	while (tmp)
	{
		while (tmp->str[j] == 32 || (tmp->str[j] >= 9 && tmp->str[j] <= 13))
			j++;
		if (tmp->str[j] == '.')
			break ;
		tmp = tmp->next;
	}
	if (!tmp)
		return (write(1, "Error", 6) - 6);
	while (tmp->str[j] != '"' && tmp->str[j] != '\0')
		j++;
	j++;
	while (tmp->str[j] != '"' && tmp->str[j] != '\0' && i++ >= 0)
		champ[pos++] = tmp->str[j++];
	while (i++ < PROG_NAME_LENGTH + 8)
		champ[pos++] = 0;
	return (pos);
}

int		init_comment(char *champ, int pos, t_list *code)
{
	int		i;
	int		j;
	t_list	*tmp;

	i = 0;
	j = 0;
	tmp = code;
	while (tmp)
	{
		j = 0;
		while (tmp->str[j] == 32 || (tmp->str[j] >= 9 && tmp->str[j] <= 13))
			j++;
		if (tmp->str[j] == '.' && tmp->str[j + 1] == 'c')
			break ;
		tmp = tmp->next;
	}
	while (tmp->str[j] != '"' && tmp->str[j] != '\0')
		j++;
	j++;
	while (tmp->str[j] != '"' && tmp->str[j] != '\0' && i++ >= 0)
		champ[pos++] = tmp->str[j++];
	while (i++ < COMMENT_LENGTH + 4)
		champ[pos++] = 0;
	return (pos);
}

int		find_acb2(char *in, int i, int acb)
{
	while (in[i] != SEPARATOR_CHAR && in[i] != '\0' && in[i] != COMMENT_CHAR)
		i++;
	if (in[i] == COMMENT_CHAR || in[i] == '\0')
		return (acb);
	i = skip_spaces(in, ++i);
	if (in[i] == 'r')
		acb = acb + 16;
	else if (in[i] == DIRECT_CHAR)
		acb = acb + 32;
	else
		acb = acb + 48;
	while (in[i] != SEPARATOR_CHAR && in[i] != '\0' && in[i] != COMMENT_CHAR)
		i++;
	if (in[i] == COMMENT_CHAR || in[i] == '\0')
		return (acb);
	i = skip_spaces(in, ++i);
	if (in[i] == 'r')
		acb = acb + 4;
	else if (in[i] == DIRECT_CHAR)
		acb = acb + 8;
	else
		acb = acb + 12;
	while (in[i] != SEPARATOR_CHAR && in[i] != '\0' && in[i] != COMMENT_CHAR)
		i++;
	return (acb);
}

int		find_acb(char *in)
{
	int		i;
	int		j;
	int		acb;

	i = 0;
	j = 0;
	i = skip_spaces(in, i);
	while (is_label_char(in[i + j]) == 1)
		j++;
	if (in[i + j] == LABEL_CHAR)
		i = i + j + 1;
	i = skip_spaces(in, i);
	while (in[i] != 32 && (in[i] < 9 || in[i] > 13) && in[i] != '\0')
		i++;
	i = skip_spaces(in, i);
	if (in[i] == 'r')
		acb = 64;
	else
		acb = (in[i] == DIRECT_CHAR ? 128 : 192);
	return (find_acb2(in, i, acb));
}
