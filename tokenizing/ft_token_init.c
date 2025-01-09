/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 19:08:53 by suroh             #+#    #+#             */
/*   Updated: 2025/01/09 18:56:33 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_token_start(t_token_node *token_list)
{
	token_list->type = T_IDENTIFIER;
	if (!ft_strncmp(token_list->token_value, "(", 1))
		token_list->type = T_OP_PAR;
	else if (!ft_strncmp(token_list->token_value, ")", 1))
		token_list->type = T_CL_PAR;
	else if (!ft_strncmp(token_list->token_value, "|", 1))
	{
		token_list->type = T_PIPE;
		if (!ft_strncmp(token_list->token_value, "||", 2))
			token_list->type = T_OR;
	}
	else if (!ft_strncmp(token_list->token_value, "<", 1))
	{
		token_list->type = T_LESS;
		if (!ft_strncmp(token_list->token_value, "<<", 2))
			token_list->type = T_DLESS;
	}
	else if (!ft_strncmp(token_list->token_value, ">", 1))
	{
		token_list->type = T_GREAT;
		if (!ft_strncmp(token_list->token_value, ">>", 2))
			token_list->type = T_DGREAT;
	}
	else if (!ft_strncmp(token_list->token_value, "&&", 2))
		token_list->type = T_AND;
}

void	ft_init_node(t_token_node **current, t_token_node *token_list)
{
	t_token_node	*new_node;

	new_node = malloc(sizeof(t_token_node));
	if (!new_node)
	{
		ft_free_token_list(token_list);
		*current = NULL;
		return ;
	}
	new_node->next = NULL;
	new_node->token_value = NULL;
	new_node->prev = *current;
	(*current)->next = new_node;
	*current = new_node;
}

void	ft_link_token(t_token_node *token_list, char **tmp, int *count)
{
	t_token_node	*current;
	int				i;

	if (!token_list || !tmp || !count)
		return ;
	current = token_list;
	i = -1;
	while (++i < (*count))
	{
		if (i > 0)
		{
			ft_init_node(&current, token_list);
			if (current == NULL)
				return ;
		}
		current->token_value = malloc(ft_strlen(tmp[i]) + 1);
		if (!(current->token_value))
		{
			ft_free_token_list(token_list);
			return ;
		}
		ft_strlcpy(current->token_value, tmp[i], ft_strlen(tmp[i]) + 1);
		ft_token_start(current);
		current->next = NULL;
	}
}

t_token_node	*ft_token_init(char *line, int *token_count)
{
	int				i;
	char			*delim;
	char			**temp_token;
	t_token_node	*token_list;

	delim = " \t\n";
	*token_count = ft_strtok_count(line, delim);
	token_list = malloc(sizeof(t_token_node));
	if (!token_list)
		return (NULL);
	temp_token = malloc(sizeof(char *) * (*token_count + 1));
	if (!temp_token)
	{
		free(token_list);
		return (NULL);
	}
	i = 0;
	temp_token[i] = ft_strtok(line, delim);
	while (temp_token[i] != NULL)
		temp_token[++i] = ft_strtok(NULL, delim);
	ft_link_token(token_list, temp_token, token_count);
	free(temp_token);
	return (token_list);
}

t_token_node	*ft_tokenizer(char *input)
{
	t_token_node	*token_list;
	char			*line;
	int				token_count;

	token_count = 0;
	line = ft_strdup(input);
	if (!line)
		return (NULL);
	token_list = ft_token_init(line, &token_count);
	if (!token_list)
	{
		free(line);
		return (NULL);
	}
	free(line);
	input = NULL;
	return (token_list);
}
