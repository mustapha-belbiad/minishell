/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_vers_outils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kouc <ael-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 14:19:36 by ael-kouc          #+#    #+#             */
/*   Updated: 2022/08/18 20:58:32 by ael-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

t_file	*init_file(char	*f, int type)
{
	t_file *file;

	file = malloc(sizeof(t_file));
	file->file_name = f;
	file->type = type;
	file->next = NULL;
	return(file);
}

t_cmd   *init_cmd(char **c, t_file *f)
{
    t_cmd	*cmd;
    t_file	*newfile = NULL;
    t_file	*tmp;

	tmp = f;
    cmd = malloc(sizeof(t_cmd));
    cmd->cmd = c;
	while (tmp)
	{
		file_add_back(&newfile , ft_strdup(tmp->file_name), tmp->type);
		tmp = tmp->next;
	}
	cmd->file = newfile;
	cmd->next = NULL; 
	return(cmd);
}

void	file_add_back(t_file **file, char *f, int type)
{
	t_file *last;
	t_file *tmp;
	
	if (!*file)
	{
		*file = init_file(f, type);
		return ;
	}
	last = init_file(f, type); 
	tmp = (*file);
	while(tmp->next)
		tmp = tmp->next;
	tmp->next = last;
}

void	cmd_add_back(t_cmd **cmd, char **c, t_file *f)
{
	t_cmd *last;
	t_cmd *tmp;
	
	if (!*cmd)
	{
		*cmd = init_cmd(c, f);
		return ;
	}
	last = init_cmd(c, f); 
	tmp = (*cmd);
	while(tmp->next)
		tmp = tmp->next;
	tmp->next = last;
}