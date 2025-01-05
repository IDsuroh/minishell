/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:47:00 by suroh             #+#    #+#             */
/*   Updated: 2024/04/24 15:23:13 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	unsigned int	slen;
	char			*str;

	slen = ft_strlen(s);
	str = (char *)ft_calloc(sizeof(char), slen + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < slen)
	{
		str[i] = (*f)(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return ((char *)str);
}
// char	ft_convert(unsigned int index, char c)
// {
// 	(void)index;
// 	if (c >= 'a' && c <= 'z')
// 		c -= 32;
// 	else if (c >= 'A' && c <= 'Z')
// 		c += 32;
// 	return (c);
// }

// int	main()
// {
// 	char *s = "HELLO chinoca";
// 	char *result = ft_strmapi(s, &ft_convert);
// 	printf("Result: %s\n", result);
// 	free(result);
// 	return 0;
// }
