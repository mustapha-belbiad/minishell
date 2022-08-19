/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kouc <ael-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 10:54:56 by ael-kouc          #+#    #+#             */
/*   Updated: 2022/07/01 12:33:12 by ael-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"
#include "../libft/libft.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//EXPAND_FROM_ENV/////////////////////////////////////////////////////////////////////////////////////////////
// char	*get_real_val(char *str, char **env)
// {
// 	int		i;
// 	char	*tmp;

// 	i = 0;
// 	while(env[i])
// 	{
// 		if(!strncmp(str, env[i], ft_strlen(str)))
// 		{
// 			tmp = str;
// 			str = ft_substr(env[i], ft_strlen(tmp) + 1, ft_strlen(env[i]));
// 			break;
// 		}
// 		i++;
// 	}
// 	if(env[i] == 0)
// 	{
// 		tmp = str;
// 		str = ft_strdup("\0");
// 	}
// 	return(str);
// }

// char	*get_char_to_find(char *str, char **env)
// {
// 	int		i;
// 	char	*tmp;
// 	char	*exp;
// 	char	*after_str;
// 	char	*zebi;
	
// 	i = 0;
// 	while(str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
// 		i++;
// 	str = ft_substr(str, 0, i);
// 	if(strcmp(str, tmp))
// 		after_str = ft_substr(tmp, ft_strlen(str), ft_strlen(tmp));
		
// 	else
// 		after_str = ft_strdup("\0");
// 	exp = get_real_val(str, env);
// 	zebi = ft_strjoin(exp, after_str);
// 	return(zebi);
// }

// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// //GET_VALUE_BEFOR_FIRST_DOLLAR////////////////////////////////////////////////////////////////////////////////
// int	check_ther_is_doll(char *str)
// {
// 	int i;
// 	while(str[i])
// 	{
// 		if(str[i] == '$')
// 			return(i);
// 		i++;
// 	}
// 	return(-1);
// }

// // char	*str_befor_doll(char *str, int i)
// // {
// // 	char *befor_d;
// // 	int j = 0;
	
// // 	befor_d = ft_substr(str, 0, i);
// // 	return(befor_d);
// // }

// // char	*get_real_value(char *first_str, char **env)
// // {
// // 	char *befor_d;
	
// // 	if (check_ther_is_doll(first_str) == -1)
// // 		return (ft_strdup("\0"));
// // 	printf("here\n");
// // 	befor_d = str_befor_doll(first_str, (check_ther_is_doll(first_str)));
// // 	printf("-----%s-----\n", befor_d);
// // 	return(befor_d);
// // }

// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// /////////EXPAND_DOLLAR////////////////////////////////////////////////////////////////////////////////////////
// // t_token	*expand_doll(t_token *token, char **env)
// // {
// // 	t_token	*tmp;
// // 	char	*from_z_t_d;
// // 	char	*from_env;
// // 	char	*tmp_f;
// // 	tmp = token;
// // 	while(tmp)
// // 	{
// // 		if(tmp->type == D_Q || tmp->type == CMD_WORD)
// // 		{
// // 			from_z_t_d = get_real_value(tmp->value, env);
// // 			printf("from  =================; %s\n", from_z_t_d);
// // 			if(from_z_t_d[0] == '\0')
// // 			{
// // 				free(from_z_t_d);
// // 				break;
// // 			}
// // 			from_env =ft_substr(tmp->value, ft_strlen(from_z_t_d) + 1, ft_strlen(tmp->value));
// // 			tmp_f = from_env;
// // 			from_env = get_from_env(from_env, env);
// // 			// printf("%s\n", from_env);
// // 		}
// // 		tmp = tmp->next;
// // 	}
// // 	return(token);
// // }


// void	epand_dollar(t_token *token, char **env)
// {
// 	t_token	*tmp;
// 	char	**split_doll;
// 	int		i;
// 	char	*f;
	
// 	tmp = token;
// 	i = 0;
// 	while(tmp)
// 	{
// 		if(tmp->type == D_Q || tmp->type == CMD_WORD)
// 		{
// 			if(check_ther_is_doll(tmp->value) == -1)
// 				break;
// 			if(tmp->value[0] == '$')
// 				split_doll = ft_split(tmp->value, '$');
				
// 			else
// 			{
// 				i = 1;
// 				split_doll = ft_split(tmp->value, '$');
// 			}
// 			f = tmp->value;
// 			tmp->value = exp_d(split_doll, i, env);
// 			printf("here");
// 			printf("%s\n", tmp->value);
// 		}
// 		tmp = tmp->next;
// 	}
// }