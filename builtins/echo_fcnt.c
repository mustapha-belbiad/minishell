/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_fcnt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelbiad <mbelbiad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 18:52:48 by mbelbiad          #+#    #+#             */
/*   Updated: 2022/09/27 20:03:29 by mbelbiad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

int	ft_check_echo(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[i] == '-' && cmd[i + 1] == 'n')
	{
		while (cmd[++i] == 'n')
			;
		if (cmd[i] == '\0')
			return (1);
	}
	return (0);
}

void	ft_echo_exec(t_cmd *cmd, int i, int fd)
{
	if (i == 1)
	{
		while (cmd->cmd[i])
		{
			ft_putstr_fd(cmd->cmd[i], fd);
			ft_putstr_fd(" ", fd);
			i++;
		}
		ft_putstr_fd("\n", fd);
		return ;
	}
	else
	{
		while (cmd->cmd[i])
		{
			ft_putstr_fd(cmd->cmd[i], fd);
			if (cmd->cmd[i + 1] != '\0')
				ft_putstr_fd(" ", fd);
			i++;
		}
	}
}

void	echo_fcnt(t_cmd *cmd)
{
	int	i;
	int	fd;

	if (cmd->file != NULL)
		fd = redirect_builtings(cmd);
	else
		fd = 1;
	if (cmd->cmd[1] == NULL)
	{
		ft_putstr_fd("\n", fd);
		return ;
	}
	i = 1;
	while (cmd->cmd[i])
	{
		if (ft_check_echo(cmd->cmd[i]) == 1)
			i++;
		else
			break ;
	}
	ft_echo_exec(cmd, i, fd);
}
