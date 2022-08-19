/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kouc <ael-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 04:22:12 by ael-kouc          #+#    #+#             */
/*   Updated: 2021/11/23 02:23:52 by ael-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*hay;
	char	*nee;
	size_t	i;
	size_t	j;

	if (len == 0 && !haystack && needle)
		return (NULL);
	hay = (char *)haystack;
	nee = (char *)needle;
	i = 0;
	if (nee[0] == '\0')
		return (hay);
	while (hay[i] && i < len)
	{
		j = 0;
		while (hay[i + j] && hay[i + j] == nee[j] && (j + i) < len)
		{
			if (nee[j + 1] == '\0')
				return (&hay[i]);
			j++;
		}
		i++;
	}
	return (0);
}
