/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 04:14:40 by ael-kouc          #+#    #+#             */
/*   Updated: 2021/11/22 04:14:49 by ael-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count(long int num)
{
	int	count;

	count = 0;
	if (num <= 0)
	{
		num = num * (-1);
		count++;
	}
	while (num > 0)
	{
		num /= 10;
		count++;
	}
	return (count);
}

char	*ft_min_itoa(char *str, long int nb, int a, int count)
{
	str = malloc(sizeof(char) * (count + 1));
	if (!str)
		return (NULL);
	str[count--] = '\0';
	while (count >= 0)
	{
		str[count--] = (nb % 10) + 48;
		nb = nb / 10;
	}
	if (a < 0)
		str[0] = '-';
	return (str);
}

char	*ft_itoa(int n)
{
	int			a;
	int			count;
	long int	nb;
	char		*str;

	nb = n;
	a = 0;
	str = NULL;
	if (!nb)
		return (ft_strdup("0"));
	count = ft_count(nb);
	if (nb < 0)
	{
		nb *= -1;
		a--;
	}
	return (ft_min_itoa(str, nb, a, count));
}
