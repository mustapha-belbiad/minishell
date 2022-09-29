/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelbiad <mbelbiad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:27:31 by mbelbiad          #+#    #+#             */
/*   Updated: 2022/09/29 18:27:10 by mbelbiad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

void	ft_waiting(pid_t pid)
{
	waitpid(pid, &g_env->status_num, 0);
	if (pid != 0)
	{
		if (WIFEXITED(g_env->status_num))
			g_env->ret_val = WEXITSTATUS(g_env->status_num);
		else if (WIFSIGNALED(g_env->status_num))
			g_env->ret_val = WTERMSIG(g_env->status_num) + 128;
	}	
	while (wait(NULL) != -1)
		;
}

t_cmd	*ft_execute_pipe(t_cmd *cmd, char **envp)
{
	if (cmd->cmd != NULL)
	{
		pipe (g_env->fd_exec);
		g_env->pid = fork();
		if (g_env->pid == 0)
			run_exection(cmd, g_env->in_fd, g_env->i, envp);
		else
		{
			close(g_env->fd_exec[1]);
			if (g_env->in_fd != -1)
				close(g_env->in_fd);
			g_env->in_fd = g_env->fd_exec[0];
			g_env->i++;
		}
	}
	return (cmd);
}

void	ft_dup_files(int i, int size, int in_fd, t_cmd *cmd)
{
	close(g_env->fd_exec[0]);
	if (i != size -1)
	{
		dup2(g_env->fd_exec[1], 1);
		close(g_env->fd_exec[1]);
	}
	if (in_fd != -1)
	{
		dup2(in_fd, 0);
		close(in_fd);
	}
	if (cmd->file != NULL)
		redrct_for_exec(cmd);
}

int	ft_check_str_herdoc(char *file, char *str)
{
	char	*rr;

	if (str[0] != 0
		&& (ft_strncmp(file, str, ft_strlen(str)) == 0))
	{
		free(str);
		return (0);
	}
	else
	{
		rr = ft_strjoin(str, "\n");
		ft_putstr_fd(rr, g_env->fd_hr[1]);
		free(rr);
		free(str);
	}
	return (1);
}

void	here_doc(char *file)
{
	char	*str;

	pipe(g_env->fd_hr);
	while (1)
	{
		g_env->crtl_c = 1;
		str = readline(">");
		if (!str)
			break ;
		if (str)
		{
			if (ft_check_str_herdoc(file, str) == 0)
				break ;
		}
	}
	close(g_env->fd_hr[1]);
	g_env->crtl_c = 0;
}
