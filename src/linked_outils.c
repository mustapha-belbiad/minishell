/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_outils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kouc <ael-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 18:38:06 by ael-kouc          #+#    #+#             */
/*   Updated: 2022/08/22 21:30:08 by ael-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishel.h"

void    free_t_token(t_token *token)
{
    t_token *tmp;
    while(token)
    {
        free(token->value);
        tmp = token;
        free(tmp);
        token = token->next;
    }
}
