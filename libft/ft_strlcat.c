/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:30:33 by suroh             #+#    #+#             */
/*   Updated: 2024/04/24 12:55:53 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	destlen;
	size_t	srclen;

	destlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	if (!dst && size == 0)
		return (srclen);
	if (size <= destlen)
		return (srclen + size);
	i = 0;
	while (destlen + i < size - 1 && src[i] != 0)
	{
		dst[destlen + i] = src[i];
		i++;
	}
	dst[destlen + i] = '\0';
	return (destlen + srclen);
}

// int	main()
// {
// 	char	dst[10] = "this";
// 	char	src[5] = "that";
// 	printf("%zu\n%s\n", ft_strlcat(dst, src, 10), dst);
// 	printf("%zu\n", ft_strlen(src));
// }
