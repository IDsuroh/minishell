/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 23:13:49 by suroh             #+#    #+#             */
/*   Updated: 2025/01/04 23:44:39 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*mem;
	size_t	len;

	len = n;
	mem = malloc((len * sizeof(char)) + 1);
	if (!mem)
		return (NULL);
	mem[len] = '\0';
	while (len--)
		mem[len] = s[len];
	return (mem);
}
