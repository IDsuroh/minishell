/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:36:37 by suroh             #+#    #+#             */
/*   Updated: 2024/05/04 16:57:18 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void	ft_putnbr_fd(int n, int fd)
// {
// 	long int	num;
// 	char		value;

// 	num = n;
// 	if (num < 0)
// 	{
// 		ft_putchar_fd('-', 1);
// 		num *= -1;
// 	}
// 	value = (num % 10) + 48;
// 	num = num / 10;
// 	if (num > 0)
// 		ft_putnbr_fd(num, fd);
// 	ft_putchar_fd(value, 1);
// }
//	This was wrong because the ft_putchar_fd was set to 1 instead of fd.

void	ft_putnbr_fd(int n, int fd)
{
	long	nb;

	nb = n;
	if (nb < 0)
	{
		write(fd, "-", 1);
		nb *= -1;
	}
	if (nb > 9)
	{
		ft_putnbr_fd(nb / 10, fd);
		ft_putchar_fd((nb % 10) + '0', fd);
	}
	else
		ft_putchar_fd(nb + '0', fd);
}

// int	main()
// {
// 	ft_putnbr_fd(147, 1);
// 	ft_putchar_fd('\n', 1);
// 	ft_putnbr_fd(-2147483648, 1);
// 	ft_putchar_fd('\n', 1);
// 	ft_putnbr_fd(2147483647, 1);
// 	ft_putchar_fd('\n', 1);
// 	ft_putnbr_fd(10, 1);
// 	ft_putchar_fd('\n', 1);
// 	ft_putnbr_fd(-42, 1);
// 	ft_putchar_fd('\n', 1);
// 	ft_putnbr_fd(2147483647, 1);
// 	ft_putchar_fd('\n', 1);
// 	ft_putnbr_fd(2, 1);
// 	ft_putchar_fd('\n', 1);
// }
