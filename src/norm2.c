/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kouc <ael-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 04:51:36 by ael-kouc          #+#    #+#             */
/*   Updated: 2022/09/21 14:07:52 by ael-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

char	*norm_5(t_lexer	*lexer)
{
	lexer_advance(lexer);
	return (ft_itoa(g_env->ret_val));
}

char	*expand2(t_lexer *lexer, char **env)
{
	char	*str;
	int		i;
	char	*real_value;

	i = 0;
	lexer_advance(lexer);
	lexer->j = lexer->i;
	while (lexer->src[lexer->j] && (ft_isalnum(lexer->src[lexer->j])
			|| lexer->src[lexer->j] == '_') && lexer->src[lexer->j] != '$')
		lexer->j++;
	str = malloc(sizeof(char) * (lexer->j - lexer->i + 1));
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
