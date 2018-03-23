/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dasm_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbuy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 17:27:05 by dbuy              #+#    #+#             */
/*   Updated: 2018/03/14 17:27:06 by dbuy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"

int		usage(void)
{
	char *a;
	char *b;
	char *c;
	char *d;
	char *e;

	a = "./dasm [-l], [-m], [f], [o] <champion.cor> [output file]\n";
	b = "[-l]: leaks\n";
	c = "[-m]: display labels\n";
	d = "[-f]: write output to file *.s or user-defined file\n";
	e = "[-o]: display offset with reference to binary\n";
	write(1, a, ft_strlen(a));
	write(1, b, ft_strlen(b));
	write(1, c, ft_strlen(c));
	write(1, d, ft_strlen(d));
	write(1, e, ft_strlen(e));
	return (1);
}

int		dasm_no_file(char *file, int flag)
{
	char *a;

	a = "Cant read file: ";
	write(1, a, ft_strlen(a));
	write(1, file, ft_strlen(file));
	write(1, "\n", 1);
	if ((flag & 2) == 2)
		system("leaks dasm");
	return (1);
}

int		cant_find_file(int flag)
{
	char *a;

	a = "NULL FILE GIVEN\n";
	write(1, a, ft_strlen(a));
	if ((flag & 2) == 2)
		system("leaks dasm");
	return (1);
}

int		wrong_file_name(char *file, int flag)
{
	char *a;

	a = "Wrong file name: ";
	write(1, a, ft_strlen(a));
	write(1, file, ft_strlen(file));
	write(1, "\n", 1);
	if ((flag & 2) == 2)
		system("leaks dasm");
	return (1);
}

int		invalid_file(void)
{
	char *er;

	er = "Invalid file\n";
	write(1, er, ft_strlen(er));
	return (1);
}
