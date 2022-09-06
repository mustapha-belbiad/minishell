/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelbiad <mbelbiad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 17:24:27 by ael-kouc          #+#    #+#             */
/*   Updated: 2022/09/05 17:50:14 by mbelbiad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../../minishel.h"
# define ERROR 0
# define GOOD 1
# define STAR 2
# define WORD 3
# define HERDOK 4

typedef struct parser
{
	char			*value;
	int				e_type;
	int				betwin_c_w;
	struct parser	*next;
}	t_parser;

typedef struct file
{
	char		*file_name;
	int			e_type;
	struct file	*next;
}	t_file;

typedef struct cmd
{
	char		**cmd;
	t_file		*file;
	struct cmd	*next;
}	t_cmd;

t_parser	*init_parser(char *value, int e_type, int i);
int			check_err_quote(t_token *token);
int			check_err_red(t_token *token);
int			check_err_pip(t_token *token);
t_parser	*return_error(t_token *token);
void		parser_add_back(t_parser **parser, char *value,
				int e_type, int btw);
t_file		*init_file(char	*f, int e_type);
t_cmd		*init_cmd(char **c, t_file *f);
void		file_add_back(t_file **file, char *f, int e_type);
void		cmd_add_back(t_cmd **cmd, char **c, t_file *f);
t_file		*init_file(char	*f, int e_type);
t_cmd		*init_cmd(char **c, t_file *f);
void		file_add_back(t_file **file, char *f, int e_type);
void		cmd_add_back(t_cmd **cmd, char **c, t_file *f);
///////////////
t_file		*check_if(t_file *file, char *file_name, int e_type);
t_cmd		*check_if1(t_cmd *file, char **file_name, t_file *e_type);
t_file		*pick_files(t_token *tmp, t_file *file);
t_cmd		*fill_cmd(t_token *token, t_cmd *cmd);
char		**pick_double(t_token *tmp);
int			ft_strncmpp(char *str, char c);
int			test_cmp(char *str, char *str1);
int			red_flag(t_token *token);

#endif
