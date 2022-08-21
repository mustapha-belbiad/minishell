/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kouc <ael-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 08:04:35 by ael-kouc          #+#    #+#             */
/*   Updated: 2022/08/21 21:51:14 by ael-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"


int	check_err_quote(t_token *token)
{
	t_token *tmp;
	
	tmp = token;
	while (tmp)
	{
		if (tmp->e_type == RED_FLAG)
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
		if(tmp->e_type == REDIRECT_IN || tmp->e_type == REDIRECT_OT
			|| tmp->e_type == D_REDIRECT_IN || tmp->e_type == D_REDIRECT_OT)
		{
			if(tmp->next == NULL)
				return(0);
			if(!(tmp->next->e_type == DOLLAR || tmp->next->e_type == S_Q
				|| tmp->next->e_type == D_Q || tmp->next->e_type == CMD_WORD))
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
	if(tmp->next->e_type == PIP)
		return(0);
	while(tmp)
	{
		if(tmp->e_type == PIP)
		{
			if(!(tmp->next) || tmp->next->e_type == PIP)
				return(0);
		}
		tmp = tmp->next;
	}
	return(1);
}

