/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_utils_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:50:30 by suroh             #+#    #+#             */
/*   Updated: 2025/01/09 20:31:30 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*mem;
	size_t	len;

	len = ft_strlen(s);
	if (n < len)
		len = n;
	mem = malloc((len * sizeof(char)) + 1);
	if (!mem)
		return (NULL);
	ft_memcpy(mem, s, len);
	mem[len] = '\0';
	return (mem);
}
