/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_vers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelbiad <mbelbiad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 10:07:26 by ael-kouc          #+#    #+#             */
/*   Updated: 2022/08/19 19:26:23 by mbelbiad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"
t_cmd	*check_if1(t_cmd *file, char **file_name, t_file *type)
{
	if(!file)
		return(init_cmd(file_name, type));
	else
		cmd_add_back(&file, file_name, type);
	return(file);
}

t_file	*check_if(t_file *file, char *file_name, int type)
{
	if (!file)
		return(init_file(file_name, type));
	else
		file_add_back(&file, file_name, type);
	return(file);
}

char **return_cmd(char *str)
{
	char **spl;
	int i;

	i = 0;
	if(!str)
		return(NULL);
	spl = malloc(sizeof(char *) * 3);
	while(str[i] != ' ' && str[i])
		i++;
	i++;
	spl[0] = ft_substr(str, 0, i);
	if(i == ft_strlen(str))
	{
		spl[1] = 0;
	}
	else
	{
		spl[1] = ft_substr(str, i, ft_strlen(str));
		spl[2] = NULL;
	}
		
	return(spl);
}

char	**pick_double(t_token *tmp)
{
	t_token *pickd;
	char	*str;
	char	*tmp1;
	char	**cmd;
	
	pickd = tmp;
	str = ft_strdup("\0");
	while(pickd)
	{
		if(tmp->type == PIP)
			break;
		if(pickd->type == D_Q || pickd->type == S_Q
			|| pickd->type == CMD_WORD || pickd->type == SPACE)
		{
			tmp1 = str;
			str = ft_strjoin(str, pickd->value);
			free(tmp1);
		}
		pickd = pickd->next;
	}
	cmd = return_cmd(str);
	free(str);
	return(cmd);
}

t_file	*pick_files(t_token *tmp, t_file *file)
{
	int i;

	i = 0;
	printf("dssddsdsds\n");
	while(tmp)
	{
		if(tmp->type == PIP)
			break;
		if(tmp->type == D_REDIRECT_IN || tmp->type == D_REDIRECT_OT
			|| tmp->type == REDIRECT_IN || tmp->type == RED_FLAG)
		{
			i = tmp->type;
			file = check_if(file, tmp->next->value, tmp->type);
			tmp = tmp->next;
		}
		tmp = tmp->next;
	}
	if(!file)
		return(check_if(file, NULL, 0));
	return(file);
}

t_cmd   *fill_cmd(t_token *token, t_cmd *cmd)
{
	t_token *tmp;
	t_file *file;
	char	*tmp1;
	char	*str;

	tmp = token;
	file = NULL;
	str = ft_strdup("\0");
	if(tmp->next)
		tmp = tmp->next;
	while(tmp)
	{	
		if(tmp->type == D_REDIRECT_IN || tmp->type == D_REDIRECT_OT
			|| tmp->type == REDIRECT_IN || tmp->type == REDIRECT_OT)
		{
			file_add_back(&file , tmp->next->value ,  tmp->type);
			tmp = tmp->next;
		}
		else if(tmp->type == D_Q || tmp->type == S_Q
		|| tmp->type == CMD_WORD || tmp->type == SPACE)
		{
			tmp1 = str;
			str = ft_strjoin(str, tmp->value);
			free(tmp1);
		}
		if (tmp->type == PIP)
		{

			cmd_add_back(&cmd, return_cmd(str), file);
			file = NULL;
			str = ft_strdup("\0");	
		}
		tmp = tmp->next;
	}
	if (file || str )
		cmd_add_back(&cmd, return_cmd(str), file);
	return(cmd);
}
