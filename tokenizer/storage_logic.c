/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   storage_logic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:33:07 by suroh             #+#    #+#             */
/*   Updated: 2025/01/15 20:40:48 by suroh            ###   ########.fr       */
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
	ft_strlcpy(token, token_start, i);
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
