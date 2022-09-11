/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelbiad <mbelbiad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 15:18:06 by mbelbiad          #+#    #+#             */
/*   Updated: 2022/09/11 05:13:55 by mbelbiad         ###   ########.fr       */
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
    else
    {
        printf("%s \n", cmd->cmd[0]);
    }
}

void exit_fcnt(char *cmd)
{
    (void)cmd;
    printf("hooopla\n");
    exit(1);
}

int    ft_check_echo(t_cmd *cmd)
{
    char **check;
    int i;
    int j;
    int index;
    
    i = 0;
    index = 0;
    // while (cmd->cmd[1][i])
    // {
    if (cmd->cmd[1][i] == '-' && cmd->cmd[1][i + 1] == 'n')
    {
        i = 0;
        while(cmd->cmd[1][++i] == 'n')
            ;
        if (cmd->cmd[1][i] == '\0')
            return (i);
    }
    else
        return(0);
    return(0);
}
    //     if(cmd->cmd[1][i] == '-' && cmd->cmd[1][i + 1] == 'n')
    //     {
    //         // if (cmd->cmd[1][i + 1] != 'n' && cmd->cmd[i + 2] != ' ')
    //         //     return (0);
    //         j = i + 1;
    //         while(cmd->cmd[1][j] == 'n')
    //             j++;
    //         i = j;
    //         if (cmd->cmd[1][i] == '\0')
    //         {
    //              printf("==> 1 :%c\n", cmd->cmd[1][i]);
    //             return (0);
    //         }
    //         if (cmd->cmd[1][i] != '\0')
    //         {
    //             printf("==> 1: %c\n", cmd->cmd[1][i]);
    //             return (i);
    //         }
    //         // if (cmd->cmd[1][i] == '-' ||)
    //         //     return(0);
    //     }
    //    // i = j;
    //     if (cmd->cmd[1][i] != ' ' || cmd->cmd[1][i] != '\0')
    //         break;
    //     else
    //         i++; 
    //}
    //return (0);    

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
    i = ft_check_echo(cmd);
    // if (cmd->file != 0)
    //     echo_redirect(cmd, i);
    // else 
    // {}
        if (i == 0 && cmd->cmd[1] != NULL)
        {
            i = 0;
            while (cmd->cmd[++i])
            {
                ft_putstr_fd(cmd->cmd[i], fd);
                ft_putstr_fd(" ", fd);
            }
            printf("\n");
        }
        else 
        {
            i = 1;
            while(cmd->cmd[++i])
            {
                ft_putstr_fd(cmd->cmd[i], 1);
                if (cmd->cmd[i + 1] != '\0')
                     ft_putstr_fd(" ", 1);
            }
        }
    }
    
   // printf("====== > {%s} \n", cmd->cmd[1]); //&& (cmd->cmd[1][2] == ' ' || cmd->cmd[1][2] == '\0'))
    // if((cmd->cmd[1][0] == '-' && cmd->cmd[1][1] == 'n')
    //     && (cmd->cmd[1][2] == ' ' || cmd->cmd[1][2] == '\0'))
    // {
    //     int i = 1;
    //     while(cmd->cmd[1][++i])
    //         printf("%c", cmd->cmd[1][i]);
    // }
    // else 
    //     printf("%s\n", cmd->cmd[1]);
 //}

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
    
    // home = ft_
    str = malloc(sizeof(char *));
    if (cmd->cmd[1] == NULL)
    {
        // env->envir = ft_strdup("hola\n");
        // printf("%s\n", env->envir);
        str = ft_strdup("/Users/mbelbiad"); //path of HOME;
        //printf("%s\n", str);
    }
    else
        str = ft_strdup(cmd->cmd[1]);
    if (chdir(str) == -1)
        printf("No such file or directory \n");
    free(str);
}

void    ft_check_Quot(t_cmd **cmd)
{
    char **sp;

    sp = ft_split((*cmd)->cmd[1], '=');
    if (sp == NULL || sp[1] == NULL)
        return ;
    if (sp[1][0] == '"')
        return ;
     else
     {
        sp[1] = ft_strjoin("\"", sp[1]);
        sp[1] = ft_strjoin(sp[1], "\"");
        sp[1] = ft_strjoin("=", sp[1]);
        free((*cmd)->cmd[1]);
        (*cmd)->cmd[1]= ft_strjoin(sp[0], sp[1]);
        printf(" -{%s}- \n",  (*cmd)->cmd[1]);
        return ;
    }
}

