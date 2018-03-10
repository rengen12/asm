//
// Created by Denis BUY on 3/10/18.
//

#include "op.h"
#include "asm.h"

int 	usage(void)
{
	char *a;

	a = "./dasm <champion.cor>";
	write(1, a, ft_strlen(a));
	write (1, "\n", 1);
	return (1);
}

int 	no_file(char *file)
{
	char *a;

	a = "Cant read file: ";
	write(1, a, ft_strlen(a));
	write(1, file, ft_strlen(file));
	write (1, "\n", 1);
	return (1);
}

int 	wrong_file_name(char *file)
{
	char *a;

	a = "Wrong file name: ";
	write(1, a, ft_strlen(a));
	write(1, file, ft_strlen(file));
	write (1, "\n", 1);
	return (1);
}

char *find_cor(char *file)
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

char	*get_name(char *file)
{
	char *ret;
	if ((ret = find_cor(file)) == NULL)
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
	out->start = j[0];
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

void	set_link(t_list *code, t_list *tmp)
{
	static int i;
	char *a;

	i++;
	a = ft_itoa(i);
	code->str = strconcat(strconcat(strconcat("label_", a), ": "), code->str);
	code->num = code->num + 7 + ft_strlen(a);
	tmp->str = strconcat(strconcat(strconcat(tmp->str, ":"), "label_"), a);
	tmp->num = tmp->num + 8 + ft_strlen(a);
	tmp->num++;
	tmp->str[tmp->num] = '\t';
	tmp->num++;
}

int 	make_link(t_list *code, int val)
{
	t_list	*tmp;

	tmp = code;
	while (tmp)
	{
		if (code->start - tmp->start == -val && code->start != tmp->start)
		{
			printf("\n>>>>>>>>>>>>>>>>>>>found!\n");
			set_link(code, tmp);
			break ;
		}
		tmp = tmp->next;
	}
	return (0);
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
			*i = *i + 1;
		}
		else if (type == 3)
		{
			value = ft_itoa(in[*i] * 256 + in[*i + 1]);
			while (value[j] != '\0')
				out->str[out->num++] = value[j++];
			*i = *i + 2;
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
				if ((int)val < -255)
					val = val + 256;
				value = ft_itoa(val);
//				printf("value = %s\n", value);
				*i = *i + 4;
			}
//			if ((make_link(out, val)) == 0)
				while (value[j] != '\0')
					out->str[out->num++] = value[j++];
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

t_list 	*add_all(t_list*out, char *in, int max, int pos)
{
	int i;

	i = PROG_NAME_LENGTH + 16 + COMMENT_LENGTH;
	while (i < max)
//	max++;
		out = add_command(out, in, &i, pos);
//		out = add_command(out, in, &i, pos);
	return (out);
}

void	print_list(t_list *code)
{
	t_list *tmp;

	tmp = code;
	while(tmp)
	{
		printf("%s", tmp->str);
//		printf("start = %d\n", tmp->start);
		tmp = tmp->next;
	}
}

void	decompile(char *in, int max, char *file)
{
	t_list 	*out;
	int		pos;

	if (file)
		printf("");
	pos = 0;

	out = NULL;
	out = add_name(out, in, max, pos);
	out = add_comment(out, in, max, pos);
	out = add_all(out, in, max, pos);
	out = lstrev(out);
	print_list(out);
}

int 	invalid_file(void)
{
	char *er;

	er = "Invalid file\n";
	write(1, er, ft_strlen(er));
	return (1);
}

int 	main(int ac, char **av)
{
	int		fd;
	int 	pos;
	char	*file;
	char 	*in;
	char 	buff;


	pos = 0;
	if (ac != 2)
		return (usage());
	if (((fd = open(av[1], O_RDONLY)) < 3))
		return (no_file(av[1]));
	if (!(file = get_name(av[1])))
		return (wrong_file_name(av[1]));
	in = (char *)malloc(10000);
	while (read(fd, &buff, 1) > 0)
		in[pos++] = buff;
	if (pos < COMMENT_LENGTH + PROG_NAME_LENGTH + 10)
		return (invalid_file());
	decompile(in, pos - 1, file);
	return (0);
}
