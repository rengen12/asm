/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
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

char	*make_filename(char *file)
{
	char	*ret;
	int		i;
	int		len;

	len = ft_strlen(file);
	i = -1;
	ret = (char*)malloc(ft_strlen(file) + 3);
	while (++i < len - 2)
		ret[i] = file[i];
	ret[i] = '.';
	ret[++i] = 'c';
	ret[++i] = 'o';
	ret[++i] = 'r';
	ret[++i] = '\0';
	return (ret);
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

int		set_math(t_list *tmp, int i)
{
	int sign;
	int val;

	i = skip_spaces(tmp->str, i);
	if (tmp->str[i] == '-')
		sign = -1;
	else if (tmp->str[i] == '+')
		sign = 1;
	else
		return (0);
	if (tmp->str[i] == '-' || tmp->str[i] == '+')
		i++;
	i = skip_spaces(tmp->str, i);
	val = sign * ft_atoi(tmp->str + i);
	return (val);
}

void	add_args2(t_list *tmp, char *in, int *pos)
{
	int arg;

	arg = (int)ft_atoi(tmp->str + tmp->i + 1);
	if ((tmp->op >= 9 && tmp->op <= 12) || tmp->op == 14 || tmp->op == 15)
	{
		in[*pos] = (char)((arg << 16) >> 24);
		*pos = *pos + 1;
		in[*pos] = (char)((arg << 24) >> 24);
		*pos = *pos + 1;
	}
	else
	{
		in[*pos] = (char)(arg >> 24);
		*pos = *pos + 1;
		in[*pos] = (char)((arg << 8) >> 24);
		*pos = *pos + 1;
		in[*pos] = (char)((arg << 16) >> 24);
		*pos = *pos + 1;
		in[*pos] = (char)((arg << 24) >> 24);
		*pos = *pos + 1;
	}
	tmp->i = skip_numeric(tmp->str, tmp->i + 1);
}

int		add_args3(t_list *tmp, char *in, int *pos, t_lab **add)
{
	char	*t;
	int		arg;

	t = tmp->str + tmp->i;
	if (t[tmp->i] == LABEL_CHAR)
	{
		*add = save_address(*pos, t + tmp->i + 1, *add, 1);
		(*add)->start = tmp->start;
		*pos = *pos + 2;
		tmp->i = skip_labelchar(t, tmp->i + 2);
		tmp->i = skip_spaces(t, tmp->i);
		(*add)->math = set_math(tmp, tmp->i);
		tmp->i = skip_math(t, tmp->i);
	}
	else
	{
		arg = (int)ft_atoi(t + tmp->i + 1);
		in[(*pos)++] = (char)(arg >> 24);
		in[(*pos)++] = (char)((arg << 8) >> 24);
		in[(*pos)++] = (char)((arg << 16) >> 24);
		in[(*pos)++] = (char)((arg << 24) >> 24);
		tmp->i = skip_numeric(t, tmp->i);
	}
	return (tmp->i);
}

int		add_args4(t_list *tmp, int *pos, t_lab **add)
{
	*add = save_address(*pos, tmp->str + tmp->i + 2, *add, 0);
	(*add)->start = tmp->start;
	*pos = ((tmp->op >= 9 && tmp->op <= 12) || tmp->op == 14 || \
									tmp->op == 15 ? *pos + 2 : *pos + 4);
	tmp->i = skip_labelchar(tmp->str, tmp->i + 2);
	tmp->i = skip_spaces(tmp->str, tmp->i);
	(*add)->math = set_math(tmp, tmp->i);
	tmp->i = skip_math(tmp->str, tmp->i);
	return (tmp->i);
}

void	add_args5(t_list *tmp, int *pos, char *in, t_lab **add)
{
	tmp->i = (tmp->str[tmp->i] == SEPARATOR_CHAR ? tmp->i + 1 : tmp->i);
	tmp->i = skip_spaces(tmp->str, tmp->i);
	if (tmp->str[tmp->i] == 'r')
	{
		in[(*pos)++] = (char)ft_atoi(tmp->str + tmp->i++ + 1);
		tmp->i = skip_numeric(tmp->str, tmp->i);
	}
	else if (tmp->str[tmp->i] == DIRECT_CHAR)
	{
		if (tmp->str[tmp->i + 1] == LABEL_CHAR)
			tmp->i = add_args4(tmp, pos, add);
		else
			add_args2(tmp, in, pos);
	}
	else
		tmp->i = add_args3(tmp, in, pos, add);
}

int		add_args(char *in, int pos, t_list *tmp, t_lab **add)
{
	int		j;
	int		n;

	n = 0;
	tmp->i = skip_spaces(tmp->str, 0);
	j = skip_labelchar(tmp->str, tmp->i) - tmp->i;
	tmp->i = (tmp->str[tmp->i + j] == LABEL_CHAR ? tmp->i + j + 1 : tmp->i);
	tmp->i = skip_spaces(tmp->str, tmp->i);
	while (tmp->str[tmp->i] != 32 && (tmp->str[tmp->i] < 9 || \
							tmp->str[tmp->i] > 13) && tmp->str[tmp->i] != '\0')
		tmp->i++;
	while (n++ < 3 && tmp->str[tmp->i] != '\0' && tmp->str[tmp->i] \
															!= COMMENT_CHAR)
	{
		add_args5(tmp, &pos, in, add);
		while (tmp->str[tmp->i] != SEPARATOR_CHAR && tmp->str[tmp->i] != '\0' \
											&& tmp->str[tmp->i] != COMMENT_CHAR)
			tmp->i++;
	}
	return (pos);
}

char	*binary(int a)
{
	char *ret;
	char *hex;

	hex = "0123456789abcdef";
	ret = (char*)malloc(19);
	ret[0] = ((a >> 7 > 0) ? '1' : '0');
	ret[1] = ((a >> 6) % 2 > 0 ? '1' : '0');
	ret[2] = ' ';
	ret[3] = ((a >> 5) % 2 > 0 ? '1' : '0');
	ret[4] = ((a >> 4) % 2 > 0 ? '1' : '0');
	ret[5] = ' ';
	ret[6] = ((a >> 3) % 2 > 0 ? '1' : '0');
	ret[7] = ((a >> 2) % 2 > 0 ? '1' : '0');
	ret[8] = ' ';
	ret[9] = '0';
	ret[10] = '0';
	ret[18] = '\0';
	ret[11] = ' ';
	ret[12] = '(';
	ret[13] = '0';
	ret[14] = 'x';
	ret[15] = (hex[a / 16]);
	ret[16] = (hex[a % 16]);
	ret[17] = ')';
	return (ret);
}

char	*hexa(unsigned char i)
{
	char *hex;
	char *ret;

	ret = (char*)malloc(3);
	ret[2] = '\0';
	hex = "0123456789abcdef";
	ret[0] = hex[(i >> 4)];
	ret[1] = hex[i % 16];
	return (ret);
}

void	add_instr3(int tm, int *pos, char *champ)
{
	char *t;

	while (tm++ != *pos)
	{
		t = hexa(champ[tm - 1]);
		write(1, t, ft_strlen(t));
		free(t);
		write(1, " ", 1);
	}
	write(1, "\n", 1);
}

void	add_instr2(t_list *tmp, int acb, int start, int *pos)
{
	char *t;

	write(1, "\n", 1);
	t = ft_itoa(start - COMMENT_LENGTH - PROG_NAME_LENGTH - 16);
	write(1, t, ft_strlen(t));
	free(t);
	write(1, " (", 2);
	t = ft_itoa(*pos - start);
	write(1, t, ft_strlen(t));
	free(t);
	write(1, ")\t", 2);
	write(1, tmp->str, ft_strlen(tmp->str));
	write(1, "\n\t\tOP = ", 8);
	t = ft_itoa(tmp->op);
	write(1, t, ft_strlen(t));
	free(t);
	write(1, "\n\t\tacb = ", 9);
	if (tmp->op == 1 || tmp->op == 9 || tmp->op == 12 || tmp->op == 15)
		t = "NULL";
	else
		t = binary(acb);
	write(1, t, ft_strlen(t));
	if (ft_strcmp(t, "NULL") != 0)
		free(t);
	write(1, "\n\t\targs = ", 10);
}

int		add_instr(char *champ, int pos, t_list *tmp, t_lab **address)
{
	int			tm;
	int			acb;
	int			start;

	start = pos;
	tmp->start = pos;
	champ[pos] = (char)tmp->op;
	pos++;
	acb = (tmp->op == 12 || tmp->op == 15 || tmp->op == 1 || tmp->op == 9 ? 0 \
														: find_acb(tmp->str));
	if (tmp->op != 12 && tmp->op != 15 && tmp->op != 1 && tmp->op != 9)
		champ[pos++] = (char)acb;
	tm = pos;
	pos = add_args(champ, pos, tmp, address);
	if (tmp->j == 2)
	{
		add_instr2(tmp, acb, start, &pos);
		add_instr3(tm, &pos, champ);
	}
	return (pos);
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
				champ[tmp->pos] = (char)((val << 16) >> 24);
				champ[tmp->pos + 1] = (char)((val << 24) >> 24);
			}
			search = search->next;
		}
		tmp = tmp->next;
	}
}

