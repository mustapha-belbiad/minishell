/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kouc <ael-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 11:42:55 by ael-kouc          #+#    #+#             */
/*   Updated: 2022/07/01 22:12:20 by ael-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
#define TOKEN_H
#include "lexer.h"


typedef struct token
{
    char	*value;
	enum
	{
		START,
		CMD_WORD,
		PIP,
		S_Q,
		D_Q,
		REDIRECT_IN,//  <
		REDIRECT_OT,//  >
		D_REDIRECT_IN, // <<
		D_REDIRECT_OT, // >>
		DOLLAR,// $
		SPACE,
		RED_FLAG,
	}	type;
	struct token *next;
	struct token *prev;
}	t_token;

t_token	*init_token(char *value, int type);
void	token_add_back(t_token **token, char *value, int type);
int		check_special_c(char c);
void    free_first_node(t_token *token);
int		ft_lstsize(t_token *token);
t_token	*get_value_of_dollar(t_token *token, char **env);
char	*check_env(char *str, char **env);
// void	*expand_doll(t_token *token, char **env);
#endif