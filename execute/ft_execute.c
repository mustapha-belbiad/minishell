/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelbiad <mbelbiad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 21:17:19 by mbelbiad          #+#    #+#             */
/*   Updated: 2022/09/02 21:29:40 by mbelbiad         ###   ########.fr       */
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
	free(cmd);
	return (0);
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
	if (Pth == NULL )
	{
		write (1, "command not found\n", 19);
		return (Pth);
	}
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
	// if (redi_heredoc(cmd) == 0)
	// 	return ;
	comd = get_the_path(cmd, env);
	execve(comd[0], comd, envp);	
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
	int d;
	int j = -1;
	
	size = ft_lstsizeee(cmd);
	printf("size %d\n", size);
	t_cmd *tmp1;

	tmp1 = cmd;
	in_fd = -1;
	while(cmd != NULL)
	{
		pipe (fd);
		pid = fork();
		if (pid == 0)
		{
			run_exection(cmd, fd, in_fd, i, size, env, envp);
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
		
		//free(comd);
	}
	close(fd[1]);
	close(fd[0]);
	// while (waitpid(i, &d, 0) != -1)
	// 	;
	while(wait(NULL) != -1)
		;
} 