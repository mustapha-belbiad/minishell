/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelbiad <mbelbiad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 21:17:19 by mbelbiad          #+#    #+#             */
/*   Updated: 2022/08/30 18:09:20 by mbelbiad         ###   ########.fr       */
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

void here_doc(char *file)
{
	char *str;
	
	while (1)
	{
		str =readline(">");
		if (str != NULL)
			str = ft_strjoin(str, "\n");
		if (ft_strcmp(file, str) != 0 && str != NULL)
			break;
	}
}

void    ft_execute(t_cmd *cmd, t_env *env, t_mini *mini, char **envp)
{
	int fd[2];
	char **comd;
	t_file *tmp;
	int i;
	int input;
	int output;
	t_cmd *tmp1;

	tmp1 = cmd;
	
	while (tmp1->next != NULL)
	{
		if (pipe(fd) == -1)
		{
			printf("-- {%s} -- \n", tmp1->cmd[0]);
			perror("pipe error");
			return ;
		}
		tmp1 = tmp1->next;
	}
	//comd = get_the_path(cmd, env);
	input = -1;
	while(cmd != NULL)
	{
		i = fork();
		if (i == 0)
		{
			if (input == -1)
			{
				close(fd[0]);
				dup2(fd[1], 1);
			}
			else 
			{
				dup2(fd[0], 0);
				dup2(fd[1], 1);
			}
			tmp = cmd->file;
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
				else if (tmp->e_type == 6)
				{
					output = file_out(tmp->file_name);
					dup2(output, 1);
			//printf("out put file is : %s \n", cmd->file->file_name); 
				}
				else if (tmp->e_type == 8)
				{
					output = append_mode(tmp->file_name);
					dup2(output, 1);
					printf("out put file is : %s \n", cmd->file->file_name); 
				}
				else if (tmp->e_type == 7) // herdoc
				{
					//printf(" ======> hani hna -------- \n");
					here_doc(tmp->file_name);
					if (cmd->cmd[0] == NULL)
						return ;
				// 	dup2(output, 1);
				// 	printf("out put file is : %s \n", cmd->file->file_name); 
				}
				tmp = tmp->next;
			}
			printf(" ===== hopla 111 \n");
			comd = get_the_path(cmd, env);
			if (!comd)
			{
				printf("{%s}\n", comd[0]);
				printf("hooooopla \n");
				return ;
			}
			printf(" ===== hopla \n");
			execve(comd[0], comd, envp);
		}
		wait(NULL);
		//close(fd[1]);
		
		//free(comd);
		cmd = cmd->next;
	}
	close(fd[0]);
	close (fd[1]);
	
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