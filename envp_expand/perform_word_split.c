/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_word_split.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 20:58:19 by suroh             #+#    #+#             */
/*   Updated: 2025/03/30 23:15:14 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	count_these_tokens(t_token_node **tokens)
{
	int	count;

	count = 0;
	while (tokens[count])
		count++;
	return (count);
}

static t_token_node	*create_token_node(const char *value, int type)
{
	t_token_node	*node;

	node = malloc(sizeof(t_token_node));
	if (!node)
		return (NULL);
	node->token_value = ft_strdup(value);
	node->type = type;
	return (node);
}

static void	process_token_split(t_token_node *token, t_token_node **new_tokens,
		int *new_count)
{
	int		j;
	char	**split_words;

	split_words = ft_split(token->token_value, ' ');
	if (split_words)
	{
		j = -1;
		while (split_words[++j])
		{
			new_tokens[*new_count] = create_token_node(split_words[j],
					token->type);
			(*new_count)++;
		}
		free_tokstor(split_words);
	}
}

static void	process_token(t_token_node *token, t_token_node **new_tokens,
		int *new_count)
{
	if (ft_strchr(token->token_value, '='))
	{
		new_tokens[*new_count] = token;
		(*new_count)++;
	}
	else if (ft_strchr(token->token_value, ' '))
	{
		process_token_split(token, new_tokens, new_count);
		free(token->token_value);
		free(token);
	}
	else
	{
		new_tokens[*new_count] = token;
		(*new_count)++;
	}
}

t_token_node	**perform_ws(t_token_node **tokens)
{
	t_token_node	**new_tokens;
	int				old_count;
	int				new_count;
	int				i;

	old_count = count_these_tokens(tokens);
	new_tokens = ft_calloc((old_count * 2) + 1, sizeof(t_token_node *));
	if (!new_tokens)
		return (tokens);
	new_count = 0;
	i = 0;
	while (tokens[i])
	{
		process_token(tokens[i], new_tokens, &new_count);
		i++;
	}
	new_tokens[new_count] = NULL;
	free(tokens);
	return (new_tokens);
}
