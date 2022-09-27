/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kouc <ael-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 11:50:32 by ael-kouc          #+#    #+#             */
/*   Updated: 2022/09/25 20:26:02 by ael-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

t_lexer	*init_lexer(char *src)
{
	t_lexer	*lexer;

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
	while (lexer->src[lexer->i] == ' ' || lexer->src[lexer->i] == '\t'
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

char	*take_id(t_lexer *lexer, char **env)
{
	char	*value;
	char	*c;
	char	*tmp;

	value = malloc(sizeof(char));
	value[0] = '\0';
	while (!(check_special_c(lexer->c) == 0) && lexer->c != '\0')
	{
		if (lexer->c == '$' && lexer->src[lexer->i + 1] == '?')
		{
			lexer_advance(lexer);
			c = ft_itoa(g_env->ret_val);
		}
		else if (lexer->c == '$' && ft_isalnum(lexer->src[lexer->i + 1])
			&& lexer->src[lexer->i + 1] != '_')
			c = expand(lexer, env);
		else
			c = get_c_as_str(lexer->c);
		tmp = value;
		value = ft_strjoin(value, c);
		free_norm(tmp, c);
		lexer_advance(lexer);
	}
	lexer_back(lexer);
	return (value);
}

void	lexer_advance_with(t_lexer *lexer, t_token *token, char *value,
	int e_type)
{
	if (lexer->src[lexer->i] != '\0')
		lexer_advance(lexer);
	token_add_back(&token, value, e_type);
	free(value);
}
