/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelbiad <mbelbiad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 11:47:34 by ael-kouc          #+#    #+#             */
/*   Updated: 2022/08/21 22:32:52 by mbelbiad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

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
        add_history(str);
        mini->lexer = init_lexer(str);
        mini->token = pick_tokens(mini->lexer, envp);
        tmpv = mini->token;
        cmd = fill_cmd(mini->token, cmd);

        ft_check_builtins(cmd, eniv);        
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
        // while(tmp1)
        // {
        //     printf("-------------cmd------------/\n");
        //     printf("{%s}\n", tmp1->cmd[0]);
        //     printf("{%s}\n", tmp1->cmd[1]);
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
    }
}