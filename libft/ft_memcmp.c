/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 04:15:33 by ael-kouc          #+#    #+#             */
/*   Updated: 2021/11/22 04:15:59 by ael-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*src;
	unsigned char	*dest;
	size_t			i;

	src = (unsigned char *)s1;
	dest = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (src[i] == dest[i] && i < n - 1)
		i++;
	return (src[i] - dest[i]);
}
