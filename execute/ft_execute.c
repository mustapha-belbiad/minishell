/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelbiad <mbelbiad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 21:17:19 by mbelbiad          #+#    #+#             */
/*   Updated: 2022/09/02 03:34:52 by mbelbiad         ###   ########.fr       */
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
	while (cmd->cmd[i])
	{
		printf ("cmd is : %s\n", cmd->cmd[i++]);
	}
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

void    ft_execute(t_cmd *cmd, t_env *env, t_mini *mini, char **envp)
{
	int fd[2];
	int in_fd;
	char **comd;
	t_file *tmp;
	int i;
	t_cmd *tmp1;

	tmp1 = cmd;
	
	// while (tmp1->next != NULL)
	// {
	// 	if (pipe(fd) == -1)
	// 	{
	// 		printf("-- {%s} -- \n", tmp1->cmd[0]);
	// 		perror("pipe error");
	// 		return ;
	// 	}
	// 	tmp1 = tmp1->next;
	// }
	//comd = get_the_path(cmd, env);
	in_fd = -1;
	// pipe (fd);
	while(cmd != NULL)
	{
		if (cmd->next != NULL)
		{
			//printf("=======> {1}\n ");
			pipe (fd);
		}
		i = fork();
		if (i == 0)
		{
			// dup2(in_fd, 0);
			// //dup2(fd[1], 1);
			// //close (in_fd);
			// close(fd[0]);
			if (in_fd == -1)
			{
				printf("hola\n");
				close(fd[0]);
				dup2(fd[1], 1);
				close(fd[1]);
			}
			else if (cmd->next == NULL)
			{
				//printf(" ===> hola  {%s}\n", cmd->cmd[0]);
				close(fd[1]);
				dup2(fd[0], 0);
				dup2(1, 1);
				close(fd[0]);
			}
			else
			{
				//printf("hola 2\n");
				dup2(fd[0], 0);
				dup2(fd[1], 1);
				close(fd[0]);
				close(fd[1]);
			}
			  
			// if (redi_heredoc(cmd) == 0)
			// 	return ;
			comd = get_the_path(cmd, env);
			if (!comd)
			{
				//printf("{%s}\n", comd[0]);
				printf("hooooopla \n");
				return ;
			}
			// if (cmd->next == NULL)
			// 	dup2(1, 1);
			//printf ("{%s}\n", cmd->cmd[0]);
			// close(fd[0]);
			// close(fd[1]);
			execve(comd[0], comd, envp);
		}
		// else 
		// {
	 	in_fd = 0;
			// close(fd[0]);
			// close(fd[1]);
		// }
		
		cmd = cmd->next;
		
		//free(comd);
	}
	close(fd[0]);
	close(fd[1]);
	while(wait(NULL) != -1)
		;
	// i = fork();
	// if (i == 0)
	// {
	// 	dup2(in_fd, 0);
	// 	close(in_fd);
	// 	// dup2(1, 1);
	// 	// close(1);
	// 	comd = get_the_path(cmd, env);
	// 	if (!comd)
	// 	{
	// 			//printf("{%s}\n", comd[0])
	// 		printf("hooooopla \n");
	// 		return ;
	// 	}
	// 	// close(in_fd);
	// 	// close(fd[1]);
	// 	printf("hoplaaa  =%d=    {%s}\n", in_fd, cmd->cmd[0]);
	// 	execve(comd[0], comd, envp);
	// }
	// wait(NULL);
	//close(in_fd);
} 