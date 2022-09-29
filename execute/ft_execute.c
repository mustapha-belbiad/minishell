/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelbiad <mbelbiad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 21:17:19 by mbelbiad          #+#    #+#             */
/*   Updated: 2022/09/29 18:11:03 by mbelbiad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

char	*strrr(t_env *env, char *pth)
{
	int	i;

	i = 0;
	env = g_env;
	while (env != NULL)
	{
		if (ft_strnstr(env->envir, pth, 5) != NULL)
			break ;
		env = env->next;
	}
	if (env == NULL)
		return (0);
	return (env->envir);
}

char	**command_check(char **cmd, char **rest)
{
	char	*path;
	int		i;

	i = 0;
	while (cmd[i])
	{
		cmd[i] = ft_strjoin(cmd[i], "/");
		path = ft_strjoin(cmd[i], rest[0]);
		if (access(path, F_OK) == 0)
		{
			free(rest[0]);
			rest[0] = path;
			while (cmd[++i])
				free(cmd[i]);
			free(cmd);
			return (rest);
		}
		free(path);
		i++;
	}
	return (cmd);
}

char	**get_the_path(t_cmd *cmd)
{
	char	*path;
	char	**str;
	char	**pth;
	int		i;

	i = 0;
	path = strrr(g_env, "PATH=");
	if (path == NULL)
		return (0);
	path = ft_substr(path, 6, ft_strlen(path));
	str = ft_split(path, ':');
	free(path);
	pth = command_check(str, cmd->cmd);
	return (pth);
}

void	run_exection(t_cmd *cmd, int in_fd, int i, char **envp)
{
	char	**comd;

	signal(SIGQUIT, SIG_DFL);
	if (cmd->cmd[0] == NULL)
		exit(g_env->ret_val);
	ft_dup_files(i, g_env->size, in_fd, cmd);
	if (ft_check_builtins(cmd) == 1)
		exit(g_env->ret_val);
	if (access(cmd->cmd[0], F_OK) != 0)
		comd = get_the_path(cmd);
	else
		comd = cmd->cmd;
	if (!comd)
	{
		printf("%s: No such file or directory \n", cmd->cmd[0]);
		exit(g_env->ret_val);
	}
	if (execve(comd[0], comd, envp) < 0)
	{
		printf("command not found\n");
		exit(g_env->ret_val);
	}	
}

void	ft_execute(t_cmd *cmd, char **envp)
{
	g_env->i = 0;
	g_env->size = ft_lstsizeee(cmd);
	g_env->in_fd = -1;
	while (cmd != NULL)
	{
		if (redi_heredoc(cmd) == 0)
		{
			cmd = cmd->next;
			g_env->i++;
		}
		else
		{
			if (cmd->next == NULL && (ft_check_builtins(cmd) == 1))
				break ;
			ft_execute_pipe(cmd, envp);
			if (g_env->pid != 0)
				cmd = cmd->next;
		}
	}
	close(g_env->fd_exec[1]);
	close(g_env->fd_exec[0]);
	ft_waiting(g_env->pid);
}
