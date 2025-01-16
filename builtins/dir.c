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

	buff = malloc(1000 * sizeof(char));
	getcwd(buff, 1000);
	if (buff)
		ft_putstr_fd(buff, 1);
	free(buff);
}
//
//int	main(void)
//{
//	_cd("..");
//	_pwd();
//}
