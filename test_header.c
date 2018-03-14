/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_header.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbuy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 17:20:32 by dbuy              #+#    #+#             */
/*   Updated: 2018/03/14 17:20:33 by dbuy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

char	*test_label_char(char *error)
{
	int i;

	i = 0;
	if (LABEL_CHAR == 32 || (LABEL_CHAR >= 9 && LABEL_CHAR <= 13))
		error = "LABEL_CHAR == whitespace";
	else if (LABEL_CHAR == DIRECT_CHAR)
		error = "COMMENT_CHAR == DIRECT_CHAR";
	else if (LABEL_CHAR == SEPARATOR_CHAR)
		error = "COMMENT_CHAR == SEPARATOR_CHAR";
	while (LABEL_CHARS[i] != '\0')
		if (LABEL_CHAR == LABEL_CHARS[i++])
			error = "LABEL_CHAR == one of LABEL_CHARS";
	return (error);
}

char	*test_direct_char(char *error)
{
	int i;

	i = 0;
	if (DIRECT_CHAR == 32 || (DIRECT_CHAR >= 9 && DIRECT_CHAR <= 13))
		error = "LABEL_CHAR == whitespace";
	else if (DIRECT_CHAR == SEPARATOR_CHAR)
		error = "COMMENT_CHAR == SEPARATOR_CHAR";
	while (LABEL_CHARS[i] != '\0')
		if (DIRECT_CHAR == LABEL_CHARS[i++])
			error = "DIRECT_CHAR == one of LABEL_CHARS";
	return (error);
}

char	*test_separator_char(char *error)
{
	int i;

	i = 0;
	if (SEPARATOR_CHAR == 32 || (SEPARATOR_CHAR >= 9 && DIRECT_CHAR <= 13))
		error = "LABEL_CHAR == whitespace";
	while (LABEL_CHARS[i] != '\0')
		if (SEPARATOR_CHAR == LABEL_CHARS[i++])
			error = "SEPARATOR_CHAR == one of LABEL_CHARS";
	return (error);
}

char	*test_comment_char(char *error)
{
	int i;

	i = 0;
	if (COMMENT_CHAR == 32 || (COMMENT_CHAR >= 9 && COMMENT_CHAR <= 13))
		error = "LABEL_CHAR == whitespace";
	else if (COMMENT_CHAR == LABEL_CHAR)
		error = "COMMENT_CHAR == LABEL_CHAR";
	else if (COMMENT_CHAR == DIRECT_CHAR)
		error = "COMMENT_CHAR == DIRECT_CHAR";
	else if (COMMENT_CHAR == SEPARATOR_CHAR)
		error = "COMMENT_CHAR == SEPARATOR_CHAR";
	while (LABEL_CHARS[i] != '\0')
		if (COMMENT_CHAR == LABEL_CHARS[i++])
			error = "COMMENT_CHAR == one of LABEL_CHARS";
	return (error);
}

char	*test_header(char *error)
{
	int		i;
	char	*a;
	char	*b;

	i = -1;
	a = "FILE IS CORRUPTED DUE TO INVALID HEADER FILE";
	b = ", please check and recompile:\n";
	error = test_comment_char(error);
	error = test_label_char(error);
	error = test_direct_char(error);
	error = test_separator_char(error);
	while (LABEL_CHARS[++i] != '\0')
		if (LABEL_CHARS[i] == 32 || (LABEL_CHARS[i] > 8 && LABEL_CHARS[i] < 14))
			error = "One of LABEL_CHARS == whitespace";
	if (error)
	{
		write(1, a, ft_strlen(a));
		write(1, b, ft_strlen(b));
	}
	return (error);
}
