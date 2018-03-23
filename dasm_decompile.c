/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dasm_decomplile.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbuy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 17:27:05 by dbuy              #+#    #+#             */
/*   Updated: 2018/03/14 17:27:06 by dbuy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"

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

void	decompile2(char *file, t_list *out, int flag)
{
	int		fd;
	int		i;
	t_list	*tmp;
	char	*start;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR\
														| S_IRGRP | S_IROTH);
	tmp = out;
	i = 0;
	write(1, "writing sourse code to file: ", 29);
	write(1, file, ft_strlen(file));
	write(1, "\n", 1);
	while (tmp)
	{
		if ((flag & 8) == 8 && i++ > 2)
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
