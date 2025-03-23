/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 18:16:37 by suroh             #+#    #+#             */
/*   Updated: 2025/03/23 19:48:09 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	copy_quoted_segment(const char *s, char quote, char *dest,
			t_indices *idx)
{
	idx->src++;
	while (s[idx->src] && s[idx->src] != quote)
	{
		dest[idx->dest++] = s[idx->src];
		idx->src++;
	}
	if (s[idx->src] == quote)
		idx->src++;
}

static char	*remove_quotes(char *s)
{
	char		*result;
	int			len;
	t_indices	idx;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	idx.src = 0;
	idx.dest = 0;
	while (s[idx.src])
	{
		if ((is_quote_closed((char *)(s + idx.src)) && is_quote(s[idx.src])))
			copy_quoted_segment(s, s[idx.src], result, &idx);
		else
			result[idx.dest++] = s[idx.src++];
	}
	result[idx.dest] = '\0';
	return (result);
}

static void	concatenate_adjacent_tokens(t_token_node **tokens, int i)
{
	int		j;
	char	*temp;

	while (tokens[i + 1] && tokens[i + 1]->adjacent)
	{
		temp = ft_strjoin(tokens[i]->token_value, tokens[i + 1]->token_value);
		if (!temp)
			return ;
		free(tokens[i]->token_value);
		tokens[i]->token_value = temp;
		free(tokens[i + 1]->token_value);
		free(tokens[i + 1]);
		j = i + 1;
		while (tokens[j] != NULL)
		{
			tokens[j] = tokens[j + 1];
			j++;
		}
	}
}

void	process_quote_rem_and_concat(t_token_node **tokens)
{
	int		i;
	char	*clean;

	if (!tokens)
		return ;
	i = -1;
	while (tokens[++i] != NULL)
	{
		clean = remove_quotes(tokens[i]->token_value);
		free(tokens[i]->token_value);
		tokens[i]->token_value = clean;
	}
	i = -1;
	while (tokens[++i] != NULL)
		concatenate_adjacent_tokens(tokens, i);
}
