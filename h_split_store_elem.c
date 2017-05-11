/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_split_store_elem.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschafer <aschafer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 17:27:43 by aschafer          #+#    #+#             */
/*   Updated: 2016/11/14 17:28:06 by aschafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libhash.h"

void	h_split_store_elem(t_hash *hash, char *str, char c)
{
	char	**tab;
	char	*string;
	int		i;

	i = 2;
	tab = ft_strsplit(str, c);
	string = ft_strdup(tab[1]);
	if (ft_tablen(tab) > 2)
	{
		while (tab[i])
		{
			string = ft_strrejoin(string, string, "=");
			string = ft_strrejoin(string, string, tab[i]);
			i++;
		}
	}
	h_add_elem(hash, tab[0], string);
	ft_memdel((void**)&string);
	ft_free_tab(&tab);
}
