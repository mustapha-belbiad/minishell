/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kouc <ael-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 11:51:20 by ael-kouc          #+#    #+#             */
/*   Updated: 2022/06/27 14:47:08 by ael-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

t_token	*init_token(char *value, int type)
{
	t_token *token;

	token = malloc(sizeof(t_token));
	token->value = value;
	token->type = type;
	token->next = NULL;
	
	// token->betwen_c_w = 0;//if warner == 0 cmd // warner == 1 word // warner == 2 file
	return (token);
}

void	token_add_back(t_token **token, char *value, int type)
{
	t_token *last;
	t_token *tmp;
	
	last = init_token(value, type); 
	tmp = (*token);
	while(tmp->next)
		tmp = tmp->next;
	tmp->next = last;
}

int ft_lstsize(t_token *token)
{
	t_token *tmp;
	int		i;
	
	tmp = token;
	while(tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return(i);
}