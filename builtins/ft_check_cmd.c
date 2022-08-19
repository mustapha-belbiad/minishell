/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelbiad <mbelbiad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 15:18:06 by mbelbiad          #+#    #+#             */
/*   Updated: 2022/08/19 19:44:03 by mbelbiad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

int	ft_strrrcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
    // printf("--- : %s \n", s1);
    // printf("---- : %s \n", s2);
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
        // printf("------ \n");
        // printf("+++%s", s1);
        // printf("'%c' || '%c'  \n", s1[i], s2[i]);
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
    printf("houlyaaa\n");
    if(cmd->cmd[1][0] == '-' && cmd->cmd[1][1] == 'n')
    {
        printf("3aaa \n");
        printf("%s", cmd->cmd[1]);
    }
    else 
        printf("%s\n", cmd->cmd[1]);
}

void    cd_fcnt(t_cmd *cmd)
{
    char *str;

    str = malloc(sizeof(char *));
    str = ft_strjoin("/", cmd->cmd[1]);
    chdir(str);
    free(str);
}

void    ft_check_builtins(t_cmd *cmd)
{
    printf (" === {%s} ====", cmd->cmd[0]);
    if (ft_strrrcmp(cmd->cmd[0], "pwd") == 1) /*getcwd*/
        pwd_fcnt(cmd->cmd[0]);
    // else if (ft_strrrcmp(cmd->cmd[0], "cd") == 1) /*chdir fcn*/
    //     cd_fcnt(cmd->cmd[0]);
    // else if (ft_strrrcmp(cmd, "export") == 1)
    //     return(1);
    // else if (ft_strrrcmp(cmd, "unset") == 1)
    //     return(1);
    // else if (ft_strrrcmp(cmd, "env") == 1)
    //     return(1);
    else if (ft_strrrcmp(cmd->cmd[0], "exit") == 1)
        exit_fcnt(cmd->cmd[0]);
    else if (ft_strrrcmp(cmd->cmd[0], "echo") == 1) /*"\\ whit no \n;*/
        echo_fcnt(cmd);
    printf("houlyaaa 3333 \n");
    // else
    //     printf("command not found \n");
}

