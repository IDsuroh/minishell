/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:37:44 by suroh             #+#    #+#             */
/*   Updated: 2024/04/30 12:02:11 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

// int	main()
// {
// 	t_list	*lst = ft_lstnew("string");
// 	t_list	*new = ft_lstnew("content");
// 	t_list	*last
// 	ft_lstadd_front(&lst, new);
// 	last = ft_lstlast(lst);
// 	printf("%s\n", (char *)last->content);
// 	free(lst);
// 	free(last);
// 	return (0);
// }
