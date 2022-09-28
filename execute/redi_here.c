/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redi_here.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelbiad <mbelbiad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 19:07:17 by mbelbiad          #+#    #+#             */
/*   Updated: 2022/09/28 04:45:11 by mbelbiad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

int	check_file(char	*argv)
{
	int	check;

	check = open(argv, O_RDONLY);
	return (check);
}

int	file_output(char	*argv)
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
void hola(int sig)
{
	(void)sig;
	return ;
}
void	here_doc(char *file)
{
	char *str;
	char *rr;
	//int i;
	
	
	pipe(g_env->fd_hr);
	while (1)
	{
		g_env->crtl_c = 1;
		str = readline(">");
		if (!str)
			break ;
		if (str)
		{
			if ( str[0] != 0 && 
				(ft_strncmp(file, str, ft_strlen(str)) == 0))
			{
				free(str);
				break;
			}
			else 
			{
				rr = ft_strjoin(str, "\n");
				ft_putstr_fd(rr, g_env->fd_hr[1]);
				free(rr);
				free(str);
			}
		}
	}
	close(g_env->fd_hr[1]);
	g_env->crtl_c = 0;
}

int	redrct_for_exec(t_cmd *cmd)
{
	t_file *tmp;
    int j;
   // int output;
	j = 0;
	if (cmd->file == NULL)
		return(3);
    tmp = cmd->file;
	while (tmp)
	{
		if (tmp->e_type == 5 || tmp->e_type == 7)
		{
			if(file_in(tmp, j) == 0)
				return(0);
			// if (cmd->cmd[0] == NULL)
			// 	break;
		}
		else if (tmp->e_type == 6 || tmp->e_type == 8)
		{
			file_out(tmp, j);
			// if (cmd->cmd[0] == NULL)
			// 	break;
		}
		tmp = tmp->next;
	}
    return (1);
}

int redi_heredoc(t_cmd *cmd)
{
    t_file *tmp;
    //int input;
    //int output;
	int j = 1;
	if (cmd->file == NULL)
		return(3);
    tmp = cmd->file;
	while (tmp)
	{
		

		if (tmp->e_type == 5 || tmp->e_type == 7)
		{
			if (file_in(tmp, j) == 0)
				return(0);
			// if (cmd->cmd[0] == NULL)
			// 	break;
		}
		else if (tmp->e_type == 6 || tmp->e_type == 8)
		{
			file_out(tmp, j);
			// if (cmd->cmd[0] == NULL)
			// 	break;
		}
		tmp = tmp->next;
	}
    return (1);
}