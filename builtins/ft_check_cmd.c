/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelbiad <mbelbiad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 15:18:06 by mbelbiad          #+#    #+#             */
/*   Updated: 2022/08/21 17:00:45 by mbelbiad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"


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

void pwd_fcnt(char *cmd)
{
    free(cmd);
    cmd = malloc(1024 * sizeof(char *));
    if (getcwd(cmd, 1024) == NULL)
    {
        printf("faild \n");
        return ;
    }
    printf("%s \n", cmd);
}

void exit_fcnt(char *cmd)
{
    (void)cmd;
    printf("hooopla\n");
    exit(1);
}

void echo_fcnt(t_cmd *cmd)
{
    if (cmd->cmd[1] == NULL)
        printf("\n");
    else if((cmd->cmd[1][0] == '-' && cmd->cmd[1][1] == 'n')
        && (cmd->cmd[1][2] == ' ' || cmd->cmd[1][2] == '\0'))
    {
        int i = 1;
        while(cmd->cmd[1][++i])
            printf("%c", cmd->cmd[1][i]);
    }
    else 
        printf("%s\n", cmd->cmd[1]);
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

void env_fcnt(t_env *envv)
{
    t_env *tmp;
    
    tmp = envv;
    while(tmp->next != NULL)
    {
        if (ft_check_env(tmp->envir) == 0)
            tmp = tmp->next;
        else 
        {
            printf("%s\n", tmp->envir);
            tmp = tmp->next;
        }
    }
}

void    cd_fcnt(t_cmd *cmd)
{
    char *str;

    str = malloc(sizeof(char *));
    if (cmd->cmd[1][0] == '\0')
    {
        str = ft_strdup("/Users/mbelbiad"); //path of HOME;
        //printf("%s\n", str);
    }
    else
        str = ft_strdup(cmd->cmd[1]);
    if (chdir(str) == -1)
        printf("No such file or directory \n");
    free(str);
}
int check_exist(t_env **env, t_cmd *cmd)
{
    char **sp;
   t_env *tmp;
    
    sp = ft_split(cmd->cmd[1], '=');
    tmp = (*env);
    while((*env) != NULL)
    {
        if (ft_strcmp(sp[0],(*env)->envir) == 1)
        {   if (sp[1] == NULL)
            {
                free(sp);
                return(0);
            }
            free((*env)->envir);
            (*env)->envir = ft_strdup(cmd->cmd[1]);
            (*env) = tmp;
            free(sp);
            return(0);
        }
        (*env) = (*env)->next;
    }
    free(sp);
    (*env) = tmp;
    return(1);
}

void    ft_check_Quot(t_cmd **cmd)
{
    char **sp;

    sp = ft_split((*cmd)->cmd[1], '=');
    if (sp == NULL)
        return ;
    // printf("hoplaaa ---{%s}-- > \n", sp[0]);
    // printf("hoplaaa ---{%s}-- > \n", sp[1]);
    if (sp[1][0] == '"')
    {
        //printf("hoplaaa \n");
        return ;
    }
     else
     {
              //printf("hoplaaa =====> \n");
        sp[1] = ft_strjoin("\"", sp[1]);
        sp[1] = ft_strjoin(sp[1], "\"");
        sp[1] = ft_strjoin("=", sp[1]);
        free((*cmd)->cmd[1]);
        (*cmd)->cmd[1]= ft_strjoin(sp[0], sp[1]);
        return ;
     }

}

void    export_fcnt(t_cmd *cmd, t_env *env)
{
    t_env *tmp;

    tmp = env;
    if (cmd->cmd[1][0] == '\0')
    {
        //printf("hoopla\n");
        tmp = env;
        while (tmp != NULL)
        {
            printf("%s ", "declare -x");
            printf("%s\n", tmp->envir);
            tmp = tmp->next;
        }
    }
    else
    {
        //check_exist(&env, cmd);
        if (check_exist(&env, cmd) == 1)
        {
            
            ft_check_Quot(&cmd);
            ft_list_addback(&env, ft_lstnew(cmd->cmd[1]));
        }
        // tmp = env;
        // while (tmp != NULL)
        // {
        //     printf("%s ", "declare -x");
        //     printf("%s\n", tmp->envir);
        //     tmp = tmp->next;
        // }
    }
}
void    ft_check_builtins(t_cmd *cmd, t_env *eniv)
{
    if (ft_strrrcmp(cmd->cmd[0], "pwd") == 1) /*getcwd*/
        pwd_fcnt(cmd->cmd[0]);
    else if (ft_strrrcmp(cmd->cmd[0], "cd") == 1) /*chdir fcn*/
        cd_fcnt(cmd);
    else if (ft_strrrcmp(cmd->cmd[0], "export") == 1)
        export_fcnt(cmd, eniv);
    // else if (ft_strrrcmp(cmd, "unset") == 1)
    //     return(1);
    else if (ft_strrrcmp(cmd->cmd[0], "env") == 1)
        env_fcnt(eniv);
    else if (ft_strrrcmp(cmd->cmd[0], "exit") == 1)
        exit_fcnt(cmd->cmd[0]);
    else if (ft_strrrcmp(cmd->cmd[0], "echo") == 1) /*"\\ whit no \n;*/
        echo_fcnt(cmd);
    //printf("houlyaaa 3333 \n");
    // else
    //     printf("command not found \n");
}

