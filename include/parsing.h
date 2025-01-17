/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:12:28 by suroh             #+#    #+#             */
/*   Updated: 2025/01/06 19:19:19 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

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
