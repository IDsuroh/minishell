/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   storage_logic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:33:07 by suroh             #+#    #+#             */
/*   Updated: 2025/03/20 20:26:48 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*store_quote(char *token_start, char *token_end, char **saveptr)
{
	char	*token;
	int		i;

	token_end = token_start + 1;
	i = 1;
	while (*token_end && *token_end != *token_start)
	{
		token_end++;
		i++;
	}
	if (*token_end == *token_start)
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

char	*store_separator(char *token_start, char *token_end, char **saveptr)
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

char	*store_var(char *token_start, char *token_end, char **saveptr)
{
	char	*token;
	int		i;

	
	token_end = token_start + 1;
	i = 1;
	if (*token_end == '?' || *token_end == '$')
		handle_short_var(&token_end, &i);
	else
		handle_normal_var(&token_end, &i);
	token = (char *)malloc(sizeof(char) * (i + 1));
	if (!token)
		return (NULL);
	ft_strlcpy(token, token_start, i + 1);
	*saveptr = token_end;
	return (token);
}

char	*store_string(char *token_start, char *token_end, char **saveptr)
{
	char	*token;
	int		i;

	token_end = token_start + 1;
	i = 1;
	while (*token_end && !is_delimiter(*token_end)
		&& '$' != *token_end && !is_separator(*token_end))
	{
		if ((*token_end == '\'' || *token_end == '\"')
			&& is_quote_closed(token_end))
			break ;
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

/*
 * char	*store_quote(char *token_start, char *token_end, char **saveptr)
 * Purpose:
 *		This function extracts a token that starts with a quote character
 *		(either single ' or double ").
 *
 * char	*store_separator(char *token_start, char *token_end, char **saveptr)
 * Purpose:
 * 		This function extracts a separator token, which may be a
 * 		single-character or a double-character separator
 * 		(e.g., redirection operators like '>', '>>', '|', '||', '&&').
 *
 * char	*store_var(char *token_start, char *token_end, char **saveptr)
 * Purpose:
 * 		This function extracts a variable token. Variable tokens start
 * 		with the $ symbol and may be followed by a special character (? or $)
 * 		or a normal variable name.
 *
 * 			*file to check for this function:
 * 				./storage_logic_helper.c
 *
 * char	*store_string(char *token_start, char *token_end, char **saveptr)
 * Purpose:
 * 		This function extracts a "string" token, which is a sequence of
 * 		characters that is not interrupted by delimiters, a variable symbol ($),
 * 		or a separator.
 *
 * 		There’s a special check: if it encounters a quote character (' or ")
 * 		that is properly closed (as determined by is_quote_closed), it stops
 * 		scanning—this ensures that a quote within a string is handled separately.
 *
 *			*next file to check:
 *				./create_node_list.c
 */
