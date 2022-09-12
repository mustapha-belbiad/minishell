/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_outils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kouc <ael-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 18:38:06 by ael-kouc          #+#    #+#             */
/*   Updated: 2022/09/11 01:47:52 by ael-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishel.h"

int cmp(t_token *token)
{
    if(token->next != NULL && (token->e_type == CMD_WORD || token->e_type == D_Q || token->e_type == S_Q))
    {
        if(token->next->e_type == CMD_WORD || token->next->e_type == D_Q || token->next->e_type == S_Q)
            return(1);
    }
    return(0);
}

void	ft_list_remove_if(t_token **begin_list)
{
	t_token *head;
	t_token *save;
	t_token *t_remove;
    char    *tmp;

	head = *begin_list;
	save = NULL;
	t_remove = NULL;

	while (head->next != NULL)
	{
		if (cmp(head))
		{
            save = head;
            tmp = head->value;
			head->value = ft_strjoin(head->value, head->next->value);
            free(tmp);
            t_remove = head->next;
            head = head->next->next;
            free(t_remove->value);
            free(t_remove);
            head = save;
		}
		else
            head = head->next;
	}
}

void    get_null(t_token *token, t_cmd *cmd)
{
    t_token *t_tok;
    t_cmd   *t_cm;
    int y;
    int i;

    t_tok = token;
    t_cm = cmd;
    while(t_cm)
    {
        y = 0;
        while(t_tok && t_tok->e_type != PIP)
        {
            if(t_tok->e_type == CMD_WORD || t_tok->e_type == D_Q
                || t_tok->e_type == S_Q)
                y++;
            t_tok = t_tok->next;
        }
        if(y == 0)
        {
            i = 0;
            while(t_cm->cmd[i])
            {
                free(t_cm->cmd[i]);
                t_cm->cmd[i] = NULL;
                i++;
            }
        }
        if(t_tok && t_tok->e_type == PIP)
            t_tok = t_tok->next;
        t_cm = t_cm->next;
    }    
}