/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:01:27 by jlima-so          #+#    #+#             */
/*   Updated: 2025/06/11 09:05:53 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstadd_front(t_list **lst, t_list *newt)
{
	if (lst == NULL || newt == NULL)
		return ;
	if (*lst == NULL)
		*lst = newt;
	else
	{
		newt->next = *lst;
		*lst = newt;
	}
}
