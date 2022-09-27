/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kouc <ael-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 07:01:02 by ael-kouc          #+#    #+#             */
/*   Updated: 2022/09/27 22:03:01 by ael-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

int	lent(void)
{
	t_env	*tmp;
	int		i;

	tmp = g_env;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

void	change_envir(void)
{
	int		i;
	t_env	*tmp;

	i = 0;
	g_env->envb = malloc(sizeof(char *) * (lent() + 1));
	tmp = g_env;
	i = 0;
	while (tmp)
	{
		g_env->envb[i] = ft_strdup(tmp->envir);
		tmp = tmp->next;
		i++;
	}
	g_env->envb[i] = NULL;
}

void	catch_sig(int signum)
{
	if (g_env->crtl_c == 1)
	{
		printf("\n");
		close(0);
		g_env->crtl_c = 0;
	}
	else
	{
		(void)signum;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	get_line(void)
{
	signal(SIGINT, catch_sig);
	signal(SIGQUIT, SIG_IGN);
}
