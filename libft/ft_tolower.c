/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelbiad <mbelbiad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 04:23:16 by ael-kouc          #+#    #+#             */
/*   Updated: 2022/08/30 22:06:35 by mbelbiad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
	while(s1[i] && s2[i])
	{
		if(s1[i] != s2[i])
			return(0);
		i++;
	}
	return(1);
}