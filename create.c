/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbuy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 13:39:55 by dbuy              #+#    #+#             */
/*   Updated: 2018/03/14 13:39:57 by dbuy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

char	*make_filename(char *file)
{
	char	*ret;
	int		i;
	int		len;

	len = ft_strlen(file);
	i = -1;
	ret = (char*)malloc(ft_strlen(file) + 3);
	while (++i < len - 2)
		ret[i] = file[i];
	ret[i] = '.';
	ret[++i] = 'c';
	ret[++i] = 'o';
	ret[++i] = 'r';
	ret[++i] = '\0';
	return (ret);
}

void	print_success(int display, char *file, int fd)
{
	if ((display & 4) != 4 && fd > 0)
	{
		write(1, "Writing binary to file: ", 24);
		write(1, file, ft_strlen(file));
		write(1, "\n", 1);
	}
}

char	*free_ch_file(char *ch, char *file)
{
	free(ch);
	free(file);
	return ("");
}

char	*create(t_list *code, char *file, int display)
{
	char	*c;
	int		pos;
	int		fd;
	int		tmp;

	file = make_filename(file);
	c = (char*)malloc(CHAMP_MAX_SIZE + 99 + PROG_NAME_LENGTH + COMMENT_LENGTH);
	ft_bzero(c, CHAMP_MAX_SIZE + 100 + PROG_NAME_LENGTH + COMMENT_LENGTH);
	pos = init_header(c);
	if ((pos = init_name(c, pos, code)) == 0)
		return (free_ch_file(c, file));
	pos = init_comment(c, pos, code);
	tmp = pos;
	pos = first_trace(&c, pos, code, 1);
	if (pos == -1)
		return (free_ch_file(c, file));
	if ((display & 4) == 4)
		pos = first_trace(&c, PROG_NAME_LENGTH + COMMENT_LENGTH + 16, code, 2);
	fd = ((display & 4) != 4 ? open(file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR\
										| S_IWUSR | S_IRGRP | S_IROTH) : -2);
	add_size(c, pos - tmp);
	print_success(display, file, fd);
	write(fd, c, pos);
	free_ch_file(c, file);
	return (NULL);
}
