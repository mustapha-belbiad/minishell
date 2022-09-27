/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kouc <ael-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 05:39:19 by ael-kouc          #+#    #+#             */
/*   Updated: 2022/09/25 20:25:36 by ael-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

void	free_norm(char *tmp, char *c)
{
	free(tmp);
	free(c);
}

void	nor1(t_lexer *lexer, t_token *token, char **env)
{
	if (check_special_c(lexer->c) == 1)
	{
		lexer_advance_with(lexer, token, take_id(lexer, env), CMD_WORD);
		check_after_w(token, lexer);
	}
	if (lexer->c == '|')
		lexer_advance_with(lexer, token, ft_strdup("|"), PIP);
	if (lexer->c == '>' && lexer->src[lexer->i + 1] == '>')
	{
		lexer_advance(lexer);
		lexer_advance_with(lexer, token, ft_strdup(">>"), D_REDIRECT_OT);
	}
	if (lexer->c == '<' && lexer->src[lexer->i + 1] == '<')
	{
		lexer_advance(lexer);
		lexer_advance_with(lexer, token, ft_strdup("<<"), D_REDIRECT_IN);
	}
	if (lexer->c == '>' && lexer->src[lexer->i + 1] != '>')
		lexer_advance_with(lexer, token, ft_strdup(">"), REDIRECT_OT);
	if (lexer->c == '<' && lexer->src[lexer->i + 1] != '<')
		lexer_advance_with(lexer, token, ft_strdup("<"), REDIRECT_IN);
	if (lexer->c == '\'')
		pick_bitwen_sq(lexer, token);
	if (lexer->c == '"')
		pick_bitwen_dq(lexer, token, env);
}

t_token	*pick_tokens(t_lexer *lexer, char **env)
{
	t_token	*token;

	token = init_token("START", START);
	while (lexer->i < (int)ft_strlen(lexer->src) && lexer->c != '\0')
	{
		lexer_skip_space(lexer);
		nor1(lexer, token, env);
	}
	free(lexer->src);
	free(lexer);
	return (token);
}
