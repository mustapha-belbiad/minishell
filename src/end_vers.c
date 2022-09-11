/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_vers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelbiad <mbelbiad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 10:07:26 by ael-kouc          #+#    #+#             */
/*   Updated: 2022/09/09 23:36:40 by mbelbiad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

t_cmd	*check_if1(t_cmd *file, char **file_name, t_file *e_type)
{
	if (!file)
		return (init_cmd(file_name, e_type));
	else
		cmd_add_back(&file, file_name, e_type);
	return (file);
}

t_file	*check_if(t_file *file, char *file_name, int e_type)
{
	if (!file)
		return (init_file(file_name, e_type));
	else
		file_add_back(&file, file_name, e_type);
	return (file);
}

char	**return_cmd(char *str)
{
	char	**spl;
	int		i;
	char	**cmd;
	char	**tmp;
	int		j;

	i = 0;
	if (str == NULL)
		return (0);
	spl = malloc(sizeof(char *) * 3);
	while (str[i] != ' ' && str[i])
		i++;
	i++;
	spl[0] = ft_substr(str, 0, i - 1);
	// printf("======={%s}\n",spl[0]);
	// if(spl[0][0] == '\0')
	// {
	// 	spl[0] = 0;
	// 	return(spl);
	// }
		
	if (i == ft_strlen(str))
	{
		spl[1] = 0;
	}
	else
	{
		spl[1] = ft_substr(str, i, ft_strlen(str));
		spl[2] = NULL;
	}
	cmd = malloc(sizeof(char *) * ft_count_words(str, ' ') + 1);
	cmd[0] = spl[0];
	tmp = ft_split(spl[1], ' ');
	i = 1;
	j = 0;
	while(tmp[j])
	{
		cmd[i] = tmp[j];
		j++;
		i++;
	}
	cmd[i] = 0;
	return (cmd);
}

char	**pick_double(t_token *tmp)
{
	t_token	*pickd;
	char	*str;
	char	*tmp1;
	char	**cmd;

	pickd = tmp;
	str = ft_strdup("\0");
	while (pickd)
	{
		if (tmp->e_type == PIP)
			break ;
		if (pickd->e_type == D_Q || pickd->e_type == S_Q
			|| pickd->e_type == CMD_WORD || pickd->e_type == SPACE)
		{
			tmp1 = str;
			str = ft_strjoin(str, pickd->value);
			free(tmp1);
		}
		pickd = pickd->next;
	}
	cmd = return_cmd(str);
	free(str);
	return (cmd);
}

// t_file	*pick_files(t_token *tmp, t_file *file)
// {
// 	while (tmp)
// 	{
// 		if (tmp->e_type == PIP)
// 			break ;
// 		if (tmp->e_type == D_REDIRECT_IN || tmp->e_type == D_REDIRECT_OT
// 			|| tmp->e_type == REDIRECT_IN || tmp->e_type == RED_FLAG)
// 		{
// 			file = check_if(file, tmp->next->value, tmp->e_type);
// 			tmp = tmp->next;
// 		}
// 		tmp = tmp->next;
// 	}
// 	if (!file)
// 		return (check_if(file, NULL, 0));
// 	return (file);
// }

// void	norm_fill_cmd(t_token *tmp, t_file *file, char *str, t_cmd *cmd)
// {
// 	char *tmp1;

// 	while (tmp)
// 	{	
// 		if (tmp->e_type == D_REDIRECT_IN || tmp->e_type == D_REDIRECT_OT
// 			|| tmp->e_type == REDIRECT_IN || tmp->e_type == REDIRECT_OT)
// 		{
// 			file_add_back(&file, tmp->next->value, tmp->e_type);
// 			tmp = tmp->next;
// 		}
// 		else if (tmp->e_type == D_Q || tmp->e_type == S_Q
// 			|| tmp->e_type == CMD_WORD || tmp->e_type == SPACE)
// 		{
// 			tmp1 = str;
// 			str = ft_strjoin(str, tmp->value);
// 			free(tmp1);
// 		}
// 		if (tmp->e_type == PIP)
// 		{
// 			cmd_add_back(&cmd, return_cmd(str), file);
// 			file = NULL;
// 			str = ft_strdup("\0");
// 		}
// 		tmp = tmp->next;
// 	}
// }

int	red_flag(t_token *token)
{
	if (check_err_quote(token) == 0)
		return(1);
	else if (check_err_red(token) == 0)
		return(1);
	else if (check_err_pip(token) == 0)
		return(1);
	else
		return(0);
}

t_cmd	*fill_cmd(t_token *token, t_cmd *cmd)
{
	t_token	*tmp;
	t_file	*file;
	char	*tmp1;
	char	*str;

	if (red_flag(token) == 1)
	{
		printf("syntax error\n");
		return(NULL);
	}	
	tmp = token;
	file = NULL;
	str = ft_strdup("\0");
	change_value(token);
	while (tmp)
	{	
		if (tmp->e_type == D_REDIRECT_IN || tmp->e_type == D_REDIRECT_OT
			|| tmp->e_type == REDIRECT_IN || tmp->e_type == REDIRECT_OT)
		{
			file_add_back(&file, tmp->next->value, tmp->e_type);
			tmp = tmp->next;
		}
		else if (tmp->e_type == D_Q || tmp->e_type == S_Q
			|| tmp->e_type == CMD_WORD || tmp->e_type == SPACE)
		{
			tmp1 = str;
			str = ft_strjoin(str, tmp->value);
			free(tmp1);
		}
		if (tmp->e_type == PIP)
		{
			cmd_add_back(&cmd, return_cmd(str), file);
			file = NULL;
			free(str);
		}
		tmp = tmp->next;
	}
	if (file || str)
	{
		cmd_add_back(&cmd, return_cmd(str), file);
		free(str);
	}	
	return (cmd);
}
