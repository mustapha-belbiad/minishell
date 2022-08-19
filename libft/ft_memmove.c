/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 04:16:26 by ael-kouc          #+#    #+#             */
/*   Updated: 2021/11/22 04:16:31 by ael-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*a;
	char	*b;

	a = (char *)dst;
	b = (char *)src;
	if (a > b)
	{
		while (len--)
		{
			a[len] = b[len];
		}
		return (a);
	}
	return (ft_memcpy(a, b, len));
}
