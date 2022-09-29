/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cd_fcnt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelbiad <mbelbiad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 14:59:23 by mbelbiad          #+#    #+#             */
/*   Updated: 2022/09/29 03:37:14 by mbelbiad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

void	pwd_fcnt(t_cmd *cmd)
{
	int	fd;

	if (cmd->file != NULL)
		fd = redirect_builtings(cmd);
	else
		fd = 1;
	free(cmd->cmd[0]);
	cmd->cmd[0] = malloc(1024 * sizeof(char *));
	if (getcwd(cmd->cmd[0], 1024) == NULL)
	{
		printf("faild \n");
		g_env->ret_val = 1;
		return ;
	}
	ft_putstr_fd(cmd->cmd[0], fd);
	ft_putstr_fd("\n", fd);
	g_env->ret_val = 0;
}

void	change_for_pwd(t_env *g_env, char *change)
{
	t_env	*tmp;
	char	*tmp2;

	tmp = g_env;
	while (tmp)
	{
		if (ft_strncmp(tmp->envir, "PWD", 3) == 0)
		{
			tmp2 = ft_strjoin("PWD=", change);
			free(tmp->envir);
			tmp->envir = tmp2;
			break ;
		}
		tmp = tmp->next;
	}
	free(change);
}

void	change_for_oldpwd(t_env *g_env, char *change)
{
	t_env	*tmp;
	char	*tmp2;

	change = ft_substr(change, 4, ft_strlen(change));
	tmp = g_env;
	while (tmp)
	{
		if (ft_strncmp(tmp->envir, "OLDPWD", 6) == 0)
		{
			tmp2 = ft_strjoin("OLDPWD=", change);
			free(tmp->envir);
			tmp->envir = tmp2;
			break ;
		}
		tmp = tmp->next;
	}
	free(change);
}

int	change_env(t_env *g_env, char *value)
{
	char	*change;

	if (ft_strncmp(value, "OLDPWD", 6) == 0)
	{
		change = strrr(g_env, "PWD");
		if (change == NULL)
			return (0);
		change_for_oldpwd(g_env, change);
	}
	else if (ft_strncmp(value, "PWD", 3) == 0)
	{
		change = malloc(1024 * sizeof(char *));
		if (getcwd(change, 1024) == NULL)
		{
			free(change);
			return (0);
		}
		change_for_pwd(g_env, change);
	}
	return (1);
}

void	cd_fcnt(t_cmd *cmd)
{
	char	*str;
	t_env	*env;
	char	*tmp2;
	char	*home;

	if (cmd->file != NULL)
		redirect_builtings(cmd);
	env = g_env;
	if (cmd->cmd[1] == NULL)
	{
		home = strrr(env, "HOME=");
		if (home == NULL)
		{
			printf("No such file or directory \n");
			g_env->ret_val = 1;
			return ;
		}
		str = ft_substr(home, 6, ft_strlen(home));
		tmp2 = ft_strjoin("/", str);
		free(str);
	}
	else
		tmp2 = ft_strdup(cmd->cmd[1]);
	cd_fcnt2(tmp2);
}
