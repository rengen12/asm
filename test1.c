//
// Created by Denis BUY on 3/4/18.
//

#include "asm.h"
#include "op.h"

t_list	*test_math(char *in, int i, t_list *error, int num)
{
	char *tr;

//	printf("test math str1 = '%s'\n", in);
	tr = (char*)malloc(ft_strlen(in) + 1);

	tr = copy_index(tr, in, i + 1, 1);
	if (ft_atoi(tr) == 2659464979)
		return(listadd(error, listn(strjoin(ft_itoa(num), ft_itoa(i)))));
//	printf("test math str2 = '%s'\n", tr);
	return (error);
}

t_list	*test_reg(char *in, int i, int num)
{
	char	*tr;
	long 	reg;

	tr = (char*)malloc(ft_strlen(in) + 1);
	tr = copy_index(tr, in, i, 1);
	reg = ft_atoi(tr);
	if (reg < 1 || reg > REG_NUMBER)
	{
//		printf("ERROR reg = %ld at str = '%s', i = %d\n", reg, in, i);
		return (listn(strjoin(ft_itoa(num), ft_itoa(i))));
	}
	return (NULL);
}

int		is_label_char(char test)
{
	char	*label;
	int 	i;

	i = -1;
	label = LABEL_CHARS;
	while(label[++i] != '\0')
		if (test == label[i])
			return (1);
	return (0);
}

