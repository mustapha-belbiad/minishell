/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_file_norm.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelbiad <mbelbiad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 03:23:39 by mbelbiad          #+#    #+#             */
/*   Updated: 2022/09/29 15:09:13 by mbelbiad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

void	check_exist2(t_env *tmp, t_cmd *cmd, char **sp, int i)
{
	free(tmp->envir);
	ft_check_quot(&cmd);
	tmp->envir = ft_strdup(cmd->cmd[i]);
	ft_free(sp);
	g_env->ret_val = 1;
}

void	exit_fcnt2_norm(t_cmd *cmd, int i)
{
	i = -1;
	while (cmd->cmd[1][++i])
	{
		if (!ft_isdigit(cmd->cmd[1][i]))
		{
			g_env->ret_val = 255;
			printf("exit\n");
			printf("numeric argument required \n");
			exit(g_env->ret_val);
		}
	}
	printf("bash: exit: too many arguments \n");
	g_env->ret_val = 1;
	return ;
}

void	cd_fcnt2(char *tmp2)
{
	if (change_env(g_env, "OLDPWD") == 0)
	{	
		free(tmp2);
		g_env->ret_val = 1;
		return ;
	}
	if (chdir(tmp2) == -1)
	{
		printf("No such file or directory \n");
		g_env->ret_val = 1;
	}
	if (change_env(g_env, "PWD") == 0)
	{
		free(tmp2);
		g_env->ret_val = 1;
		return ;
	}
	g_env->ret_val = 0;
	free(tmp2);
}

int	first_arg(t_cmd *cmd, t_env *tmp1, int i)
{
	t_env	*tmp2;

	if (ft_strcmp(cmd->cmd[i], tmp1->envir) == 1)
	{
		tmp2 = tmp1;
		g_env = tmp2->next;
		g_env->envb = tmp2->envb;
		free(tmp2->envir);
		free(tmp2);
		g_env->ret_val = 0;
		change_envir();
		return (0);
	}
	return (1);
}
