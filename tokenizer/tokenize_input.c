/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 18:43:24 by suroh             #+#    #+#             */
/*   Updated: 2025/01/13 18:28:23 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*store_quote(char *token_start, char *token_end, char **saveptr)
{
	char	*token;
	int		i;

	token_end = token_start + 1;
	i = 1;
	while (*token_end && !is_quote(*token_end))
	{
		token_end++;
		i++;
	}
	if (is_quote(*token_end))
	{
		token_end++;
		i++;
	}
	token = (char *)malloc(sizeof(char) * (i + 1));
	if (!token)
		return (NULL);
	ft_strlcpy(token, token_start, i + 1);
	*saveptr = token_end;
	return (token);
}

static char	*store_separator(char *token_start, char *token_end, char **saveptr)
{
	char	*token;
	int		i;

	i = 1;
	token_end = token_start + 1;
	if (*token_start == *token_end)
		i = 2;
	token = (char *)malloc(sizeof(char) * (i + 1));
	if (!token)
		return (NULL);
	if (i == 1)
	{
		token[0] = *token_start;
		token[1] = '\0';
		*saveptr = token_start + 1;
	}
	else
	{
		token[0] = *token_start;
		token[1] = *token_start;
		token[2] = '\0';
		*saveptr = token_start + 2;
	}
	return (token);
}

static char	*store_string(char *token_start, char *token_end, char **saveptr)
{
	char	*token;
	int		i;

	token_end = token_start;
	i = 0;
	while (*token_end && !is_delimiter(*token_end)
		&& !is_separator(*token_end) && !is_quote(*token_end))
	{
		token_end++;
		i++;
	}
	token = (char *)malloc(sizeof(char) * (i + 1));
	if (!token)
		return (NULL);
	ft_strlcpy(token, token_start, i + 1);
	*saveptr = token_end;
	return (token);
}

char	*ft_strtok_r(char *str, char **saveptr)
{
	char	*token_start;
	char	*token_end;
	char	*token;

	if (str != NULL)
		*saveptr = str;
	if (*saveptr == NULL)
		return (NULL);
	while (**saveptr && is_delimiter(**saveptr))
		(*saveptr)++;
	if (**saveptr == '\0')
		return (NULL);
	token_start = *saveptr;
	token_end = token_start;
	if (is_quote(*token_start))
		token = store_quote(token_start, token_end, saveptr);
	else if (is_separator(*token_start))
		token = store_separator(token_start, token_end, saveptr);
	else
		token = store_string(token_start, token_end, saveptr);
	if (token == NULL)
		return (NULL);
	if (*saveptr && **saveptr == '\0')
		*saveptr = NULL;
	return (token);
}

char	**tokenize_input(char *input, int token_count)
{
	char	**token_storage;
	char	*token;
	char	*saveptr;
	int		i;

	saveptr = NULL;
	token_storage = (char **)malloc(sizeof(char *) * (token_count + 1));
	if (!token_storage)
		return (NULL);
	i = 0;
	token = ft_strtok_r(input, &saveptr);
	while (token != NULL && i < token_count)
	{
		token_storage[i++] = token;
		token = ft_strtok_r(NULL, &saveptr);
	}
	token_storage[i] = NULL;
	while (token != NULL)
	{
		free(token);
		token = ft_strtok_r(NULL, &saveptr);
	}
	return (token_storage);
}

/*ft_strtok_r keeps an internal “state” (via saveptr), you need
 * to keep calling it in order to retrieve all remaining tokens.
 * Even though you’ve already decided not to store any more tokens
 * (because you hit token_count), those extra tokens still exist
 * in the input string.
 * Each call to ft_strtok_r(NULL, &saveptr) returns the next token
 * that was allocated internally (by store_string, store_quote, etc.).
 * If you didn’t call ft_strtok_r(NULL, &saveptr) again in that
 * leftover loop, you’d never get those extra pointers back—and
 * thus would never have a chance to free them, causing a memory leak.
 * For example, the last remaining '\0'.
 */
