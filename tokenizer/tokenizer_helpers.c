/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:44:08 by suroh             #+#    #+#             */
/*   Updated: 2025/02/18 23:15:57 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*mem;
	size_t	len;

	len = ft_strlen(s);
	if (n < len)
		len = n;
	mem = (char *)malloc(sizeof(char) * (len + 1));
	if (!mem)
		return (NULL);
	ft_memcpy(mem, s, len);
	mem[len] = '\0';
	return (mem);
}

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
