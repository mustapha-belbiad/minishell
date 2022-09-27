/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kouc <ael-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 11:51:20 by ael-kouc          #+#    #+#             */
/*   Updated: 2022/09/25 20:24:52 by ael-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

t_token	*init_token(char *value, int e_type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->value = ft_strdup(value);
	token->e_type = e_type;
	token->next = NULL;
	return (token);
}

void	token_add_back(t_token **token, char *value, int e_type)
{
	t_token	*last;
	t_token	*tmp;

	if (!*token)
	{
		*token = init_token(value, e_type);
		return ;
	}
	last = init_token(value, e_type);
	tmp = (*token);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = last;
}

int	ft_lstsize(t_token *token)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = token;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}
