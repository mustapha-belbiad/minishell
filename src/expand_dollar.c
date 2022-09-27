/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kouc <ael-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 10:54:56 by ael-kouc          #+#    #+#             */
/*   Updated: 2022/09/17 04:45:58 by ael-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

void	change_value5(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->e_type == REDIRECT_IN || tmp->e_type == REDIRECT_OT
			|| tmp->e_type == D_REDIRECT_OT || tmp->e_type == D_REDIRECT_IN)
		{
			if (tmp->next && (tmp->next->e_type == CMD_WORD
					|| tmp->next->e_type == D_Q || tmp->next->e_type == S_Q))
			{
				tmp = tmp->next;
				while (tmp && (tmp->e_type == CMD_WORD || tmp->e_type == D_Q
						|| tmp->e_type == S_Q))
				{
					tmp->e_type = J;
					tmp = tmp->next;
				}
			}
		}
		if (tmp && tmp->next)
			tmp = tmp->next;
		else
			break ;
	}
}
