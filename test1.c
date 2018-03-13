//
// Created by Denis BUY on 3/4/18.
//

#include "asm.h"
#include "op.h"

t_list	*test_math(char *in, int i, t_list *error, int num)
{
	char *tr;

	tr = (char*)malloc(ft_strlen(in) + 1);
	tr = copy_index(tr, in, i + 1, 1);
	if (ft_atoi(tr) == 2659464979)
		return(listadd(error, listn(strjoin(ft_itoa(num), ft_itoa(i)))));
	return (error);
}

t_list	*test_reg(char *in, int i, int num)
{
	char	*tr;
	long 	reg;

	tr = (char*)malloc(ft_strlen(in) + 1);
	tr = copy_index(tr, in, i, 1);
	reg = ft_atoi(tr);
	free(tr);
	if (reg < 1 || reg > REG_NUMBER)
		return (listn(strjoin(ft_itoa(num), ft_itoa(i))));
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
		i = skip_spaces(tmp->str, i);
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

t_list	*test_label(char *in, int i, t_list *tmp, t_list *code)
{
	int		size;
	char	*label;
	int		j;

	j = 0;
	size = 0;
	while (is_label_char(in[i++]) == 1)
		size++;
	i = i - size - 1;
	label = (char*)malloc(size + 1);
	label[size] = '\0';
	while (size-- > 0)
		label[j++] = in[i++];
	if (find_label(label, code) == 0)
		return (listn(strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white))));
	free(label);
	return (NULL);
}

t_list	*test_ld(char *com, char *in, t_list *tmp, t_list *code)
{
	int		i;
	int		j;
	t_list	*error;

	i = 0;
	j = -1;

	while (in[i] == com[++j])
		i++;
	i = skip_spaces(in, i);
	if (in[i] == DIRECT_CHAR)
		i++;
	if (in[i] == LABEL_CHAR)
	{
		if ((error = test_label(in, ++i, tmp, code)) != NULL)
			return (error);
		i = skip_labelchar(in, i);
		i = skip_math(in, i);
	}
	else
	{
		if ((in[i] < '0' || in[i] > '9') && in[i] != '-')
			return (listn(strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white))));
		i = skip_numeric(in, i);
	}
	i = skip_spaces(in, i);
//	printf("in[i] = '%c'\n", in[i]);
	if (in[i] != SEPARATOR_CHAR)
		return (listn(strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white))));
	i++;
	i = skip_spaces(in, i);
	if (in[i] != 'r')
		return (listn(strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white))));
	i++;
	if ((error = test_reg(in, i, tmp->num)) != NULL)
		return (error);
	i = skip_numeric(in, i);
	i = skip_spaces(in, i);
	if (in[i] != '\0')
		return (listn(strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white))));
	return (error);
}

t_list	*test_st(char *in, t_list *error, t_list *tmp, t_list *code)
{
	int		i;
	int		j;
	char 	*com;

	com = "st";
	i = 0;
	i = skip_spaces(in, i);
	j = -1;
	while (in[i] == com[++j])
		i++;
	i = skip_spaces(in, i);
	if (in[i] != 'r')
		return (listn(strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white))));
	i++;
	if ((error = test_reg(in, i, tmp->num)) != NULL)
		return (error);
	while (in[i] >= '0' && in[i] <= '9')
		i++;
	i = skip_spaces(in, i);
	if (in[i] != SEPARATOR_CHAR)
		return (listn(strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white))));
	i++;
	i = skip_spaces(in, i);
	if (in[i] == 'r')
	{
		if ((error = test_reg(in, i + 1, tmp->num)) != NULL)
			return (error);
		i++;
		while (in[i] >= '0' && in[i] <= '9')
			i++;
		i = skip_spaces(in, i);
		if (in[i] != '\0')
			return (listn(strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white))));
	}
	else if (in[i] == LABEL_CHAR)
	{
		if ((error = test_label(in, i + 1, tmp, code)) != NULL)
			return (error);
		i++;
		while (is_label_char(in[i]) == 1)
			i++;
		i = skip_math(in, i);
		if (in[i] != '\0')
			return (listn(strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white))));
	}
	else if ((in[i] >= '0' && in[i] <= '9') || in[i] == '-')
	{
		i = skip_numeric(in, i);
		i = skip_spaces(in, i);
		if (in[i] != '\0')
			return (listn(strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white))));
	}
	else
		return (listn(strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white))));
	return (error);
}

