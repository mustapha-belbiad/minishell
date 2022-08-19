/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelbiad <mbelbiad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 11:47:34 by ael-kouc          #+#    #+#             */
/*   Updated: 2022/08/19 22:50:04 by mbelbiad         ###   ########.fr       */
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
        if(tmp->type == REDIRECT_IN || tmp->type == REDIRECT_OT
            || tmp->type == D_REDIRECT_OT || tmp->type == D_REDIRECT_IN)
        {
            i = tmp->type;
            tmp->next->type = i; 
            tmp = tmp->next;
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

    files = NULL;
    mini = malloc(sizeof(t_mini));
    mini->env = get_env(envp);
    
    while(1)
    {
        str = readline("minishel>");
        add_history(str);
        mini->lexer = init_lexer(str);
        mini->token = pick_tokens(mini->lexer, envp);
        change_value(mini->token);
        tmpv = mini->token;
        mini->parser = return_error(mini->token);
        // printf("%s\n", mini->parser->value);
        cmd = fill_cmd(mini->token, cmd);
        
        //-------------------------------------------
        ft_check_builtins(cmd);

        
        // if (ft_strrrcmp(cmd->cmd[0], "pwd") == 1)
        // {
        //     char b[1024];
        //     printf("--------hoppla ----------------------------\n");
        //     getcwd(b, 1024);
        //     printf("%s \n", b);
        // }


        //-------------------------------------------
        // t_token *tmp;
        // tmp = mini->token;
        // tmp = tmp->next;
        // while(tmp)
        // {
        //     printf("{%s}  ===  %d\n", tmp->value, tmp->type);
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
        //     printf("%s\n", tmp1->cmd[0]);
        //     printf("%s\n", tmp1->cmd[1]);
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