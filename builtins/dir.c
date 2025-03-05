/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miteixei <miteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 19:10:17 by miteixei          #+#    #+#             */
/*   Updated: 2025/03/04 21:15:53 by miteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/libft/libft.h"

void	_echo(char **args)
{
	bool	dash_n;

	dash_n = false;
	while (*args)
	if (**args == '-' && *(*args + 1) == 'n' && *(*args + 2) == '\0')
	{
		dash_n = true;
		++args;
	}
	while (*args)
	{
		ft_putstr_fd(*(args++), 1);
		if (*args)
			ft_putchar_fd(' ', 1);
	}
	if (!dash_n)
		ft_putchar_fd('\n', 1);
}

void	_cd(t_almighty *boy, char *dir)
{
	char	*buff;

	(void)boy;
	buff = NULL;
	buff = getcwd(buff, 0);
	if (chdir(dir))
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(dir, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return ;
	}
//	if (buff)
//	{
//		// ahhhhh i'll do this later
//		_export(boy, 
}

void	_pwd(void)
{
	char	*buff;

	buff = NULL;
	buff = getcwd(buff, 0);
	if (buff)
		ft_putstr_fd(buff, 1);
	free(buff);
}

void	_export(t_almighty *boy, char *var)
{
	if (!var)
	{
		// need to make a whole function that copies the var_list and sorts it
		//   then print "declare -x " before each var name
	}
	if (!ft_strchr(var, '='))
		add_var(boy->var_list, create_var(ft_strdup(var), NULL));
	else
	{
		add_var(boy->var_list, create_var(
			ft_strndup(var, ft_strchr(var, '=') - var),
			ft_strdup(ft_strchr(var, '=') + 1)));
	}
}

void	_unset(t_almighty *boy, char *key)
{
	rem_var(boy->var_list, get_value(boy->var_list, key));
}

void	_env(t_almighty *boy)
{
	print_vars(make_envp(boy->var_list));
}

void	_exit_(t_almighty *boy, int *var_exit)
{
	int	exit_val;

	if (var_exit)
		exit_val = *var_exit;
	else
		exit_val = boy->exit_stat;
	// FREE EVERYTHING
	exit(exit_val);
}
