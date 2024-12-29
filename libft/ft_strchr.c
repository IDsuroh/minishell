/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:05:05 by suroh             #+#    #+#             */
/*   Updated: 2024/04/24 12:32:58 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != (char)c)
		s++;
	if (s[i] == (char)c)
		return ((char *)s);
	return (NULL);
}

// int	main()
// {
// 	printf("%s\n", ft_strchr("aaeaaaef", 'e'));
// }
