/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:12:28 by suroh             #+#    #+#             */
/*   Updated: 2025/02/01 21:35:29 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "tokenizer.h"

/*
 * Minimal representation of redirections for a single command.
 * e.g. <, >, <<, >>, plus the filenames.
 * type contains T_LESS, T_GREAT, T_DLESS, T_DGREAT
 * filename contains "file.txt"
 */

typedef struct s_redir
{
	t_token_type		type;
	char				*filename;
	struct s_redir		*next;
}	t_redir;

/*
 * Minimal representation of a simple command which holds an array of (argv)s
 * + a linked list of redirections.
 * e.g. ls -l
 * argv contains ["ls", "-l"]
 * redirections contains [redir1, redir2]
 */

typedef struct s_simple_cmd
{
	char		**argv;
	t_redir		*redir;
}	t_simple_cmd;

/*
 * Pipelines (sequence of commands separated by '|'):
 * can store multiple commands by linking a list of pipe sequence nodes.
 */

typedef struct s_pipe_sequence
{
	t_simple_cmd				*cmd;
	struct s_pipe_sequence		*next;
}	t_pipe_sequence;

/*
 * Operators (||, &&):
 * can store multiple operators by linking a list of operator sequence nodes.
 */

typedef struct s_op_sequence
{
	t_pipe_sequence				*pipe;
	struct s_op_sequence		*next;
}	t_op_sequence;

/*
 * A simple parser context: tracks
 * - the list of tokens from the tokenizer
 * - the current token being processed or the current parsing index
 */

typedef struct s_parser
{
	t_token_node	**tokens;
	int				cur_idx;
	bool			incomp_error;
	bool			consec_error;
	bool			redir_error;
}	t_parser;

/* parse_tokens:
 * 	Takes the array of token pointers from the tokenizer.
 * 	Then returns a linked list of commands (pipeline).
 *
 * free_pipeline:
 * 	Frees all memory allocated for the pipeline list.
 */

// functions to look up and mimic
//
// token_access.c
t_token_node		*get_current_token(t_parser *parser);
t_token_node		*get_next_token(t_parser *parser);
t_token_node		*get_prev_token(t_parser *parser);
void				advance_token(t_parser *parser);

// initiators.c
t_op_sequence		*malloc_t_op_sequence(void);
t_pipe_sequence		*malloc_t_pipe_sequence(void);
t_simple_cmd		*malloc_t_simple_cmd(void);
t_redir				*malloc_t_redir(t_token_type type, char *filename);

// sequence_appenders.c
void				append_argv(t_simple_cmd *cmd, char *arg);
void				append_redir(t_simple_cmd *cmd, t_redir *redir);

// parse_command.c
t_simple_cmd		*parse_command(t_parser *parser);

// parse_pipeline.c
t_pipe_sequence		*parse_pipeline(t_parser *parser);

// parse_oeprators.c
t_op_sequence		*parse_operators(t_parser *parser);

// parser_helpers.c
void				free_redir(t_redir *redir);
void				free_pipeline(t_pipe_sequence *pipeline);
void				free_op_sequence(t_op_sequence *op_sequence);

// parser.c
t_op_sequence		*parse_tokens(t_token_node **tokens);
#endif
