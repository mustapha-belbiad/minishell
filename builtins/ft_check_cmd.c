/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelbiad <mbelbiad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 15:18:06 by mbelbiad          #+#    #+#             */
/*   Updated: 2022/09/26 18:14:48 by mbelbiad         ###   ########.fr       */
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
	while ((s1[i] != '\0' && s2[i] != '\0'))
	
	{
		if (s1[i] != s2[i])
		{
			return (0);
		}
		i++;
	}
	if (s1[i] != s2[i])
	{
		return(0);
	}
	return(1);
}
int redirect_builtings(t_cmd *cmd)
{
	t_file *tmp;
	int fd;
	
	tmp = cmd->file;
	while (tmp)
	{
		if (tmp->e_type == 6)
			fd = file_output(tmp->file_name);
		else if (tmp->e_type == 8)
			fd = append_mode(tmp->file_name);
		tmp = tmp->next;
	}
	return(fd);
}
void pwd_fcnt(t_cmd *cmd)
{
	int fd;
	
	if (cmd->file != NULL)
		fd = redirect_builtings(cmd);
	else 
		fd = 1;
	free(cmd->cmd[0]);
	cmd->cmd[0] = malloc(1024 * sizeof(char *));
	if (getcwd(cmd->cmd[0], 1024) == NULL)
	{
		printf("faild \n");
		return ;
	}
	ft_putstr_fd(cmd->cmd[0], fd);
	ft_putstr_fd("\n", fd);
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

void echo_fcnt(t_cmd *cmd)
{
	int i;
	int fd;

	if (cmd->file != NULL)
		fd = redirect_builtings(cmd);
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

void    env_fcnt(t_cmd *cmd)
{
	t_env *tmp;
	int fd;

	if (cmd->file != NULL)
		fd = redirect_builtings(cmd);
	else 
		fd = 1;
	tmp = g_env;
	while(tmp != NULL)
	{
		if (ft_check_env(tmp->envir) == 0)
			tmp =tmp->next;
		else 
		{
			ft_remove_Quot(&g_env);
			ft_putstr_fd(tmp->envir, fd);
			ft_putstr_fd("\n", fd);
			tmp =tmp->next;
		}
	}
}

void	change_for_pwd(t_env *g_env, char *change)
{
	t_env *tmp;
	
	tmp = g_env;
	while (tmp)
	{
		if (ft_strncmp(tmp->envir, "PWD", 3) == 0)
		{
			change = ft_strjoin("PWD=", change);
			tmp->envir = ft_strdup(change);
			printf("after {%s}\n", tmp->envir);
			break ;
		}
		tmp = tmp->next;
	}
	free(change);
}

void change_for_oldpwd(t_env *g_env, char *change)
{
	t_env *tmp;
	
	printf("{%s}\n", change);
	tmp = g_env;
	while (tmp)
	{
		if (ft_strncmp(tmp->envir, "OLDPWD", 6) == 0)
		{
			change = ft_strjoin("OLDPWD=", change);
			tmp->envir = ft_strdup(change);
			printf("after {%s}\n", tmp->envir);
			break ;
		}
		tmp = tmp->next;
	}
	free(change);
}

void change_env(t_env *g_env, char *value)
{
	t_env *tmp;
	char *change;

	if (ft_strncmp(value, "OLDPWD", 6) == 0)
	{
		change = strrr(g_env, "PWD");
		if (change == NULL)
		{
			printf("holaaa \n");
			return ;
		}
		change = ft_substr(change, 4, ft_strlen(change));
		change_for_oldpwd(g_env, change);
		free(change);
	}
	else if(ft_strncmp(value, "PWD", 3) == 0)
	{
		change =  malloc(1024 * sizeof(char *));
		if (getcwd(change, 1024) == NULL)
		{
			printf("faild \n");
			return ;
		}
		change_for_pwd(g_env, change);
		free(change);
	}
	
}
void    cd_fcnt(t_cmd *cmd)
{
	char *str;
	t_env *env;
	char *home;
	char *pwd;
	if (cmd->file != NULL)
		redirect_builtings(cmd);
	env = g_env;
	str = malloc(sizeof(char *));
	if (cmd->cmd[1] == NULL)
	{
		
		home = strrr(env, "HOME=");
		if (home == NULL)
			return ;
		str = ft_substr(home, 6, ft_strlen(home));
		str = ft_strjoin("/", str);
	}
	else
		str = ft_strdup(cmd->cmd[1]);
	change_env(g_env, "OLDPWD");
	if (chdir(str) == -1)
		printf("No such file or directory \n");
	change_env(g_env, "PWD");
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
	char *check;
	
	
	i = 1;
	tmp = (*cmd);
	while (tmp->cmd[i])
	{
		check = ft_strchr(tmp->cmd[i], '=');
		sp = ft_split(tmp->cmd[i], '=');
		if (sp == NULL || sp[0] == NULL)
			break;
		if (check && check[1] == '=')
			sp[1] = ft_substr(check, 1, ft_strlen(check)); 
		if ((sp[1] != NULL && sp[1][0] == '"') || sp[1] == NULL)
			i++;
		else if (ft_search(tmp->cmd[i], '=') == 1 && sp[1] == NULL)
		{
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
			i++;
		}
	}
}

int check_exist(t_cmd *cmd, int i)
{
	char **sp;
   t_env *tmp;
   
	sp = ft_split(cmd->cmd[i], '=');
	if (ft_isalpha(sp[0][0]) != 1)
	{
		printf("not valid \n");
		return(0);
	}
	tmp = g_env;
	while(tmp != NULL)
	{
		if (sp[0] && ft_strcmp2(sp[0],tmp->envir) == 1)
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
	//free(sp);
	return(1);
}

int ft_check_unset(char *cmd)
{
	int i;
	
	
	if (cmd == NULL || cmd[0] == '\0')
		return(0);
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
	int fd;
	
	if (cmd->file != NULL)
		fd = redirect_builtings(cmd);
	else 
		fd = 1;
	if (cmd->cmd[1] == NULL)
	{
		tmp =  g_env;
		if (cmd->next != NULL)
			{
				while (tmp != NULL)
				{
					ft_putstr_fd("declare -x ", fd);
					ft_putstr_fd(tmp->envir, fd);
					ft_putstr_fd("\n", fd);
					tmp = tmp->next;
				}
				
			}
			else 
			{
				while (tmp != NULL)
				{
					ft_putstr_fd("declare -x ", fd);
					ft_putstr_fd(tmp->envir, fd);
					ft_putstr_fd("\n", fd);
					tmp = tmp->next;
				}
			}
	}
	else
	{   
		i = 0;
		while (cmd->cmd[++i])
		{
			if (check_exist(cmd, i) == 1)
			{
				ft_check_Quot(&cmd);
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
		
	if (cmd->file != NULL)
		redirect_builtings(cmd);
	cmd_tp = cmd;
	while (cmd_tp->cmd[++i])
	{
			
		if (ft_check_unset(cmd->cmd[i]) == 0)
		{
			printf("%s : not a valid identifier \n", cmd->cmd[i]);
			return ;
		}
		tmp1 = g_env;
		if (ft_strcmp(cmd->cmd[i], tmp1->envir) == 1)
		{
			tmp1 = g_env->next;
			g_env = tmp1;
			return ;
		}
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
	// if ( cmd->next == NULL )
	// {
	// 	printf("holla \n");
	// 	redrct_for_exec(cmd);
	// }
	if (cmd->cmd[0] == NULL)
		return(0);
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
	//return (0);
	// else
	printf("lololololololo 111 \n");
}