int		test_label_repeat(t_lab *label, char **error)
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
				error[0] = strconcat("ERROR: duplicated label: ", tmp->lab);
				return (1);
			}
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
	return (0);
}

void	clear_links(t_lab *label, t_lab *address)
{
	t_lab *tmp;
	t_lab *buff;

	tmp = label;
	while (tmp)
	{
		buff = tmp;
		free(tmp->lab);
		free(buff);
		tmp = tmp->next;
	}
	tmp = address;
	while (tmp)
	{
		buff = tmp;
		free(tmp->lab);
		free(buff);
		tmp = tmp->next;
	}
}

int		first_trace2(t_list *tmp, t_list *code, t_lab **label, int *i)
{
	char	*error;

	error = NULL;
	while (is_label_char(tmp->str[*i]))
	{
		code->j = 0;
		while (is_label_char(tmp->str[*i + code->j]))
			code->j++;
		if (tmp->str[*i + code->j] == LABEL_CHAR)
		{
			*label = add_label(*label, new_label(tmp, code->pos, *i));
			if (test_label_repeat(*label, &error) == 1)
				return (-1);
			*i = *i + code->j + 1;
			*i = skip_spaces(tmp->str, *i);
		}
		else
			break ;
	}
	return (0);
}

int		first_trace(char *champ, int pos, t_list *code, int flag)
{
	t_list		*tmp;
	t_lab		*label;
	t_lab		*address;
	int			i;

	tmp = code;
	label = NULL;
	address = NULL;
	while ((tmp = tmp->next))
	{
		i = skip_spaces(tmp->str, 0);
		if (tmp->str[i] == COMMENT_CHAR || tmp->str[i] == '.'\
														|| tmp->str[i] == '\0')
			continue ;
		code->pos = pos;
		if (first_trace2(tmp, code, &label, &i) == -1)
			return (-1);
		if (tmp->str[i] == '\0' || tmp->str[i] == COMMENT_CHAR)
			continue ;
		tmp->j = flag;
		pos = (tmp->op > 0 ? add_instr(champ, pos, tmp, &address) : pos);
	}
	add_links(champ, label, address);
	clear_links(label, address);
	return (pos);
}

