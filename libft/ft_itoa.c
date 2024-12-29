/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:59:45 by suroh             #+#    #+#             */
/*   Updated: 2024/04/24 14:45:05 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_length_checker(int n)
{
	int			c;
	long int	numcheck;

	c = 0;
	numcheck = n;
	if (numcheck <= 0)
		c++;
	while (numcheck != 0)
	{
		numcheck = numcheck / 10;
		c++;
	}
	return (c);
}

char	*ft_itoa(int n)
{
	char		*s;
	char		mod;
	int			slen;
	long int	num;

	num = n;
	slen = ft_length_checker(n);
	s = (char *)ft_calloc(sizeof(char), (slen + 1));
	if (!s)
		return (NULL);
	s[slen--] = '\0';
	if (num == 0)
		s[0] = '0';
	if (num < 0)
	{
		s[0] = '-';
		num *= -1;
	}
	while (num != 0)
	{
		mod = (num % 10) + 48;
		num = num / 10;
		s[slen--] = mod;
	}
	return ((char *)s);
}

// int	main()
// {
// 	int	i = -2147483648;
// 	char	*s = ft_itoa(i);
// 	printf("%s\n", s);
// 	free(s);
// }