/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kouc <ael-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 04:16:48 by ael-kouc          #+#    #+#             */
/*   Updated: 2021/11/23 01:57:01 by ael-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void	*b, int c, size_t len)
{
	size_t			i;
	unsigned char	*k;

	k = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		k[i] = (unsigned char)c;
		i++;
	}
	return (k);
}
