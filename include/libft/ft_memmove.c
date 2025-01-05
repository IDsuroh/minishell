/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:38:09 by suroh             #+#    #+#             */
/*   Updated: 2024/04/24 12:41:30 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*s;
	unsigned char	*d;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (!dest && !src)
		return (NULL);
	if (d > s)
		while (n--)
			d[n] = s[n];
	else
		ft_memcpy(dest, src, n);
	return (dest);
}

// int	main()
// {
// 	char	*s = "string";
// 	char	d[256] = "ingstr"; 
// 	ft_memmove(d, s, 15);
// 	printf("%s\n", d);
// }
