/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishel.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelbiad <mbelbiad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 11:43:13 by ael-kouc          #+#    #+#             */
/*   Updated: 2022/09/25 23:37:56 by mbelbiad         ###   ########.fr       */
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
	char **input;
	int ret_val;
	int status_num;
	int	fd_hr[2];
	int fd_exec[2];
	int crtl_c;
	struct t_env *next;
}	t_env;

t_env	*g_env;

int		lent_d_pointer(char **str);
char	**get_env(char	**str);
t_nav	*init_nav(t_nav *nav);

//----------- builtins ------------------------------
int		ft_check_builtins(t_cmd *cmd, int fd[2]);
int		ft_envp(char **envp);
void	*ft_link_env(t_env *envi, char **env);
void	ft_list_addback(t_env **lst, t_env *new);
t_env	*ft_lstnew(void *env);
int ft_strcmp2(char *s1, char *s2);
int file_in(t_file *tmp, int j);
int	check_file(char	*argv);
int	file_output(char	*argv);
void file_out(t_file *tmp, int j);
int	append_mode(char	*argv);

void	get_line();

//---------------------------------------------------

//-------- execute ----------------------------------
void    ft_execute(t_cmd *cmd, t_env *env, t_mini *mini, char **envp);
int		redi_heredoc(t_cmd *cmd);
void	run_exection(t_cmd *cmd, int in_fd, int i, int size, char **envp);
int		ft_lstsizeee(t_cmd *lst);
void	here_doc(char *file);
char	*strrr(t_env *env, char *pth);
int	redrct_for_exec(t_cmd *cmd);

void	catch_sig(int signum);

#endif