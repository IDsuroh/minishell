/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 22:56:52 by suroh             #+#    #+#             */
/*   Updated: 2025/03/02 21:43:41 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

# include "minishell.h"

# define RESET  "\033[0m"          // Reset to default color
# define ID     "\033[38;5;32m"    // Green for identifiers
# define LSS    "\033[38;5;33m"    // Light blue for '<'
# define GRT    "\033[38;5;34m"    // Cyan for '>'
# define DLSS   "\033[38;5;36m"    // Light cyan for '<<'
# define DGRT   "\033[38;5;93m"    // Bright pink for '>>'
# define PP     "\033[38;5;94m"    // Bright purple for '|'
# define ND     "\033[38;5;196m"   // Red for '&&'
# define OR     "\033[38;5;202m"   // Orange for '||'
# define VR     "\033[38;5;226m"   // Yellow for variables
# define XVR    "\033[38;5;229m"   // Light yellow for special variables ($?)
# define PD     "\033[38;5;45m"    // Blue for $$ (process ID)

// print_utils_1.c
const char	*token_type_to_string(t_token_type type);
const char	*get_token_color(t_token_type type);

// print_utils_2.c
void		print_tokens_colors(t_token_node **current);
void		print_pipe(t_pipe_sequence *pipe);
void		print_cmd(t_op_sequence *seq);
void		print_parsing(t_op_sequence *tmp_seq);

#endif
