/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 23:08:11 by suroh             #+#    #+#             */
/*   Updated: 2025/01/05 21:57:34 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

/*
 * Structure to store the command and the tokens / Lexer tools
 */

typedef struct s_shell
{
	char	*cmd;
	char	*delim;
	char	**token;
}	t_shell;

//Lexer functions

char	*ft_strtok(char *str, const char *delim);
void	init_shell(t_shell *shell, char *input);
void	ft_token_init(t_shell *shell);
void	ft_init_lex(t_shell *shell, char *input);
int		ft_token_count(t_shell *shell);

/*
 * Command Table / AST(Abstract Syntax Tree) / Parse Tree
 *
 * Parent Structure to store the Command Table
 */

typedef struct s_cmd
{
	struct s_cmd	*next;
	char			*command;
	char			*infile;
	char			*outfile;
	char			**flags;
	int				is_append;
	int				is_background;
}	t_cmd;

typedef struct s_pipeline
{
	int		n_cmds;
	t_cmd	**cmds;
}	t_pipeline;

#endif
