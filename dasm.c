/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dasm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbuy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 17:27:05 by dbuy              #+#    #+#             */
/*   Updated: 2018/03/14 17:27:06 by dbuy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"

char	*find_cor(char *file, int flag, char **av)
{
	int		i;
	char	*ret;

	i = (int)ft_strlen(file);
	if (i < 4)
		return (NULL);
	if (file[i - 1] == 'r' && file[i - 2] == 'o' && file[i - 3] == 'c' &&\
															file[i - 4] == '.')
	{
		if ((flag >> 10) > 0)
		{
			ret = (char*)malloc(ft_strlen(av[flag >> 10]) + 1);
			ret = ft_strcpy(ret, av[flag >> 10]);
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

int		is_label_char(char c)
{
	char	*test;
	int		i;

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

int		main(int ac, char **av)
{
	int		fd;
	ssize_t	pos;
	int		flag;
	char	*file;
	char	*in;

	flag = find_flag_dasm(ac, av);
	if (ac == 1 || ac > 7)
		return (usage());
	file = av[(flag & 896) >> 7];
	if ((flag & 16) != 16)
		return (cant_find_file(flag));
	if (((fd = open(file, O_RDONLY)) < 3))
		return (dasm_no_file(file, flag));
	if (!(file = get_name(file, flag, av)))
		return (wrong_file_name(av[1], flag));
	in = (char *)malloc(10000);
	pos = read(fd, in, 10000);
	if (pos < COMMENT_LENGTH + PROG_NAME_LENGTH + 10 || pos == 10000)
		return (invalid_file());
	decompile(in, (int)pos - 1, file, flag);
	if ((flag & 2) == 2)
		system("leaks dasm");
	return (0);
}
