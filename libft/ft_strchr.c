/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 04:19:47 by ael-kouc          #+#    #+#             */
/*   Updated: 2021/11/22 04:19:52 by ael-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char	*s, int c)
{
	char	*h;
	int		i;

	h = (char *)s;
	c = (char)c;
	i = 0;
	if (c == 0)
		return (&h[ft_strlen(s)]);
	while (h[i] != '\0')
	{
		if (h[i] == c)
			return (h + i);
		i++;
	}
	return (NULL);
}
