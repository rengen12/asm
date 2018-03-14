/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbuy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 17:46:19 by dbuy              #+#    #+#             */
/*   Updated: 2018/02/22 19:28:48 by dbuy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*ft_buff_offset(char *buff)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (i < BUFF_SIZE && buff[i] != '\n' && buff[i] != '\0')
		i++;
	if (buff[i] == '\n')
		count++;
	if (i != BUFF_SIZE)
	{
		ft_memmove(buff, buff + i + 1, BUFF_SIZE - i);
		buff[BUFF_SIZE - i - 1] = '\0';
	}
	if (i == BUFF_SIZE || count == 0 || buff[0] == '\0')
		ft_bzero(buff, BUFF_SIZE);
	return (buff);
}

char	*ft_realloc(char *line)
{
	int		i;
	char	*new;

	if (!line)
		return (NULL);
	i = ft_strlen(line);
	if (!(new = (char*)malloc(i + 1 + BUFF_SIZE)))
		return (NULL);
	ft_bzero(new, i + 1 + BUFF_SIZE);
	ft_memcpy(new, line, i);
	free(line);
	return (new);
}

int		ft_convert(char *line, char *buff, int n)
{
	int i;
	int ret;
	int pos;
	int b;

	ret = 0;
	b = 0;
	if (!line)
		return (3);
	i = ft_strlen(line);
	pos = i;
	while (b < BUFF_SIZE && buff[b] != '\n' && buff[b] != '\0')
		line[i++] = buff[b++];
	line[i] = '\0';
	if (buff[i] == '\n')
		ret = 1;
	if (buff[i] == '\0' && n == 0)
		ret = 0;
	if (i == BUFF_SIZE)
		ret = 1;
	buff = ft_buff_offset(buff);
	if (b == BUFF_SIZE)
		ret = 2;
	return (ret);
}

int		ft_find(t_files *files, const int fd)
{
	int i;

	i = 0;
	while (files[i].active == 1)
	{
		if (files[i].fd == fd)
			return (i);
		i++;
	}
	if (!files)
		if (!(files = (t_files*)malloc(sizeof(t_files))))
			return (-1);
	files[i].fd = fd;
	files[i].active = 1;
	if (!(files[i].buff = (char*)malloc(BUFF_SIZE)))
		return (-1);
	ft_bzero(files[i].buff, BUFF_SIZE);
	return (i);
}

int		get_next_line(const int fd, char **line)
{
	static t_files	files[2000];
	int				index;
	int				n;
	int				flag;
	int				offset;

	n = -1;
	if (!line || fd < 0 || !(line[0] = (char*)malloc(BUFF_SIZE + 1)))
		return (-1);
	ft_bzero(line[0], BUFF_SIZE + 1);
	if ((index = ft_find(files, fd)) < 0)
		return (-1);
	if ((files[index].buff)[0] != '\0')
		if ((n = ft_convert(line[0], files[index].buff, 0) == 1))
			return (1);
	line[0] = ft_realloc(line[0]);
	while ((flag = read(fd, files[index].buff, BUFF_SIZE)) > 0)
	{
		if ((n = ft_convert(line[0], files[index].buff, offset) < 2))
			return (1);
		offset = offset + BUFF_SIZE;
		if (!(line[0] = ft_realloc(line[0])))
			return (-1);
	}
	return (n == -1 ? flag : 1);
}
