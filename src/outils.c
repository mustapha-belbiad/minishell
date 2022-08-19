/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kouc <ael-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:27:43 by ael-kouc          #+#    #+#             */
/*   Updated: 2022/08/18 14:29:48 by ael-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"


char	*get_c_as_str(char c)
{
	char *str;

	str = malloc(sizeof(char ) * 2);
	str[0] = c;
	str[1] = '\0';
	return(str);
}

int	eroor_quote(t_lexer *lexer, char c)
{
	lexer->j = lexer->i + 1;
	while(lexer->src[lexer->j])
	{
		if(lexer->src[lexer->j] == c)
			return(1);
		lexer->j++;
	}
	return(0);
}

int eroor_pip(t_lexer *lexer, char c)
{
	lexer->j = lexer->i - 1;
	while(lexer->src[lexer->j] <= 32 &&
		lexer->j >= 0)
		lexer->j--;
	if(lexer->src[lexer->j] == '|')
		return(1);
	lexer->j = lexer->i + 1;
	while(lexer->src[lexer->j] <= 32 &&
		lexer->src[lexer->j])
		lexer->j++;
	if(lexer->src[lexer->j] == '|' ||
		lexer->src[lexer->j] == '\0')
		return(1);
	return(0);
}

void	check_after_w(t_token *token, t_lexer *lexer)
{
	lexer->j = lexer->i;
	while(lexer->src[lexer->j] && lexer->src[lexer->j] <= 32)
		lexer->j++;
	if(check_special_c(lexer->src[lexer->j]) == 1)
		token_add_back(&token, " ", SPACE);
	else if(lexer->src[lexer->j] == '"' ||
		lexer->src[lexer->j] == '\'')
	token_add_back(&token, " ", SPACE);
	lexer->j = 0;
}

t_nav	*init_nav(t_nav *nav)
{
	nav = malloc(sizeof(t_nav));
	nav->i = 0;
	nav->j = 0;
	nav->y = 0;
	return(nav);
}