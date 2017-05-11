/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_print.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschafer <aschafer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 17:26:21 by aschafer          #+#    #+#             */
/*   Updated: 2016/11/14 17:26:22 by aschafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libhash.h"

static void	h_print_inf(t_hash *hash, int opts, int col)
{
	char *temp;

	temp = NULL;
	if (opts & LEN_OK)
	{
		temp = ft_itoa(hash->size);
		ft_putendl("");
		ft_putstr("Hash size ");
		ft_putstr_color(temp, hash->size > hash->nb_elem ? 2 : 3);
		free(temp);
		temp = ft_itoa(hash->nb_elem);
		ft_putstr(", number of elements in the hash ");
		ft_putstr_color(temp, hash->size > hash->nb_elem ? 2 : 3);
		free(temp);
		ft_putstr(", number of collisions ");
		ft_putstr_color((temp = ft_itoa(col)), 5);
		free(temp);
		ft_putstr_color(hash->size > hash->nb_elem ? " :)\n" : " :(\n",
		hash->size > hash->nb_elem ? 2 : 3);
	}
}

static void	h_print_num(t_elem *curr_elem, int opts, int i, int e)
{
	char *temp;

	temp = NULL;
	if (opts & NUM_OK)
	{
		temp = ft_itoa(i);
		ft_putstr_color(temp, curr_elem->next || e > 1 ? 3 : 2);
		ft_putstr(" -> ");
	}
	if (temp)
		free(temp);
}

static void	h_print_val(t_elem *curr_elem, int opts, int e)
{
	if (opts & VAL_OK)
	{
		ft_putstr(" = ");
		ft_putstr_color(curr_elem->value, curr_elem->next || e > 1 ? 3 : 2);
	}
}

static void	h_print_hash(t_elem *curr_elem, int opts, int i, int e)
{
	h_print_num(curr_elem, opts, i, e);
	ft_putstr_color(curr_elem->key, curr_elem->next || e > 1 ? 3 : 2);
	h_print_val(curr_elem, opts, e);
	ft_putendl("");
}

void		h_print(t_hash *hash, int opts)
{
	t_elem	*curr_elem;
	int		i;
	int		e;
	int		col;

	col = 0;
	i = 0;
	e = 0;
	while (i < hash->size)
	{
		if ((curr_elem = hash->hash_tab[i]))
		{
			while (curr_elem)
			{
				h_print_hash(curr_elem, opts, i, ++e);
				curr_elem = curr_elem->next;
			}
		}
		col += e > 1 ? e : 0;
		e = 0;
		i++;
	}
	h_print_inf(hash, opts, col);
}
