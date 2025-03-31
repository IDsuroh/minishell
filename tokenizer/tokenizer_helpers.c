/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:44:08 by suroh             #+#    #+#             */
/*   Updated: 2025/03/30 21:41:05 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_tokens(char **token_storage)
{
	int	i;

	if (!token_storage)
		return ;
	i = 0;
	while (token_storage[i])
	{
		free(token_storage[i]);
		i++;
	}
	free(token_storage);
}

void	free_node_list(t_token_node **token_list)
{
	int	i;

	if (!token_list)
		return ;
	i = 0;
	while (token_list[i] != NULL)
	{
		if (token_list[i]->token_value)
			free(token_list[i]->token_value);
		free(token_list[i]);
		i++;
	}
	free(token_list);
}

void	free_incomp_node_list(t_token_node **token_list, int allocated)
{
	int	i;

	if (!token_list)
		return ;
	i = 0;
	while (i < allocated)
	{
		free(token_list[i]->token_value);
		free(token_list[i]);
		i++;
	}
	free(token_list);
}

void	free_node_list_no_values(t_token_node **node_list)
{
	int	i;

	i = 0;
	while (node_list[i])
	{
		free(node_list[i]);
		i++;
	}
	free(node_list);
}

void	free_tokstor(char **token_storage)
{
	int	i;

	if (!token_storage)
		return ;
	i = -1;
	while (token_storage[++i])
		free(token_storage[i]);
	free(token_storage);
}
