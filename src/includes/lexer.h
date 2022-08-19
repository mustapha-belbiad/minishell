/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kouc <ael-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 11:41:21 by ael-kouc          #+#    #+#             */
/*   Updated: 2022/07/01 22:16:22 by ael-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
#define LEXER_H
#include "token.h"
typedef struct lexer
{
	char	c;
	int		src_size;
	int		j;
	char	*src;
	int		i;
}	t_lexer;

t_lexer	*init_lexer(char *src); 
void	lexer_advance(t_lexer *lexer);
void	lexer_skip_space(t_lexer *lexer);
char	*get_c_as_str(char c);
char	*take_id(t_lexer *lexer, t_token *token, char **env);
t_token	*pick_tokens(t_lexer *lexer, char **env);
void	lexer_advance_with(t_lexer *lexer, t_token *token, char *value,
	int type);
void    lexer_back(t_lexer *lexer);
int		no_second_quote(t_lexer *lexer, char c);
void	check_after_space(t_lexer *lexer, t_token *token);
void	check_after_w(t_token *token, t_lexer *lexer);
void	epand_dollar(t_token *token, char **env);
char	*expand(t_lexer *lexer, char **env);
void    pick_bitwen_sq(t_lexer *lexer, t_token *token, char **env);
void    pick_bitwen_dq(t_lexer *lexer, t_token *token, char **env);
char	*expand2(t_lexer *lexer, char **env);
#endif