/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redi_here.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelbiad <mbelbiad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 19:07:17 by mbelbiad          #+#    #+#             */
/*   Updated: 2022/09/06 02:47:14 by mbelbiad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

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
	char **rr;

	//g_env->fd;
	while (1)
	{
		str = readline(">");
		str = ft_strjoin(str, "\n");
		//ft_putstr_fd(str, g_env->fd);
		if (ft_strchr(file, ';') != 0)
		{
			rr = ft_split(file, ';');
			if (ft_strcmp(str, rr[0]) != 0)
			{
				//printf("%s\n", str);
				break;
			}
		}
		else if (ft_strcmp(file, str) != 0)
		{
			printf(" == >hani kharj \n");
			break;
		}
	}
}

int redi_heredoc(t_cmd *cmd)
{
    t_file *tmp;
    int input;
    int output;

    tmp = cmd->file;
			while (tmp)
			{
				if (tmp->e_type == 5)
				{
					input = check_file(tmp->file_name);
					if (input == -1)
					{
						perror ("open");
						return(0);
					}
					dup2(input, 0);
				}
				else if (tmp->e_type == 6)
				{
					output = file_out(tmp->file_name);
					dup2(output, 1);
					//close(output);
				}
				else if (tmp->e_type == 8)
				{
					output = append_mode(tmp->file_name);
					dup2(output, 1);
					printf("out put file is : %s \n", cmd->file->file_name); 
				}
				else if (tmp->e_type == 7) // herdoc
				{
	
					here_doc(tmp->file_name);
					if (cmd->cmd[0] == NULL)
						break;
					// else
					// 	dup2(g_env->fd, 0);
				}
				tmp = tmp->next;
            }
		// if (cmd->cmd[0] == NULL)
		// 	return (0);
    return (1);
}