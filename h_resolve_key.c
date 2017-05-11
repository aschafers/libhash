/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_resolve_key.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschafer <aschafer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 17:26:39 by aschafer          #+#    #+#             */
/*   Updated: 2016/11/14 17:26:40 by aschafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libhash.h"

int	h_get_key(int size, char *key)
{
	int ret;
	int i;

	ret = 0;
	i = 0;
	while (key[i])
	{
		if (key[i + 1])
			ret += key[i] * (key[i + 1] * i);
		else
			ret += key[i] * i;
		i++;
	}
	return (ret % size);
}
