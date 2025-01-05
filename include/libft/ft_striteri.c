/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:24:24 by suroh             #+#    #+#             */
/*   Updated: 2024/04/24 16:11:59 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i] != '\0')
	{
		(*f)(i, &s[i]);
		i++;
	}
}

// void	ft_convert(unsigned int index, char *c)
// {
// 	(void)index;
// 	if (*c >= 'a' && *c <= 'z')
// 		*c -= 32;
// 	else if (*c >= 'A' && *c <= 'Z')
// 		*c += 32;
// }

// int	main()
// {
// 	char s[] = "HELLO chinoca";
// 	ft_striteri(s, ft_convert);
// 	printf("Result: %s\n", s);
// 	return 0;
// }
