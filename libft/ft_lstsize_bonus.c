/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:16:21 by suroh             #+#    #+#             */
/*   Updated: 2024/04/30 12:05:42 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	c;

	c = 0;
	while (lst != NULL)
	{
		c++;
		lst = lst->next;
	}
	return (c);
}

// int	main()
// {
// 	t_list	*lst = ft_lstnew("content");
// 	t_list	*new = ft_lstnew("strings");
// 	printf("%d\n", ft_lstsize(lst));
// 	printf("%d\n", ft_lstsize(new));
// 	ft_lstadd_front(&lst, new);
// 	printf("%d\n", ft_lstsize(lst));
// 	while (lst != NULL)
// 	{
// 		t_list *nn = lst->next;
// 		free(lst);
// 		lst = nn;
// 	}
// 	return (0);
// }