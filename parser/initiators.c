/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:21:35 by suroh             #+#    #+#             */
/*   Updated: 2025/03/27 21:41:45 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_op_sequence	*malloc_t_op_sequence(void)
{
	t_op_sequence	*new_node;

	new_node = (t_op_sequence *)malloc(sizeof(t_op_sequence));
	if (!new_node)
		return (NULL);
	new_node->pipe = NULL;
	new_node->next = NULL;
	new_node->prev = NULL;
	new_node->op = OP_NONE;
	return (new_node);
}

t_pipe_sequence	*malloc_t_pipe_sequence(void)
{
	t_pipe_sequence	*new_node;

	new_node = (t_pipe_sequence *)malloc(sizeof(t_pipe_sequence));
	if (!new_node)
		return (NULL);
	new_node->cmd = NULL;
	new_node->next = NULL;
	return (new_node);
}

t_simple_cmd	*malloc_t_simple_cmd(void)
{
	t_simple_cmd	*cmd;

	cmd = (t_simple_cmd *)malloc(sizeof(t_simple_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = malloc(sizeof(char *));
	if (!cmd->argv)
	{
		free(cmd);
		return (NULL);
	}
	cmd->argv[0] = NULL;
	cmd->redir = NULL;
	cmd->in_pipeline = false;
	return (cmd);
}

t_redir	*malloc_t_redir(t_token_type type, char *filename)
{
	t_redir	*r;

	r = (t_redir *)ft_calloc(1, sizeof(t_redir));
	if (!r)
		return (NULL);
	r->type = type;
	r->filename = filename;
	return (r);
}
