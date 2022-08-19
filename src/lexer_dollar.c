/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kouc <ael-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 16:41:57 by ael-kouc          #+#    #+#             */
/*   Updated: 2022/07/02 11:40:27 by ael-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"
int	stlen(char *str)
{
	int	i;

	i = 0;
	while(str[i] != '=')
		i++;
	return(i);
}

char	*check_env(char *str, char **env)
{
	int		i;
	char	*tmp;

	i = 0;
	while(env[i])
	{
		if(ft_strncmp(env[i], str, ft_strlen(str)) == 0)
		{
			str = ft_substr(env[i], ft_strlen(str) + 1, ft_strlen(env[i]));
			return(str);
		}
		i++;
	}
	str = ft_strdup("\0");
	return(str);
}

char	*expand(t_lexer *lexer, char **env)
{
	char	*str;
	int i;
	char	*real_value;
	char	b;
	
	i = 0;
	lexer_advance(lexer);
	lexer->j = lexer->i;
	while(lexer->src[lexer->j] && (ft_isalnum(lexer->src[lexer->j])
		|| lexer->src[lexer->j] == '_'))
		lexer->j++;
	str = malloc(sizeof(char) * (lexer->j - lexer->i) + 1);
	while(lexer->i < lexer->j)
	{
		str[i] = lexer->c;
		lexer_advance(lexer);
		i++;
	}
	str[i] = '\0';
	// printf("====%s\n", str);
	real_value = check_env(str, env);
	lexer_back(lexer);
	return(real_value);
}

char	*expand2(t_lexer *lexer, char **env)
{
	char	*str;
	int i;
	char	*real_value;
	char	b;
	
	i = 0;
	lexer_advance(lexer);
	lexer->j = lexer->i;
	while(lexer->src[lexer->j] && (ft_isalnum(lexer->src[lexer->j])
		|| lexer->src[lexer->j] == '_') && lexer->src[lexer->j] != '$')
		lexer->j++;
	str = malloc(sizeof(char) * (lexer->j - lexer->i + 1));
	while(lexer->i < lexer->j)
	{
		str[i] = lexer->c;
		lexer_advance(lexer);
		i++;
	}
	real_value = check_env(str, env);
	lexer_back(lexer);
	return(real_value);
}