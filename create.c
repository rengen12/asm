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
//	printf(">>>>>>>>>>>>>%s\n", file);
//	printf("len = %d\n", len);
	i = -1;
	ret = (char*)malloc(ft_strlen(file) + 3);
	while (++i < len - 2)
		ret[i] = file[i];
	ret[i] = '.';
	ret[++i] = 'c';
	ret[++i] = 'o';
	ret[++i] = 'r';
	ret[++i] = '\0';
//	printf(">>>>>>>>>>>>>%s\n", ret);
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
		acb = 64;
	else if (in[i] == DIRECT_CHAR)
		acb = 128;
	else
		acb = 192;
	while (in[i] != SEPARATOR_CHAR && in[i]!= '\0' && in[i] != COMMENT_CHAR)
		i++;
	if (in[i] == COMMENT_CHAR)
		return (acb);
	if (in[i] == SEPARATOR_CHAR)
		i++;
	while (in[i] == 32 || (in[i] >= 9 && in[i] <= 13))
		i++;
//	printf("acb = %d, next char = '%c', i = %d\n", acb, in[i], i);
	if (in[i] != '\0')
	{
		if (in[i] == 'r')
			acb = acb + 16;
		else if (in[i] == DIRECT_CHAR)
			acb = acb + 32;
		else
			acb = acb + 48;
		while (in[i] != SEPARATOR_CHAR && in[i]!= '\0' && in[i] != COMMENT_CHAR)
			i++;
	}
	if (in[i] == COMMENT_CHAR)
		return (acb);
	if (in[i] == SEPARATOR_CHAR)
		i++;
	while (in[i] == 32 || (in[i] >= 9 && in[i] <= 13))
		i++;
//	printf("acb = %d, next char = '%c', i = %d\n", acb, in[i], i);
	if (in[i] != '\0')
	{
		if (in[i] == 'r')
			acb = acb + 4;
		else if (in[i] == DIRECT_CHAR)
			acb = acb + 8;
		else
			acb = acb + 12;
		while (in[i] != SEPARATOR_CHAR && in[i]!= '\0' && in[i] != COMMENT_CHAR)
			i++;
	}
//	printf("final acb = %d\n", acb);
	return (acb);
}

t_lab	*save_address(int pos, char *str, t_lab *address, int indir, int start)
{
	t_lab	*new;
	char	*label;
	int		i;

//	printf("saving address '%s'\n", str);
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
	new->start = start;
	new->indir = (indir == 1 ? 1 : 0);
//	printf("saved address = '%s'\n", str);
	return (new);
}

int 	set_math(t_list *tmp, int i)
{
	int sign;
	int val;

//	printf("STR = %s\n", tmp->str + i);
	i = skip_spaces(tmp->str, i);
	if (tmp->str[i] == '-')
		sign = -1;
	else if (tmp->str[i] == '+')
		sign = 1;
	else
		return (0);
//	printf("sign = %d\n", sign);
	if (tmp->str[i] == '-' || tmp->str[i] == '+')
		i++;
	i = skip_spaces(tmp->str, i);
	val = sign * ft_atoi(tmp->str + i);
//	printf("RETURNING = %d\n", val);
	return (val);
}

