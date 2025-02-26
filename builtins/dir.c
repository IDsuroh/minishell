#include "../include/minishell.h"
#include "../include/libft/libft.h"

void	_echo(char **args)
{
}

void	_cd(char *dir)
{
	if (chdir(dir))
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(dir, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
}

void	_pwd(void)
{
	char	*buff;

	buff = NULL;
	buff = getcwd(buff, 0);
	if (buff)
		ft_putstr_fd(buff, 1);
}

void	_export(char *var)
{
}

void	_unset(t_almighty *boy, char *key)
{
	rem_var(boy->var_list, get_value(boy->var_list, key));
}

void	_env(t_almighty *boy)
{
	print_vars(make_envp(boy->var_list));
}

void	_exit(t_almighty *boy, int *exit)
{
	int	__exit;

	if (exit)
		__exit = *exit;
	else
		__exit = boy->exit_stat;
	// FREE EVERYTHING
	exit(__exit);
}

int	main(void)
{
	_cd("/bin");
	_pwd();
}
