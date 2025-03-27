/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 18:16:37 by suroh             #+#    #+#             */
/*   Updated: 2025/03/27 20:42:31 by suroh            ###   ########.fr       */
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

static void	processed_quote_flag(char *src, char *dest, t_indices *idx,
		t_token_node *token)
{
	while (src[idx->src])
	{
		if ((is_quote_closed(src + idx->src) && is_quote(src[idx->src])))
		{
			copy_quoted_segment(src, src[idx->src], dest, idx);
			token->processed_quote = true;
		}
		else
		{
			dest[idx->dest++] = src[idx->src++];
			token->processed_quote = false;
		}
	}
}

static char	*remove_quotes(t_token_node *token)
{
	char		*result;
	int			len;
	t_indices	idx;

	if (!token->token_value)
		return (NULL);
	len = ft_strlen(token->token_value);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	idx.src = 0;
	idx.dest = 0;
	processed_quote_flag(token->token_value, result, &idx, token);
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
		clean = remove_quotes(tokens[i]);
		free(tokens[i]->token_value);
		tokens[i]->token_value = clean;
	}
	i = -1;
	while (tokens[++i] != NULL)
		concatenate_adjacent_tokens(tokens, i);
}