int 	add_args(char *in, int pos, t_list *tmp, t_lab **address)
{
	int 	i;
	int 	j;
	int 	n;
	int 	arg;

	i = 0;
	j = 0;
	n = 0;
//	printf(">>>>>>>>>>>>>>>>> '%s', pos = %d\n", c , pos);
	i = skip_spaces(tmp->str, i);
	j = skip_labelchar(tmp->str, i) - i;
	if (tmp->str[i + j] == LABEL_CHAR)
		i = i + j + 1;
	i = skip_spaces(tmp->str, i);
	while (tmp->str[i] != 32 && (tmp->str[i] < 9 || tmp->str[i] > 13) && tmp->str[i] != '\0')
		i++;
//	printf("Making args\n");
	while (n++ < 3 && tmp->str[i] != '\0' && tmp->str[i] != COMMENT_CHAR)
	{
		if (tmp->str[i] == SEPARATOR_CHAR)
			i++;
		i = skip_spaces(tmp->str, i);
		if (tmp->str[i] == 'r')
		{
			in[pos++] = (char)ft_atoi(tmp->str + i++ + 1);
			i = skip_numeric(tmp->str, i);
		}
		else if (tmp->str[i] == DIRECT_CHAR)
		{
			if (tmp->str[i + 1] == LABEL_CHAR)
			{
				*address = save_address(pos, tmp->str + i + 2, *address, 0, tmp->start);
				if ((tmp->op >= 9 && tmp->op <=12) || tmp->op == 14 || tmp->op == 15)
					pos = pos + 2;
				else
					pos = pos + 4;
				i = i + 2;
				while (is_label_char(tmp->str[i]))
					i++;
				i = skip_spaces(tmp->str, i);
//				printf("str = %s\n", tmp->str + i);
				(*address)->math = set_math(tmp, i);
//				printf("addr = %d\n", (*address)->math);
				i = skip_math(tmp->str, i);
			}
			else
			{
				arg = (int) ft_atoi(tmp->str + i + 1);
				if ((tmp->op >= 9 && tmp->op <=12) || tmp->op == 14 || tmp->op == 15)
				{
					in[pos++] = (arg << 16) >> 24;
					in[pos++] = (arg << 24) >> 24;
				}
				else
				{
					in[pos++] = arg >> 24;
					in[pos++] = (arg << 8) >> 24;
					in[pos++] = (arg << 16) >> 24;
					in[pos++] = (arg << 24) >> 24;
				}
				i++;
				while (tmp->str[i] >= '0' && tmp->str[i] <= '9')
					i++;
			}
		}
		else
		{
			if (tmp->str[i] == LABEL_CHAR)
			{
				*address = save_address(pos, tmp->str + i + 1, *address, 1, tmp->start);
				pos++;
				pos++;
				i = i + 2;
				while (is_label_char(tmp->str[i]))
					i++;
				i = skip_spaces(tmp->str, i);
//				printf("str = %s\n", tmp->str + i);
				(*address)->math = set_math(tmp, i);
//				printf("addr2 = %d\n", (*address)->math);
				i = skip_math(tmp->str, i);
			}
			else
			{
				arg = (int)ft_atoi(tmp->str + i + 1);
				in[pos++] = arg >> 24;
				in[pos++] = (arg << 8) >> 24;
				in[pos++] = (arg << 16) >> 24;
				in[pos++] = (arg << 24) >> 24;
				while (tmp->str[i] >= '0' && tmp->str[i] <= '9')
					i++;
			}
		}
		while (tmp->str[i] != SEPARATOR_CHAR && tmp->str[i] != '\0' && tmp->str[i] != COMMENT_CHAR)
			i++;
	}
//	printf("Returning args\n");
//	printf(">>>>>>>>>>>>>>>>>  pos = %d\n", pos);
	return (pos);
}

char	*binary(int a)
{
	char *ret;
	char * hex;

	hex = "0123456789abcdef";
//	printf("\n>>>>acb = %d\n", a);
	ret = (char*)malloc(19);
	ret[0] = ((a >> 7 > 0) ? '1' : '0');
	ret[1] = ((a >> 6) % 2  > 0 ? '1' : '0');
	ret[2] = ' ';
//	printf("a >> 5 = %d\n", a >> 5);
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
//	printf("<<<<<ret = %s\n", ret);
	return (ret);
}

char	*hexa(unsigned char i)
{
	char *hex;
	char *ret;

//	printf("\n>>>>>>>>>>>>i = %u\n", i);
	ret = (char*)malloc(3);
	ret[2] = '\0';
	hex = "0123456789abcdef";
	ret[0] = hex[(i >> 4)];
	ret[1] = hex[i % 16];
//	printf("ret = %s<<<<<<<<<<<<<<\n", ret);
	return (ret);
}

int 	add_instr(char *champ, int pos, t_list *tmp, t_lab **address, int flag)
{
//	printf("flag = %d\n", flag);
//	printf("pos = %d\n", pos);
	int			tm;
	int			acb;
	int 		start;
	char		*t;

	start = pos;
	tmp->start = pos;
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
	tm = pos;
	pos = add_args(champ, pos, tmp, address);
	if (flag == 2)
	{
		write (1, "\n", 1);
		t = ft_itoa(start - COMMENT_LENGTH - PROG_NAME_LENGTH - 16);
		free(t);
		write (1, t, ft_strlen(t));
		write (1, " (", 2);
		t = ft_itoa(pos - start);
		write (1, t, ft_strlen(t));;
		free(t);
		write (1, ")\t", 2);
		write (1, tmp->str, ft_strlen(tmp->str));
//		printf("\n%d (%d)\t%s\n", start - 2192, pos - start,  tmp->str);
		write (1, "\n\t\tOP = ", 8);
		t = ft_itoa(tmp->op);
		write (1, t, ft_strlen(t));
		free(t);
//		printf("\t\tOP = %d\n", tmp->op);
		write (1, "\n\t\tacb = ", 9);
		if (tmp->op == 1 || tmp->op == 9 || tmp->op == 12 || tmp->op ==  15)
			t = "NULL";
		else
			t = binary(acb);
		write(1, t, ft_strlen(t));
		if (ft_strcmp(t, "NULL") != 0)
			free(t);
//		printf("%x\n", acb);
		write(1, "\n\t\targs = ", 10);
		while (tm++ != pos)
		{
			t = hexa(champ[tm - 1]);
			write(1, t, ft_strlen(t));
			free(t);
			write(1, " ", 1);
		}
//			printf("%x  ", champ[tm - 1]);
		write(1, "\n", 1);
	}
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
		printf("LABEL: '%s', pos = %d\n", tmp->lab, tmp->pos -2192);
		tmp = tmp->next;
	}
}