t_list	*test_add(char *com, char *in, t_list *tmp)
{
	int		i;
	int		j;
	t_list	*error;

	i = 0;

	i = skip_spaces(in, i);
	j = -1;
	while (in[i] == com[++j])
		i++;
//	printf("char = '%c'\n", in[i]);
	j = 0;
//	printf("TESTED str = '%s', i = %d\n", in, i);
	while (j++ < 2)
	{
		i = skip_spaces(in, i);
		if (in[i] != 'r')
			return (listn(strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white))));
		i++;
		if ((error = test_reg(in, i, tmp->num)) != NULL)
			return (error);
		i = skip_numeric(in, i);
		i = skip_spaces(in, i);
		if (in[i] != SEPARATOR_CHAR)
			return (listn(strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white))));
		i++;
	}
	i = skip_spaces(in, i);
	if (in[i] != 'r')
		return (listn(strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white))));
	i++;
//	printf("char = '%c'\n", in[i]);
	if ((error = test_reg(in, i, tmp->num)) != NULL)
		return (error);
	i = skip_numeric(in, i);
	i = skip_spaces(in, i);
	if (in[i] != '\0')
		return (listn(strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white))));
	return (error);
}

t_list	*test_and(char *com, char *in, t_list *tmp)
{
	int		i;
	int		j;
	t_list	*error;

	i = 0;
	i = skip_spaces(in, i);
	j = -1;
	while (in[i] == com[++j])
		i++;
//	printf("char = '%c'\n", in[i]);
	j = 0;
//	printf("TESTED str = '%s', i = %d\n", in, i);
	while (j++ < 2)
	{
		i = skip_spaces(in, i);
		if (in[i] == 'r')
		{
			i++;
			if ((error = test_reg(in, i, tmp->num)) != NULL)
				return (error);
			i = skip_numeric(in, i);
		}
		else if (in[i] == DIRECT_CHAR)
		{
			i++;
			i = skip_numeric(in, i);
		}
		else if (in[i] >= '0' && in[i] <= '9')
			i = skip_numeric(in, i);
		else
			return (listn(strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white))));
		i = skip_spaces(in, i);
		if (in[i] != SEPARATOR_CHAR)
			return (listn(strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white))));
		i++;
	}
	i = skip_spaces(in, i);
	if (in[i] == 'r')
	{
		i++;
		if ((error = test_reg(in, i, tmp->num)) != NULL)
			return (error);
		i = skip_numeric(in, i);
	}
	else
		return (listn(strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white))));
	i = skip_spaces(in, i);
	if (in[i] != '\0')
		return (listn(strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white))));
	return (error);
}

t_list	*test_fork(char *com, char *in, t_list *tmp, t_list *code)
{
	int i;
	int j;
	t_list *error;


	error = NULL;
	i = 0;
	j = -1;
	while (in[i] == com[++j])
		i++;
	i = skip_spaces(in, i);
	if (in[i] != DIRECT_CHAR)
		return (listn(strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white + 1))));
	i++;
	if (in[i] == LABEL_CHAR)
	{
		if ((error = test_label(in, ++i, tmp, code)) != NULL)
			return (error);
		i = skip_labelchar(in, i);
		i = skip_math(in, i);
	}
	else if ((in[i] >= '0' && in[i] <= '9') || in[i] == '-')
		i = skip_numeric(in, i);
	i = skip_spaces(in, i);
	if (in[i] != '\0')
		return (listn(strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white))));
//	while(1);
	return (error);
}

