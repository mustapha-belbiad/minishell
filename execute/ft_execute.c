/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelbiad <mbelbiad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 21:17:19 by mbelbiad          #+#    #+#             */
/*   Updated: 2022/09/11 04:43:57 by mbelbiad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

char	*strrr(t_env *env)
{
	char	*pth;
	char	*re;
	int		i;

	i = 0;	
	pth = "PATH=";
	while (env != NULL)
	{
		if (ft_strnstr(env->envir, pth, 5) != NULL)
			break;
		env = env->next;
	}
	
	if (env == NULL)
		exit(0);
	// while (env[++i])
	// 	printf("%s \n", env[i]);
	//while (ft_strnstr(env[i], pth, 5) == NULL && env[i] != NULL)
	//	i++;
	// re = env[i];
	// if (re == NULL)
	// 	exit (3);
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

char	**get_the_path(t_cmd *cmd, t_env *env)
{
	char	*Path;
	char	**str;
	char	**rest;
	char	**Pth;
	int i;

	i = 0;
	// while (cmd->cmd[i])
	// {
	// 	printf ("cmd is : %s\n", cmd->cmd[i++]);
	// }
	Path = strrr(env);
	Path = ft_substr(Path, 6, ft_strlen(Path));
	str= ft_split(Path, ':');
	//printf("--- {%s} --- \n", str[0]);
	//free(Path); 
	//rest = ft_split(argv, ' ');
	// if (access(, F_OK) == 0)
	// {
	// 	//ft_free(str); \\\ command with path 
	// 	return (rest);
	// }
	// printf(" str ;; == {%s} \n", str[0]);
	Pth = command_check(str, cmd->cmd);
	//printf("rest ;; --------------------------------- {%s} \n", Pth[0]);
	// if (Pth == NULL )
	// {
	// 	write (1, "\n", 19);
	// 	return (Pth);
	// }
	i = -1;
	// while(Pth[++i])
	// 	printf(" {%s} \n", Pth[i]);
	return (Pth);
}
void	run_exection(t_cmd *cmd, int *fd, int in_fd, int i, int size, t_env *env, char **envp)
{
	char **comd;
	
	close(fd[0]);
	if (i != size -1)
	{
		dup2(fd[1], 1);
		close(fd[1]);
	}
	// dup2 outfils
	if (in_fd != -1)
	{
		dup2(in_fd, 0);
		close(in_fd);
	}
	//dup2 infils
	if (redi_heredoc(cmd) == 0)
		return ;
	comd = get_the_path(cmd, env);
	if (!comd)
		return ;
	//printf("%s \n", comd[0]);
	if (execve(comd[0], comd, envp) < 0)
	{
		write (1, "command not found\n", 19);
		exit(1);
	}	
}

void    ft_execute(t_cmd *cmd, t_env *env, t_mini *mini, char **envp)
{
	int fd[2];
	int in_fd;
	char **comd;
	t_file *tmp;
	pid_t pid;
	int i = 0;
	int size;
	int j = -1;
	
	if (cmd->cmd == NULL)
		return ;
	size = ft_lstsizeee(cmd);
	t_cmd *tmp1;

	tmp1 = cmd;
	in_fd = -1;
	while(cmd != NULL)
	{
		pipe (fd);
		if (ft_check_builtins(cmd) == 1)
		{
			cmd = cmd->next;
			i++;
		}
		else 
		{
			pid = fork();
			if (pid == 0)
			{
				run_exection(cmd, fd, in_fd, i, size, env, envp);
				if (!cmd->cmd)
					break;
			}
	 		else 
			{
				close(fd[1]);
				if (in_fd != -1)
					close(in_fd);
				in_fd = fd[0];
				cmd = cmd->next;
				i++;
			}
		
		}
		
		//free(comd);
	}
	close(fd[1]);
	close(fd[0]);
	while (waitpid(pid, &g_env->ret_val, 0) != -1)
		;
	// while(wait(NULL) != -1)
	// 	;
	// if (!cmd->cmd)
	// 	return ;
} 