void	add_links(char *champ, t_lab *label, t_lab *address)
{
	t_lab	*tmp;
	t_lab	*search;
	int 	val;

	tmp = address;
	while (tmp)
	{
		search = label;
		while (search)
		{
			if (ft_strcmp(tmp->lab, search->lab) == 0)
			{
				val = search->pos - tmp->start + tmp->math;
//				printf("val = %d\n", val);
				champ[tmp->pos] = (char)((val << 16) >> 24);
				champ[tmp->pos + 1] = (char)((val << 24) >> 24);
			}
			search = search->next;
		}
		tmp = tmp->next;
	}
}

int 	test_label_repeat(t_lab *label, t_list **error)
{
	t_lab	*tmp;
	t_lab	*tmp2;

//	print_labels(label);
	tmp = label;
	while (tmp)
	{
		tmp2 = tmp->next;
		while (tmp2)
		{
			if (ft_strcmp(tmp->lab, tmp2->lab) == 0)
			{
				error[0] = listn(strconcat("ERROR: duplicated label: ", tmp->lab));
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

int		first_trace(char *champ, int pos, t_list *code, t_list **error)
{
	t_list	*tmp;
	t_lab	*label;
	t_lab	*address;
	int 	i;
	int 	j;
	static int flag;

//	printf("FLAG = %d\n", flag);
		flag++;
//	printf("FLAG = %d\n", flag);
	tmp = code;
	label = NULL;
	address = NULL;
	while ((tmp = tmp->next))
	{
//		printf(">>>>>>>pos = %d\n", pos - 2192);
		i = 0;
		i = skip_spaces(tmp->str, i);
		if (tmp->str[i] == COMMENT_CHAR || tmp->str[i] == '.' || tmp->str[i] == '\0')
			continue ;
		while (is_label_char(tmp->str[i]))
		{
			j = 0;
			while (is_label_char(tmp->str[i + j]))
				j++;
			if (tmp->str[i + j] == LABEL_CHAR)
			{
				label = add_label(label, new_label(tmp, pos, i));
				if (test_label_repeat(label, error) == 1)
					return (-1);
				i = i + j + 1;
				i = skip_spaces(tmp->str, i);
			}
			else
				break;
		}
		if (tmp->str[i] == '\0' || tmp->str[i] == COMMENT_CHAR)
			continue ;
		if (tmp->op > 0)
			pos = add_instr(champ, pos, tmp, &address, flag);
//		printf("op = %d\n", tmp->op);
//		printf("pos = %d\n", pos);
	}
//	print_labels(label);
//	printf("ADDRESS:\n");
//	print_labels(address);
	add_links(champ, label, address);
	clear_links(label, address);
	return (pos);
}

void	add_size(char *in, int size)
{
	in[PROG_NAME_LENGTH + 10] = (char)(size >> 8);
	in[PROG_NAME_LENGTH + 11] = (char)size;
}

t_list	*create(t_list *code, char *file, int display, t_list **error)
{
	char	*champ;
	int		size;
	int 	pos;
	int 	fd;
	int		tmp;

	fd = -2;
	file = make_filename(file);
	pos = -1;
	size = CHAMP_MAX_SIZE + 1 + 4 + PROG_NAME_LENGTH + COMMENT_LENGTH;
	champ = (char*)malloc(size);
	while (++pos < size)
		champ[pos] = 0;
	pos = init_header(champ);
	pos = init_name(champ, pos, code);

//	printf("POSITION = %d\n", pos);
	pos = init_comment(champ, pos, code);
	tmp = pos;

	pos = first_trace(champ, pos, code, error);
	if (error[0] != NULL)
		return (error[0]);
	if ((display & 4) == 4)
		pos = first_trace(champ, 2192, code, error); // FIX THIS!
	if ((display & 4) != 4)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if ((display & 4) != 4)
	printf("Writing binary to file %s\n", file);
//	printf("pos = '%d', display = %d, fd = %d\n", pos, display, fd);
	add_size(champ, pos - tmp);
	if ((display & 4) != 4 && fd > 0)
		write (fd, champ, pos);
	free(file);
	free(champ);
	return (NULL);
}