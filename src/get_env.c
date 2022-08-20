/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelbiad <mbelbiad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 14:17:45 by ael-kouc          #+#    #+#             */
/*   Updated: 2022/08/20 18:41:28 by mbelbiad         ###   ########.fr       */
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
	//char	**env;
	int		i;

	i = 0;
	envv = malloc(sizeof(char *) * (lent_d_pointer(str) + 1));
	while(str[i])
	{
		envv[i] = ft_strdup(str[i]);
		i++;	
	}
	envv[i] = NULL;
	return(envv);
}