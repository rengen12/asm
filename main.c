
#include "op.h"
#include "asm.h"

int 	print_usage(void)
{
	char *a;

	a = "Usage: ./asm <sourcefile.s>";
	write(1, a, ft_strlen(a));
	write(1, "\n", 1);
	return (0);
}

int 	print_error(t_list *error)
{
	t_list	*tmp;

	tmp = error;
	while (tmp)
	{
		write(1, tmp->str, ft_strlen(tmp->str) + 1);
		write(1, "\n", 1);
		tmp =tmp->next;
	}
	return (1);
}

int 	find_s(char *in)
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

int 	find_comment(char *in)
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

int 	ft_findstr(char *in, t_list *code)
{
	int 	ret;
	t_list	*tmp;

	tmp = code;
	ret = 1;
	while (tmp)
	{
		if (ft_strcmp(in, tmp->str) == 0)
			break;
		tmp = tmp->next;
		ret++;
	}
	return (ret);
}

t_list	*test_first(char *in, t_list *code, t_list *error, char *name) // NAME_CMD_STRING
{
	int		i;
	int 	j;

	j = 0;
	i = -1;
	while (in[++i] != '\0')
		if (in[i] != ' ' && (in[i] < 9 || in[i] > 13))
			break ;
	if (in[i] != name[0])
		return (error = listadd(error, listn(strjoin(ft_itoa(ft_findstr(in, code)), ft_itoa(i)))));
	while (in[i] != '\0' && name[j] != '\0')
		if (in[i++] != name[j++])
			error = listadd(error, listn(strjoin(ft_itoa(ft_findstr(in, code)), ft_itoa(i - 1))));
	if (in[i] == '\0' || name[j] != '\0')
			error = listadd(error, listn(strjoin(ft_itoa(ft_findstr(in, code)), ft_itoa(i))));
	while (in[i] != '"' && in[i] != '\0')
	{
		if (in[i] != '"' && in[i] != ' ' && (in[i] < 9 || in[i] > 13))
			return (error = listadd(error, listn(strjoin(ft_itoa(ft_findstr(in, code)), ft_itoa(i)))));
		i++;
	}
	if (in[i] != '"')
		error = listadd(error, listn(strjoin(ft_itoa(ft_findstr(in, code)), ft_itoa(i))));
	i++;
	while (in[i] != '"' && in[i] != '\0')
		i++;
	if (in[i] != '"')
		error = listadd(error, listn(strjoin(ft_itoa(ft_findstr(in, code)), ft_itoa(i))));
	i++;
	while (in[i] != '\0')
	{
		if (in[i] != ' ' || (in[i] < 9 || in[i] > 13) || in[i] != '\0')
			return (error = listadd(error, listn(strjoin(ft_itoa(ft_findstr(in, code)), ft_itoa(i)))));
		i++;
	}
	if (ft_strcmp(name, NAME_CMD_STRING) == 0 && i > PROG_NAME_LENGTH + 5)
		return (error = listadd(error, listn("Too long name")));
	if (ft_strcmp(name, COMMENT_CMD_STRING) == 0 && i > COMMENT_LENGTH + 8)
		return (error = listadd(error, listn("Too long name")));
	return (error);
}

char 	*copy_index(char *ret, char *in, int i, int numeric)
{
	int j;

	j = -1;
//	printf("\t\t>>>>>>>>>>>COPY_INDEX = '%s', i = %d, num = %d\n", in, i, numeric);

//	while (in[i] == 32 || (in[i] >= 9 && in[i] <=13) || in[i] == '\t')
//		i++;
	if (numeric == 0)
		while (in[++j + i] != '\0')
			ret[j] = in[j + i];
	else
		while (in[++j + i] != '\0' && (in[i] == 32 || (in[i] >= 9 && in[i] <= 13) || (in[i] >= '0' && in[i] <= '9') || in[i] == '+' || in[i] == '-' || in[i] == '*' || in[i] == '/'))
			ret[j] = in[j + i];
	ret[j] = '\0';
//	printf("\t\tCOPY_INDEX = '%s'\n", ret);
	return (ret);
}

