/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:46:09 by suroh             #+#    #+#             */
/*   Updated: 2024/11/12 21:39:17 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*mem;
	size_t	slen;
	size_t	value;

	slen = ft_strlen(s);
	value = 0;
	if (!s)
		return (NULL);
	if (start <= slen)
		value = slen - start;
	if (value > len)
		value = len;
	mem = malloc(sizeof(char) * (value + 1));
	if (!mem)
		return (NULL);
	ft_memmove(mem, s + start, value);
	mem[value] = '\0';
	return ((char *)mem);
}

// int	main()
// {
// 	printf("%s\n", ft_substr("From here", 5, 3));
// 	printf("%s\n", ft_substr("", 0, 0));
// 	printf("%s\n", ft_substr("hola", 2, 30));
// 	printf("%s\n", ft_substr("hola", 3, 2));
// 	printf("%s\n", ft_substr("hola", 4, 20));
// }