int 	find_label(char *label, t_list *code)
{
	t_list	*tmp;
	int		i;
	int 	j;

	tmp = code;
	while (tmp)
	{
		j = 0;
		i = 0;
		while (tmp->str[i] == 32 || (tmp->str[i] >= 9 && tmp->str[i] <= 13))
			i++;
		if (tmp->str[i] == label[0])
		{
			while (tmp->str[i] != '\0' && label[j] != '\0' && tmp->str[i] == label[j])
			{
				i++;
				j++;
			}
			if (label[j] == '\0' && tmp->str[i] == LABEL_CHAR)
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

t_list	*test_label(char *in, int i, int num, t_list *code)
{
	int		size;
	char	*label;
	int		j;

	j = 0;
	size = 0;
	while (is_label_char(in[i++]) == 1)
		size++;
//	printf("size = '%d'\n", size);
	i = i - size - 1;
	label = (char*)malloc(size + 1);
	label[size] = '\0';
	while (size-- > 0)
		label[j++] = in[i++];
//	printf("label = '%s'\n", label);
	if (find_label(label, code) == 0)
		return (listn(strjoin(ft_itoa(num), ft_itoa(i))));
	return (NULL);
}

t_list	*test_live(char *com, char *in, t_list *error, int num)
{
	int i;
	int j;

//	printf("str tested = %s, num = %d\n", in, num);
	i = 0;
	while (in[i] == 32 || (in[i] >= 9 && in[i] <= 13))
		i++;
	j = -1;
	while (in[i] == com[++j])
		i++;
//	printf("char = '%c'\n", in[i]);
	while (in[i] == 32 || (in[i] >= 9 && in[i] <= 13))
		i++;
	if (in[i] != DIRECT_CHAR)
	{
//		printf("returned error, num = %s \n", ft_itoa(num));
		return (listadd(error, listn(strjoin(ft_itoa(num), ft_itoa(i)))));
	}
	if (in[++i] < '0' || in[i] > '9')
		return (listadd(error, listn(strjoin(ft_itoa(num), ft_itoa(i)))));
//	error = test_math(in, i, error, num);
	return (error);
}

t_list	*test_ld(char *com, char *in, t_list *error, int num)
{
	int		i;
	int		j;

//	printf("testing com = '%s'\n", in);
	i = 0;
	while (in[i] == 32 || (in[i] >= 9 && in[i] <= 13))
		i++;
	j = -1;
	while (in[i] == com[++j])
		i++;
	while (in[i] == 32 || (in[i] >= 9 && in[i] <= 13))
		i++;
	if (in[i] == DIRECT_CHAR)
		i++;
//	if ((error = test_math(in, i, error, num)) != NULL)
//		return (error);
	if ((in[i] < '0' || in[i] > '9') && in[i] != '-')
		return (listadd(error, listn(strjoin(ft_itoa(num), ft_itoa(i)))));
	if (in[i] == '-')
		i++;
	while (in[i] >= '0' && in[i] <= '9')
		i++;
	while (in[i] == 32 || (in[i] >= 9  && in[i] <= 13))
		i++;
	if (in[i] != SEPARATOR_CHAR)
		return (listadd(error, listn(strjoin(ft_itoa(num), ft_itoa(i)))));
	i++;
	while (in[i] == 32 || (in[i] >= 9  && in[i] <= 13))
		i++;
	if (in[i] != 'r')
		return (listadd(error, listn(strjoin(ft_itoa(num), ft_itoa(i)))));
	i++;
	if ((error = test_reg(in, i, num)) != NULL)
		return (error);
	while (in[i] >= '0' && in[i] <= '9')
		i++;
	while (in[i] == 32 || (in[i] >= 9  && in[i] <= 13))
		i++;

	if (in[i] != '\0' && in[i] != COMMENT_CHAR)
		return (listadd(error, listn(strjoin(ft_itoa(num), ft_itoa(i)))));
//	printf("test\n");
	return (error);
}

t_list	*test_st(char *in, t_list *error, int num, t_list *code)
{
	int		i;
	int		j;
	char 	*com;

	com = "st";
	i = 0;
	while (in[i] == 32 || (in[i] >= 9 && in[i] <= 13))
		i++;
	j = -1;
	while (in[i] == com[++j])
		i++;
	while (in[i] == 32 || (in[i] >= 9 && in[i] <= 13))
		i++;
	if (in[i] != 'r')
		return (listn(strjoin(ft_itoa(num), ft_itoa(i))));
	i++;
	if ((error = test_reg(in, i, num)) != NULL)
		return (error);
	while (in[i] >= '0' && in[i] <= '9')
		i++;
	while (in[i] == 32 || (in[i] >= 9  && in[i] <= 13))
		i++;
	if (in[i] != SEPARATOR_CHAR)
		return (listn(strjoin(ft_itoa(num), ft_itoa(i))));
	i++;
	while (in[i] == 32 || (in[i] >= 9  && in[i] <= 13))
		i++;
	if (in[i] == 'r')
	{
		if ((error = test_reg(in, i + 1, num)) != NULL)
			return (error);
		i++;
		while (in[i] >= '0' && in[i] <= '9')
			i++;
		while (in[i] == 32 || (in[i] >= 9  && in[i] <= 13))
			i++;
		if (in[i] != '\0')
			return (listn(strjoin(ft_itoa(num), ft_itoa(i))));
	}
	else if (in[i] == LABEL_CHAR)
	{
		if ((error = test_label(in, i + 1, num, code)) != NULL)
			return (error);
		i++;
		while (is_label_char(in[i]) == 1)
			i++;
		while (in[i] == 32 || (in[i] >= 9  && in[i] <= 13))
			i++;
		if (in[i] != '\0')
			return (listn(strjoin(ft_itoa(num), ft_itoa(i))));
	}
	else if (in[i] >= '0' && in[i] <= '9')
	{
		while (in[i] >= '0' && in[i] <= '9')
			i++;
		while (in[i] == 32 || (in[i] >= 9  && in[i] <= 13))
			i++;
		if (in[i] != '\0')
			return (listn(strjoin(ft_itoa(num), ft_itoa(i))));
	}
	else
		return (listn(strjoin(ft_itoa(num), ft_itoa(i))));
	return (error);
}

t_list	*test_add(char *com, char *in, t_list *error, int num)
{
	int		i;
	int		j;

	i = 0;

	while (in[i] == 32 || (in[i] >= 9 && in[i] <= 13))
		i++;
	j = -1;
	while (in[i] == com[++j])
		i++;
//	printf("char = '%c'\n", in[i]);
	j = 0;
//	printf("TESTED str = '%s', i = %d\n", in, i);
	while (j++ < 2)
	{
		while (in[i] == 32 || (in[i] >= 9 && in[i] <= 13))
			i++;

		if (in[i] != 'r')
			return (listn(strjoin(ft_itoa(num), ft_itoa(i))));
		i++;
		if ((error = test_reg(in, i, num)) != NULL)
			return (error);
		while (in[i] >= '0' && in[i] <= '9')
			i++;
		while (in[i] == 32 || (in[i] >= 9 && in[i] <= 13))
			i++;
		if (in[i] != SEPARATOR_CHAR)
			return (listn(strjoin(ft_itoa(num), ft_itoa(i))));
		i++;
	}

	while (in[i] == 32 || (in[i] >= 9 && in[i] <= 13))
		i++;

	if (in[i] != 'r')
		return (listn(strjoin(ft_itoa(num), ft_itoa(i))));
	i++;
//	printf("char = '%c'\n", in[i]);
	if ((error = test_reg(in, i, num)) != NULL)
		return (error);
	while (in[i] >= '0' && in[i] <= '9')
		i++;
	while (in[i] == 32 || (in[i] >= 9 && in[i] <= 13))
		i++;
	if (in[i] != '\0')
		return (listn(strjoin(ft_itoa(num), ft_itoa(i))));
	return (error);
}

t_list	*test_and(char *com, char *in, t_list *error, int num)
{
	int		i;
	int		j;

	i = 0;

	while (in[i] == 32 || (in[i] >= 9 && in[i] <= 13))
		i++;
	j = -1;
	while (in[i] == com[++j])
		i++;
//	printf("char = '%c'\n", in[i]);
	j = 0;
//	printf("TESTED str = '%s', i = %d\n", in, i);
	while (j++ < 2)
	{
		while (in[i] == 32 || (in[i] >= 9 && in[i] <= 13))
			i++;
		if (in[i] == 'r')
		{
			i++;
			if ((error = test_reg(in, i, num)) != NULL)
				return (error);
			while (in[i] >= '0' && in[i] <= '9')
				i++;
		}
		else if (in[i] == DIRECT_CHAR)
		{
			i++;
			while (in[i] >= '0' && in[i] <= '9')
				i++;
		}
		else if (in[i] >= '0' && in[i] <= '9')
			while (in[i] >= '0' && in[i] <= '9')
				i++;
		else
			return (listn(strjoin(ft_itoa(num), ft_itoa(i))));
		while (in[i] == 32 || (in[i] >= 9 && in[i] <= 13))
			i++;
		if (in[i] != SEPARATOR_CHAR)
			return (listn(strjoin(ft_itoa(num), ft_itoa(i))));
		i++;
	}
	while (in[i] == 32 || (in[i] >= 9 && in[i] <= 13))
		i++;
	if (in[i] == 'r')
	{
		i++;
		if ((error = test_reg(in, i, num)) != NULL)
			return (error);
		while (in[i] >= '0' && in[i] <= '9')
			i++;
	}
	else
		return (listn(strjoin(ft_itoa(num), ft_itoa(i))));
	while (in[i] == 32 || (in[i] >= 9 && in[i] <= 13))
		i++;
	if (in[i] != '\0')
		return (listn(strjoin(ft_itoa(num), ft_itoa(i))));
	return (error);
}

t_list	*test_fork(char *com, char *in, int num, t_list *code)
{
	int i;
	int j;
	t_list *error;

	error = NULL;
//	printf("str tested = %s, num = %d\n", in, num);
	i = 0;
	while (in[i] == 32 || (in[i] >= 9 && in[i] <= 13))
		i++;
	j = -1;
	while (in[i] == com[++j])
		i++;
//	printf("char = '%c'\n", in[i]);
	while (in[i] == 32 || (in[i] >= 9 && in[i] <= 13))
		i++;
	if (in[i] != DIRECT_CHAR)
	{
//		printf("returned error, num = %s \n", ft_itoa(num));
		return (listn(strjoin(ft_itoa(num), ft_itoa(i))));
	}
	i++;
	if (in[i] == LABEL_CHAR)
	{
		i++;
		if ((error = test_label(in, i, num, code)) != NULL)
			return (error);
		while (is_label_char(in[i]))
			i++;
	}
	else if ((in[i] >= '0' && in[i] <= '9') || in[i] == '-')
	{
		if (in[i] == '-' && (in[i + 1] >= '0' && in[i + 1] <= '9'))
			i++;
		while (in[i] >= '0' && in[i] <= '9')
			i++;
	}

	while (in[i] == 32 || (in[i] >= 9 && in[i] <= 13))
		i++;
//	printf(">>>>>>>char = '%c'\n", in[i]);
	if (in[i] != '\0' && in[i] != COMMENT_CHAR)
		return (listn(strjoin(ft_itoa(num), ft_itoa(i))));
//	printf("test\n");
	return (error);
}

t_list	*test_ldi(char *com, char *in, int num, t_list *code)
{
	int		i;
	int		j;
	t_list	*error;

	i = 0;
	error = NULL;
	while (in[i] == 32 || (in[i] >= 9 && in[i] <= 13))
		i++;
	j = -1;
	while (in[i] == com[++j])
		i++;
//	printf("char = '%c'\n", in[i]);
	j = 0;
	while (j++ < 2)
	{
		while (in[i] == 32 || (in[i] >= 9 && in[i] <= 13))
			i++;
		if (in[i] == 'r')
		{
			i++;
			if ((error = test_reg(in, i, num)) != NULL)
				return (error);
			while (in[i] >= '0' && in[i] <= '9')
				i++;
		}
		else if (in[i] == DIRECT_CHAR)
		{
			i++;
			if (in[i] == LABEL_CHAR)
			{
				i++;
				if ((error = test_label(in, i, num, code)) != NULL)
					return (error);
				while (is_label_char(in[i]))
					i++;
			}
			else
				while (in[i] >= '0' && in[i] <= '9')
					i++;
		}
		else if (in[i] >= '0' && in[i] <= '9' && j == 1)
			while (in[i] >= '0' && in[i] <= '9')
				i++;
		else if (in[i] == LABEL_CHAR && j == 1)
		{
			i++;
			if ((error = test_label(in, i, num, code)) != NULL)
				return (error);
		}
		else
			return (listn(strjoin(ft_itoa(num), ft_itoa(i))));
		while (in[i] == 32 || (in[i] >= 9 && in[i] <= 13))
			i++;
		if (in[i] != SEPARATOR_CHAR && j == 1)
			return (listn(strjoin(ft_itoa(num), ft_itoa(i))));
		if (j == 1)
			i++;
	}
	while (in[i] == 32 || (in[i] >= 9 && in[i] <= 13))
		i++;
	if (in[i] != SEPARATOR_CHAR && j == 1)
		return (listn(strjoin(ft_itoa(num), ft_itoa(i))));
//	printf("char = '%c', i = %d\n", in[i], i);
	i++;
	if (in[i] != 'r')
		return (listn(strjoin(ft_itoa(num), ft_itoa(i))));
	i++;
	if ((error = test_reg(in, i, num)) != NULL)
		return (error);
	while (in[i] >= '0' && in[i] <= '9')
		i++;
	while (in[i] == 32 || (in[i] >= 9 && in[i] <= 13))
		i++;
	if (in[i] != '\0' && in[i] != COMMENT_CHAR)
		return (listn(strjoin(ft_itoa(num), ft_itoa(i))));

	return (error);
}

t_list	*test_sti(char *com, char *in, int num, t_list *code)
{
	int		i;
	int		j;
	t_list	*error;

	i = 0;
	error = NULL;
	while (in[i] == 32 || (in[i] >= 9 && in[i] <= 13))
		i++;
	j = -1;
	while (in[i] == com[++j])
		i++;
//	printf("char = '%c'\n", in[i]);
	j = 0;
//	printf("TESTED str = '%s', i = %d\n", in, i);
	while (in[i] == 32 || (in[i] >= 9 && in[i] <= 13))
		i++;
	if (in[i] != 'r')
		return (listn(strjoin(ft_itoa(num), ft_itoa(i))));
	i++;
	if ((error = test_reg(in, i, num)) != NULL)
		return (error);
	while (in[i] >= '0' && in[i] <= '9')
		i++;
	if (in[i] != SEPARATOR_CHAR)
		return (listn(strjoin(ft_itoa(num), ft_itoa(i))));
	i++;
	while (j++ < 2)
	{
		while (in[i] == 32 || (in[i] >= 9 && in[i] <= 13))
			i++;
		if (in[i] == 'r')
		{
			i++;
			if ((error = test_reg(in, i, num)) != NULL)
				return (error);
			while (in[i] >= '0' && in[i] <= '9')
				i++;
		}
		else if (in[i] == DIRECT_CHAR)
		{
			i++;
			if (in[i] == LABEL_CHAR)
			{
				i++;
				if ((error = test_label(in, i, num, code)) != NULL)
					return (error);
			}
			else
				while (in[i] >= '0' && in[i] <= '9')
					i++;
		}
		else if (in[i] >= '0' && in[i] <= '9' && j == 1)
			while (in[i] >= '0' && in[i] <= '9')
				i++;
		else if (in[i] == LABEL_CHAR && j == 1)
		{
			i++;
			if ((error = test_label(in, i, num, code)) != NULL)
				return (error);
		}
		else
			return (listn(strjoin(ft_itoa(num), ft_itoa(i))));
		while (in[i] == 32 || (in[i] >= 9 && in[i] <= 13))
			i++;
		if (in[i] != SEPARATOR_CHAR && j == 1)
			return (listn(strjoin(ft_itoa(num), ft_itoa(i))));
		if (j == 1)
			i++;
	}
	while (in[i] == 32 || (in[i] >= 9 && in[i] <= 13))
		i++;
	if (in[i] != '\0' && in[i] != COMMENT_CHAR)
		return (listn(strjoin(ft_itoa(num), ft_itoa(i))));
	return (error);
}

t_list	*test_aff(char *com, char *in, int num)
{
	int		i;
	int		j;
	t_list	*error;

	i = 0;
	error = NULL;
	while (in[i] == 32 || (in[i] >= 9 && in[i] <= 13))
		i++;
	j = -1;
	while (in[i] == com[++j])
		i++;
	j = 0;
	while (in[i] == 32 || (in[i] >= 9 && in[i] <= 13))
		i++;
	if (in[i] != 'r')
		return (listn(strjoin(ft_itoa(num), ft_itoa(i))));
	i++;
	if ((error = test_reg(in, i, num)) != NULL)
		return (error);
	while (in[i] >= '0' && in[i] <= '9')
		i++;
	while (in[i] == 32 || (in[i] >= 9 && in[i] <= 13))
		i++;
	if (in[i] != '\0' && in[i] != COMMENT_CHAR)
		return (listn(strjoin(ft_itoa(num), ft_itoa(i))));
	return (error);
}