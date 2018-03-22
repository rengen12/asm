/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbuy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 13:20:23 by dbuy              #+#    #+#             */
/*   Updated: 2018/03/14 13:20:25 by dbuy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"

int		print_usage(void)
{
	char *a;
	char *b;
	char *d;
	char *c;

	a = "Usage: ./asm [-a] | [-h] | [-l] <sourcefile.s>\n-a: Instead of";
	b = " creating binary displays step-by-step coding process\n";
	c = "-h: help, no output binary file, flag [-a] ignored\n";
	d = "-l: leaks\n";
	write(1, a, ft_strlen(a));
	write(1, b, ft_strlen(b));
	write(1, c, ft_strlen(c));
	write(1, d, ft_strlen(d));
	return (0);
}

int		print_error(char *error, int display)
{
	write(1, error, ft_strlen(error));
	write(1, "\n", 1);
	if ((display & 2) == 2)
		system("leaks asm");
	return (1);
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

int		find_s(char *in)
{
	int	i;

	i = 0;
	while (in[i++] != '\0')
	{
		if (in[i] == '.' && in[i + 1] == 's')
			if (in[i + 2] == '\0')
				return (1);
	}
	return (0);
}

int		find_comment(char *in)
{
	int i;

	i = 0;
	while (in[i] != '\0')
	{
		if (in[i] != COMMENT_CHAR)
			return (0);
		if (in[i] == COMMENT_CHAR)
			return (1);
		i++;
	}
	return (0);
}

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
	if (in[i] == '"')
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

char	*copy_index(char *ret, char *in, int i, int numeric)
{
	int j;

	j = -1;
	if (numeric == 0)
		while (in[++j + i] != '\0')
			ret[j] = in[j + i];
	else
		while (in[++j + i] != '\0' && (in[i] == 32 || (in[i] >= 9 && \
		in[i] <= 13) || (in[i] >= '0' && in[i] <= '9')\
		|| in[i] == '+' || in[i] == '-'))
			ret[j] = in[j + i];
	ret[j] = '\0';
	return (ret);
}

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

int		is_only_spaces(char *in)
{
	int i;

	i = 0;
	while (in[i] == 32 || (in[i] >= 9 && in[i] <= 13))
		i++;
	if (in[i] == '\0')
		return (1);
	return (0);
}

int		is_substr(char *a, char *b)
{
	int i;

	i = 0;
	while (a[i] != 0 && b[i] != 0 && a[i] == b[i])
		i++;
	if (b[i] == '\0')
		return (1);
	return (0);
}

int		find_op2(char *in)
{
	if (is_substr(in, "add") == 1)
		return (4);
	else if (is_substr(in, "aff") == 1)
		return (16);
	else if (is_substr(in, "and") == 1)
		return (6);
	else if (is_substr(in, "xor") == 1)
		return (8);
	else if (is_substr(in, "or") == 1)
		return (7);
	else if (is_substr(in, "zjmp") == 1)
		return (9);
	else if (is_substr(in, "fork") == 1)
		return (12);
	else if (is_only_spaces(in) == 1)
		return (0);
	return (-1);
}

int		find_op(char *in)
{
	if (is_substr(in, "lldi") == 1)
		return (14);
	if (is_substr(in, "ldi") == 1)
		return (10);
	else if (is_substr(in, "lld") == 1)
		return (13);
	else if (is_substr(in, "ld") == 1)
		return (2);
	else if (is_substr(in, "lfork") == 1)
		return (15);
	else if (is_substr(in, "live") == 1)
		return (1);
	else if (is_substr(in, "sti") == 1)
		return (11);
	else if (is_substr(in, "st") == 1)
		return (3);
	else if (is_substr(in, "sub") == 1)
		return (5);
	else
		return (find_op2(in));
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

char	*valid(char *file, char *error, int display)
{
	int		fd;
	t_list	*src;
	char	*line;

	src = NULL;
	line = NULL;
	if (find_s(file) == 0)
		return (strconcat("Wrong file type ", file));
	if ((fd = open(file, O_RDONLY)) < 0)
		return (strconcat("Can't read source file ", file));
	while (get_next_line(fd, &line) > 0)
	{
		src = listadd(src, listn(line));
		free(line);
	}
	free(line);
	src = lstrev(src);
	src = trim_comment(src);
	src = trim_white(src);
	if ((error = test_code(src, error)) != NULL)
		return (error);
	if ((error = create(src, file, display)) != NULL)
		clear_src(src);
	return (error == NULL ? clear_src(src) : error);
}

int		find_flag(int ac, char **av)
{
	int ret;
	int max;

	max = 255;
	ret = 0;
	ac--;
	while (ac > 0)
	{
		if (ft_strcmp(av[ac], "-h") == 0)
			ret = ret | (max & 1);
		else if (ft_strcmp(av[ac], "-l") == 0)
			ret = ret | (max & 2);
		else if (ft_strcmp(av[ac], "-a") == 0)
			ret = ret | (max & 4);
		else
		{
			if ((ret & 8) == 8)
				ret = ret | (max & 16);
			ret = ret | (max & 8);
			ret = ret | (ac << 5);
		}
		ac--;
	}
	return (ret);
}

int		print_man(int display)
{
	int		fd;
	char	*er;
	char	*man;

	man = NULL;
	er = "MAN file <asm.man> is missing\n";
	fd = open("asm.man", O_RDONLY);
	if (fd < 0)
	{
		write(1, er, ft_strlen(er));
		return (-1);
	}
	while (get_next_line(fd, &man))
	{
		write(1, man, ft_strlen(man));
		write(1, "\n", 1);
		free(man);
	}
	free(man);
	if ((display & 2) == 2)
		system("leaks asm");
	return (0);
}

int		invalid_flags(int display)
{
	char	*er;

	er = "Invalid arguments, run \"./asm\" for more information\n";
	write(1, er, ft_strlen(er));
	if ((display & 2) == 2)
		system("leaks asm");
	return (-1);
}

int		no_file(int display)
{
	char	*er;

	er = "Cant find file among arguments\n";
	write(1, er, ft_strlen(er));
	if ((display & 2) == 2)
		system("leaks asm");
	return (-1);
}

char	*find_file(char **av, int flag)
{
	int i;

	i = flag >> 5;
	return (av[i]);
}

int		main(int ac, char **av)
{
	int		display;
	char	*file;
	char	*error;

	error = NULL;
	if (ac == 1 || ac > 5)
		return (print_usage());
	display = find_flag(ac, av);
	if ((display & 1) == 1)
		return (print_man(display));
	if ((display & 8) != 8)
		return (no_file(display));
	if ((display & 16) == 16)
		return (invalid_flags(display));
	if ((error = test_header(error)) != NULL)
		return (print_error(error, display));
	file = find_file(av, display);
	if ((error = valid(file, error, display)) != NULL)
		return (print_error(error, display));
	if ((display & 2) == 2)
		system("leaks asm");
	return (0);
}
