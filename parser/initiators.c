/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:21:35 by suroh             #+#    #+#             */
/*   Updated: 2025/03/18 17:12:01 by suroh            ###   ########.fr       */
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

	r = (t_redir *)malloc(sizeof(t_redir));
	if (!r)
		return (NULL);
	r->type = type;
	r->filename = filename;
	r->next = NULL;
	return (r);
}

//t_operator	*malloc_t_operator(void)	???

/*
 * current_t_pipe_sequence:
 * 	Allocates a single t_pipe_sequence node (command in a pipeline).
 *
 * create_t_simple_cmd:
 * 	Allocates a single t_simple_cmd (argv is NULL initially).
 *
 * append_argv:
 * 	Goal is to add 'arg' to the t_simple_cmd->argv array (expanding the array).
 * 
 * Initial State (Before append_argv):
 * 	cmd->argv:
 * ┌───────────────────┬───────────────────────┬───────────────────────┬────────┐
 * │  cmd->argv[0]     │  cmd->argv[1]        │ cmd->argv[2]         │   ...    │
 * └───────────────────┴───────────────────────┴───────────────────────┴────────┘
 *            ↓                 ↓                      ↓
 *          "echo"           "hello"                 NULL
 *
 * We allocate (i + 2) pointers, because: We need space for i existing arguments,
 * plus 1 for the new argument, plus 1 more for the final NULL terminator.
 * Then copy old pointers to new_argv then add arg to the new_argv[2], then NULL
 * to new_argv[3].
 *
 * create_t_redir & append_redir:
 * 	For handling <, >. <<, >> tokens + the target filename.
 * r->type = type; — The redirection type (e.g., <, >, <<, >>).
 * r->filename = filename; — Points to the string
 * 						that represents the file/target.
 * r->next = NULL; — No subsequent redirection yet.
 *
 * If successful, returns a pointer to the new t_redir.
 * This newly allocated pointer will eventually be appended to
 * 					a t_simple_cmd’s redirection list.
 *
 * Check if There’s a First Redirection
 * If cmd->redir is NULL, this is the first redirection,
 * 					so set cmd->redir = redir;.
 * 
 * Otherwise, Walk to the End of the List
 * 
 * If cmd->redir is not NULL, we have existing redirections.
 * We loop (while (cur->next)) until we reach the last redirection node in
 * 								the linked list.
 * 
 * Attach
 * cur->next = redir; — Add the new redirection node at
 * 						the end of the linked list.
 */
