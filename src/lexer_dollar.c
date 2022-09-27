/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kouc <ael-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 16:41:57 by ael-kouc          #+#    #+#             */
/*   Updated: 2022/09/25 20:36:59 by ael-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

int	stlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=')
		i++;
	return (i);
}

int	ft_strncmpp(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != c)
		i++;
	return (i);
}

int	test_cmp(char *str, char *str1)
{
	if (ft_strlen(str) <= (size_t)ft_strncmpp(str1, '='))
		return (ft_strncmpp(str1, '='));
	else
		return (ft_strlen(str));
}

char	*check_env(char *str, char **env)
{
	int		i;
	char	*tmp;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], str, test_cmp(str, env[i])) == 0)
		{
			tmp = str;
			str = ft_substr(env[i], ft_strlen(str) + 1, ft_strlen(env[i]));
			free(tmp);
			return (str);
		}
		i++;
	}
	tmp = str;
	str = ft_strdup("\0");
	free(tmp);
	return (str);
}

char	*expand(t_lexer *lexer, char **env)
{
	char	*str;
	int		i;
	char	*real_value;

	i = 0;
	lexer_advance(lexer);
	lexer->j = lexer->i;
	while (lexer->src[lexer->j] && (ft_isalnum(lexer->src[lexer->j])
			|| lexer->src[lexer->j] == '_'))
		lexer->j++;
	str = malloc(sizeof(char) * (lexer->j - lexer->i) + 1);
	while (lexer->i < lexer->j)
	{
		str[i] = lexer->c;
		lexer_advance(lexer);
		i++;
	}
	str[i] = '\0';
	real_value = check_env(str, env);
	lexer_back(lexer);
	return (real_value);
}
