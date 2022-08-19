/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kouc <ael-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 12:59:42 by ael-kouc          #+#    #+#             */
/*   Updated: 2022/07/01 12:30:09 by ael-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char    *ft_realloc(char *str, size_t size)
{
    char *tmp;
    int i;

    i = 0;
    tmp = str;
    str = malloc(sizeof(char) * ft_strlen(tmp) + size);
    while (tmp[i])
    {
        str[i] = tmp[i];
        i++;
    }
    str[i] = '\0';
    free(tmp);
    return(str);
}