t_list	*test_ldi(char *com, char *in, t_list *tmp, t_list *code)
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
		i = skip_spaces(in, i);
		if (in[i] == 'r')
		{
			i++;
			if ((error = test_reg(in, i, tmp->num)) != NULL)
				return (error);
			i = skip_numeric(in, i);
		}
		else if (in[i] == DIRECT_CHAR)
		{
			i++;
			if (in[i] == LABEL_CHAR)
			{
				i++;
				if ((error = test_label(in, i, tmp, code)) != NULL)
					return (error);
				while (is_label_char(in[i]))
					i++;
				i = skip_math(in, i);
			}
			else
				i = skip_numeric(in, i);
		}
		else if (in[i] >= '0' && in[i] <= '9' && j == 1)
			i = skip_numeric(in, i);
		else if (in[i] == LABEL_CHAR && j == 1)
		{
			i++;
			if ((error = test_label(in, i, tmp, code)) != NULL)
				return (error);
			i = skip_labelchar(in, i);
			i = skip_math(in, i);
		}
		else
			return (listn(strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white))));
		i = skip_spaces(in, i);
		if (in[i] != SEPARATOR_CHAR && j == 1)
			return (listn(strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white))));
		if (j == 1)
			i++;
	}
	i = skip_spaces(in, i);
	if (in[i] != SEPARATOR_CHAR && j == 1)
		return (listn(strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white))));
	i++;
	if (in[i] != 'r')
		return (listn(strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white))));
	i++;
	if ((error = test_reg(in, i, tmp->num)) != NULL)
		return (error);
	i = skip_numeric(in, i);
	i = skip_spaces(in, i);
	if (in[i] != '\0' && in[i] != COMMENT_CHAR)
		return (listn(strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white))));
	return (error);
}

t_list	*test_sti(char *com, char *in, t_list *tmp, t_list *code)
{
	int		i;
	int		j;
	t_list	*error;

	i = 0;
	i = skip_spaces(in, i);
	j = -1;
	while (in[i] == com[++j])
		i++;
	j = 0;
	i = skip_spaces(in, i);
	if (in[i] != 'r')
		return (listn(strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white))));
	i++;
	if ((error = test_reg(in, i, tmp->num)) != NULL)
		return (error);
	i = skip_numeric(in, i);
	if (in[i] != SEPARATOR_CHAR)
		return (listn(strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white))));
	i++;
	while (j++ < 2)
	{
		i = skip_spaces(in, i);
		if (in[i] == 'r')
		{
			i++;
			if ((error = test_reg(in, i, tmp->num)) != NULL)
				return (error);
			i = skip_numeric(in, i);
		}
		else if (in[i] == DIRECT_CHAR)
		{
			i++;
			if (in[i] == LABEL_CHAR)
			{
				i++;
				if ((error = test_label(in, i, tmp, code)) != NULL)
					return (error);
				i = skip_labelchar(in, i);
				i = skip_math(in, i);
			}
			else
				i = skip_numeric(in, i);
		}
		else if (in[i] >= '0' && in[i] <= '9' && j == 1)
			i = skip_numeric(in, i);
		else if (in[i] == LABEL_CHAR && j == 1)
		{
			i++;
			if ((error = test_label(in, i, tmp, code)) != NULL)
				return (error);
			i = skip_labelchar(in, i);
			i = skip_math(in, i);
		}
		else
			return (listn(strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white))));
		i = skip_spaces(in, i);
		if (in[i] != SEPARATOR_CHAR && j == 1)
			return (listn(strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white))));
		if (j == 1)
			i++;
	}
	i = skip_spaces(in, i);
	if (in[i] != '\0' && in[i] != COMMENT_CHAR)
		return (listn(strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white))));
	return (error);
}

t_list	*test_aff(char *com, char *in, t_list *tmp)
{
	int		i;
	int		j;
	t_list	*error;

	i = 0;
	i = skip_spaces(in, i);
	j = -1;
	while (in[i] == com[++j])
		i++;
	j = 0;
	while (in[i] == 32 || (in[i] >= 9 && in[i] <= 13))
		i++;
	if (in[i] != 'r')
		return (listn(strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white))));
	i++;
	if ((error = test_reg(in, i, tmp->num)) != NULL)
		return (error);
	i = skip_numeric(in, i);
	i = skip_spaces(in, i);
	if (in[i] != '\0' && in[i] != COMMENT_CHAR)
		return (listn(strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white))));
	return (error);
}
