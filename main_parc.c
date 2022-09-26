/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelbiad <mbelbiad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 11:47:34 by ael-kouc          #+#    #+#             */
/*   Updated: 2022/09/26 00:24:37 by mbelbiad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"
int chack_readl(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        if(str[i] != ' ')
            return(1);
        i++;
    }
    return(0);
}

void    change_value(t_token *token)
{
    t_token *tmp;
    int     i;
    
    tmp = token;
    while(tmp)
    {
        if(tmp->e_type == REDIRECT_IN || tmp->e_type == REDIRECT_OT
            || tmp->e_type == D_REDIRECT_OT || tmp->e_type == D_REDIRECT_IN)
        {
            if(tmp->next)
            {
                tmp->next->e_type = tmp->e_type;
                tmp = tmp->next;
            }
            if(tmp->e_type == S_Q || tmp->e_type == D_Q || tmp->e_type == CMD_WORD)
            {
                while(tmp->e_type == S_Q || tmp->e_type == D_Q || tmp->e_type == CMD_WORD)
                {
                    tmp->e_type = J;
                    tmp = tmp->next;
                }
            }
        }
        tmp = tmp->next;
    }
}
void test()
{
    printf("holaaa\n");    
}

int main(int ac, char **av, char **envp)
{
    t_mini  *mini;
    char    *str;
    t_cmd   *cmd;
    t_file  *files;
    t_cmd   *tmp1;
    t_token *tmpv;

    t_env   *eniv;

    eniv = malloc(sizeof(t_env));
    
    files = NULL;
    mini = malloc(sizeof(t_mini));
    mini->env = get_env(envp);

    eniv = ft_link_env(eniv, mini->env);
    g_env = ft_link_env(eniv, mini->env);
    g_env->ret_val = 0;
    g_env->crtl_c = 0;
    
    int fd;
    get_line();
    while(1)
    {
        fd = dup(0);

        str = readline("minishel>");
        //printf("strat again \n");
        if(str == NULL)
        {
            printf("exit\n");
            exit(1);
        }
        if(str[0] && chack_readl(str) == 1)
        {
            add_history(str);
            mini->lexer = init_lexer(str);
            mini->token = pick_tokens(mini->lexer, envp);
            tmpv = mini->token;
            cmd = fill_cmd(mini->token, cmd);

            

            // if (cmd->next == NULL && (ft_check_builtins(cmd, g_env->fd_exec) == 1))
            // {
            //      //if (ft_check_builtins(cmd, g_env->fd_exec) == 1)
            //      printf("================================ \n");
		    //         g_env->ret_val = 1;
            // }    
            if (cmd != NULL)
            {
                    ft_execute(cmd, eniv, mini, envp);
            }
            // if(cmd->file != NULL)
            // { 
            //     printf("come estas \n ");
            //     redi_heredoc(cmd);
            // }
           // printf("============> = \n");    
        }
         
           
        // t_token *tmp;
        // tmp = mini->token;
        // tmp = tmp->next;
        // while(tmp)
        // {
        //     printf("{%s}  ===  %d\n", tmp->value, tmp->e_type);
        //     tmp = tmp->next;
        // }
        // free (mini->lexer->src);
        // free(mini->lexer);
        
        // while(mini->token != NULL)
        // {
        //     tmp = mini->token;
        //     mini->token = mini->token->next;
        //     free(tmp);
        // }
        // free(str);
        // tmp1 = cmd;
        // int i = 0;
        // while(tmp1)
        // {
        //     i = 0;
        //     printf("-------------cmd------------/\n");
        //     while(tmp1->cmd[i])
        //         printf("{%s}\n", tmp1->cmd[i++]);    
        //     t_file *tmpf = tmp1->file ;
        //     printf("-------------file------------/\n");

        //     while (tmpf)
        //     {
        //         printf("%s\n", tmpf->file_name);
        //         tmpf =  tmpf->next;
        //     }
        //     printf("-------------------------/\n");

        // //     printf("-------------------------");
        //     tmp1 = tmp1->next;
        // }
        mini->token = NULL;
        cmd = NULL;
        free(str);
        str = 0;
        dup2(fd,0);
    }
}