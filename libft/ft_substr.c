/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kouc <ael-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 04:23:00 by ael-kouc          #+#    #+#             */
/*   Updated: 2022/05/24 06:53:36 by ael-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	i;
	unsigned int	j;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		len = 0;
	i = 0;
	while (i < len && s[i])
		i++;
	str = malloc(i + 1);
	if (!str)
		return (NULL);
	j = 0;
	while (j < i)
	{
		str[j++] = s[start++];
	}
	str[j] = '\0';
	return (str);
}
