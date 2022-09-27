/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_fcnt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelbiad <mbelbiad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 18:32:34 by mbelbiad          #+#    #+#             */
/*   Updated: 2022/09/27 18:51:06 by mbelbiad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

int	ft_check_unset(char *cmd)
{
	int	i;

	if (cmd == NULL || cmd[0] == '\0')
		return (0);
	if (cmd[0] >= '0' && cmd[0] <= '9')
		return (0);
	if (cmd[0] == '_')
		i = 1;
	else
		i = 0;
	while (cmd[i])
	{
		if ((cmd[i] >= '0' && cmd[i] <= '9')
			|| (cmd[i] >= 'a' && cmd[i] <= 'z')
			|| (cmd[i] >= 'A' && cmd[i] <= 'Z')
			|| cmd[i] == '_')
			i++;
		else
			return (0);
	}
	return (1);
}

void	ft_unset_remove(t_env *tmp1, t_cmd *cmd, int i)
{
	t_env	*tmp2;
	t_env	*head;

	while (tmp1 != NULL)
	{
		if (ft_strcmp(cmd->cmd[i], tmp1->envir) == 1)
		{
			tmp2 = tmp1;
			head->next = tmp2->next;
			tmp1 = g_env;
			break ;
		}
		head = tmp1;
		tmp1 = tmp1->next;
	}
}

void	unset_fcnt(t_cmd *cmd)
{
	t_env	*tmp1;
	t_cmd	*cmd_tp;
	int		i;

	i = 0;
	if (cmd->file != NULL)
		redirect_builtings(cmd);
	cmd_tp = cmd;
	while (cmd_tp->cmd[++i])
	{	
		if (ft_check_unset(cmd->cmd[i]) == 0)
		{
			printf("%s : not a valid identifier \n", cmd->cmd[i]);
			return ;
		}
		tmp1 = g_env;
		if (ft_strcmp(cmd->cmd[i], tmp1->envir) == 1)
		{
			tmp1 = g_env->next;
			g_env = tmp1;
			return ;
		}
		ft_unset_remove(tmp1, cmd, i);
	}
}

int	ft_check_env(char *env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (env[i] == '=')
			break ;
	}
	if (env[i] == '=')
		return (1);
	else
		return (0);
}

void	env_fcnt(t_cmd *cmd)
{
	t_env	*tmp;
	int		fd;

	if (cmd->file != NULL)
		fd = redirect_builtings(cmd);
	else
		fd = 1;
	tmp = g_env;
	while (tmp != NULL)
	{
		if (ft_check_env(tmp->envir) == 0)
			tmp = tmp->next;
		else
		{
			ft_remove_quot(&g_env);
			ft_putstr_fd(tmp->envir, fd);
			ft_putstr_fd("\n", fd);
			tmp = tmp->next;
		}
	}
}
