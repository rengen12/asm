/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbuy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 18:58:32 by dbuy              #+#    #+#             */
/*   Updated: 2018/03/14 18:58:34 by dbuy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char	*ft_trans(char *a, int n, int index)
{
	int x;

	x = n % 10;
	if (x < 0)
		x = -x;
	a[index] = (char)((x) + 48);
	if (index > 0)
		a = ft_trans(a, n / 10, index - 1);
	if (n < 0)
		a[0] = '-';
	return (a);
}

char		*ft_itoa(int n)
{
	char	*a;
	int		len;
	int		nc;

	nc = n;
	len = 0;
	if (n < 0)
		len++;
	while ((nc / 10) != 0)
	{
		nc = nc / 10;
		len++;
	}
	if (!(a = (char*)malloc(sizeof(char) * (len + 2))))
		return (NULL);
	a = ft_trans(a, n, len);
	a[len + 1] = '\0';
	if (n == 0)
		a[0] = '0';
	return (a);
}
