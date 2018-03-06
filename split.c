//
// Created by Denis BUY on 3/4/18.
//

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbuy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 10:44:00 by dbuy              #+#    #+#             */
/*   Updated: 2018/02/22 19:24:21 by dbuy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int				ft_word_count(char const *s, char c)
{
	int i;
	int len;

	i = 0;
	len = 0;
	if (s[0] == '\0')
		return (0);
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && s[i] == c)
			i++;
		if (s[i] != c && s[i] != '\0')
		{
			len++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
	}
	return (len);
}

static int		ft_getnextword(char const *s, char c, int j)
{
	int len;

	len = 0;
	while (s[j] != '\0' && s[j] == c)
		j++;
	while (s[j] != '\0' && s[j] != c)
	{
		j++;
		len++;
	}
	return (len + 1);
}

char			**ft_strsplitfree(char **a, int i)
{
	while (i - 1 >= 0)
	{
		free(a[i - 1]);
		i--;
	}
	free(a);
	a = NULL;
	return (a);
}

char			**ft_strsplit(char const *s, char c)
{
	int		i;
	int		j;
	int		b;
	char	**a;
	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	if (!(a = (char**)malloc(sizeof(char*) * (ft_word_count(s, c) + 1))))
		return (NULL);
	while (i < (ft_word_count(s, c)))
	{
		b = 0;
		if (!(a[i] = (char*)malloc(ft_getnextword(s, c, j))))
			return (ft_strsplitfree(a, i));
		while (s[j] != '\0' && s[j] == c)
			j++;
		while (s[j] != '\0' && s[j] != c)
			a[i][b++] = s[j++];
		a[i++][b] = '\0';
	}
	a[i] = 0;
	return (a);
}
