/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_utils_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 18:42:39 by suroh             #+#    #+#             */
/*   Updated: 2025/01/09 22:23:26 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	set_null_char(char **input, char *token_end)
{
	if (*token_end == '\0')
		*input = NULL;
	else
	{
		*token_end = '\0';
		*input = token_end + 1;
	}
}

static char	*return_before_separator(char *token_start, char *token_end,
	char **input)
{
	char	*tmp;

	tmp = ft_strdup(token_end);
	*token_end = '\0';
	*input = tmp;
	return (token_start);
}

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
	if (ft_is_quote(*token_start))
		return (ft_store_quote(token_start, &input));
	else if (ft_is_separator(*token_start))
		return (ft_store_separator(token_start, &input));
	token_end = token_start;
	while (*token_end && !ft_strchr(delim, *token_end)
		&& !ft_is_separator(*token_end))
		token_end++;
	if (ft_is_separator(*token_end))
		return (return_before_separator(token_start, token_end, &input));
	set_null_char(&input, token_end);
	return (token_start);
}

int	ft_strtok_count(char *str, char *delim)
{
	int		count;
	char	*tmp;
	char	*token;

	count = 0;
	tmp = ft_strdup(str);
	token = ft_strtok(tmp, delim);
	while (token != NULL)
	{
		count++;
		token = ft_strtok(NULL, delim);
	}
	free(tmp);
	return (count);
}
