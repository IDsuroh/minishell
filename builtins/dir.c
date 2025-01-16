#include "../include/minishell.h"
#include "../include/libft/libft.h"

void	_cd(char *dir)
{
	if (chdir(dir))
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(dir, 2);
		ft_putstr_fd(": No such file or directory", 2);
		ft_putchar_fd('\n', 2);
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

int	main(void)
{
	_cd("/bin");
	_pwd();
}
