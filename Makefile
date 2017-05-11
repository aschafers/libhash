# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bdesbos <bdesbos@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/29 15:12:07 by bdesbos           #+#    #+#              #
#    Updated: 2017/01/30 20:42:25 by qle-bevi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libhash.a

SRC_PATH = .

OBJ_PATH = obj

HEAD = includes/libhash.h ../libft/includes/libft.h

CHECK_LIB = ../libft/libft.a

SRC_NAME = h_add_elem.c h_create_hash.c h_get_elem_by_key.c \
		   h_get_value_by_key.c h_hash_to_tab.c h_lst_new.c h_lst_push.c \
		   h_memory.c h_print.c h_resolve_key.c h_set_or_create_elem.c \
		   h_split_store_elem.c

INCL = -I./includes/ -I../libft/includes

CC = gcc

FLAGS = -Wall -Werror -Wextra -O2 -g

INC = -I./includes/ -I../libft/include

OBJ_NAME = $(SRC_NAME:%.c=%.o)

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))

OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

all: title $(NAME)

title:
	@make -C ../libft/ all
	@echo "Checking libhash..."

$(NAME): $(OBJ)
	@ar rcs $@ $^
	@echo "\n✅  LIBHASH BUILT !\n"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(HEAD) $(CHECK_LIB)
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(CC) $(FLAGS) $(INCL) -o $@ -c $<
	@echo "libhash => \033[33;32m$@\033[33;0m"

clean:
	@rm -f $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true
	@echo "libhash cleaned"

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re title
