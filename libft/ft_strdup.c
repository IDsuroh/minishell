/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:31:21 by suroh             #+#    #+#             */
/*   Updated: 2024/05/04 14:49:52 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*mem;
	size_t	len;

	len = ft_strlen(s);
	mem = malloc((len * sizeof(char)) + 1);
	if (!mem)
		return (NULL);
	mem[len] = '\0';
	while (len--)
		mem[len] = s[len];
	return (mem);
}

// int	main()
// {
// 	const char	*str = "originalstring";
// 	const char	*new = ft_strdup(str);
// 	printf("%s\n", new);
// }