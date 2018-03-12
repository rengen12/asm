//
// Created by Denis BUY on 3/4/18.
//

#include "asm.h"

size_t	ft_strlen(char *a)
{
	size_t i;

	if (!a)
		return (0);
	i = 0;
	while (a[i] != '\0')
		i++;
	return (i);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*a1;
	char	*a2;

	if (n == 0 || dest == src)
		return (dest);
	a1 = (char*)dest;
	a2 = (char*)src;
	while (n-- > 0)
		*a1++ = *a2++;
	return (dest);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*c1;
	unsigned char	*c2;

	c1 = (unsigned char*)dest;
	c2 = (unsigned char*)src;
	if (c2 < c1)
		while ((int)n-- > 0)
			*(c1 + n) = *(c2 + n);
	else
		ft_memcpy(c1, c2, n);
	return (dest);
}

long		ft_atoi(const char *str)
{
	unsigned long	res;
	unsigned long	restemp;
	long			i;
	long			sign;

	i = 0;
	res = 0;
	sign = 1;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
//	if (str[i] < 48 || str[i] > 57)
//		return (-1);
	while (str[i] >= 48 && str[i] <= 57)
	{
		restemp = res * 10 + str[i++] - 48;
		if (restemp < res || restemp > 4294967295)
			return (4294967295);
		res = restemp;
	}
	return (res * sign);
}

void	ft_bzero(void *b, size_t len)
{
	unsigned char *cur;

	if (len == 0)
		return ;
	cur = (unsigned char *)b;
	while (len--)
	{
		*cur = 0;
		if (len)
			cur++;
	}
}