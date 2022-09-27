/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_list_of_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kouc <ael-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 21:33:57 by ael-kouc          #+#    #+#             */
/*   Updated: 2022/09/21 14:06:45 by ael-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

char	*change_value_cmd(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '~')
		{
			i++;
			while (str[i] && str[i] != '~')
			{
				if (str[i] == ' ')
					str[i] = 127;
				i++;
			}
		}
		if (str[i] != '\0')
			i++;
	}
	return (str);
}

char	*deleat(char *str)
{
	int		i;
	char	*c;
	char	*ret;
	char	*tmp;

	i = 0;
	ret = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '~')
			i++;
		else
		{
			tmp = ret;
			c = get_c_as_str(str[i]);
			ret = ft_strjoin(ret, c);
			free(c);
			free(tmp);
			i++;
		}
	}
	free(str);
	return (ret);
}

char	**change_value2(char **str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		str[i] = deleat(str[i]);
		i++;
	}
	return (str);
}
