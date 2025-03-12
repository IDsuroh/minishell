/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:12:28 by suroh             #+#    #+#             */
/*   Updated: 2025/03/11 21:51:35 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "tokenizer.h"

typedef struct s_redir
{
	t_token_type		type;
	char				*filename;
	struct s_redir		*next;
}	t_redir;

typedef struct s_simple_cmd
{
	char		**argv;
	t_redir		*redir;
}	t_simple_cmd;

typedef struct s_pipe_sequence
{
	t_simple_cmd				*cmd;
	struct s_pipe_sequence		*next;
}	t_pipe_sequence;

typedef enum e_operator
{
	OP_NONE,
	OP_AND,
	OP_OR
}	t_operator;

typedef struct s_op_sequence
{
	t_pipe_sequence				*pipe;
	t_operator					op;
	struct s_op_sequence		*next;
	struct s_op_sequence		*prev;
}	t_op_sequence;

typedef struct s_parser
{
	t_token_node	**tokens;
	int				cur_idx;
}	t_parser;

// token_access.c
t_token_node		*get_current_token(t_parser *parser);
t_token_node		*get_next_token(t_parser *parser);
void				advance_token(t_parser *parser);

// initiators.c
t_op_sequence		*malloc_t_op_sequence(void);
t_pipe_sequence		*malloc_t_pipe_sequence(void);
t_simple_cmd		*malloc_t_simple_cmd(void);
t_redir				*malloc_t_redir(t_token_type type, char *filename);

// parse_command.c
t_simple_cmd		*parse_command(t_parser *parser);

// parse_pipe_sequence.c
t_pipe_sequence		*parse_pipe_sequence(t_parser *parser);

// parse_sequence.c
t_op_sequence		*parse_sequence(t_parser *parser);

// parser_helpers.c
void				free_redir(t_redir *redir);
void				free_pipeline(t_pipe_sequence *pipeline);
void				free_op_sequence(t_op_sequence *op_sequence);

// parser.c
t_op_sequence		*parse_tokens(t_token_node **tokens);
#endif
