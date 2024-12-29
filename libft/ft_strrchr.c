/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:18:23 by suroh             #+#    #+#             */
/*   Updated: 2024/05/04 16:41:29 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	flen;

	flen = ft_strlen(s);
	while (flen >= 0)
	{
		if (s[flen] == (char)c)
			return ((char *)(s + flen));
		flen--;
	}
	return (NULL);
}

// int	main()
// {
// 	printf("%s\n", ft_strrchr("aef", 'e'));
// }
