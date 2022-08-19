/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 04:22:26 by ael-kouc          #+#    #+#             */
/*   Updated: 2021/11/22 04:22:30 by ael-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char	*s, int c)
{
	char	*x;
	int		l;

	x = (char *)s;
	if (c == 0)
		return (x + ft_strlen(s));
	l = ft_strlen(s);
	while (l >= 0)
	{
		if (x[l] == (unsigned char)c)
			return (&x[l]);
		l--;
	}
	return (0);
}
