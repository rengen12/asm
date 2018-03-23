/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbuy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 13:20:23 by dbuy              #+#    #+#             */
/*   Updated: 2018/03/14 13:20:25 by dbuy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"

char	*valid(char *file, char *error, int display)
{
	int		fd;
	t_list	*src;
	char	*line;

	src = NULL;
	line = NULL;
	if (find_s(file) == 0)
		return (strconcat("Wrong file type ", file));
	if ((fd = open(file, O_RDONLY)) < 0)
		return (strconcat("Can't read source file ", file));
	while (get_next_line(fd, &line) > 0)
	{
		src = listadd(src, listn(line));
		free(line);
	}
	free(line);
	src = src_modif(src);
	if (empty(src) == 1)
		return (strconcat("Invalid file", ""));
	if ((error = test_code(src, error)))
		return (error);
	if ((error = create(src, file, display)) != NULL)
		clear_src(src);
	return (error == NULL ? clear_src(src) : error);
}

int		find_flag(int ac, char **av)
{
	int ret;
	int max;

	max = 255;
	ret = 0;
	ac--;
	while (ac > 0)
	{
		if (ft_strcmp(av[ac], "-h") == 0)
			ret = ret | (max & 1);
		else if (ft_strcmp(av[ac], "-l") == 0)
			ret = ret | (max & 2);
		else if (ft_strcmp(av[ac], "-a") == 0)
			ret = ret | (max & 4);
		else
		{
			if ((ret & 8) == 8)
				ret = ret | (max & 16);
			ret = ret | (max & 8);
			ret = ret | (ac << 5);
		}
		ac--;
	}
	return (ret);
}

char	*find_file(char **av, int flag)
{
	int i;

	i = flag >> 5;
	return (av[i]);
}

int		main(int ac, char **av)
{
	int		display;
	char	*file;
	char	*error;

	error = NULL;
	if (ac == 1 || ac > 5)
		return (print_usage());
	display = find_flag(ac, av);
	if ((display & 1) == 1)
		return (print_man(display));
	if ((display & 8) != 8)
		return (no_file(display));
	if ((display & 16) == 16)
		return (invalid_flags(display));
	if ((error = test_header(error)) != NULL)
		return (print_error(error, display));
	file = find_file(av, display);
	if ((error = valid(file, error, display)) != NULL)
		return (print_error(error, display));
	if ((display & 2) == 2)
		system("leaks asm");
	return (0);
}
