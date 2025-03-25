/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 18:43:24 by suroh             #+#    #+#             */
/*   Updated: 2025/03/25 21:02:00 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*extract_token(char *token_start, char *token_end, char **saveptr)
{
	char	*token;

	if ((is_quote(*token_start) && is_quote_closed(token_start))
		|| (is_var_squote(token_start) || is_var_dquote(token_start)))
		token = store_quote(token_start, token_end, saveptr);
	else if (is_separator(*token_start))
		token = store_separator(token_start, token_end, saveptr);
	else if (is_var(token_start))
		token = store_var(token_start, token_end, saveptr);
	else
		token = store_string(token_start, token_end, saveptr);
	return (token);
}

char	*ft_strtok_r(char *str, char **saveptr, char **token_start_ptr)
{
	char	*token_start;
	char	*token_end;
	char	*token;

	if (str != NULL)
		*saveptr = str;
	while (*saveptr && **saveptr && is_delimiter(**saveptr))
		(*saveptr)++;
	if (*saveptr == NULL || **saveptr == '\0')
		return (NULL);
	token_start = *saveptr;
	if (token_start_ptr)
		*token_start_ptr = token_start;
	token_end = token_start;
	token = extract_token(token_start, token_end, saveptr);
	if (token == NULL)
		return (NULL);
	if (*saveptr && **saveptr == '\0')
		*saveptr = NULL;
	return (token);
}

char	**tokenize_input(char *input, int token_count, int *pos)
{
	char	**token_storage;
	char	*token;
	char	*saveptr;
	char	*token_start;
	int		i;

	saveptr = input;
	token_storage = ft_calloc(token_count + 1, sizeof(char *));
	if (!token_storage)
		return (NULL);
	i = 0;
	token = ft_strtok_r(input, &saveptr, &token_start);
	while (token != NULL && i < token_count)
	{
		pos[i] = (int)(token_start - input);
		token_storage[i] = token;
		token = ft_strtok_r(NULL, &saveptr, &token_start);
		i++;
	}
	token_storage[i] = NULL;
	return (token_storage);
}
