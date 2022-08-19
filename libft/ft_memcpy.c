/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kouc <ael-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 04:16:09 by ael-kouc          #+#    #+#             */
/*   Updated: 2021/11/23 01:42:35 by ael-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void	*dst, const void	*src, size_t n)
{
	unsigned char	*dest;
	unsigned char	*srrc;
	size_t			i;

	dest = (unsigned char *)dst;
	srrc = (unsigned char *)src;
	i = 0;
	if (dest == srrc)
		return (dest);
	if (dest == NULL && srrc == NULL)
		return (NULL);
	while (i < n)
	{
		dest[i] = srrc[i];
		i++;
	}
	return (dest);
}
