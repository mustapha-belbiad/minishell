/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kouc <ael-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 03:50:20 by ael-kouc          #+#    #+#             */
/*   Updated: 2022/09/25 21:22:09 by ael-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

char	*ft_change(t_token *tmp)
{
	char	*c;
	char	*str;
	char	*tmp2;

	c = ft_strdup("~");
	str = ft_strjoin(c, tmp->value);
	tmp2 = str;
	str = ft_strjoin(str, c);
	free(tmp2);
	free(c);
	free(tmp->value);
	return (str);
}

int	norm_if(t_token *tmp, char c)
{
	if (c == '1')
	{
		if (tmp->e_type == D_REDIRECT_IN || tmp->e_type == D_REDIRECT_OT
			|| tmp->e_type == REDIRECT_IN || tmp->e_type == REDIRECT_OT)
			return (1);
		return (0);
	}
	else if (c == '2')
	{
		if (tmp->e_type == D_Q || tmp->e_type == S_Q
			|| tmp->e_type == CMD_WORD || tmp->e_type == SPACE)
			return (1);
		return (0);
	}
	return (0);
}

char	*giv_str(t_token *tmp, char *str)
{
	char	*tmp1;

	tmp1 = str;
	str = ft_strjoin(str, tmp->value);
	free(tmp1);
	return (str);
}

t_cmd	*get_cmd(t_token *tmp, t_cmd *cmd, char	*str, t_file *file)
{
	while (tmp)
	{	
		if (norm_if(tmp, '1'))
		{
			file_add_back(&file, tmp->next->value, tmp->e_type);
			tmp = tmp->next;
		}
		else if (norm_if(tmp, '2'))
		{
			if (tmp->e_type == D_Q || tmp->e_type == S_Q)
				tmp->value = ft_change(tmp);
			str = giv_str(tmp, str);
		}
		else if (tmp->e_type == PIP)
		{
			cmd_add_back(&cmd, return_cmd(str), file);
			file = NULL;
			str = ft_strdup("");
		}
		tmp = tmp->next;
	}
	if (file || str)
		cmd_add_back(&cmd, return_cmd(str), file);
	return (cmd);
}

t_cmd	*fill_cmd(t_token *token, t_cmd *cmd)
{
	t_token	*tmp;
	t_file	*file;
	char	*str;

	if (red_flag(token) == 1)
	{
		printf("syntax error\n");
		return (NULL);
	}
	tmp = token;
	file = NULL;
	str = ft_strdup("");
	change_value(token);
	change_value5(token);
	cmd = get_cmd(tmp, cmd, str, file);
	get_null(token, cmd);
	return (cmd);
}
