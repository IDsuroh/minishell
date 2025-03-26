/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 18:12:24 by suroh             #+#    #+#             */
/*   Updated: 2025/03/26 22:38:47 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "parser.h"
# include <sys/wait.h>

typedef struct s_almighty	t_almighty;

typedef struct s_pid_node
{
	pid_t				pid;
	struct s_pid_node	*next;
}						t_pid_node;

typedef struct s_pipeline_variables
{
	t_pipe_sequence	*current;
	int				prev_pipe_read;
	int				pipefd[2];
}					t_pipeline_variables;

// cd_n_pwd.c
void	_cd(t_almighty *mighty, char **args);
void	_pwd(t_almighty *mighty);

// cd_helpers.c
int		count_args(char **args);
char	*resolve_dir(t_almighty *mighty, char **args);
int		change_and_update_oldpwd(t_almighty *mighty, char *dir);
void	update_new_pwd(t_almighty *mighty);

// echo.c
void	_echo(t_almighty *mighty, char **args);

// env.c
void	_env(t_almighty *mighty);

// exit.c
int		exit_builtin(t_almighty *mighty, char **argv, int saved_stdout);
void	_exit_(t_almighty *mighty, int *var_exit);

// exit_helpers.c
bool	is_numeric(char *str);
void	handle_no_arg_exit(t_almighty *mighty, int saved_stdout);
void	handle_non_numeric_exit(t_almighty *mighty, int saved_stdout);
void	handle_numeric_exit(t_almighty *mighty, char **argv, int saved_stdout);

// export.c
void	_export(t_almighty *mighty, char *var);

// unset.c
void	_unset(t_almighty *mighty, char *key);

// execute.c
void	execute_child_command(t_simple_cmd *cmd, t_almighty *mighty);
int		execute_command(t_simple_cmd *cmd, t_almighty *mighty);
void	execute_parsed_structure(t_op_sequence *op_seq, t_almighty *mighty);

// execute_child_command_helper.c
void	handle_cmd_not_found(t_simple_cmd *cmd, t_almighty *mighty,
			char *exec_path);
void	handle_dir_error(t_almighty *mighty, char *exec_path);
void	handle_no_file_error(t_almighty *mighty, char *exec_path);
void	check_executable_status(t_simple_cmd *cmd, t_almighty *mighty,
			char *exec_path);
void	handle_exec_failure(char *exec_path);

// execute_helper.c
bool	validate_command_tokens(t_simple_cmd *cmd);
void	restore_stdin_to_tty(void);

// execute_builtin.c
bool	is_builtin_command(const char *cmd);
int		execute_builtin(t_simple_cmd *cmd, t_almighty *mighty);

// execute_pipeline.c
int		execute_pipeline(t_pipe_sequence *pipe_seq, t_almighty *mighty);

// execute_pipeline_helper.c
void	child_pipeline_setup(t_pipeline_variables *pvs, t_almighty *mighty);
void	parent_pipeline_setup(t_pipeline_variables *pvs, t_almighty *mighty,
			pid_t pid);

// execute_redirections.c
int		execute_redirections(t_redir *redir);

// find_executable.c
char	*find_executable(char *cmd);

// find_executable_helper.c
bool	is_cmd_a_path(char *cmd);
void	free_paths(char **paths);

// handle_heredoc_redirection.c
int		handle_heredoc_redirection(t_redir *redir);

// manage_pid_list.c
void	add_child_pid(t_almighty *mighty, pid_t pid);
void	remove_child_pid(t_almighty *mighty, pid_t pid);
void	send_signal_to_all_children(t_almighty *mighty, int sig);

#endif
