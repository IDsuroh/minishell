/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   storage_logic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:33:07 by suroh             #+#    #+#             */
/*   Updated: 2025/01/18 20:51:55 by suroh            ###   ########.fr       */
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
	{
		token_end++;
		i = 2;
	}
	else
	{
		while (*token_end && !is_separator(*token_end)
			&& !is_delimiter(*token_end))
		{
			token_end++;
			i++;
		}
	}
	token = (char *)malloc(sizeof(char) * (i + 1));
	if (!token)
		return (NULL);
	ft_strlcpy(token, token_start, i + 1);
	*saveptr = token_end;
	return (token);
}

char	*store_fake_var(char *token_start, char *token_end, char **saveptr)
{
	char	*token;
	char	*tmp;
	int		count;

	token_end = token_start;
	count = 0;
	token = NULL;
	tmp = NULL;
	tmp = tmp_fake_var(token_start, &token_end);
	if (!tmp)
		return (NULL);
	count = fake_var_len(tmp);
	token = (char *)malloc(sizeof(char) * (count + 1));
	if (!token)
	{
		free(tmp);
		return (NULL);
	}
	token = epur_fake_var(token, tmp);
	free(tmp);
	*saveptr = token_end;
	return (token);
}

char	*store_string(char *token_start, char *token_end, char **saveptr)
{
	char	*token;
	int		i;

	token_end = token_start + 1;
	i = 1;
	while (*token_end && !is_delimiter(*token_end) && !is_var(token_end)
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

//All of these functions return token and saves the next part of
//the input string to saveptr. The token is stored in a string and
//returned to the tokenize_input function.
//
//store_quote:		' or "
//	- Any string the starts with a quote and ends with
//		a quote or a '\0'.
//
//store_separator:	|, >, <, &
//	- Any string that is a separator or a double separator.
//
//store_var:		$
//	- Any string that starts with a $ and ends with a separator
//		or a delimiter.
//	- If the string is $? or $$, the token will be 3 characters
//		long with a '\0'.
//
//store_string:
//	- Any string that is not a quote, separator, variable,
//		that ends with a delimiter, a quote, a separator, a variable.
//
//store_fake_var:	$ (with whitespaces) content
//	- Any string that starts with a $ and continued by multiple or
//		single whitespaces then ends with a separator or a '\0'.
//	- This function needs a lot of other helper functions due to
//		the complexity of the category "fake variable".
//
//next file to read: env_storage_helpers.c
