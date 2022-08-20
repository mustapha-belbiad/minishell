/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelbiad <mbelbiad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 15:18:06 by mbelbiad          #+#    #+#             */
/*   Updated: 2022/08/20 19:29:09 by mbelbiad         ###   ########.fr       */
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

void env_fcnt(t_env *envv)
{
    
    while(envv->next != NULL)
    {
        printf("%s\n", envv->envir);
        envv = envv->next;
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

void    ft_check_builtins(t_cmd *cmd, t_env *eniv)
{
    if (ft_strrrcmp(cmd->cmd[0], "pwd") == 1) /*getcwd*/
        pwd_fcnt(cmd->cmd[0]);
    else if (ft_strrrcmp(cmd->cmd[0], "cd") == 1) /*chdir fcn*/
        cd_fcnt(cmd);
    // else if (ft_strrrcmp(cmd, "export") == 1)
    //     return(1);
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

