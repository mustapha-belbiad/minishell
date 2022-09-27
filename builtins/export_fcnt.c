/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_fcnt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kouc <ael-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 15:46:07 by mbelbiad          #+#    #+#             */
/*   Updated: 2022/09/27 21:32:11 by ael-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

void	ft_free(char	**cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		free(cmd[i++]);
	free(cmd);
}

int	ft_check_args2(char **check)
{
	int	j;

	j = 0;
	while (check[0] && check[0][++j])
	{
		if (!ft_isalnum(check[0][j])
			&& check[0][j] != '_'
			&& check[0][j] != '='
			&& check[0][j] != '"')
		{
			printf(" { %s} : not valid \n", check[0]);
			return (0);
		}
	}
	j = -1;
	while (check[1] && check[1][++j])
	{
		if (!ft_isprint(check[1][j]))
		{
			printf(" { %s} : not valid \n", check[1]);
			return (0);
		}
	}
	return (1);
}

void	add_to_export(t_cmd *cmd)
{
	int	i;

	if (cmd->cmd[1][0] != '\0')
	{
		i = 0;
		while (cmd->cmd[++i])
		{
			if (check_exist(cmd, i) == 1)
			{
				ft_check_quot(&cmd);
				ft_list_addback(&g_env, ft_lstnew(cmd->cmd[i]));
			}
		}
	}
	change_envir();
}

void	export_fcnt(t_cmd *cmd)
{
	t_env	*tmp;
	int		fd;

	if (cmd->file != NULL)
		fd = redirect_builtings(cmd);
	else
		fd = 1;
	if (cmd->cmd[1] == NULL)
	{
		tmp = g_env;
		while (tmp != NULL)
		{
			ft_putstr_fd("declare -x ", fd);
			ft_putstr_fd(tmp->envir, fd);
			ft_putstr_fd("\n", fd);
			tmp = tmp->next;
		}
	}
	else
		add_to_export(cmd);
}

void	ft_remove_quot(t_env **cmd)
{
	char	**sp;

	sp = ft_split((*cmd)->envir, '"');
	if (sp == NULL || sp[1] == NULL)
		return ;
		(*cmd)->envir = ft_strjoin(sp[0], sp[1]);
}
