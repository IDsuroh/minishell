/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 18:12:24 by suroh             #+#    #+#             */
/*   Updated: 2025/03/05 18:39:19 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "parser.h"
# include <fcntl.h>

# define T_INPUT	1
# define T_OUTPUT	2
# define T_APPEND	3

void	execute_commands(t_op_sequence *tmp_seq);

#endif
