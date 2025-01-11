/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 20:11:44 by suroh             #+#    #+#             */
/*   Updated: 2025/01/10 15:19:24 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	ft_is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (true);
	return (false);
}

bool	ft_is_separator(char c)
{
	if (c == '|' || c == '>' || c == '<' || c == '&')
		return (true);
	return (false);
}

char	*ft_store_quote(char *token_start, char **input)
{
	char	*quote_start;
	char	*quote_end;
	char	*quote;

	quote_start = token_start;
	quote_end = token_start + 1;
	while (*quote_end && *quote_end != *quote_start)
		quote_end++;
	if (*quote_end == '\0')
	{
		*input = NULL;
		return (quote_start);
	}
	quote = ft_strndup(token_start, quote_end - token_start + 1);
	*input = quote_end + 1;
	return (quote);
}

char	*ft_store_separator(char *token_start, char **input)
{
	char	*separator;
	size_t	s_len;

	if (*token_start == *(token_start + 1))
		s_len = 2;
	else
		s_len = 1;
	separator = ft_strndup(token_start, s_len);
	*input = token_start + s_len;
	return (separator);
}

void	ft_free_token_list(t_token_node *token_list)
{
	t_token_node	*temp;

	while (token_list != NULL)
	{
		temp = token_list;
		token_list = token_list->next;
		free(temp->token_value);
		free(temp);
	}
}
