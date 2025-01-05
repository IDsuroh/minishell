/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 18:03:23 by suroh             #+#    #+#             */
/*   Updated: 2025/01/04 21:06:04 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_single_quote(const char *input, size_t *i)
{
	char	*result;
	size_t	start;
	size_t	len;

	start = ++(*i);
	while (input[*i] != '\0' && input[*i] != '\'')
		(*i)++;
	if (input[*i] == '\0')
	{
		perror("minishell: syntax error: single quote\n");
		return (NULL);
	}
	len = *i - start;
	result = ft_strndup(input + start, len);
	(*i)++;
	return (result);
}
