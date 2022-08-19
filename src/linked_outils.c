/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_outils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kouc <ael-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 18:38:06 by ael-kouc          #+#    #+#             */
/*   Updated: 2022/08/18 20:42:02 by ael-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishel.h"

void	parser_add_back(t_parser **parser, char *value, int type, int btw)
{
	t_parser *last;
	t_parser *tmp;
	
	
	last = init_parser(value, type, btw);
	tmp = (*parser);
	while(tmp->next)
		tmp = tmp->next;
	tmp->next = last;
}

