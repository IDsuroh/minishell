/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 22:49:29 by suroh             #+#    #+#             */
/*   Updated: 2025/01/29 17:42:17 by suroh            ###   ########.fr       */
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

/*
 * free_redirections:
 *   Frees the linked list of t_redir nodes.
 *   (If you used strdup for `filename`, remember to free it.)
 *
 * free_pipeline:
 *   Frees only the pipeline structs, not the token strings.
 */
