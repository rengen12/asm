//
// Created by Denis BUY on 3/5/18.
//

#include "asm.h"
#include "op.h"

int		init_header(char *header)
{
	int		head;
	int 	pos;
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

char 	*make_filename(char *file)
{
	char	*ret;
	int 	i;
	int 	len;

	len = ft_strlen(file);
	printf(">>>>>>>>>>>>>%s\n", file);
	printf("len = %d\n", len);
	i = -1;
	ret = (char*)malloc(ft_strlen(file) + 3);
	while (++i < len - 2)
		ret[i] = file[i];
	ret[i] = '.';
	ret[++i] = 'c';
	ret[++i] = 'o';
	ret[++i] = 'r';
	ret[++i] = '\0';
	printf(">>>>>>>>>>>>>%s\n", ret);
	return (ret);
}

int 	init_name(char *champ, int pos, t_list *code)
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
//	printf("name str = '%s', j = %d, char = '%c'\n", tmp->str, j, tmp->str[j]);
	while (tmp->str[j] != '"' && tmp->str[j] != '\0' && i++ >= 0)
		champ[pos++] = tmp->str[j++];
//	printf("name str = '%s', j = %d, char = '%c'\n", tmp->str, j, tmp->str[j]);
	while (i++ < PROG_NAME_LENGTH + 8)
		champ[pos++] = 0;
	return (pos);
}

int 	init_comment(char *champ, int pos, t_list *code)
{
	int		i;
	int		j;
	t_list	*tmp;

	i = 0;
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
//	printf("name str = '%s', j = %d, char = '%c'\n", tmp->str, j, tmp->str[j]);
	while (tmp->str[j] != '"' && tmp->str[j] != '\0' && i++ >= 0)
		champ[pos++] = tmp->str[j++];
//	printf("name str = '%s', j = %d, char = '%c'\n", tmp->str, j, tmp->str[j]);
	while (i++ < COMMENT_LENGTH + 4)
		champ[pos++] = 0;
	return (pos);
}

int 	find_acb(char *in)
{
	int 	i;
	int 	j;
	int 	acb;

	i = 0;
	j = 0;
	acb = 0;
//	printf(">>>>>>>>>>>>>>>>> '%s'\n", in);
	while (in[i] == 32 || (in[i] >= 9 && in[i] <= 13))
		i++;
	while (is_label_char(in[i + j]) == 1)
		j++;
	if (in[i + j] == LABEL_CHAR)
		i = i + j + 1;
	while (in[i] == 32 || (in[i] >= 9 && in[i] <= 13))
		i++;
	while (in[i] != 32 && (in[i] < 9 || in[i] > 13) && in[i] != '\0')
		i++;
	while (in[i] == 32 || (in[i] >= 9 && in[i] <= 13))
		i++;
	if (in[i] == 'r')
	{
		acb = 64;
		while (in[i] != SEPARATOR_CHAR && in[i] != '\0')
			i++;
	}
	else if (in[i] == DIRECT_CHAR)
	{
		acb = 128;
		while (in[i] != SEPARATOR_CHAR && in[i]!= '\0')
			i++;
	}
	else
	{
		acb = 192;
		while (in[i] != SEPARATOR_CHAR && in[i]!= '\0')
			i++;
	}
	if (in[i] == SEPARATOR_CHAR)
		i++;
	while (in[i] == 32 || (in[i] >= 9 && in[i] <= 13))
		i++;
//	printf("acb = %d, next char = '%c', i = %d\n", acb, in[i], i);
	if (in[i] != '\0')
	{
		if (in[i] == 'r')
		{
			acb = acb + 16;
			while (in[i] != SEPARATOR_CHAR && in[i] != '\0')
				i++;
		}
		else if (in[i] == DIRECT_CHAR)
		{
			acb = acb + 32;
			while (in[i] != SEPARATOR_CHAR && in[i]!= '\0')
				i++;
		}
		else
		{
			acb = acb + 48;
			while (in[i] != SEPARATOR_CHAR && in[i]!= '\0')
				i++;
		}
	}
	if (in[i] == SEPARATOR_CHAR)
		i++;
	while (in[i] == 32 || (in[i] >= 9 && in[i] <= 13))
		i++;
//	printf("acb = %d, next char = '%c', i = %d\n", acb, in[i], i);
	if (in[i] != '\0')
	{
		if (in[i] == 'r')
		{
			acb = acb + 4;
			while (in[i] != SEPARATOR_CHAR && in[i] != '\0')
				i++;
		}
		else if (in[i] == DIRECT_CHAR)
		{
			acb = acb + 8;
			while (in[i] != SEPARATOR_CHAR && in[i]!= '\0')
				i++;
		}
		else
		{
			acb = acb + 12;
			while (in[i] != SEPARATOR_CHAR && in[i]!= '\0')
				i++;
		}
	}
//	printf("final acb = %d\n", acb);
	return (acb);
}

t_lab	*save_address(int pos, char *str, t_lab *address)
{
	t_lab	*new;
	char	*label;
	int		i;

	printf("saving address '%s'\n", str);
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
//	printf("saved address = '%s'\n", new->lab);
	return (new);
}

