/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchung <pchung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:20:18 by pchung            #+#    #+#             */
/*   Updated: 2025/04/27 17:01:07 by pchung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (del == NULL || lst == NULL)
		return ;
	if (lst->content != NULL)
	{
		del(lst->content);
	}
	free(lst);
}

// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q a.out");
// }
// static void	del(void* content)
// {
// 	free(content);
// 	return ;
// }
// #include "libft.h"
// int	main(){
// 	char *test_value = ft_strdup("Hello World");
// 	t_list	*test3 = ft_lstnew(test_value);
// 	t_list	*test5 = ft_lstnew(NULL);
// 	ft_lstdelone(NULL, NULL);
// 	ft_lstdelone(test3, del);
// 	ft_lstdelone(test5, del);
// }
