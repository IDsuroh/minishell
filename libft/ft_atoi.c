/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 18:23:54 by suroh             #+#    #+#             */
/*   Updated: 2024/05/04 15:58:46 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int			i;
	int			minuscount;
	long int	value;

	i = 0;
	value = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	minuscount = 1;
	if (nptr[i] == 45)
	{
		minuscount = -1;
		i++;
	}
	else if (nptr[i] == 43)
		i++;
	while (ft_isdigit(nptr[i]) == 1)
	{
		value = value * 10 + (nptr[i] - '0');
		i++;
	}
	return ((value * minuscount));
}

// int	main(void)
// {
// 	char	*str = "  3    	+areg2	3	-1234arg";
// 	printf("%d\n", ft_atoi(str));
// }
