/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbuy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 13:20:23 by dbuy              #+#    #+#             */
/*   Updated: 2018/03/14 13:20:25 by dbuy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"

int		print_usage(void)
{
	char *a;
	char *b;
	char *d;
	char *c;

	a = "Usage: ./asm [-a] | [-h] | [-l] <sourcefile.s>\n-a: Instead of";
	b = " creating binary displays step-by-step coding process\n";
	c = "-h: help, no output binary file, flag [-a] ignored\n";
	d = "-l: leaks\n";
	write(1, a, ft_strlen(a));
	write(1, b, ft_strlen(b));
	write(1, c, ft_strlen(c));
	write(1, d, ft_strlen(d));
	return (0);
}

int		print_error(char *error, int display)
{
	write(1, error, ft_strlen(error));
	write(1, "\n", 1);
	if ((display & 2) == 2)
		system("leaks asm");
	return (1);
}

int		print_man(int display)
{
	int		fd;
	char	*er;
	char	*man;

	man = NULL;
	er = "MAN file <asm.man> is missing\n";
	fd = open("asm.man", O_RDONLY);
	if (fd < 0)
	{
		write(1, er, ft_strlen(er));
		return (-1);
	}
	while (get_next_line(fd, &man))
	{
		write(1, man, ft_strlen(man));
		write(1, "\n", 1);
		free(man);
	}
	free(man);
	if ((display & 2) == 2)
		system("leaks asm");
	return (0);
}

int		invalid_flags(int display)
{
	char	*er;

	er = "Invalid arguments, run \"./asm\" for more information\n";
	write(1, er, ft_strlen(er));
	if ((display & 2) == 2)
		system("leaks asm");
	return (-1);
}

int		no_file(int display)
{
	char	*er;

	er = "Cant find file among arguments\n";
	write(1, er, ft_strlen(er));
	if ((display & 2) == 2)
		system("leaks asm");
	return (-1);
}
