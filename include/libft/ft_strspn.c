/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 21:36:59 by suroh             #+#    #+#             */
/*   Updated: 2025/02/11 21:41:10 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strspn(const char *s, const char *accept)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s[i])
	{
		j = 0;
		while (accept[j])
		{
			if (s[i] == accept[j])
				break ;
			j++;
		}
		if (!accept[j])
			break ;
		i++;
	}
	return (i);
}

/*int	main(void)
{
	const char	*text = "   hello world";
	// Compute the number of whitespace characters at the beginning of text.
	size_t		count = strspn(text, " \t\n");
	printf("The first %zu characters are whitespace.\n", count);
	return (0);
}*/
// The line "if (!accept[j]) break;" checks whether the inner loop
// did NOT find a matching character in 'accept' for the current s[i].
// If no match was found (i.e., end of the accept string is reached),
// it means s[i] is not one of the characters in 'accept', so we break out.
