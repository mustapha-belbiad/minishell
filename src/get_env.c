/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kouc <ael-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 14:17:45 by ael-kouc          #+#    #+#             */
/*   Updated: 2022/06/28 14:23:06 by ael-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

int lent_d_pointer(char **str)
{
	int	i;

	i = 0;
	while(str[i])
		i++;
	return(i);
}

char	**get_env(char	**str)
{
	char	**env;
	int		i;

	i = 0;
	env = malloc(sizeof(char *) * (lent_d_pointer(str) + 1));
	while(str[i])
	{
		env[i] = ft_strdup(str[i]);
		i++;	
	}
	env[i] = NULL;
	return(env);
}