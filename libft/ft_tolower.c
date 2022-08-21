/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelbiad <mbelbiad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 04:23:16 by ael-kouc          #+#    #+#             */
/*   Updated: 2022/08/21 16:41:16 by mbelbiad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		return (c + 32);
	else
		return (c);
}

int ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	char **cmd = ft_split(s2, '=');
	while(s1[i] && cmd[0][i])
	{
		if(s1[i] != cmd[0][i])
			break;
		i++;
	}
	
	if (s1[i] != cmd[0][i])
	{
		free(cmd);
		return (0);
	}
	else 
	{
		free(cmd);
		return(1);
	}
}