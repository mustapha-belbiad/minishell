/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelbiad <mbelbiad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 21:17:19 by mbelbiad          #+#    #+#             */
/*   Updated: 2022/08/30 04:06:12 by mbelbiad         ###   ########.fr       */
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
	while(Pth[++i])
		printf(" {%s} \n", Pth[i]);
	return (Pth);
}

int	check_file(char	*argv)
{
	int	check;

	check = open(argv, O_RDONLY);
	return (check);
}

int	file_out(char	*argv)
{
	int	out;

	out = open(argv, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (out == -1)
		perror ("open");
	return (out);
}

int	append_mode(char	*argv)
{
	int	out;

	out = open(argv, O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (out == -1)
		perror ("open");
	return (out);
}

// void her_doc()
// {
	
// }

void    ft_execute(t_cmd *cmd, t_env *env, t_mini *mini, char **envp)
{
	int id;
	char **comd;
	int i;
	int input;
	int output;
	// if (pipe(fd) == -1)
	// {
    //      write (1, "Error in pipe\n", 9);
	// 	return ;
	// }
	
	// int fd[2];
	// if (pipe(fd) == -1)
	// {
	// 	write (1, "Error in pipe\n", 9);
	// 	return ;
	// }
	//comd = get_the_path(cmd, env);
	// if (cmd->cmd == NULL)
	// 	return ;
	// i = -1;
	// while (cmd)
	// {
	// 	if (cmd->file->e_type == 5)
	// 	{
	// 		input = check_file(cmd->file->file_name);
	// 		if (input == -1)
	// 		{
	// 			perror ("open");
	// 			return ;
	// 		}
	// 		printf("input file is : %s \n", cmd->file->file_name);
	// 	}
	// 	else if (cmd->file->e_type == 6)
	// 	{
	// 		output = file_out(cmd->file->file_name);
	// 		printf("out put file is : %s \n", cmd->file->file_name); 
	// 	}
	// 	cmd = cmd->next;
	// }
	while(cmd != NULL)
	{
		comd = get_the_path(cmd, env);
		if (!comd)
		{
			printf("hooooopla \n");
			return ;
		}
		// printf("------{%s}---- \n", comd[0]);
		// printf("------{%s}---- \n", comd[1]);
		i = fork();
		if (i == 0)
		{
			int j = 0;
			t_file *tmp = cmd->file;
			while (tmp)
			{
				//printf(" ===={%s}=== \n", cmd->cmd[i]);
				if (tmp->e_type == 5)
				{
					input = check_file(tmp->file_name);
					if (input == -1)
					{
						perror ("open");
						return ;
					}
					dup2(input, 0);
				// dup2(1, 1);
			//printf("input file is : %s \n", tmp->file_name);
				}
				if (tmp->e_type == 6)
				{
					output = file_out(tmp->file_name);
					dup2(output, 1);
			//printf("out put file is : %s \n", cmd->file->file_name); 
				}
				if (tmp->e_type == 8)
				{
					output = append_mode(tmp->file_name);
					dup2(output, 1);
					printf("out put file is : %s \n", cmd->file->file_name); 
				}
				// if (tmp->e_type == 7) // herdoc
				// {
				// 	output = append_mode(tmp->file_name);
				// 	dup2(output, 1);
				// 	printf("out put file is : %s \n", cmd->file->file_name); 
				// }
				tmp = tmp->next;
			}
			execve(comd[0], comd, envp);
		}
		wait(NULL);
		free(comd);
		cmd = cmd->next;
	}
	
	// while(comd[++i])
	// {
	// 	pipe(fd);
		
	// 	printf(" ----- {%s} \n", comd[i]);
		
	// 	execve(comd[0], comd, NULL);
	// }
    // id = fork();
	// if (id == 0)
	// {
	// 	printf(" ---- { %s }\n", comd[0]);
	// 	printf(" ---- {%s}\n", comd[1]);
	// 	// dup2(0 ,0);
	// 	dup2(0, 1);
	// 	printf(" -- {%s} -- \n", comd[0]);
	//   	execve(comd[0], comd, envp);
	// }
	// close(fd[0]);
	// close(fd[1]);
    // wait(NULL);
} 