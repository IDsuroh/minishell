/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:46:48 by suroh             #+#    #+#             */
/*   Updated: 2024/05/04 17:05:37 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*mem;

	mem = malloc(nmemb * size);
	if (!mem)
		return (NULL);
	ft_bzero(mem, nmemb * size);
	return (mem);
}

// int	main()
// {
//  	char	*str1;
//  	str1 = ft_calloc(10, sizeof(int));
//  	printf("%s\n", str1);
// 	ft_memmove(str1, "Its a long string", sizeof(int) * 10);
// 	printf("%s\n", str1);
// 	free(str1);
// }