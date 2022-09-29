/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_in.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelbiad <mbelbiad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 14:52:31 by mbelbiad          #+#    #+#             */
/*   Updated: 2022/09/29 15:25:13 by mbelbiad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

int	in_file2(t_file *tmp, int j)
{
	int	in;

	in = check_file(tmp->file_name);
	if (in == -1 && j != 0)
	{
		perror ("open");
		g_env->ret_val = 1;
		return (0);
	}
	if (j == 0)
	{
		dup2(in, 0);
		close(in);
	}
	return (1);
}

int	file_in(t_file *tmp, int j)
{
	if (tmp->e_type == 5)
	{
		if (in_file2(tmp, j) == 0)
			return (0);
	}
	else if (tmp->e_type == 7)
	{
		if (j == 1)
			here_doc(tmp->file_name);
		else if (j == 0)
		{
			dup2(g_env->fd_hr[0], 0);
			close(g_env->fd_hr[0]);
		}
	}
	return (1);
}

void	file_out(t_file *tmp, int j)
{
	int	output;

	if (tmp->e_type == 6)
	{
		output = file_output(tmp->file_name);
		if (j == 0)
		{
			dup2(output, 1);
			close(output);
		}
	}
	else if (tmp->e_type == 8)
	{
		output = append_mode(tmp->file_name);
		if (j == 0)
		{
			dup2(output, 1);
			close(output);
		}
	}
}
