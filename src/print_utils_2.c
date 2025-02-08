/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 18:59:43 by suroh             #+#    #+#             */
/*   Updated: 2025/02/08 19:08:50 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/colors.h"

void	print_tokens_colors(t_token_node **current)
{
	int	i;

	i = 0;
	while (current[i] != NULL)
	{
		printf("Token[%d]: %s%s%s, Type: %s%s%s\n",
			i,
			get_token_color(current[i]->type),
			current[i]->token_value, RESET,
			get_token_color(current[i]->type),
			token_type_to_string(current[i]->type), RESET);
		i++;
	}
}

void	print_pipe(t_pipe_sequence *pipe)
{
	int		i;
	t_redir	*redir;

	i = 0;
	while (pipe->cmd->argv[i])
	{
		printf("\t\tArgument #%d: %s\n", i, pipe->cmd->argv[i]);
		i++;
	}
	redir = pipe->cmd->redir;
	while (redir)
	{
		printf("\t\tRedir: type = %d to %s\n", redir->type, redir->filename);
		redir = redir->next;
	}
}

void	print_cmd(t_op_sequence *seq)
{
	int	i;

	i = 0;
	while (seq->pipe)
	{
		printf("\tPipe #%d:\n", i);
		if (seq->pipe->cmd && seq->pipe->cmd->argv)
			print_pipe(seq->pipe);
		seq->pipe = seq->pipe->next;
		i++;
	}
}

void	print_parsing(t_op_sequence *tmp_seq)
{
	t_op_sequence	*head_seq;
	int				cmd_idx;

	head_seq = tmp_seq;
	cmd_idx = 0;
	while (tmp_seq)
	{
		printf("Command #%d:\n", cmd_idx);
		print_cmd(tmp_seq);
		tmp_seq = tmp_seq->next;
		cmd_idx++;
	}
	free_op_sequence(head_seq);
}
