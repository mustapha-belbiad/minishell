/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kouc <ael-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 11:42:55 by ael-kouc          #+#    #+#             */
/*   Updated: 2022/09/11 21:43:45 by ael-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H
# include "lexer.h"

typedef struct token
{
	enum
	{
		START,
		CMD_WORD,
		PIP,
		S_Q,
		D_Q,
		REDIRECT_IN,
		REDIRECT_OT,
		D_REDIRECT_IN,
		D_REDIRECT_OT,
		DOLLAR,
		SPACE,
		RED_FLAG,
		J,
	}	e_type;
	char			*value;
	struct token	*next;
}	t_token;

t_token	*init_token(char *value, int e_type);
void	token_add_back(t_token **token, char *value, int e_type);
int		check_special_c(char c);
void	free_first_node(t_token *token);
int		ft_lstsize(t_token *token);
t_token	*get_value_of_dollar(t_token *token, char **env);
char	*check_env(char *str, char **env);
void    change_value(t_token *token);
char	**return_cmd(char *str);
void	ft_list_remove_if(t_token **token);
int		cmp(t_token *token);
// char	**return_cmd(char *str)
// {
// 	char	**spl;
// 	char	*str;
// 	char	*tmp;
// 	int		i;

// 	i = 0;
// 	str  =ft_strdup("");
// 	spl = malloc(sizeof(char *) * 30);
// 	while(token)
// 	{
// 		if(token->e_type == CMD_WORD || token->e_type == D_Q || token->e_type == S_Q)
// 		{
// 			tmp = str;
// 			str = ft_strjoin(str, token->value);
// 			free(tmp);
// 		}
// 		if(token->e_type == D_REDIRECT_IN || token->e_type == D_REDIRECT_OT
// 			|| token->e_type == REDIRECT_IN || token->e_type == REDIRECT_IN
// 			|| token->e_type == SPACE)
// 		{
// 			spl[i] = ft_strdup(str);
// 			i++;
// 			free(str);
// 			str = ft_strdup("");
// 		}
// 		if(token->e_type == PIP || token->next == NULL)
// 		{
// 			spl[i] = ft_strdup(str);
// 			i++;
// 			break;
// 		}
// 		token = token->next;
// 	}
// 	spl[i] = NULL;
// 	if(str)
// 		free(str);
// 	return(spl);
// }
// void	*expand_doll(t_token *token, char **env);
#endif