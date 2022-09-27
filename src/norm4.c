/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kouc <ael-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 00:17:38 by ael-kouc          #+#    #+#             */
/*   Updated: 2022/09/18 00:39:58 by ael-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

void	lexer_back(t_lexer *lexer)
{
	lexer->i--;
	lexer->c = lexer->src[lexer->i];
}

void	check_after(t_lexer *lexer, t_token *token)
{
	lexer->j = lexer->i;
	while (lexer->src[lexer->j] <= 32)
		lexer->j++;
	if (check_special_c(lexer->src[lexer->j]) == 1)
		token_add_back(&token, " ", SPACE);
}

int	check_n(t_lexer *lexer)
{
	if (lexer->c == '$' && ft_isalnum(lexer->src[lexer->i + 1])
		&& lexer->src[lexer->i + 1] != '_'
		&& lexer->src[lexer->i + 1] != '"')
		return (1);
	return (0);
}

char	*check_n1(t_lexer *lexer, char *c, char *value)
{
	char	*tmp;

	tmp = value;
	value = ft_strjoin(value, c);
	free(tmp);
	free(c);
	lexer_advance(lexer);
	return (value);
}

char	*get_exit_code(t_lexer *lexer, char *c)
{
	lexer_advance(lexer);
	c = ft_itoa(g_env->ret_val);
	return (c);
}