int 	add_args(char *in, int pos, char *c, t_lab *address)
{
	int 	i;
	int 	j;
	int 	n;
	int 	arg;

	i = 0;
	j = 0;
	n = 0;
//	printf(">>>>>>>>>>>>>>>>> '%s'\n", in);
	while (c[i] == 32 || (c[i] >= 9 && c[i] <= 13))
		i++;
	while (is_label_char(c[i + j]) == 1)
		j++;
	if (c[i + j] == LABEL_CHAR)
		i = i + j + 1;
	while (c[i] == 32 || (c[i] >= 9 && c[i] <= 13))
		i++;
	while (c[i] != 32 && (c[i] < 9 || c[i] > 13) && c[i] != '\0')
		i++;
//	printf("Making args\n");
	while (n++ < 3)
	{
		if (c[i] == '\0')
			break ;
		if (c[i] == SEPARATOR_CHAR)
			i++;
		while (c[i] == 32 || (c[i] >= 9 && c[i] <= 13))
			i++;
		if (c[i] == 'r')
		{
			arg = (int) ft_atoi(c + i + 1);
			in[pos] = (char) arg;
			pos++;
			i++;
			while (c[i] >= '0' && c[i] <= '9')
				i++;
		}
		else if (c[i] == DIRECT_CHAR)
		{
			if (c[i + 1] == LABEL_CHAR)
			{
				address = save_address(pos, c + i + 2, address);
				arg = 0;
				in[pos++] = 0;
				in[pos++] = 0;
				i = i + 2;
				while (is_label_char(c[i]))
					i++;
			}
			else
			{
				arg = (int) ft_atoi(c + i + 1);
				in[pos++] = arg >> 24;
				in[pos++] = (arg << 8) >> 24;
				in[pos++] = (arg << 16) >> 24;
				in[pos++] = (arg << 24) >> 24;
				i++;
				while (c[i] >= '0' && c[i] <= '9')
					i++;
			}
		}
		else
		{
			if (c[i] == LABEL_CHAR)
			{
				address = save_address(pos, c + i + 1, address);
				arg = 0;
				in[pos++] = 0;
				in[pos++] = 0;
				i = i + 2;
				while (is_label_char(c[i]))
					i++;
			}
			else
			{
				arg = (int) ft_atoi(c + i + 1);
				in[pos++] = arg >> 24;
				in[pos++] = (arg << 8) >> 24;
				in[pos++] = (arg << 16) >> 24;
				in[pos++] = (arg << 24) >> 24;
				while (c[i] >= '0' && c[i] <= '9')
					i++;
			}
		}
		while (c[i] != SEPARATOR_CHAR && c[i] != '\0')
			i++;
	}
//	printf("Returning args\n");
	return (pos);
}

int 	add_instr(char *champ, int pos, t_list *tmp, t_lab *address)
{
//	printf("test\n");
//	printf("pos = %d\n", pos);

	int	acb;

//	printf("STR = '%s', acb = %d\n", tmp->str, acb);
	champ[pos] = (char)tmp->op;
	pos++;
	if (tmp->op == 12 || tmp->op == 15 || tmp->op == 1 || tmp->op == 9)
		acb = 0;
	else
		acb = find_acb(tmp->str);
	if (tmp->op != 12 && tmp->op != 15 && tmp->op != 1 && tmp->op != 9)
	{
		champ[pos] = (char)acb;
		pos++;
	}
	pos = add_args(champ, pos, tmp->str, address);
	return (pos);
}

t_lab	*new_label(t_list *node, int pos, int i)
{
//	printf("label was found\n");
	t_lab	*ret;
	int 	tmp;
	char 	*label;
	int 	j;

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

void	print_labels(t_lab *label)
{
	t_lab *tmp;

	printf("LABELS:\n");
	tmp = label;
	while (tmp)
	{
		printf("LABEL: '%s', pos = %d\n", tmp->lab, tmp->pos);
		tmp = tmp->next;
	}
}

int		first_trace(char *champ, int pos, t_list *code)
{
	t_list	*tmp;
	t_lab	*label;
	t_lab	*address;
	int 	i;
	int 	j;

	tmp = code;
	label = NULL;
	address = NULL;
	while (tmp)
	{
		i = 0;
		j = 0;
		while (tmp->str[i] == 32 || (tmp->str[i] >= 9 && tmp->str[i] <= 13))
			i++;
		if (tmp->str[i] == COMMENT_CHAR || tmp->str[i] == '.' || tmp->str[i] == '\0')
		{
			tmp = tmp->next;
			continue ;
		}
		if (is_label_char(tmp->str[i]))
			while (is_label_char(tmp->str[i + j]))
				j++;
		if (tmp->str[i + j] == LABEL_CHAR)
		{
//			printf("label was found at '%s'\n", tmp->str);
			label = add_label(label, new_label(tmp, pos, i));
			i = i + j + 1;
			while (tmp->str[i] == 32 || (tmp->str[i] >= 9 && tmp->str[i] <= 13))
				i++;
		}
		if (tmp->str[i] == '\0')
		{
			tmp = tmp->next;
			continue ;
		}
		if (tmp->op > 0)
			pos = add_instr(champ, pos, tmp, address);
		tmp = tmp->next;
//		printf("op = %d\n", tmp->op);
//		printf("pos = %d\n", pos);
	}
	print_labels(address);
	return (pos);
}

void	add_size(char *in, int size)
{
	in[PROG_NAME_LENGTH + 11] = (char)size;
}

t_list	*create(t_list *code, t_list *error, char *file)
{
	char	*champ;
	int		size;
	int 	pos;
	int 	fd;
	int		tmp;

	if (error)
		code = code->next;
	file = make_filename(file);
	pos = -1;
	size = CHAMP_MAX_SIZE + 1 + 4 + PROG_NAME_LENGTH + COMMENT_LENGTH;
	champ = (char*)malloc(size);
	while (++pos < size)
		champ[pos] = 0;
	pos = init_header(champ);
	pos = init_name(champ, pos, code);
	printf("POSITION = %d\n", pos);
	pos = init_comment(champ, pos, code);
	tmp = pos;
	pos = first_trace(champ, pos, code);
	printf("pos = '%d'\n", pos);
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	printf("writing to file %s\n", file);
	add_size(champ, pos - tmp);
	write (fd, champ, pos);
	return (error);
}