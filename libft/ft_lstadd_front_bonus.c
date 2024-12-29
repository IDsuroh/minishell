/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:29:58 by suroh             #+#    #+#             */
/*   Updated: 2024/11/12 19:16:24 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *nw)
{
	if (!lst || !nw)
		return ;
	nw->next = *lst;
	*lst = nw;
}

// int	main(void)
// {
// 	t_list	*new;
// 	t_list	*new1;
// 	new = ft_lstnew("HI");
// 	new1 = ft_lstnew("string");
// 	printf("original '%s'\n",
// 	(char *)new1->content);
// 	ft_lstadd_front(&new1, new);
// 	printf("new1's new '%s'\n", (char *)new1->content);
// 	printf("new1's next '%s'\n",
// 	(char *)new1->next->content);
// 	return (0);
// }
