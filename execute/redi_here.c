/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redi_here.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelbiad <mbelbiad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 19:07:17 by mbelbiad          #+#    #+#             */
/*   Updated: 2022/09/29 18:44:02 by mbelbiad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

int	check_file(char	*argv)
{
	int	check;

	check = open(argv, O_RDONLY);
	return (check);
}

int	file_output(char	*argv)
{
	int	out;

	out = open(argv, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (out == -1)
	{
		perror ("open");
		g_env->ret_val = 1;
	}
	return (out);
}

int	append_mode(char	*argv)
{
	int	out;

	out = open(argv, O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (out == -1)
	{
		perror ("open");
		g_env->ret_val = 1;
	}
	return (out);
}

int	redrct_for_exec(t_cmd *cmd)
{
	t_file	*tmp;
	int		j;

	j = 0;
	if (cmd->file == NULL)
		return (1);
	tmp = cmd->file;
	while (tmp)
	{
		if (tmp->e_type == 5 || tmp->e_type == 7)
		{
			if (file_in(tmp, j) == 0)
			{
				g_env->ret_val = 1;
				return (0);
			}
		}
		else if (tmp->e_type == 6 || tmp->e_type == 8)
			file_out(tmp, j);
		tmp = tmp->next;
	}
	return (1);
}

int	redi_heredoc(t_cmd *cmd)
{
	t_file	*tmp;
	int		j;

	j = 1;
	if (cmd->file == NULL)
		return (3);
	tmp = cmd->file;
	while (tmp)
	{
		if (tmp->e_type == 5 || tmp->e_type == 7)
		{
			if (file_in(tmp, j) == 0)
				return (0);
		}
		else if (tmp->e_type == 6 || tmp->e_type == 8)
			file_out(tmp, j);
		tmp = tmp->next;
	}
	return (1);
}
