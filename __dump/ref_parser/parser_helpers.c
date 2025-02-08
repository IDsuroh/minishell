/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 22:49:29 by suroh             #+#    #+#             */
/*   Updated: 2025/01/30 21:27:45 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_redir(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir->next;
		free(redir);
		redir = tmp;
	}
}

void	free_pipeline(t_pipe_sequence *pipeline)
{
	t_pipe_sequence	*tmp_seq;

	while (pipeline)
	{
		tmp_seq = pipeline->next;
		if (pipeline->cmd)
		{
			free(pipeline->cmd->argv);
			free_redir(pipeline->cmd->redir);
			free(pipeline->cmd);
		}
		free(pipeline);
		pipeline = tmp_seq;
	}
}

void	free_op_sequence(t_op_sequence *op_sequence)
{
	t_op_sequence	*tmp_seq;

	while (op_sequence)
	{
		tmp_seq = op_sequence->next;
		if (op_sequence->pipe)
			free_pipeline(op_sequence->pipe);
		free(op_sequence);
		op_sequence = tmp_seq;
	}
}

/*
 * free_redirections:
 *   Frees the linked list of t_redir nodes.
 *   (If you used strdup for `filename`, remember to free it.)
 *
 * free_pipeline:
 *   Frees only the pipeline structs, not the token strings.
 */
