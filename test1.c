/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbuy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 13:30:41 by dbuy              #+#    #+#             */
/*   Updated: 2018/03/14 13:30:43 by dbuy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

char	*test_reg(char *in, int i, int num)
{
	char	*tr;
	long	reg;

	tr = (char*)malloc(ft_strlen(in) + 1);
	tr = copy_index(tr, in, i, 1);
	reg = ft_atoi(tr);
	free(tr);
	if (reg < 1 || reg > REG_NUMBER)
		return (strjoin(ft_itoa(num), ft_itoa(i)));
	return (NULL);
}

int		is_label_char(char test)
{
	char	*label;
	int		i;

	i = -1;
	label = LABEL_CHARS;
	while (label[++i] != '\0')
		if (test == label[i])
			return (1);
	return (0);
}

int		find_label(char *label, t_list *code)
{
	t_list	*tmp;
	int		i;
	int		j;

	tmp = code;
	while (tmp)
	{
		j = 0;
		i = 0;
		i = skip_spaces(tmp->str, i);
		if (tmp->str[i] == label[0])
		{
			while (tmp->str[i] != '\0' && label[j] != '\0' \
			&& tmp->str[i] == label[j])
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

char	*test_label(char *in, int i, t_list *tmp, t_list *code)
{
	int		size;
	char	*label;
	char	*a;
	char	*b;
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
	{
		a = ft_itoa(tmp->num);
		b = ft_itoa(i + tmp->white);
		free(label);
		label = strjoin(a, b);
		return (label);
	}
	free(label);
	return (NULL);
}

char	*test_ld2(char *in, int i, t_list *tmp)
{
	char *error;

	i = skip_spaces(in, i);
	if (in[i] != SEPARATOR_CHAR)
		return (strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white)));
	i++;
	i = skip_spaces(in, i);
	if (in[i] != 'r')
		return (strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white)));
	i++;
	if ((error = test_reg(in, i, tmp->num)) != NULL)
		return (error);
	i = skip_numeric(in, i);
	i = skip_spaces(in, i);
	if (in[i] != '\0')
		return (strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white)));
	return (NULL);
}

char	*test_ld(char *com, char *in, t_list *tmp, t_list *code)
{
	int		i;
	int		j;
	char	*error;

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
	else if (in[i] == '-' || (in[i] >= '0' && in[i] <= '9'))
		i = skip_numeric(in, i);
	return (test_ld2(in, i, tmp));
}

char	*test_st3(char *in, int i, t_list *tmp, t_list *code)
{
	char *error;

	if (in[i] == LABEL_CHAR)
	{
		if ((error = test_label(in, i + 1, tmp, code)) != NULL)
			return (error);
		i++;
		while (is_label_char(in[i]) == 1)
			i++;
		i = skip_math(in, i);
		if (in[i] != '\0')
			return (strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white)));
	}
	else if ((in[i] >= '0' && in[i] <= '9') || in[i] == '-')
	{
		i = skip_numeric(in, i);
		i = skip_spaces(in, i);
		if (in[i] != '\0')
			return (strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white)));
	}
	else
		return (strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white)));
	return (NULL);
}

char	*test_st2(char *in, int i, t_list *tmp, t_list *code)
{
	char *error;

	if (in[i] == 'r')
	{
		if ((error = test_reg(in, i + 1, tmp->num)) != NULL)
			return (error);
		i++;
		while (in[i] >= '0' && in[i] <= '9')
			i++;
		i = skip_spaces(in, i);
		if (in[i] != '\0')
			return (strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white)));
	}
	else
		return (test_st3(in, i, tmp, code));
	return (NULL);
}

char	*test_st(char *in, char *error, t_list *tmp, t_list *code)
{
	int		i;
	int		j;
	char	*com;

	com = "st";
	i = 0;
	i = skip_spaces(in, i);
	j = -1;
	while (in[i] == com[++j])
		i++;
	i = skip_spaces(in, i);
	if (in[i] != 'r')
		return (strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white)));
	i++;
	if ((error = test_reg(in, i, tmp->num)) != NULL)
		return (error);
	while (in[i] >= '0' && in[i] <= '9')
		i++;
	i = skip_spaces(in, i);
	if (in[i] != SEPARATOR_CHAR)
		return (strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white)));
	i++;
	i = skip_spaces(in, i);
	return (test_st2(in, i, tmp, code));
}

char	*test_add2(char *in, int i, t_list *tmp)
{
	char *error;

	error = NULL;
	i = skip_spaces(in, i);
	if (in[i] != 'r')
		return (strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white)));
	i++;
	if ((error = test_reg(in, i, tmp->num)) != NULL)
		return (error);
	i = skip_numeric(in, i);
	i = skip_spaces(in, i);
	if (in[i] != '\0')
		return (strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white)));
	return (error);
}

char	*test_add(char *com, char *in, t_list *tmp)
{
	int		i;
	int		j;
	char	*error;

	i = 0;
	i = skip_spaces(in, i);
	j = -1;
	while (in[i] == com[++j])
		i++;
	j = 0;
	while (j++ < 2)
	{
		i = skip_spaces(in, i);
		if (in[i] != 'r')
			return (strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white)));
		i++;
		if ((error = test_reg(in, i, tmp->num)) != NULL)
			return (error);
		i = skip_numeric(in, i);
		i = skip_spaces(in, i);
		if (in[i] != SEPARATOR_CHAR)
			return (strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white)));
		i++;
	}
	return (test_add2(in, i, tmp));
}

char	*test_and2(char *in, int *i, t_list *tmp, int j)
{
	char	*error;

	while (j++ < 2)
	{
		*i = skip_spaces(in, *i);
		if (in[*i] == 'r')
		{
			*i = *i + 1;
			if ((error = test_reg(in, *i, tmp->num)) != NULL)
				return (error);
			*i = skip_numeric(in, *i);
		}
		else if (in[*i] == DIRECT_CHAR)
			*i = skip_numeric(in, ++(*i));
		else if ((in[*i] >= '0' && in[*i] <= '9') || in[*i] == '-')
			*i = skip_numeric(in, *i);
		else
			return (strjoin(ft_itoa(tmp->num), ft_itoa(*i + tmp->white)));
		*i = skip_spaces(in, *i);
		if (in[*i] != SEPARATOR_CHAR)
			return (strjoin(ft_itoa(tmp->num), ft_itoa(*i + tmp->white)));
		*i = *i + 1;
	}
	return (NULL);
}

char	*test_and(char *com, char *in, t_list *tmp)
{
	int		i;
	int		j;
	char	*error;

	i = 0;
	i = skip_spaces(in, i);
	j = -1;
	while (in[i] == com[++j])
		i++;
	if ((error = test_and2(in, &i, tmp, 0)))
		return (error);
	i = skip_spaces(in, i);
	if (in[i] == 'r')
	{
		i++;
		if ((error = test_reg(in, i, tmp->num)) != NULL)
			return (error);
		i = skip_numeric(in, i);
	}
	else
		return (strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white)));
	i = skip_spaces(in, i);
	if (in[i] != '\0')
		return (strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white)));
	return (error);
}

char	*test_fork(char *com, char *in, t_list *tmp, t_list *code)
{
	int		i;
	int		j;
	char	*error;

//	printf("str test = '%s'\n", in);
	i = 0;
	j = -1;
	while (in[i] == com[++j])
		i++;
	i = skip_spaces(in, i);
	if (in[i] != DIRECT_CHAR)
		return (strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white + 1)));
//	printf("CHAR test = '%c'\n", in[i]);
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
	return (in[i] != '\0' ? strjoin(ft_itoa(tmp->num), \
	ft_itoa(i + tmp->white)) : NULL);
}

char	*test_skip_reg(char *in, int *i, t_list *tmp)
{
	char	*error;

	if (in[*i] != 'r')
		return (NULL);
	*i = *i + 1;
	if ((error = test_reg(in, *i, tmp->num)) != NULL)
		return (error);
	*i = skip_numeric(in, *i);
	return (NULL);
}

char	*test_sk_label(char *in, int *i, t_list *tmp, t_list *code)
{
	char *error;

	if (*i != LABEL_CHAR)
		return (NULL);
	*i = *i + 1;
	if ((error = test_label(in, *i, tmp, code)) != NULL)
		return (error);
	*i = skip_labelchar(in, *i);
	*i = skip_math(in, *i);
	return (NULL);
}

char	*test_ldi3(char *in, int *i, t_list *tmp)
{
	char	*error;

	*i = skip_spaces(in, *i);
	if (in[*i] != SEPARATOR_CHAR)
		return (strjoin(ft_itoa(tmp->num), ft_itoa(*i + tmp->white)));
	*i = *i + 1;
	*i = skip_spaces(in, *i);
	if (in[*i] != 'r')
		return (strjoin(ft_itoa(tmp->num), ft_itoa(*i + tmp->white)));
	if ((error = test_skip_reg(in, i, tmp)))
		return (error);
	*i = skip_spaces(in, *i);
	if (in[*i] != '\0' && in[*i] != COMMENT_CHAR)
		return (strjoin(ft_itoa(tmp->num), ft_itoa(*i + tmp->white)));
	return (NULL);
}

char	*test_ldi2(char *in, int *i, t_list *tmp, t_list *code)
{
	char	*error;

	*i = skip_spaces(in, *i);
	if (in[*i] != SEPARATOR_CHAR)
		return (strjoin(ft_itoa(tmp->num), ft_itoa(*i + tmp->white)));
	*i = skip_spaces(in, ++(*i));
	if (in[*i] == 'r')
	{
		if ((error = test_skip_reg(in, i, tmp)))
			return (error);
	}
	else if (in[*i] == DIRECT_CHAR)
	{
		if (in[++(*i)] == LABEL_CHAR)
		{
			if ((error = test_sk_label(in, i, tmp, code)))
				return (error);
			*i = skip_labelchar(in, ++(*i));
		}
		else
			*i = skip_numeric(in, *i);
	}
	else
		return (strjoin(ft_itoa(tmp->num), ft_itoa(*i + tmp->white)));
	return (NULL);
}

char	*test_ldi(char *com, char *in, t_list *tmp, t_list *code)
{
	int		i;
	char	*error;

	i = skip_com(in, com);
	if (in[i] == 'r')
	{
		if ((error = test_skip_reg(in, &i, tmp)))
			return (error);
	}
	else if (in[i] == DIRECT_CHAR)
	{
		if (in[i++] == LABEL_CHAR && (error = test_sk_label(in, &(i), tmp, code)))
			return (error);
		i = (in[i] == LABEL_CHAR ? i = skip_labelchar(in, ++i) \
														: skip_numeric(in, i));
	}
	else if (in[i] == '-' || (in[i] >= '0' && in[i] <= '9'))
		i = skip_numeric(in, i);
	else
		return (strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white)));
	if ((error = test_ldi2(in, &i, tmp, code)) != NULL)
		return (error);
	if ((error = test_ldi3(in, &i, tmp)) != NULL)
		return (error);
	return (error);
}

char	*test_sti3(char *in, int *i, t_list *tmp, t_list *code)
{
	char *error;

	*i = skip_spaces(in, *i);
	if (in[*i] == DIRECT_CHAR)
	{
		*i = *i + 1;
		if (in[*i] == LABEL_CHAR)
		{
			*i = *i + 1;
			if ((error = test_label(in, *i, tmp, code)) != NULL)
				return (error);
			*i = skip_labelchar(in, *i);
			*i = skip_math(in, *i);
		}
		else
			*i = skip_numeric(in, *i);
	}
	else if (in[*i] == 'r')
	{
		if ((error = test_skip_reg(in, i, tmp)) != NULL)
			return (error);
	}
	else
		return (strjoin(ft_itoa(tmp->num), ft_itoa(*i + tmp->white)));
	return (NULL);
}

char	*test_sti2(char *in, int *i, t_list *tmp, t_list *code)
{
	char		*e;

	e = NULL;
	*i = skip_spaces(in, *i);
	if (in[*i] == 'r')
	{
		if ((e = test_skip_reg(in, i, tmp)) != NULL)
			return (e);
	}
	else if (in[*i] == DIRECT_CHAR || (in[*i] == LABEL_CHAR) || in[*i] == '-' \
	|| ((in[*i] >= '0' && in[*i] <= '9')))
	{
		*i = (in[*i] == DIRECT_CHAR ? *i + 1 : *i);
		if (in[*i] == LABEL_CHAR)
		{
			if ((e = test_label(in, (++*i), tmp, code)))
				return (e);
		}
		*i = (in[--*i] == LABEL_CHAR ? skip_labelchar(in, ++*i) \
													: skip_numeric(in, ++*i));
	}
	if (in[*i] != SEPARATOR_CHAR)
		return (strjoin(ft_itoa(tmp->num), ft_itoa(*i + tmp->white)));
	*i = *i + 1;
	return (e);
}

char	*test_sti(char *com, char *in, t_list *tmp, t_list *code)
{
	int		i;
	char	*error;

	i = skip_com(in, com);
	if (in[i] != 'r')
		return (strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white)));
	if ((error = test_reg(in, ++i, tmp->num)) != NULL)
		return (error);
	i = skip_numeric(in, i);
	if (in[i++] != SEPARATOR_CHAR)
		return (strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white)));
	if ((error = test_sti2(in, &i, tmp, code)) != NULL)
		return (error);
	if ((error = test_sti3(in, &i, tmp, code)) != NULL)
		return (error);
	i = skip_spaces(in, i);
	if (in[i] != '\0' && in[i] != COMMENT_CHAR)
		return (strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white)));
	return (error);
}

char	*test_aff(char *com, char *in, t_list *tmp)
{
	int		i;
	int		j;
	char	*error;

	i = 0;
	i = skip_spaces(in, i);
	j = -1;
	while (in[i] == com[++j])
		i++;
	j = 0;
	while (in[i] == 32 || (in[i] >= 9 && in[i] <= 13))
		i++;
	if (in[i] != 'r')
		return (strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white)));
	i++;
	if ((error = test_reg(in, i, tmp->num)) != NULL)
		return (error);
	i = skip_numeric(in, i);
	i = skip_spaces(in, i);
	if (in[i] != '\0' && in[i] != COMMENT_CHAR)
		return (strjoin(ft_itoa(tmp->num), ft_itoa(i + tmp->white)));
	return (error);
}
