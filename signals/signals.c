/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelbiad <mbelbiad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 18:58:06 by mbelbiad          #+#    #+#             */
/*   Updated: 2022/09/26 02:34:28 by mbelbiad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

void	catch_sig(int signum)
{
	int fd;
	
	if (g_env->crtl_c == 1)
	{	
		// g_env->crtl_c = 1;
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
