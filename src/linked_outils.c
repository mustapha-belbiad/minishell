/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_outils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kouc <ael-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 18:38:06 by ael-kouc          #+#    #+#             */
/*   Updated: 2022/09/18 00:46:35 by ael-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

int	whil_t_tok(t_token *t_tok, int y)
{
	while (t_tok && t_tok->e_type != PIP)
	{
		if (t_tok->e_type == CMD_WORD || t_tok->e_type == D_Q
			|| t_tok->e_type == S_Q)
			y++;
		t_tok = t_tok->next;
	}
	return (y);
}

void	get_null(t_token *token, t_cmd *cmd)
{
	t_token	*t_tok;
	t_cmd	*t_cm;
	int		y;
	int		i;

	t_tok = token;
	t_cm = cmd;
	while (t_cm)
	{
		y = 0;
		y = whil_t_tok(t_tok, y);
		if (y == 0)
		{
			i = 0;
			while (t_cm->cmd[i])
			{
				free(t_cm->cmd[i]);
				t_cm->cmd[i] = NULL;
				i++;
			}
		}
		if (t_tok && t_tok->e_type == PIP)
			t_tok = t_tok->next;
		t_cm = t_cm->next;
	}
}
