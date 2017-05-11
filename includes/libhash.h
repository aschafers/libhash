/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libhash.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschafer <aschafer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 17:29:26 by aschafer          #+#    #+#             */
/*   Updated: 2017/01/30 20:36:36 by qle-bevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBHASH_H
# define LIBHASH_H
# define VAL_OK 1
# define NUM_OK 2
# define LEN_OK 4

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>

typedef struct s_elem		t_elem;
struct						s_elem
{
	char					*key;
	char					*value;
	t_elem					*next;
};

typedef struct s_hash		t_hash;
struct						s_hash
{
	char					*name;
	int						size;
	int						nb_elem;
	t_elem					**hash_tab;
};

/*
******	OTHER
*/

int							h_get_key(int size, char *key);

/*
******	LISTES
*/

t_elem						*lst_push_elem(t_elem **entry, char *key, \
		char *value);
t_elem						*lst_new_elem(char *key, char *value);

/*
******	ELEMENTS
*/
t_elem						*h_add_elem(t_hash *hash, char *key, char *value);
int							h_delete_elem(t_hash *hash, char *key);
void						h_split_store_elem(t_hash *hash, char *str, char c);
t_elem						*h_get_elem_by_key(t_hash *hash, char *key);
char						*h_get_value_by_key(t_hash *hash, char *key);
t_elem						*h_set_or_create_elem(t_hash *hash, char *key, \
		char *value);

/*
******	HASH
*/

t_hash						*create_hash(char *name, int size);
void						h_print(t_hash *hash, int opts);
void						h_free(t_hash **hash, int full);
char						**hash_to_tab(t_hash *hash);

#endif
