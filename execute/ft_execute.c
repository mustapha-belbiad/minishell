/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelbiad <mbelbiad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 21:17:19 by mbelbiad          #+#    #+#             */
/*   Updated: 2022/09/26 17:26:57 by mbelbiad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

char	*strrr(t_env *env, char *pth)
{
	char	*re;
	int		i;

	i = 0;
	env = g_env;
	while (env != NULL)
	{
		if (ft_strnstr(env->envir, pth, 5) != NULL)
			break;
		env = env->next;
	}
	
	if (env == NULL)
		return(0);
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
	// free(cmd);
	return (cmd);
}

char	**get_the_path(t_cmd *cmd)
{
	char	*Path;
	char	**str;
	char	**rest;
	char	**Pth;
	int i;

	i = 0;
	Path = strrr(g_env, "PATH=");
	if (Path == NULL)
		return(0);
	Path = ft_substr(Path, 6, ft_strlen(Path));
	str= ft_split(Path, ':');
	free(Path);
	Pth = command_check(str, cmd->cmd);
	return (Pth);
}

void	run_exection(t_cmd *cmd, int in_fd, int i, int size, char **envp)
{
	char **comd;

	if (cmd->cmd[0] == NULL)
		exit(0);
	close(g_env->fd_exec[0]);
	if (i != size -1)
	{
		dup2(g_env->fd_exec[1], 1);
		close(g_env->fd_exec[1]);
	}
	else if (in_fd != -1)
	{
		dup2(in_fd, 0);
		close(in_fd);
	}
	if (cmd->file!= NULL)
		redrct_for_exec(cmd);
	
	if (ft_check_builtins(cmd, g_env->fd_exec) == 1)
		exit(0);
	if (access(cmd->cmd[0], F_OK) != 0)
		comd = get_the_path(cmd);
	else
		comd = cmd->cmd;
	if (!comd)
	{
		printf("%s: No such file or directory \n", cmd->cmd[0]);
		exit(0);
	}
	if (execve(comd[0], comd, envp) < 0)
	{
		write (1, "command not found\n", 19);
		//g_env->ret_val = 0;
		printf("--> {%d}\n", g_env->ret_val);
		exit(g_env->ret_val);
	}	
}

void     ft_execute(t_cmd *cmd, t_env *env, t_mini *mini, char **envp)
{
	int in_fd;
	pid_t pid;
	int i = 0;
	int size;
	
	size = ft_lstsizeee(cmd);
	t_cmd *tmp1;
	in_fd = -1;
	while(cmd != NULL)
	{
		if (redi_heredoc(cmd) == 0)
		{
			cmd = cmd->next;
			i++;
		}
		else
		{
			if (cmd->next == NULL && (ft_check_builtins(cmd, g_env->fd_exec) == 1))
			{
				g_env->ret_val = 1;
				break ;
			}
			if (cmd->cmd != NULL)
			{ 
				pipe (g_env->fd_exec);
				pid = fork();
				if (pid == 0)
				{
					run_exection(cmd, in_fd, i, size, envp);
				}
				else 
				{
					close(g_env->fd_exec[1]);
					if (in_fd != -1)
						close(in_fd);
					in_fd = g_env->fd_exec[0];
					cmd = cmd->next;
					i++;
				}
			} 		
		
		}
		//if (cmd->next == NULL)
	 close(g_env->fd_exec[1]);
	 close(g_env->fd_exec[0]);
	
	 }
	waitpid(pid, &g_env->status_num, 0);
	if (pid != 0)
	{
		if(WIFEXITED(g_env->status_num))
			g_env->ret_val = WEXITSTATUS(g_env->status_num);
		else if (WIFSIGNALED(g_env->status_num))
			g_env->ret_val = WTERMSIG(g_env->status_num) + 128;
	}	
	while(wait(NULL) != -1)
		;
	// if (!cmd->cmd)
	// 	return ;
} 