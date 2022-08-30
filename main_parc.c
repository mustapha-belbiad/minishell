/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelbiad <mbelbiad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 11:47:34 by ael-kouc          #+#    #+#             */
/*   Updated: 2022/08/30 04:16:39 by mbelbiad         ###   ########.fr       */
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
    i = 0;
    while(tmp)
    {
        if(tmp->e_type == REDIRECT_IN || tmp->e_type == REDIRECT_OT
            || tmp->e_type == D_REDIRECT_OT || tmp->e_type == D_REDIRECT_IN)
        {
            if(tmp->next)
            {
                i = tmp->e_type;
                tmp->next->e_type = i;
                tmp = tmp->next;
            }
        }
        tmp = tmp->next;
    }
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
    
    while(1)
    {
        str = readline("minishel>");
        if(str[0] && chack_readl(str) == 1)
        {
            add_history(str);
            mini->lexer = init_lexer(str);
            mini->token = pick_tokens(mini->lexer, envp);
            tmpv = mini->token;
            cmd = fill_cmd(mini->token, cmd);
        }
        if (cmd != NULL)
        {
            //ft_check_builtins(cmd, eniv);
            ft_execute(cmd, eniv, mini, envp);
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
        tmp1 = cmd;
        int i;
        while(tmp1)
        {
            i = 0;
            printf("-------------cmd------------/\n");
            // while(cmd->cmd[i])
            //     printf("----");
            t_file *tmpf = tmp1->file ;
            printf("-------------file------------/\n");

            while (tmpf)
            {
                printf("%s\n", tmpf->file_name);
                printf("%d\n", tmpf->e_type);
                tmpf =  tmpf->next;
            }
            printf("-------------------------/\n");

             printf("-------------------------\n");
            tmp1 = tmp1->next;
        }
        mini->token = NULL;
        cmd = NULL;
        // free(str);
    }
}