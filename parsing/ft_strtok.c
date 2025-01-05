/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 23:21:45 by suroh             #+#    #+#             */
/*   Updated: 2025/01/04 23:23:53 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parsing.h"

char	*ft_strtok(char *str, const char *delim)
{
	static char	*input = NULL;
	char		*token_start;
	char		*token_end;

	if (str != NULL)
		input = str;
	if (input == NULL)
		return (NULL);
	token_start = input;
	while (*token_start && ft_strchr(delim, *token_start))
		token_start++;
	if (*token_start == '\0')
		return (input = NULL);
	token_end = token_start;
	while (*token_end && !ft_strchr(delim, *token_end))
		token_end++;
	if (*token_end == '\0')
		input = NULL;
	else
	{
		*token_end = '\0';
		input = token_end + 1;
	}
	return (token_start);
}
