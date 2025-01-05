/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:29:52 by suroh             #+#    #+#             */
/*   Updated: 2024/05/05 17:06:57 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_start_i(const char *s1, const char *set)
{
	int		start_i;
	int		j;

	start_i = 0;
	j = 0;
	while (set[j])
	{
		if (s1[start_i] == set[j])
		{
			start_i++;
			j = 0;
		}
		else
			j++;
	}
	return (start_i);
}

static int	ft_end_i(const char *s1, const char *set)
{
	int		end_i;
	int		ej;

	end_i = ft_strlen(s1) - 1;
	ej = 0;
	while (set[ej])
	{
		if (s1[end_i] == set[ej])
		{
			end_i--;
			ej = 0;
		}
		else
			ej++;
	}
	return (end_i);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*new;
	int		index;
	int		start_i;
	int		end_i;

	start_i = ft_start_i(s1, set);
	end_i = ft_end_i(s1, set);
	if (start_i > end_i)
		return (ft_strdup(""));
	new = (char *)ft_calloc((end_i - start_i + 2), sizeof(char));
	if (!new)
		return (NULL);
	index = 0;
	while (start_i <= end_i)
		new[index++] = s1[start_i++];
	new[start_i] = '\0';
	return (new);
}

// int	main(void)
// {
// 	char	str[] = "afghadlfkgbe";
// 	char	set[] = "abdehg";
// 	printf("%s\n", ft_strtrim(str, set));
// 	char s1[] = "lorem \n ipsum \t dolor \n sit \t amet";
// 	printf("%s\n", ft_strtrim(s1, " "));
// 	char s2[] = "lorem ipsum dolor sit amet";
// 	printf("%s\n", ft_strtrim(s2, "te"));
// 	char s3[] = " lorem ipsum dolor sit amet";
// 	printf("%s\n", ft_strtrim(s3, "l "));
// 	char s4[] = "lorem ipsum dolor sit amet";
// 	printf("%s\n", ft_strtrim(s4, "tel"));
// 	char s5[] = "          ";
// 	printf("%s\n", ft_strtrim(s5, " "));
// }
