/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kouc <ael-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 17:24:27 by ael-kouc          #+#    #+#             */
/*   Updated: 2022/08/18 18:23:02 by ael-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../../minishel.h"
# define ERROR 0
# define GOOD 1
# define STAR 2
# define WORD 3
# define herdok 4

typedef struct parser
{
	char		*value;
	int			type;
	int			betwin_c_w;
	struct parser	*next;
}	t_parser;

typedef struct file
{
	char		*file_name;
	int			type;
	struct file	*next;
}	t_file;

typedef struct cmd
{
	char	**cmd;
	t_file	*file;
	struct cmd	*next;
}	t_cmd;

t_parser	*init_parser(char *value, int type, int i);
int			check_err_quote(t_token *token);
int			check_err_red(t_token *token);
int			check_err_pip(t_token *token);
t_parser    *return_error(t_token *token);
void		parser_add_back(t_parser **parser, char *value, int type, int btw);
t_file		*init_file(char	*f, int type);
t_cmd		*init_cmd(char **c, t_file *f);
void		file_add_back(t_file **file, char *f, int type);
void		cmd_add_back(t_cmd **cmd, char **c, t_file *f);
t_file		*init_file(char	*f, int type);
t_cmd		*init_cmd(char **c, t_file *f);
void		file_add_back(t_file **file, char *f, int type);
void		cmd_add_back(t_cmd **cmd, char **c, t_file *f);
///////////////
t_file	*check_if(t_file *file, char *file_name, int type);
t_cmd	*check_if1(t_cmd *file, char **file_name, t_file *type);
t_file	*pick_files(t_token *tmp, t_file *file);
t_cmd   *fill_cmd(t_token *token, t_cmd *cmd);
char	**pick_double(t_token *tmp);

#endif
