/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kouc <ael-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 08:04:35 by ael-kouc          #+#    #+#             */
/*   Updated: 2022/08/17 09:41:23 by ael-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"


int	check_err_quote(t_token *token)
{
	t_token *tmp;
	
	tmp = token;
	while (tmp)
	{
		if (tmp->type == RED_FLAG)
			return(0);
		tmp = tmp->next;
	}
	return(1);
}

int check_err_red(t_token *token)
{
	t_token *tmp;

	tmp = token;
	while(tmp)
	{
		if(tmp->type == REDIRECT_IN || tmp->type == REDIRECT_OT
			|| tmp->type == D_REDIRECT_IN || tmp->type == D_REDIRECT_OT)
		{
			if(tmp->next == NULL)
			{
				return(0);
				break;
			}
			if(!(tmp->next->type == DOLLAR || tmp->next->type == S_Q
				|| tmp->next->type == D_Q || tmp->next->type == CMD_WORD))
				return(0);
		}
		tmp = tmp->next;
	}
	return(1);
}

int	check_err_pip(t_token *token)
{
	t_token *tmp;

	tmp = token;
	if(tmp->next->type == PIP)
		return(0);
	while(tmp)
	{
		if(tmp->type == PIP)
		{
			if(!(tmp->next) || tmp->next->type == PIP)
				return(0);
		}
		tmp = tmp->next;
	}
	return(1);
}

