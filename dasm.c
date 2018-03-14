/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dasm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbuy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 17:27:05 by dbuy              #+#    #+#             */
/*   Updated: 2018/03/14 17:27:06 by dbuy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"

char	*ft_strcpy(char *out, char *in)
{
	int	i;

	i = 0;
	while (in[i++] != '\0')
		out[i - 1] = in[i - 1];
	out[i - 1] = '\0';
	return (out);
}

int		usage(void)
{
	char *a;
	char *b;
	char *c;
	char *d;
	char *e;

	a = "./dasm [-l], [-m], [f], [o] <champion.cor> [output file]\n";
	b = "[-l]: leaks\n";
	c = "[-m]: display labels\n";
	d = "[-f]: write output to file *.s or user-defined file\n";
	e = "[-o]: display offset with reference to binary\n";
	write(1, a, ft_strlen(a));
	write(1, b, ft_strlen(b));
	write(1, c, ft_strlen(c));
	write(1, d, ft_strlen(d));
	write(1, e, ft_strlen(e));
	return (1);
}

int		no_file(char *file, int flag)
{
	char *a;

	a = "Cant read file: ";
	write(1, a, ft_strlen(a));
	write(1, file, ft_strlen(file));
	write(1, "\n", 1);
	if ((flag & 2) == 2)
		system("leaks dasm");
	return (1);
}

int		cant_find_file(int flag)
{
	char *a;

	a = "NULL FILE GIVEN\n";
	write(1, a, ft_strlen(a));
	if ((flag & 2) == 2)
		system("leaks dasm");
	return (1);
}

int		wrong_file_name(char *file, int flag)
{
	char *a;

	a = "Wrong file name: ";
	write(1, a, ft_strlen(a));
	write(1, file, ft_strlen(file));
	write(1, "\n", 1);
	if ((flag & 2) == 2)
		system("leaks dasm");
	return (1);
}

char	*find_cor(char *file, int flag, char **av)
{
	int		i;
	char	*ret;

	i = (int)ft_strlen(file);
	if (i < 4)
		return (NULL);
	if (file[i - 1] == 'r' && file[i - 2] == 'o' && file[i - 3] == 'c' &&\
															file[i - 4] == '.')
	{
		if ((flag >> 10) > 0)
		{
			ret = (char*)malloc(ft_strlen(av[flag >> 10]) + 1);
			ret = ft_strcpy(ret, av[flag >> 10]);
			printf("new file = %s\n", ret);
			return (ret);
		}
		ret = (char*)malloc(i);
		i = -1;
		while (file[++i] != '\0')
			ret[i] = file[i];
		ret[i - 3] = 's';
		ret[i - 2] = '\0';
		return (ret);
	}
	return (NULL);
}

char	*get_name(char *file, int flag, char **av)
{
	char *ret;

	if ((ret = find_cor(file, flag, av)) == NULL)
		return (NULL);
	return (ret);
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

int		num_args(unsigned int acb)
{
	int ret;

	ret = 0;
	if (acb == 0)
		return (1);
	if ((acb >> 6) > 0)
		ret++;
	if (((acb << 26) >> 30) > 0)
		ret++;
	if (((acb << 28) >> 30) > 0)
		ret++;
	return (ret);
}

unsigned int	get_type(unsigned char acb, int flag)
{
	static int r;

	r++;
	if (flag == 0)
		r = 0;
	if (acb == 0)
		return (2);
	if (r == 1)
		return (acb >> 6);
	else if (r == 2)
		return ((acb & 48) >> 4);
	else if (r == 3)
		return ((acb << 28) >> 30);
	return (0);
}

int		is_label_char(char c)
{
	char	*test;
	int		i;

	i = 0;
	test = LABEL_CHARS;
	while (test[i] != '\0')
	{
		if (test[i] == c)
			return (1);
		i++;
	}
	return (0);
}

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

void	add_arg2(t_list *out, char *in, int *i, int type)
{
	int		j;
	char	*value;

	j = 0;
	if (type == 1)
	{
		out->str[out->num++] = 'r';
		value = ft_itoa(in[*i]);
		while (value[j] != '\0')
			out->str[out->num++] = value[j++];
		free(value);
		*i = *i + 1;
	}
	else if (type == 3)
	{
		value = ft_itoa(in[*i] * 256 + in[*i + 1]);
		while (value[j] != '\0')
			out->str[out->num++] = value[j++];
		*i = *i + 2;
		free(value);
	}
}

void	add_arg3(t_list *out, char *in, int *i, int op)
{
	char			*value;
	unsigned int	val;

	out->str[out->num++] = DIRECT_CHAR;
	if ((op >= 9 && op <= 12) || op == 15 || op == 16)
	{
		val = (unsigned int)((unsigned char)in[*i] * 256 + \
													(unsigned char)in[*i + 1]);
		val = ((short)val < 0 ? (short)val : val);
	}
	else
	{
		val = (unsigned int)(((unsigned char)in[*i]) * 256 * 256 * 256);
		val = val + (unsigned int)(((unsigned char)in[*i + 1]) * 256 * 256);
		val = val + (unsigned int)(((unsigned char)in[*i + 2]) * 256);
		val = val + (unsigned int)(in[*i + 3]);
		val = ((int)val < -256 ? val + 256 : val);
		*i = *i + 2;
	}
	*i = *i + 2;
	value = ft_itoa(val);
	val = 0;
	while (value[val] != '\0')
		out->str[out->num++] = value[val++];
	free(value);
}

int		add_arg(t_list *out, char *in, int *i, int op)
{
	unsigned char		acb;
	int					num;
	int					type;

	acb = (in[*i - 1] == 1 || in[*i - 1] == 9 || in[*i - 1] == 12 || in[*i - 1]\
						== 15 ? (unsigned char)0 : (unsigned char)(in[(*i)++]));
	num = num_args(acb);
	out->str[out->num++] = ' ';
	while (num-- > 0)
	{
		type = get_type(acb, 1);
		if (type == 1 || type == 3)
			add_arg2(out, in, i, type);
		else if (type == 2)
			add_arg3(out, in, i, op);
		out->str[out->num++] = SEPARATOR_CHAR;
	}
	out->str[out->num - 1] = '\n';
	get_type(acb, 0);
	return (out->num);
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

t_list	*add_all(t_list *out, char *in, int max, int pos)
{
	int i;
	int flag;

	flag = out->i;
	i = PROG_NAME_LENGTH + 16 + COMMENT_LENGTH;
	while (i < max)
		out = add_command(out, in, &i, pos);
	out = lstrev(out);
	if ((flag & 1) == 1)
		make_link(out, 0, 0);
	return (out);
}

void	print_list(t_list *code, int flag)
{
	t_list	*tmp;

	tmp = code;
	while (tmp)
	{
		if ((flag & 8) == 8)
			printf("%d:\t", tmp->start);
		printf("%s", tmp->str);
		tmp = tmp->next;
	}
}

void	clear_list(t_list *in)
{
	t_list *tmp;
	t_list *buff;

	tmp = in;
	while (tmp)
	{
		buff = tmp;
		free(tmp->str);
		tmp = tmp->next;
		free(buff);
	}
}

void	decompile2(char *file, t_list *out, int flag)
{
	int		fd;
	t_list	*tmp;
	char	*start;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR\
														| S_IRGRP | S_IROTH);
	tmp = out;
	write(1, "writing sourse code to file: ", 29);
	write(1, file, ft_strlen(file));
	write(1, "\n", 1);
	while (tmp)
	{
		if ((flag & 8) == 8)
		{
			start = ft_itoa(tmp->start);
			write(fd, start, ft_strlen(start));
			free(start);
			write(fd, ":\t", 2);
		}
		write(fd, tmp->str, ft_strlen(tmp->str));
		tmp = tmp->next;
	}
}

void	decompile(char *in, int max, char *file, int flag)
{
	t_list	*out;
	int		pos;

	pos = 0;
	out = NULL;
	out = add_name(out, in, max, pos);
	out = add_comment(out, in, max, pos);
	out->i = flag;
	out = add_all(out, in, max, pos);
	if ((flag & 4) != 4)
		print_list(out, flag);
	else
		decompile2(file, out, flag);
	clear_list(out);
}

int		invalid_file(void)
{
	char *er;

	er = "Invalid file\n";
	write(1, er, ft_strlen(er));
	return (1);
}

int		find_flag_dasm2(char **av, int i, int ret, int *block)
{
	if (ft_strcmp(av[i], "-l") == 0)
		ret = ret | (2);
	else if (ft_strcmp(av[i], "-f") == 0)
	{
		*block = 1;
		ret = ret | (4);
	}
	else if (ft_strcmp(av[i], "-o") == 0)
		ret = ret | (8);
	else if (ft_strcmp(av[i], "-m") == 0)
		ret = ret | (1);
	else
	{
		if (*block == 1)
			ret = ret | (i << 10);
		if ((ret & 32) == 32)
			ret = ret | (64);
		if ((ret & 16) == 16 && *block == 0)
			ret = ret | (32);
		ret = ret | (16);
		if (*block == 0)
			ret = ret | (i << 7);
	}
	return (ret);
}

int		find_flag_dasm(int ac, char **av)
{
	int ret;
	int i;
	int block;

	ret = 0;
	block = 0;
	i = 0;
	while (++i < ac)
		ret = find_flag_dasm2(av, i, ret, &block);
	return (ret);
}

int		main(int ac, char **av)
{
	int		fd;
	ssize_t	pos;
	int		flag;
	char	*file;
	char	*in;

	flag = find_flag_dasm(ac, av);
	if (ac == 1 || ac > 7)
		return (usage());
	file = av[(flag & 896) >> 7];
	if ((flag & 16) != 16)
		return (cant_find_file(flag));
	if (((fd = open(file, O_RDONLY)) < 3))
		return (no_file(file, flag));
	if (!(file = get_name(file, flag, av)))
		return (wrong_file_name(av[1], flag));
	in = (char *)malloc(10000);
	pos = read(fd, in, 10000);
	if (pos < COMMENT_LENGTH + PROG_NAME_LENGTH + 10 || pos == 10000)
		return (invalid_file());
	decompile(in, (int)pos - 1, file, flag);
	if ((flag & 2) == 2)
		system("leaks dasm");
	return (0);
}
