//
// Created by Denis BUY on 3/10/18.
//

#include "op.h"
#include "asm.h"


char 	*ft_strcpy(char *out, char *in)
{
	int 	i;

	i = 0;
	while (in[i++] != '\0')
		out[i - 1] = in[i - 1];
	out[i - 1] = '\0';
	return (out);
}

int 	usage(void)
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

int 	no_file(char *file, int flag)
{
	char *a;

	a = "Cant read file: ";
	write(1, a, ft_strlen(a));
	write(1, file, ft_strlen(file));
	write (1, "\n", 1);
	if ((flag & 2 ) == 2)
		system("leaks dasm");
	return (1);
}

int 	cant_find_file(int flag)
{
	char *a;

	a = "NULL FILE GIVEN\n";
	write(1, a, ft_strlen(a));
	if ((flag & 2 ) == 2)
		system("leaks dasm");
	return (1);
}

int 	wrong_file_name(char *file, int flag)
{
	char *a;

	a = "Wrong file name: ";
	write(1, a, ft_strlen(a));
	write(1, file, ft_strlen(file));
	write (1, "\n", 1);
	if ((flag & 2) == 2)
		system("leaks dasm");
	return (1);
}

char	*find_cor(char *file, int flag, char **av)
{
	int		i;
	char	*ret;

	i = 0;
	while (file[i] != '\0')
		i++;
	if (i < 4)
		return (NULL);
	if (file[i - 1] == 'r' && file[i - 2] == 'o' && file[i - 3] == 'c' && file[i - 4] == '.')
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

t_list 	*add_comment(t_list *out, char *in, int max, int pos)
{
	int		i;
	int 	j;
	char	*name;
	t_list	*new;

	new = (t_list*)malloc(sizeof(t_list));
	new->next = out;
	new->str = (char*)malloc(1000);
	name = ".comment";
	i = PROG_NAME_LENGTH + 12;
	j = 0;
	while(name[j] != '\0')
		new->str[pos++] = name[j++];
	new->str[pos++] = ' ';
	new->str[pos++] = '"';
	while (in[i] != '\0' && i <= max)
		new->str[pos++] = in[i++];
	new->str[pos++] = '"';
	new->str[pos++] = '\n';
	new->str[pos++] = '\n';
	return (new);
}

t_list 	*add_name(t_list *out, char *in, int max, int pos)
{
	int		i;
	int 	j;
	char 	*name;

	out = (t_list*)malloc(sizeof(t_list));
	out->next = NULL;
	out->str = (char*)malloc(1000);

	name = ".name";
	i = 4;
	j = 0;
	while(name[j] != '\0')
		out->str[pos++] = name[j++];
	out->str[pos++] = ' ';
	out->str[pos++] = '"';
	while (in[i] != '\0' && i <= max)
		out->str[pos++] = in[i++];
	out->str[pos++] = '"';
	out->str[pos++] = '\n';
	return (out);
}

t_list 	*add_op(char *com, t_list *out, int pos, int *j)
{
	int i;

	i = 0;
	while(com[i] != 0)
		out->str[pos++] = com[i++];
	out->start = j[0] - PROG_NAME_LENGTH - COMMENT_LENGTH - 16;
	out->num = pos;
	return (out);
}

int 	num_args(unsigned int acb)
{
	int ret;

	ret = 0;
//	printf("CALCULATING NUM, acb = %d\n", acb);
	if (acb == 0)
	{
//		printf("NUM = 1\n");
		return (1);
	}

	if ((acb >> 6) > 0)
		ret++;
	if (((acb << 26) >> 30) > 0)
		ret++;
	if (((acb << 28) >> 30) > 0)
		ret++;
//	printf("NUM = %d\n", ret);
	return (ret);
}

unsigned int 	get_type(unsigned char acb, int flag)
{
	static int r;
//	printf("Getting type, acb = %u\n", acb);

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

int 	is_label_char(char c)
{
	char	*test;
	int 	i;

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

char 	*find_lab(t_list *set)
{
	int i;
	int j;
	char *ret;

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


void	set_link(t_list *set, t_list *call)
{
	static int	i;
	char		*a;
	char 		*label;
	char 		*buff;
	char 		*tmp;


//	printf("CODE = %s\n", set->str);
//	printf("TMP = %s\n", call->str);
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
//		set->str = strconcat(strconcat(strconcat("\nlabel_", a), ":\t"), set->str);
	}
//	printf("code label = '%s'\n", tmp->str);
	set->num = set->num + 9 + ft_strlen(a);
	if (label == NULL)
	{
		buff = strconcat(call->str, ":label_");
		tmp = strconcat(buff, a);
		free(buff);
		buff = strconcat(tmp, "\n");
		free(tmp);
		call->str = ft_strcpy(call->str, buff);
		free(buff);
//		call->str = strconcat(strconcat(strconcat(call->str, ":label_"), a), "\n");
		call->num = call->num + 9 + ft_strlen(a);
		call->num++;
		call->str[call->num] = '\t';
		call->num++;

	}
	else
	{

		buff = strconcat(call->str, ":");
		tmp = strconcat(buff, label);
		free(buff);
		buff = strconcat(tmp, "\n");
		free(tmp);
		call->str = ft_strcpy(call->str, buff);
		free(buff);
//		call->str = strconcat(strconcat(strconcat(call->str, ":"), label), "\n");
		call->num = call->num + 2 + ft_strlen(label);
		call->num++;
		call->str[call->num] = '\t';
		call->num++;

	}
	free(a);
	free(label);
}

void 	make_link(t_list *code)
{
	t_list	*tmp;
	t_list	*tmp2;
	int 	i;
//	int 	st;
	int 	val;

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
//			printf("str = '%s', val = %d\n",tmp->str,  val);
			while (tmp2)
			{
				if (val == tmp2->start - tmp->start && val != 0)
				{
//					printf("found link with %s\n", tmp2->str);
					tmp->str[i + 1] = '\0';

					set_link(tmp2, tmp);
				}
				tmp2 = tmp2->next;
			}
		}
		tmp = tmp->next;
	}
}

int 	add_arg(t_list *out, char *in, int *i, int op)
{
	unsigned char		acb;
	int		j;
	int		num;
	int		type;
	char	*value;
	unsigned int 	val;
//	printf(">>>>>>>>>>>>>><<<<<<<<<<<<<\n");
//	printf("i = %d\n", *i);
//	printf("op = %d\n", op);

	if (in[*i - 1] == 1 || in[*i - 1] == 9 || in[*i - 1] == 12 || in[*i - 1] == 15)
		acb = 0;
	else
	{
		acb = (unsigned char)(in[*i]);
		*i = *i + 1;
	}
	num = num_args(acb);
	out->str[out->num++] = ' ';

//	printf("num = %d\n", num);
//	printf("acb = %d\n", acb);
	while (num-- > 0) // 106
	{
		j = 0;
		type = get_type (acb, 1);
//		printf("Type = %u\n", type);
		if (type == 1)
		{
			out->str[out->num++] = 'r';
			value = ft_itoa(in[*i]);
//			printf("in[*i] = %u\n", (unsigned char)in[*i]);
//			printf("value = %s\n", value);
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
		else if (type == 2)
		{
			out->str[out->num++] = DIRECT_CHAR;
			if ((op >= 9 && op <=12) || op == 15 || op == 16)
			{
//				printf("ADDR = 2\n");
//				printf("in[*i] = %u\n", (unsigned char)in[*i]);
//				printf("in[*i + 1] = %u\n", (unsigned char)in[*i + 1]);
				val = (unsigned int)((unsigned char)in[*i] * 256 + (unsigned char)in[*i + 1]);
//				printf("val = %hd\n", (short)val);
				if ((short)val < 0)
					val = (short)val;
				value = ft_itoa(val);
//				printf("value = %s\n", value);
				*i = *i + 2;
			}
			else
			{
//				printf("in[*i] = %u\n", (unsigned char)in[*i]);
//				printf("in[*i + 1] = %u\n", (unsigned char)in[*i + 1]);
//				printf("in[*i + 2] = %u\n", (unsigned char)in[*i + 2]);
//				printf("in[*i + 3] = %u\n", (unsigned char)in[*i + 3]);


				val = (unsigned int)(((unsigned char)in[*i]) * 256 * 256 * 256);
				val = val + (unsigned int)(((unsigned char)in[*i + 1]) * 256 * 256);
				val = val + (unsigned int)(((unsigned char)in[*i + 2]) * 256);
				val = val + (unsigned int)(in[*i + 3]);


//				printf("(unsigned int)(((unsigned char)in[*i + 2]) * 256) = %u\n", (unsigned int)(((unsigned char)in[*i + 2]) * 256));
//				printf("valu = %u\n", val);
//				printf("vals = %d\n", val);
				if ((int)val < -256)
					val = val + 256;
//				else if ((int)val > 0 && (int)(val) < 256)
//					val = val - 256;
				value = ft_itoa(val);
//				printf("value = %s\n", value);
				*i = *i + 4;
			}
			while (value[j] != '\0')
				out->str[out->num++] = value[j++];
			free(value);
		}
		out->str[out->num++] = SEPARATOR_CHAR;
	}
	out->str[out->num - 1] = '\n';
	get_type(acb, 0);
	return (out->num);
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
	else if (in[*i] == 8)
		new = add_op("xor", new, pos, i);
	else if (in[*i] == 9)
		new = add_op("zjmp", new, pos, i);
	else if (in[*i] == 10)
		new = add_op("ldi", new, pos, i);
	else if (in[*i] == 11)
		new = add_op("sti", new, pos, i);
	else if (in[*i] == 12)
		new = add_op("fork", new, pos, i);
	else if (in[*i] == 13)
		new = add_op("lld", new, pos, i);
	else if (in[*i] == 14)
		new = add_op("lldi", new, pos, i);
	else if (in[*i] == 15)
		new = add_op("lfork", new, pos, i);
	else if (in[*i] == 16)
		new = add_op("aff", new, pos, i);
	else
		pos++;
	*i = *i + 1;
	pos = new->num;
	pos = add_arg(new, in, i, in[*i - 1]);
	return (new);
}

t_list 	*add_all(t_list*out, char *in, int max, int pos, int flag)
{
	int i;

	i = PROG_NAME_LENGTH + 16 + COMMENT_LENGTH;
	while (i < max)
		out = add_command(out, in, &i, pos);
	out = lstrev(out);
	if ((flag & 1) == 1)
		make_link(out);
	return (out);
}

void	print_list(t_list *code, int flag)
{
	t_list	*tmp;
//	char	*start;

	tmp = code;
	while(tmp)
	{
		if ((flag & 8) == 8)
			printf("%d:\t", tmp->start);
		printf("%s", tmp->str);
//		printf("start = %d\n", tmp->start);
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

void	decompile(char *in, int max, char *file, int flag)
{
	t_list 	*out;
	int		pos;
	int 	fd;
	t_list	*tmp;
	char	*start;

	pos = 0;
	out = NULL;
	out = add_name(out, in, max, pos);
	out = add_comment(out, in, max, pos);
	out = add_all(out, in, max, pos, flag);
	if ((flag & 4 ) != 4)
		print_list(out, flag);
	else
	{
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
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
	clear_list(out);
}

int 	invalid_file(void)
{
	char *er;

	er = "Invalid file\n";
	write(1, er, ft_strlen(er));
	return (1);
}

int 	find_flag_dasm(int ac, char **av)
{
	int ret;
	int max;
	int i;
	int block;

	max = 65535;
	ret = 0;
	block = 0;
	i = 0;
//	printf("ac = %d\n", ac);
	while (++i < ac)
	{
//		printf(">>>>>>>>>> i = %d, av[i] = %s, block = %d\n", i, av[i], block);
		if (ft_strcmp(av[i], "-l") == 0)
			ret = ret | (max & 2);
		else if (ft_strcmp(av[i], "-f") == 0)
		{
//			printf("found block\n");
			block = 1;
			ret = ret | (max & 4);
		}
		else if (ft_strcmp(av[i], "-o") == 0)
			ret = ret | (max & 8);
		else if (ft_strcmp(av[i], "-m") == 0)
			ret = ret | (max & 1);
		else
		{
//			printf("block == %d\n", block);
			if (block == 1)
				ret = ret | (i << 10);
			if ((ret & 32) == 32)
				ret = ret | (max & 64);
			if ((ret & 16) == 16 && block == 0)
				ret = ret | (max & 32);
			ret = ret | (max & 16);
			if (block == 0)
				ret = ret | (i << 7);
		}
	}
	return (ret);
}

int 	main(int ac, char **av)
{
	int		fd;
	int 	pos;
	int 	flag;
	char	*file;
	char 	*in;
	char 	buff;

	pos = 0;
	flag = find_flag_dasm(ac, av);
//	printf("flag = %d\n", flag);
	if (ac == 1 || ac > 7)
		return (usage());
	file = av[(flag & 896) >> 7];
	if ((flag & 16) != 16)
		return (cant_find_file(flag));
//	printf("file = %s\n", file);
	if (((fd = open(file, O_RDONLY)) < 3))
		return (no_file(file, flag));
	if (!(file = get_name(file, flag, av)))
		return (wrong_file_name(av[1], flag));
//	printf("out file = %s\n", file);
	in = (char *)malloc(10000);
	while (read(fd, &buff, 1) > 0)
		in[pos++] = buff;
	if (pos < COMMENT_LENGTH + PROG_NAME_LENGTH + 10)
		return (invalid_file());
	decompile(in, pos - 1, file, flag);
	if ((flag & 2) == 2)
		system("leaks dasm");
//	system("afplay ./sounds/Emerge2.wav");
	return (0);
}
