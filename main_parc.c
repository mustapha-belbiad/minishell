/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelbiad <mbelbiad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 11:47:34 by ael-kouc          #+#    #+#             */
/*   Updated: 2022/09/29 18:48:45 by mbelbiad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

int	chack_readl(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

void	change_value(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->e_type == REDIRECT_IN || tmp->e_type == REDIRECT_OT
			|| tmp->e_type == D_REDIRECT_OT || tmp->e_type == D_REDIRECT_IN)
		{
			if (tmp->next)
			{
				tmp->next->e_type = tmp->e_type;
				tmp = tmp->next;
			}
			if (tmp->e_type == S_Q || tmp->e_type == D_Q
				|| tmp->e_type == CMD_WORD)
			{
				while (tmp->e_type == S_Q || tmp->e_type == D_Q
					|| tmp->e_type == CMD_WORD)
				{
					tmp->e_type = J;
					tmp = tmp->next;
				}
			}
		}
		tmp = tmp->next;
	}
}

void	free_token(t_token **token)
{
	t_token	*tmp;

	while ((*token))
	{
		tmp = (*token);
		*token = (*token)->next;
		free(tmp->value);
		free(tmp);
	}
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*tmpcmd;
	t_file	*tmpfile;
	int		i;

	while (cmd)
	{
		tmpcmd = cmd;
		while (tmpcmd->file)
		{
			tmpfile = tmpcmd->file;
			tmpcmd->file = tmpcmd->file->next;
			free(tmpfile->file_name);
			free(tmpfile);
		}
		i = 0;
		if (tmpcmd->cmd)
		{
			while (tmpcmd->cmd[i])
			{
				free(tmpcmd->cmd[i]);
				i++;
			}
			free(tmpcmd->cmd);
		}
		cmd = cmd->next;
		free(tmpcmd);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_mini	*mini;
	char	*str;
	t_cmd	*cmd;
	t_file	*files;
	t_token	*tmpv;
	t_env	*eniv;
	int		fd;

	if (envp == NULL)
	{
		g_env->ret_val = 1;
		exit(g_env->ret_val);
	}
	eniv = malloc(sizeof(t_env));
	ac = 0;
	av = NULL;
	files = NULL;
	mini = malloc(sizeof(t_mini));
	mini->env = get_env(envp);
	g_env = ft_link_env(eniv, mini->env);
	g_env->crtl_c = 0;
	get_line();
	g_env->envb = get_env(envp);
	g_env->ret_val = 0;
	change_envir();
	while (1)
	{
		fd = dup(0);
		str = readline("minishell $ ");
		if (str == NULL)
		{
			printf("exit\n");
			exit(1);
		}
		if (str[0] && chack_readl(str) == 1)
		{
			add_history(str);
			mini->lexer = init_lexer(str);
			mini->token = pick_tokens(mini->lexer, g_env->envb);
			tmpv = mini->token;
			cmd = fill_cmd(mini->token, cmd);
			if (cmd != NULL)
				ft_execute(cmd, g_env->envb);
		}
		free_token(&mini->token);
		free_cmd(cmd);
		mini->token = NULL;
		cmd = NULL;
		free(str);
		str = 0;
		dup2(fd, 0);
	}
}
