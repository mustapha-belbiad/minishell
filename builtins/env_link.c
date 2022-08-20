/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_link.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelbiad <mbelbiad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 18:41:03 by mbelbiad          #+#    #+#             */
/*   Updated: 2022/08/20 19:10:18 by mbelbiad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

t_env	*ft_lstnew(void *env)
{
	t_env	*node;
	node = (t_env*)malloc(sizeof(t_env));
    if (!node)
	{
		write(2, "Eroor\n", 7);
		return (NULL);
	}
	node->envir = env;
	node->next = NULL;
	return (node);
}

void	ft_list_addback(t_env **lst, t_env *new)
{
	t_env	*tmp;

    if (*lst == NULL)
        *lst = new;
    else
    {
	    tmp = (*lst);
	    while (tmp->next != NULL)
		    tmp = tmp->next;
	    tmp->next = new;
    }
}

void	*ft_link_env(t_env *envi, char **env)
{
	int i;

	i = -1;
    envi = NULL;
	while (env[++i])
		ft_list_addback(&envi, ft_lstnew(env[i]));
        
    // while (envi->next != NULL)
    // {
    //     printf("%s \n", envi->envir);
    //     envi = envi->next;
    // }
    return(envi);
}