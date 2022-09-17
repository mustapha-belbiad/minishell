/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelbiad <mbelbiad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 15:18:06 by mbelbiad          #+#    #+#             */
/*   Updated: 2022/09/17 02:22:58 by mbelbiad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

// void	ft_free(char	**cmd)
// {
// 	int	i;

// 	i = 0;
// 	while (cmd[i])
// 		free(cmd[i++]);
// 	free(cmd);
// }


int	ft_strrrcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	// if (ft_strlen(s1) != ft_strlen(s2))
	// {
	//     printf(" < %zu >   < %zu > \n", ft_strlen(s1), ft_strlen(s2));
	//     return(0);
	// }
	while ((s1[i] != '\0' && s2[i] != '\0'))
	
	{
		if (s1[i] != s2[i])
		{
		//    printf("kjgfkwjbvadkjbvekjlbe +++++ wf ==> %c vss %c   ' %d '\n", s1[i], s2[i], i); 
			return (0);
		}
		i++;
	}
	if (s1[i] != s2[i])
	{
		return(0);
	}
	return(1);
	// if (ft_strlen(s1) == ft_strlen(s2))
	// {
	//     //printf("kjgfkwjbvadkjbvekjlbewf \n");
	//     return (1);
	// }
	// else
	// {
	//     printf("kjgfkwjbvadkjbvekjlbewf %c \n", s1);
	//     return (0);
	// }
}

void builtins_redirect(t_cmd *cmd)
{
	t_file *tmp;
	int out;
	int in;
	tmp = cmd->file;
	while (tmp)
	{
		if(tmp->e_type == 6)
		{
			out = open(tmp->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0777);
			cmd->cmd[0] = ft_strjoin(cmd->cmd[0], "\n");
			ft_putstr_fd(cmd->cmd[0], out);
			in  = 0;
		}
		else if (tmp->e_type == 8)
		{
			out = open(tmp->file_name, O_CREAT | O_WRONLY | O_APPEND, 0777);
			cmd->cmd[0] = ft_strjoin(cmd->cmd[0], "\n");
			ft_putstr_fd(cmd->cmd[0], out);
			 in  = 0;
		}
		else if (tmp->e_type == 7)
		{
			here_doc(tmp->file_name);
			printf("%s \n", cmd->cmd[0]);
			in  = 0;
		}
		else 
			in = 1;
		tmp = tmp->next;
	}
	if (in == 1)
		printf("%s \n", cmd->cmd[0]);
}

void pwd_fcnt(t_cmd *cmd)
{
	//int out;
	
	free(cmd->cmd[0]);
	cmd->cmd[0] = malloc(1024 * sizeof(char *));
	// redi_heredoc(cmd);
	if (getcwd(cmd->cmd[0], 1024) == NULL)
	{
		printf("faild \n");
		return ;
	}
	if (cmd->file != 0)
		builtins_redirect(cmd);
	// else if (cmd->next->cmd[0] != NULL)
	// {
	// 	dup2(fd[1], 1);
	// 	close(fd[1]);
	// }
	else
	{
		printf("%s \n", cmd->cmd[0]);
	}
}

void exit_fcnt(char *cmd)
{
	(void)cmd;
	printf("exit\n");
	exit(1);
}

int    ft_check_echo(char *cmd)
{
	int i;
	
	i = 0;
	if (cmd[i] == '-' && cmd[i  + 1] == 'n')
	{
		while(cmd[++i] == 'n')
			;
		if (cmd[i] == '\0')
			return(1);
	}
	return(0);
}  

int echo_redirect(t_cmd *cmd)
{
	 t_file *tmp;
	char    *tm;
	int out;
	
	out = 1;
	tmp = cmd->file;
	while (tmp)
	{
		if(tmp->e_type == 6)
		{
			out = open(tmp->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0777);
		}
		else if (tmp->e_type == 8)
		{
			out = open(tmp->file_name, O_CREAT | O_WRONLY | O_APPEND, 0777);
		}
		else if (tmp->e_type == 7)
		{
			here_doc(tmp->file_name);
			out = 1;
		}
		tmp = tmp->next;
	}
	return (out);
}

void echo_fcnt(t_cmd *cmd)
{
	int i;
	int fd;
	
	if (cmd->file != 0)
		fd = echo_redirect(cmd);
	else
		fd = 1;
	if (cmd->cmd[1] == NULL)
	{
		ft_putstr_fd("\n", fd);
		return ;
	}
	i = 1;
	while (cmd->cmd[i])
	{
		if (ft_check_echo(cmd->cmd[i]) == 1)
			i++;
		else 
			break;
	}
		if (i == 1)
		{
			while (cmd->cmd[i])
			{
				ft_putstr_fd(cmd->cmd[i], fd);
				ft_putstr_fd(" ", fd);
				i++;
			}
			ft_putstr_fd("\n", fd);
			return ;
		}
		else
		{
			while(cmd->cmd[i])
			{
				ft_putstr_fd(cmd->cmd[i], fd);
				if (cmd->cmd[i + 1] != '\0')
					ft_putstr_fd(" ", fd);
				i++;
			}
			return ;
	}
}

int ft_check_env(char *env)
{
	int i;

	i = -1;
	while(env[++i])
	{
		if (env[i] == '=')
			break;
	}
	if (env[i] == '=')
		return(1);
	else
		return(0);
}

void    ft_remove_Quot(t_env **cmd)
{
	char **sp;

	sp = ft_split((*cmd)->envir, '"');
	if (sp == NULL || sp[1] == NULL)
		return ;
		(*cmd)->envir = ft_strjoin(sp[0], sp[1]);
}

void    env_redi(t_cmd *cmd)
{
	t_file *tmp;
	t_env *tmp2;
	char    *tm;
	int out;

	tmp2 = g_env;
	tmp = cmd->file;
	while (tmp)
	{
		if(tmp->e_type == 6)
		{
			out = open(tmp->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0777);
			while(tmp2)
			{
				if (ft_check_env(tmp2->envir) == 0)
					tmp2 = tmp2->next;
				else 
				{
					ft_remove_Quot(&tmp2);
				   tm = ft_strjoin(tmp2->envir, "\n");
					ft_putstr_fd(tm, out);
					tmp2 = tmp2->next;
				}
			}
		}
		else if (tmp->e_type == 8)
		{
			out = open(tmp->file_name, O_CREAT | O_WRONLY | O_APPEND, 0777);
			 while(tmp2)
			{
				if (ft_check_env(tmp2->envir) == 0)
					tmp2 = tmp2->next;
				else 
				{
					ft_remove_Quot(&tmp2);
				   tm = ft_strjoin(tmp2->envir, "\n");
					ft_putstr_fd(tm, out);
					tmp2 = tmp2->next;
				}
			}
		}
		else if (tmp->e_type == 7)
		{
			here_doc(tmp->file_name);
			while (tmp2 != NULL)
			{
				printf("%s\n", tmp2->envir);
				tmp2 = tmp2->next;
			}
		}
		tmp = tmp->next;
	}
	free(tm);
}

void    env_fcnt(t_cmd *cmd)
{
	t_env *tmp;
	
	tmp = g_env;
   if (cmd->file != 0)
		env_redi(cmd);
	else 
	{
		 while(tmp != NULL)
		{
			if (ft_check_env(g_env->envir) == 0)
			   tmp =tmp->next;
			else 
			{
				ft_remove_Quot(&g_env);
				printf("%s\n",tmp->envir);
			   tmp =tmp->next;
			}
		}
   
	}
   //g_env = tmp;
}

void    cd_fcnt(t_cmd *cmd)
{
	char *str;
	t_env *env;
	char *home;

	env = g_env;
	str = malloc(sizeof(char *));
	if (cmd->cmd[1] == NULL)
	{
		
		home = strrr(env, "HOME=");
		str = ft_substr(home, 6, ft_strlen(home));
		str = ft_strjoin("/", str);
	}
	else
		str = ft_strdup(cmd->cmd[1]);
	if (chdir(str) == -1)
		printf("No such file or directory \n");
	free(str);
}
int ft_search(char *str, char c)
{
	int i;

	i = -1;
	while(str[++i])
	{
		if (str[i] == c)
			break;
	}
	if(str[i] == c)
		return(1);
	return(0);
}

void    ft_check_Quot(t_cmd **cmd)
{
	char **sp;
	t_cmd *tmp;
	int i;
	
	i = 1;
	tmp = (*cmd);
	while (tmp->cmd[i])
	{
		sp = ft_split(tmp->cmd[i], '=');
		if (sp == NULL)
			break;
		if ((sp[1] != NULL && sp[1][0] == '"') || sp[1] == NULL)
			i++;
		else if (ft_search(tmp->cmd[i], '=') == 1 && sp[1] == NULL)
		{
			 printf(" {} == {}");
			tmp->cmd[i]= ft_strjoin(tmp->cmd[i], "\"\"");
			i++;
		}
		else
		{
			sp[1] = ft_strjoin("\"", sp[1]);
			sp[1] = ft_strjoin(sp[1], "\"");
			sp[1] = ft_strjoin("=", sp[1]);
			free(tmp->cmd[i]);
			tmp->cmd[i]= ft_strjoin(sp[0], sp[1]);
			printf(" -{%s}- \n",  tmp->cmd[i]);
			i++;
		}
	}
}

int check_exist(t_cmd *cmd, int i)
{
	char **sp;
   t_env *tmp;
	
	sp = ft_split(cmd->cmd[i], '=');
	//  printf("sp[0] : {%s} \n", sp[0]);
	//  printf("sp[1] : {%s} \n", sp[1]);
	tmp = g_env;
	while(tmp != NULL)
	{
		if (ft_strcmp2(sp[0],tmp->envir) == 1)
		{   
			printf("cmd-> : {%s} \n", cmd->cmd[i]);
			if (sp[1] == NULL)
			{
				free(sp);
				return(0);
			}
			free(tmp->envir);
			ft_check_Quot(&cmd);
			tmp->envir = ft_strdup(cmd->cmd[i]);
			tmp = tmp;
			free(sp);
			return(0);
		}
		tmp = tmp->next;
	}
	free(sp);
   // (*env) = tmp;
	return(1);
}

void    export_redi(t_cmd *cmd)
{
	t_file *tmp;
	t_env *tmp2;
	char    *tm;
	int out;
	int in;
	tmp2 = g_env;
	tmp = cmd->file;
	while (tmp)
	{
		if(tmp->e_type == 6)
		{
			out = open(tmp->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0777);
			while(tmp2)
			{
				tm = ft_strjoin(tmp2->envir, "\n");
				ft_putstr_fd(tm, out);
				tmp2 = tmp2->next;
			}
		}
		else if (tmp->e_type == 8)
		{
			out = open(tmp->file_name, O_CREAT | O_WRONLY | O_APPEND, 0777);
			while(tmp2)
			{
				tm = ft_strjoin(tmp2->envir, "\n");
				ft_putstr_fd(tm, out);
				tmp2 = tmp2->next;
			}
		}
		else if (tmp->e_type == 7)
		{
			here_doc(tmp->file_name);
			while (tmp2 != NULL)
			{
				printf("%s ", "declare -x");
				printf("%s\n", tmp2->envir);
				tmp2 = tmp2->next;
			}
		}
		tmp = tmp->next;
	}
	free(tm);
}

int ft_check_unset(char *cmd)
{
	int i;
	
	if (cmd[0] >= '0' && cmd[0] <= '9')
		return (0);
	if (cmd[0] == '_')
		i = 1;
	else
		i = 0;
	while(cmd[i])
	{
		if ((cmd[i] >= '0' && cmd[i] <= '9')
			|| (cmd[i] >= 'a' && cmd[i] <= 'z')
			|| (cmd[i] >= 'A' && cmd[i] <= 'Z')
			|| cmd[i] == '_')
		{
			//printf("%c \n", cmd[i]);
			i++;
		}
		else
			return (0);
	}
	return (1);
}

void    export_fcnt(t_cmd *cmd)
{
	t_env *tmp;
	int i;
	
	if (cmd->cmd[1] == NULL)
	{
		tmp =  g_env;
		if (cmd->file != 0)
			export_redi(cmd);
		else 
		{
			while (tmp != NULL)
			{
				printf("%s ", "declare -x");
				printf("%s\n", tmp->envir);
				tmp = tmp->next;
			}
		}
		
	}
	else
	{   
		i = 0;
		while (cmd->cmd[++i])
		{
			if (ft_check_unset(cmd->cmd[i]) == 0)
			{
				printf("%s : not a valid identifier \n", cmd->cmd[i]);
				return ;
			}
			if (check_exist(cmd, i) == 1)
			{
			   /// printf(" 1 :==== %s === \n", cmd->cmd[i]);
				ft_check_Quot(&cmd);
			   // printf("2 : ==== %s === \n", cmd->cmd[i]);
				ft_list_addback(&g_env, ft_lstnew(cmd->cmd[i]));
			}
		}
	   
	}
}


void    unset_fcnt(t_cmd *cmd)
{
	t_env *tmp1;
	t_env *tmp2;
	t_env *head;
	t_cmd *cmd_tp;
	int i  = 0;
	if (cmd->cmd[1] == NULL)
	{
		if (cmd->file != 0)
			builtins_redirect(cmd);
		return ;
	}
	if (cmd->file != 0)
		builtins_redirect(cmd);
	cmd_tp = cmd;
	while (cmd_tp->cmd[++i])
	{
			
		if (ft_check_unset(cmd->cmd[i]) == 0)
		{
			printf("%s : not a valid identifier \n", cmd->cmd[i]);
			return ;
		}
		tmp1 = g_env;
		while(tmp1 != NULL)
		{
			if (ft_strcmp(cmd->cmd[i], tmp1->envir) == 1)
			{
				tmp2 = tmp1;
				head->next = tmp2->next;
				tmp1 = g_env;
				break;   
			}
			head = tmp1;
			tmp1 = tmp1->next;
		}
	}
}

int    ft_check_builtins(t_cmd *cmd, int fd[2])
{   
	//redi_heredoc(cmd);
	if (ft_strrrcmp(cmd->cmd[0], "pwd") == 1)/*getcwd*/
	{
		pwd_fcnt(cmd);
		g_env->ret_val = 0;
		return (1);
	}
	else if (ft_strrrcmp(cmd->cmd[0], "cd") == 1) /*chdir fcn*/
	{
		cd_fcnt(cmd);
		g_env->ret_val = 0;
		return (1);
	}
	else if (ft_strrrcmp(cmd->cmd[0], "export") == 1)
	{
	   export_fcnt(cmd);
	   g_env->ret_val = 0;
	   return (1); 
	}
	else if (ft_strrrcmp(cmd->cmd[0], "unset") == 1)
	{
		unset_fcnt(cmd);
		g_env->ret_val = 0;
		return (1);
	}
	else if (ft_strrrcmp(cmd->cmd[0], "env") == 1)
	{
		env_fcnt(cmd);
		g_env->ret_val = 0;
		return (1);
	}
	else if (ft_strrrcmp(cmd->cmd[0], "exit") == 1)
	{
		exit_fcnt(cmd->cmd[0]);
		g_env->ret_val = 0;
		return (1);
	}
	else if (ft_strrrcmp(cmd->cmd[0], "echo") == 1) /*"\\ whit no \n;*/
	{
		echo_fcnt(cmd);
		g_env->ret_val = 0;
		return (1);
	}
	else 
		return (0);
	// else
	//     printf("command not found \n");
}

