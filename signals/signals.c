/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelbiad <mbelbiad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 07:01:02 by ael-kouc          #+#    #+#             */
/*   Updated: 2022/09/27 16:21:24 by mbelbiad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

// char	**get_linked_ar(t_env *eniv)
// {
// 	char	**str;
// 	t_env	*tmp;
// 	int		i;
	
// 	tmp = eniv;
// 	i = 0;
// 	while(tmp)
// 	{
// 		tmp = tmp->next;
// 		i++;
// 	}
// 	tmp = eniv;
// 	str = malloc(sizeof(char *) * i + 1);
// 	i = 0;
// 	while(tmp)
// 	{
// 		str[i] = ft_strdup(tmp->envir);
// 		i++;
// 		tmp = tmp->next;
// 	}
// 	str[i] = NULL;
// 	return(str);
// }

void	catch_sig(int signum)
{
	//int fd;
	
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