char	*trim_label(char *in)
{
	int		i;
	int		block;
	char	*ret;

//	printf("search for trim\n");
	ret = (char*)malloc(ft_strlen(in) + 1);
	i = 0;
	block = 0;
	while (in[i] != '\0')
	{
		if (in[i] == 32 || (in[i] >= 9 && in[i] <=13))
		{
			i++;
			if (block == 1)
				return (ft_memcpy(ret, in, ft_strlen(in) + 1));
			continue;
		}
		else if (in[i] == ':')
		{
//			printf(": was found!\n");
//			printf("block = %d\n", block);
			if (block == 1)
				return (copy_index(ret, in, i + 1, 0));
		}
		else
		{
//			printf("BLOCK = 1, char = '%c'\n", in[i]);
			block = 1;
		}

		i++;
	}
	return (ft_memcpy(ret, in, ft_strlen(in) + 1));
}

int 	is_label(char *in)
{
	int 	i;

	i = 0;
	while (in[i] != '\0' && (in[i] == 32 || (in[i] >= 9 && in[i] <= 13)))
		i++;
	while (in[i] != '\0' && in[i] != ':' && in[i] != 32 && (in[i] < 9 || in[i] > 13))
		i++;
	if (in[i] == ':')
		return (1);
	return (0);

}

int 	is_only_spaces(char *in)
{
	int i;

	i = 0;
	while (in[i] == 32 || (in[i] >=9 && in[i] <= 13))
		i++;
	if (in[i] == '\0')
		return (1);
	return (0);
}

int 	find_op(char *in)
{
	if (in[0] == 'l')
	{
		if (in[1] == 'd')
		{
			if (in[2] == 'i')
				return (10);
			else
				return (2);
		}
		else if (in[1] == 'l')
		{
			if (in[2] == 'd')
			{
				if (in[3] == 'i')
					return (14);
				else
					return (13);
			}
		}
		else if (in[1] == 'f')
		{
			if (in[2] == 'o')
				if (in[3] == 'r')
					if (in[4] == 'k')
						return (15);
		}
		else if (in[1] == 'i')
			if (in[2] == 'v')
				if (in[3] == 'e')
					return (1);
	}
	else if (in[0] == 's')
	{
		if (in[1] == 't')
		{
			if (in[2] == 'i')
				return (11);
			else
				return (3);
		}
		else if (in[1] == 'u')
			if (in[2] == 'b')
				return (5);
	}
	else if (in[0] == 'a')
	{
		if (in[1] == 'd')
		{
			if (in[2] == 'd')
				return (4);
		}
		else if (in[1] == 'f')
		{
			if (in[2] == 'f')
				return (16);
		}
		else if (in[1] == 'n')
			if (in[2] == 'd')
				return (6);
	}
	else if (in[0] == 'o')
	{
		if (in[1] == 'r')
			return (7);
	}
	else if (in[0] == 'x')
	{
		if (in[1] == 'o')
			if (in[2] == 'r')
				return (8);
	}
	else if (in[0] == 'z')
	{
		if (in[1] == 'j')
			if (in[2] == 'm')
				if (in[3] == 'p')
					return (9);
	}
	else if (in[0] == 'f')
	{
		if (in[1] == 'o')
			if (in[2] == 'r')
				if (in[3] == 'k')
					return (12);
	}
//	printf("\t\t>>>>char = '%c'\n", in[0]);
	if (is_only_spaces(in) == 1)
		return (0);
	return (-1);
}

char	*trim_space(char *in)
{
	char	*ret;
	int 	i;

	int 	j;

	i = 0;
	j = 0;
	ret = (char*)malloc(ft_strlen(in) + 1);
	while (in[i] != '\0' && (in[i] == 32 || (in[i] >= 9 && in[i] <=13)))
		i++;
	while (in[i] != '\0')
		ret[j++] = in[i++];
	ret[j] = '\0';
	free(in);
	in = NULL;
	return (ret);
}

