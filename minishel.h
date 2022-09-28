/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishel.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelbiad <mbelbiad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 11:43:13 by ael-kouc          #+#    #+#             */
/*   Updated: 2022/09/28 00:59:21 by mbelbiad         ###   ########.fr       */
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
	char	**envb;
	struct t_env *next;
}	t_env;

t_env	*g_env;

int		lent_d_pointer(char **str);
char	**get_env(char	**str);
t_nav	*init_nav(t_nav *nav);
void    change_value5(t_token *token);
char	*norm_5(t_lexer	*lexer);
void    free_norm(char *tmp, char *c);
int		check_n(t_lexer *lexer);
char	*check_n1(t_lexer *lexer, char *c, char *value);
char	*get_exit_code(t_lexer *lexer, char *c);
void	err_n(t_lexer *lexer, t_token *token);
void	catch_sig(int signum);
void	get_line();
char	**get_linked_ar(t_env *eniv);
void	change_envir();

//----------- builtins ------------------------------
int		ft_check_builtins(t_cmd *cmd);
int		ft_envp(char **envp);
void	*ft_link_env(t_env *envi, char **env);
void	ft_list_addback(t_env **lst, t_env *new);
t_env	*ft_lstnew(void *env);
int		ft_strcmp2(char *s1, char *s2);
int		file_in(t_file *tmp, int j);
int		check_file(char	*argv);
int		file_output(char	*argv);
void	file_out(t_file *tmp, int j);
int		append_mode(char	*argv);
void	pwd_fcnt(t_cmd *cmd);
void	cd_fcnt(t_cmd *cmd);
int		redirect_builtings(t_cmd *cmd);
void    export_fcnt(t_cmd *cmd);
int		check_exist(t_cmd *cmd, int i);
void	ft_check_quot(t_cmd **cmd);
void	ft_free(char	**cmd);
void    unset_fcnt(t_cmd *cmd);
int    ft_check_args2(char **check);
void	env_fcnt(t_cmd *cmd);
void	ft_remove_quot(t_env **cmd);
void	echo_fcnt(t_cmd *cmd);

void	get_line();


//---------------------------------------------------

//-------- execute ----------------------------------
void    ft_execute(t_cmd *cmd, char **envp);
int		redi_heredoc(t_cmd *cmd);
void	run_exection(t_cmd *cmd, int in_fd, int i, int size, char **envp);
int		ft_lstsizeee(t_cmd *lst);
void	here_doc(char *file);
char	*strrr(t_env *env, char *pth);
int	redrct_for_exec(t_cmd *cmd);

void	catch_sig(int signum);



#endif