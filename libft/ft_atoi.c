/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 04:08:33 by ael-kouc          #+#    #+#             */
/*   Updated: 2021/11/22 04:08:40 by ael-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char	*str)
{
	int					sign;
	unsigned long int	rus;
	unsigned long int	i;

	sign = 1;
	rus = 0;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		rus = (rus * 10) + (str[i] - 48);
		i++;
		if (rus > 9223372036854775807 && (sign == 1))
			return (-1);
		if (rus > 9223372036854775807 && (sign == -1))
			return (0);
	}
	return (rus * sign);
}
