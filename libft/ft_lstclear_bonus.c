/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:47:24 by suroh             #+#    #+#             */
/*   Updated: 2024/05/04 15:12:51 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (!lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = temp;
	}
}

// void	del(void *content)
// {
// 	free(content);
// }

// int	main(void)
// {
// 	t_list	*new;
// 	t_list	*new1;
// 	t_list	*new2;
// 	new = ft_lstnew(ft_strdup("string 1 "));
// 	new1 = ft_lstnew(ft_strdup("string 2 "));
// 	new2 = ft_lstnew(ft_strdup("string 3 "));
// 	printf("%s\n", (char *)new->content);
// 	ft_lstadd_back(&new, new1);
// 	printf("%s\n", (char *)new->next->content);
// 	ft_lstadd_back(&new1, new2);
// 	printf("%s\n", (char *)new1->next->content);
// 	ft_lstclear(&new, del);
// 	printf("now they are all deleted\n");
// 	free(new);
// 	return (0);
// }