int check_exist(t_env **env, t_cmd *cmd)
{
    char **sp;
   t_env *tmp;
    
    sp = ft_split(cmd->cmd[1], '=');
    tmp = g_env;
    while(tmp != NULL)
    {
        if (ft_strcmp2(sp[0],tmp->envir) == 1)
        {   
            if (sp[1] == NULL)
            {
                free(sp);
                return(0);
            }
            free(tmp->envir);
            ft_check_Quot(&cmd);
            tmp->envir = ft_strdup(cmd->cmd[1]);
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

void    export_fcnt(t_cmd *cmd)
{
    t_env *tmp;
    
    // printf(" 666 :==== === \n");
    // printf(" 666 :==== %s === \n", g_env->envir);
    // tmp =  g_env;
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
        if (check_exist(&g_env, cmd) == 1)
        {
            printf(" 1 :==== %s === \n", cmd->cmd[1]);
            ft_check_Quot(&cmd);
            printf("2 : ==== %s === \n", cmd->cmd[1]);
            ft_list_addback(&g_env, ft_lstnew(cmd->cmd[1]));
        }
    }
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
            || (cmd[i] >= 'A' && cmd[i] <= 'Z'))
        {
            printf("%c \n", cmd[i]);
		    i++;
        }
        else
            return (0);
    }
    return (1);
}

void    unset_fcnt(t_cmd *cmd)
{
    char **cd;
    t_env *tmp1;
    t_env *tmp2;
    t_env *head;
    
    //printf("=== {%s}\n", cmd->cmd[1]);
    if (cmd->cmd[1] == NULL)
    {
        if (cmd->file != 0)
            builtins_redirect(cmd);
        return ;
    }
    if (cmd->file != 0)
        builtins_redirect(cmd);
   // printf("file type : {%d} \n", cmd->file->e_type);
    // if (cmd->file->e_type != 0)
	// 	here_doc(cmd->file->file_name);
    if (ft_check_unset(cmd->cmd[1]) == 0)
    {
        printf("%s : not a valid identifier \n", cmd->cmd[1]);
        return ;
    }
    head = g_env;
    
    printf("{%s}\n", g_env->envir);
    while (g_env != NULL)
    {
        if (ft_strcmp(cmd->cmd[1], g_env->envir) == 1)
        {
            tmp2 = g_env;
            tmp1->next = tmp2->next;
            g_env = head; 
            return ;   
        }
        tmp1 = g_env;
        g_env = g_env->next;
    }
    g_env = head;
}

int    ft_check_builtins(t_cmd *cmd)
{   
    //redi_heredoc(cmd);
    if (ft_strrrcmp(cmd->cmd[0], "pwd") == 1)/*getcwd*/
    {
        pwd_fcnt(cmd);
        return (1);
    }
    else if (ft_strrrcmp(cmd->cmd[0], "cd") == 1) /*chdir fcn*/
    {
        cd_fcnt(cmd);
        return (1);
    }
    else if (ft_strrrcmp(cmd->cmd[0], "export") == 1)
    {
       export_fcnt(cmd);
       return (1); 
    }
    else if (ft_strrrcmp(cmd->cmd[0], "unset") == 1)
    {
        unset_fcnt(cmd);
        return (1);
    }
    else if (ft_strrrcmp(cmd->cmd[0], "env") == 1)
    {
        env_fcnt(cmd);
        return (1);
    }
    else if (ft_strrrcmp(cmd->cmd[0], "exit") == 1)
    {
        exit_fcnt(cmd->cmd[0]);
        return (1);
    }
    else if (ft_strrrcmp(cmd->cmd[0], "echo") == 1) /*"\\ whit no \n;*/
    {
        echo_fcnt(cmd);
        return (1);
    }
    else 
        return (0);
    //printf("houlyaaa 3333 \n");
    // else
    //     printf("command not found \n");
}

