/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishel.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelbiad <mbelbiad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 11:43:13 by ael-kouc          #+#    #+#             */
/*   Updated: 2022/08/21 22:33:28 by mbelbiad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H
# include "./src/includes/lexer.h"
# include "./src/includes/token.h"
# include "./src/includes/parser.h"
# include "./libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct nav
{
	int i;
	int	j;
	int	y;
}	t_nav;


typedef struct minishel
{
	t_token		*token;
	t_lexer		*lexer;
	char		**env;
	char		*read;
	int			num_pip;
}	t_mini;

typedef struct t_env
{
	char *envir;
	struct t_env *next;
}	t_env;


int		lent_d_pointer(char **str);
char	**get_env(char	**str);
t_nav	*init_nav(t_nav *nav);

void	ft_check_builtins(t_cmd *cmd, t_env *mini);
int		ft_envp(char **envp);
void	*ft_link_env(t_env *envi, char **env);
void	ft_list_addback(t_env **lst, t_env *new);
t_env	*ft_lstnew(void *env);
int ft_strcmp2(char *s1, char *s2);

#endif