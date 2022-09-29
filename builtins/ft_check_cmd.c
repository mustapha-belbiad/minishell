/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelbiad <mbelbiad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 15:18:06 by mbelbiad          #+#    #+#             */
/*   Updated: 2022/09/29 15:01:53 by mbelbiad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

int	ft_strrrcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] != '\0' && s2[i] != '\0'))
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	if (s1[i] != s2[i])
		return (0);
	return (1);
}

int	redirect_builtings(t_cmd *cmd)
{
	t_file	*tmp;
	int		fd;

	tmp = cmd->file;
	while (tmp)
	{
		if (tmp->e_type == 6)
			fd = file_output(tmp->file_name);
		else if (tmp->e_type == 8)
		{
			fd = append_mode(tmp->file_name);
		}
		tmp = tmp->next;
	}
	return (fd);
}

void	exit_fcnt(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->cmd[1] == NULL)
		exit(g_env->ret_val);
	else if (cmd->cmd[1] != NULL && cmd->cmd[2] == NULL)
	{
		i = -1;
		while (cmd->cmd[1][++i])
		{
			if (!ft_isdigit(cmd->cmd[1][i]))
				g_env->ret_val = 255;
		}
		printf("exit\n");
		if (g_env->ret_val != 255)
			g_env->ret_val = ft_atoi(cmd->cmd[1]) % 256;
		else
			printf("numeric argument required \n");
		exit(g_env->ret_val);
	}
	else if (cmd->cmd[2] != NULL)
		exit_fcnt2_norm(cmd, i);
}

int	check_built2(t_cmd *cmd)
{
	if (ft_strrrcmp(cmd->cmd[0], "unset") == 1)
	{
		unset_fcnt(cmd);
		g_env->ret_val = 0;
		return (1);
	}
	else if (ft_strrrcmp(cmd->cmd[0], "env") == 1)
	{
		env_fcnt(cmd);
		g_env->ret_val = 0;
		return (1);
	}
	else if (ft_strrrcmp(cmd->cmd[0], "exit") == 1)
	{
		exit_fcnt(cmd);
		g_env->ret_val = 0;
		return (1);
	}
	else if (ft_strrrcmp(cmd->cmd[0], "echo") == 1)
	{
		echo_fcnt(cmd);
		g_env->ret_val = 0;
		return (1);
	}
	return (0);
}

int	ft_check_builtins(t_cmd *cmd)
{
	if (cmd->cmd[0] == NULL)
		return (0);
	if (ft_strrrcmp(cmd->cmd[0], "pwd") == 1)
	{
		pwd_fcnt(cmd);
		return (1);
	}
	else if (ft_strrrcmp(cmd->cmd[0], "cd") == 1 && g_env->size == 1)
	{
		cd_fcnt(cmd);
		return (1);
	}
	else if (ft_strrrcmp(cmd->cmd[0], "export") == 1)
	{
		export_fcnt(cmd);
		return (1);
	}
	else if (check_built2(cmd) == 1)
		return (1);
	else
		return (0);
}
