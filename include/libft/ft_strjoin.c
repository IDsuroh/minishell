/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:05:32 by suroh             #+#    #+#             */
/*   Updated: 2024/04/23 09:29:41 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*mem;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	mem = malloc((ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!mem)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		mem[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		mem[i] = s2[j];
		i++;
		j++;
	}
	mem[i] = '\0';
	return (mem);
}

// int	main(void)
// {
// 	char	*str = ft_strjoin("this", "thats");
// 	printf("%s\n", str);
// 	return (0);
// }
