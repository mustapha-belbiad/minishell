/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kouc <ael-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 11:50:32 by ael-kouc          #+#    #+#             */
/*   Updated: 2022/07/01 22:12:48 by ael-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"


t_lexer	*init_lexer(char *src)
{
	t_lexer *lexer;

	lexer = malloc(sizeof(t_lexer));
	lexer->src = ft_strdup(src);
	lexer->src_size = ft_strlen(src);
	lexer->i = 0;
	lexer->j = 0;
	lexer->c = lexer->src[lexer->i];
	return (lexer);
}

void	lexer_skip_space(t_lexer *lexer)
{
	while(lexer->src[lexer->i] == ' ' || lexer->src[lexer->i] == '\t'
		|| lexer->src[lexer->i] == '\n' || lexer->src[lexer->i] == '\r')
		lexer_advance(lexer);
}

void	lexer_advance(t_lexer *lexer)
{
	if (lexer->i < lexer->src_size && lexer->c != '\0')
	{
		lexer->i++;
		lexer->c = lexer->src[lexer->i];
	}
}

char	*take_id(t_lexer *lexer, t_token *token, char **env)
{
	char *value;
	char *c;
	char *tmp;
	
	if(lexer->src_size == 1)
		return(get_c_as_str(lexer->c));
	value = malloc(sizeof(char));
	value[0] = '\0';
	while(!(check_special_c(lexer->c) == 0) && lexer->c != '\0')
	{
		if(lexer->c == '$' && ft_isalnum(lexer->src[lexer->i + 1])
			&& lexer->src[lexer->i + 1] != '_')
			c = expand(lexer, env);
		else
			c = get_c_as_str(lexer->c);
		tmp = value;
		value = ft_strjoin(value, c);
		free(tmp);
		free(c);
		lexer_advance(lexer);
	}
	lexer_back(lexer);
	// check_after_space2(lexer, token);
	return(value);
}

void	lexer_advance_with(t_lexer *lexer, t_token *token, char *value,
	int type)
{
	if(lexer->src[lexer->i] != '\0')
		lexer_advance(lexer);
	token_add_back(&token, value, type);
}

t_token	*pick_tokens(t_lexer *lexer, char **env)
{
	t_token *token;
	token = init_token("S", START);
	while(lexer->i < ft_strlen(lexer->src) && lexer->c != '\0')
	{
		lexer_skip_space(lexer);
		if(check_special_c(lexer->c) == 1)
		{
			lexer_advance_with(lexer, token, take_id(lexer, token, env), CMD_WORD);
			check_after_w(token, lexer);
		}
			
		if(lexer->c == '|')
			lexer_advance_with(lexer, token, "|", PIP);
		if(lexer->c == '>' && lexer->src[lexer->i + 1] == '>')
		{
			lexer_advance(lexer);
			lexer_advance_with(lexer, token, ">>", D_REDIRECT_OT);
		}
		if(lexer->c == '<' && lexer->src[lexer->i + 1] == '<')
		{
			lexer_advance(lexer);
			lexer_advance_with(lexer, token, "<<", D_REDIRECT_IN);
		}
		if(lexer->c == '>' && lexer->src[lexer->i + 1] != '>')
			lexer_advance_with(lexer, token, ">", REDIRECT_OT);
		if(lexer->c == '<' && lexer->src[lexer->i + 1] != '<')
			lexer_advance_with(lexer, token, "<", REDIRECT_IN);
		if(lexer->c == '\'')
			pick_bitwen_sq(lexer, token, env);
		if(lexer->c == '"')
			pick_bitwen_dq(lexer, token, env);
	}
	return(token);
}
