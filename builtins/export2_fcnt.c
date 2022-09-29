/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2_fcnt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelbiad <mbelbiad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 17:02:34 by mbelbiad          #+#    #+#             */
/*   Updated: 2022/09/29 03:27:04 by mbelbiad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

int	ft_search(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			break ;
	}
	if (str[i] == c)
		return (1);
	return (0);
}

int	ft_check_args(t_cmd *cmd, int i)
{
	char	**check;

	check = ft_split(cmd->cmd[i], '=');
	if (check == NULL)
		return (0);
	if (ft_isalpha(cmd->cmd[i][0]) != 1
		&& cmd->cmd[i][0] != '_')
	{
		printf("not valid \n");
		ft_free(check);
		return (0);
	}
	if (ft_check_args2(check) == 0)
	{
		ft_free(check);
		return (0);
	}
	ft_free(check);
	return (1);
}

void	ft_join_quot(t_cmd *tmp, char **sp, int i)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = tmp->cmd[i];
	if (ft_search(tmp->cmd[i], '=') == 1 && sp[1] == NULL)
	{	
		tmp->cmd[i] = ft_strjoin(tmp1, "\"\"");
		free(tmp1);
	}
	else
	{
		tmp2 = ft_strjoin("\"", sp[1]);
		free(sp[1]);
		sp[1] = ft_strjoin(tmp2, "\"");
		free(tmp2);
		tmp2 = ft_strjoin("=", sp[1]);
		free(tmp->cmd[i]);
		free(sp[1]);
		tmp->cmd[i] = ft_strjoin(sp[0], tmp2);
		free(tmp2);
		free(sp[0]);
	}
	free(sp);
}

void	ft_check_quot(t_cmd **cmd)
{
	char	**sp;
	t_cmd	*tmp;
	int		i;
	char	*check;

	i = 0;
	tmp = (*cmd);
	while (tmp->cmd[++i])
	{
		check = ft_strchr(tmp->cmd[i], '=');
		sp = ft_split(tmp->cmd[i], '=');
		if (sp == NULL || sp[0] == NULL)
			break ;
		if (check && check[1] == '=')
		{
			free(sp[1]);
			sp[1] = ft_substr(check, 1, ft_strlen(check));
		}
		if ((sp[1] != NULL && sp[1][0] == '"') || sp[1] == NULL)
			ft_free(sp);
		else
			ft_join_quot(tmp, sp, i);
	}
}

int	check_exist(t_cmd *cmd, int i)
{
	char	**sp;
	t_env	*tmp;

	if (ft_check_args(cmd, i) == 0)
		return (0);
	sp = ft_split(cmd->cmd[i], '=');
	tmp = g_env;
	while (tmp != NULL)
	{
		if (sp[0] && ft_strcmp2(sp[0], tmp->envir) == 1)
		{
			if (sp[1] == NULL)
			{
				ft_free(sp);
				g_env->ret_val = 1;
				return (0);
			}
			check_exist2(tmp, cmd, sp, i);
			return (0);
		}
		tmp = tmp->next;
	}
	ft_free(sp);
	return (1);
}
