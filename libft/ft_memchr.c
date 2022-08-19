/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 04:15:07 by ael-kouc          #+#    #+#             */
/*   Updated: 2021/11/22 04:15:16 by ael-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*h;
	size_t			i;

	h = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (h[i] == (unsigned char)c)
			return (&h[i]);
		i++;
	}
	return (NULL);
}