void	add_size(char *in, int size)
{
	in[PROG_NAME_LENGTH + 10] = (char)(size >> 8);
	in[PROG_NAME_LENGTH + 11] = (char)size;
}

void	print_success(int display, char *file, int fd)
{
	if ((display & 4) != 4 && fd > 0)
	{
		write(1, "Writing binary to file: ", 24);
		write(1, file, ft_strlen(file));
		write(1, "\n", 1);
	}
}

char	*create(t_list *code, char *file, int display, char **er)
{
	char	*ch;
	int		pos;
	int		fd;
	int		tmp;

	file = make_filename(file);
	ch = (char*)malloc(CHAMP_MAX_SIZE + 5 + PROG_NAME_LENGTH + COMMENT_LENGTH);
	ft_bzero(ch, CHAMP_MAX_SIZE + 5 + PROG_NAME_LENGTH + COMMENT_LENGTH);
	pos = init_header(ch);
	pos = init_name(ch, pos, code);
	pos = init_comment(ch, pos, code);
	tmp = pos;
	pos = first_trace(ch, pos, code, 1);
	if (er[0] != NULL)
		return (er[0]);
	if ((display & 4) == 4)
		pos = first_trace(ch, PROG_NAME_LENGTH + COMMENT_LENGTH + 16, code, 2);
	fd = ((display & 4) != 4 ? open(file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR\
										| S_IWUSR | S_IRGRP | S_IROTH) : -2);
	add_size(ch, pos - tmp);
	print_success(display, file, fd);
	write(fd, ch, pos);
	free(file);
	free(ch);
	return (NULL);
}
