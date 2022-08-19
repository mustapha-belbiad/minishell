/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 04:21:15 by ael-kouc          #+#    #+#             */
/*   Updated: 2021/11/22 04:21:19 by ael-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char	*dst, const char	*src, size_t dstsize)
{
	size_t	i;
	size_t	l;

	i = 0;
	l = ft_strlen(src);
	if (dst == src)
		return (l);
	if (dst == NULL && src == NULL)
		return (0);
	if (dstsize == 0)
		return (l);
	while (src[i] && (i < dstsize - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (l);
}
