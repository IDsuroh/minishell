/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 23:08:11 by suroh             #+#    #+#             */
/*   Updated: 2025/01/04 23:40:40 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef struct s_shell
{
	char		*cmd;
	char		*cmd_cpy;
	char		*token;
	char		*delim;
}	t_shell;

char	*ft_strtok(char *str, const char *delim);

/*
 * Testing Parsing Tokenizer Functions
 */

void	init_shell(t_shell *shell);
void	ft_free_all(t_shell shell, char **argv);
void	ft_token_init(t_shell *shell, int *argc);
void	populate_argv(t_shell *shell, char **argv);
void	ft_argv_printf(char **argv);

#endif
