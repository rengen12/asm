/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dasm_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbuy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 17:27:05 by dbuy              #+#    #+#             */
/*   Updated: 2018/03/14 17:27:06 by dbuy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"

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
		return ((acb & 12) >> 2);
	return (0);
}

int				num_args(unsigned int acb)
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

void			add_arg2(t_list *out, char *in, int *i, int type)
{
	int		j;
	int		val;
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
		val = in[*i] * 256 + in[*i + 1];
		val = (val < -256 ? val + 256 : val);
		value = ft_itoa(val);
		while (value[j] != '\0')
			out->str[out->num++] = value[j++];
		*i = *i + 2;
		free(value);
	}
}

void			add_arg3(t_list *out, char *in, int *i, int op)
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

int				add_arg(t_list *out, char *in, int *i, int op)
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