t_list	*test_str(char *str, t_list *code, int num, t_list *tmp)
{
	int op;
	char *tr;
	t_list	*error;

	error = NULL;
//	printf("NUM = %d, STR = '%s'\n", num, str);
//	printf("str at start = \t%s\n", str);
	tr = trim_label(str);
	tr = trim_space(tr);
//	printf("tr = %s\n", tr);
//	printf("STR at start = %s\n", tr);
	op = find_op(tr);
//	printf("op = %d\n", op);
	if (op < 0)
	{
//		printf("INVALID_COMMAND tr = '%s'; str = '%s'\n", tr, str);
		error = listadd(error, listn(strconcat("Invalid comand ", str)));
	}
	if (op == 1)
	{
//		printf(">>>>>>>>>>STR = '%s\'\n", tr);
		error = test_live("live", tr, error, num);
	}
	else if (op == 2)
		error = test_ld("ld", tr, error, num);
	else if (op == 13)
		error = test_ld("lld", tr, error, num);
	else if (op == 3)
		error = test_st(tr, error, num, code);
	else if (op == 4)
		error = test_add("add" ,tr, error, num);
	else if (op == 5)
		error = test_add("sub" ,tr, error, num);
	else if (op == 6)
		error = test_and("and" ,tr, error, num);
	else if (op == 7)
		error = test_and("or" ,tr, error, num);
	else if (op == 8)
		error = test_and("xor" ,tr, error, num);
	else if (op == 9)
		error = test_fork("zjmp" ,tr, num, code);
	else if (op == 12)
		error = test_fork("fork" ,tr, num, code);
	else if (op == 15)
		error = test_fork("lfork" ,tr, num, code);
	else if (op == 10)
		error = test_ldi("ldi" ,tr, num, code);
	else if (op == 14)
		error = test_ldi("lldi" ,tr, num, code);
	else if (op == 11)
		error = test_sti("sti" ,tr, num, code);
	else if (op == 16)
		error = test_aff("aff" ,tr, num);
	tmp->op = op;
	return (error);
}

t_list	*test_code(t_list *code, t_list *error)
{
	t_list *tmp;
	int 	i;
	int 	num;

	tmp = code;
	i = 0;
	num = 1;
	while (tmp)
	{
		if (find_comment(tmp->str) == 1 || ft_strlen(tmp->str) == 0 || is_only_spaces(tmp->str))
		{
			tmp = tmp->next;
			num++;
			continue ;
		}
		if (i == 0)
			error = test_first(tmp->str, code, error, NAME_CMD_STRING);
		else if (i == 1)
			error = test_first(tmp->str, code, error, COMMENT_CMD_STRING);
		else
			error = test_str(tmp->str, code, num, tmp);
		if (error)
			return (error);
		tmp = tmp->next;
		num++;
		i++;
	}
	return (error);
}

int 	is_splitted(t_list *in)
{
	int i;
	int count;
//	int flag;
//	int count2;

	i = -1;
	count = 0;
//	count2 = 0;
//	flag = 0;
	while (in->str[++i] != '\0')
		if (in->str[i] == '"')
			count++;
//		else if (in->str[i] == ':')
//		{
//			flag = 1;
//			while (in->str[++i] != '\0')
//				if (in->str[i] != 32 && (in->str[i] > 13 || in->str[i] < 9))
//					count2++;
//		}
	if (count == 1)
//		|| (flag == 1 && count2 == 0))
		return (1);
	return (0);
}

void	concat(t_list *in)
{
	t_list *tmp;

	tmp = (in->next != NULL ? in->next : NULL);
	if (tmp)
		while (ft_strlen(tmp->str) == 0)
		{
			if (tmp->next)
				tmp = tmp->next;
			else
				return ;
		}
//	printf("%p\n", tmp);
	if (tmp)
	{
		in->str = strconcat(in->str, tmp->str);
		tmp->str[0] = '\0';
	}
}

t_list 	*src_join(t_list *src)
{
	t_list *tmp;
	int 	i;

	i = 0;
	tmp = src;
	while (tmp)
	{
		while (((tmp->str[i] >= 9 && tmp->str[i] <= 13) || tmp->str[i] == 32) && tmp->str != '\0')
			i++;
		if (tmp->str[i] == COMMENT_CHAR)
		{
			tmp = tmp->next;
			continue ;
		}
		while (is_splitted(tmp) == 1)
		{
//			printf("test\n");
//			printf("%s\n", tmp->str);
			concat(tmp);
		}
		tmp = tmp->next;
	}
	return (src);
}

t_list	*valid(char *file, t_list *error)
{
	int		fd;
	t_list	*src;
	char 	*line;

	src = NULL;
	if (find_s(file) == 0)
	{
		error = listadd(error, listn(strconcat("Wrong file type ", file)));
		return (error);
	}
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		error = listadd(error, listn(strconcat("Can't read source file ", file)));
		return (error);
	}
	while (get_next_line(fd, &line) > 0)
		src = listadd(src, listn(line));
	src = lstrev(src);
	src = src_join(src);
	print_error(src);
	if ((error = test_code(src, error)) != NULL)
		return (error);
	if ((error = create(src, error, file)) != NULL)
		return (error);
	return (NULL);
}


int		main(int ac, char **av)
{
	t_list *error;

	error = NULL;
	if (ac == 1 || ac > 2)
		return (print_usage());
	if ((error = valid(av[1], error)) != NULL)
		return (print_error(error));
	return 0;
}