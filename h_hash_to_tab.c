/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_hash_to_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschafer <aschafer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 17:25:13 by aschafer          #+#    #+#             */
/*   Updated: 2016/11/14 17:25:14 by aschafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libhash.h"

static char	*get_line(t_elem *elem)
{
	static char buffer[10000];

	ft_bzero(buffer, 10000);
	ft_strcat(buffer, elem->key);
	ft_strcat(ft_strcat(buffer, "="), elem->value);
	return (ft_strdup(buffer));
}

static void	fill_tab(t_hash *hash, char **tab)
{
	int		i;
	int		j;
	t_elem	*elem;

	j = 0;
	i = 0;
	while (i < hash->size)
	{
		if ((elem = hash->hash_tab[i]))
		{
			while (elem)
			{
				tab[j++] = get_line(elem);
				elem = elem->next;
			}
		}
		i++;
	}
}

char		**hash_to_tab(t_hash *hash)
{
	char	**tab;

	if (!(tab = (char **)ft_memalloc(hash->size * sizeof(char *))))
		return (NULL);
	fill_tab(hash, tab);
	return (tab);
}
