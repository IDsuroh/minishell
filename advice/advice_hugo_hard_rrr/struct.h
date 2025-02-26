/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 20:36:53 by suroh             #+#    #+#             */
/*   Updated: 2025/02/22 20:40:50 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef enum s_type{
	HEREDOC,
	APPEND,
	WRITE,
	READ,
}			t_type;

typedef struct s_redirect{
	char *file;
	t_type type;
	int fd;
	struct s_redirect *next;

}			t_redirect;

typedef struct s_cmd{
	char *cmd;
	char **args;
	t_redirect *redirect;
	
}			t_cmd;

#endif
