# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tkiselev <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/23 16:17:03 by tkiselev          #+#    #+#              #
#    Updated: 2018/09/23 16:39:53 by tkiselev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
CFLAGS=-Wall -Werror -Wextra

FT_SSL=ft_ssl

SRC_DIR=./src/
INCLUDES=includes/
MAIN_HEADER=ft_ssl.h
LIBFT_DIR=libft/
LIBFT=libft.a
LIBFT_HEADER=libft.h

SRCS=$(addprefix $(SRC_DIR), main.c\
	md5.c\
	md5_sha_algo_staff.c\
	md5_sha_output.c\
	md5_sha_parser_1.c\
	md5_sha_parser_2.c\
	sha256.c\
	staff.c)

OBJS=$(SRCS:.c=.o)

all: $(LIBFT) $(FT_SSL)

$(FT_SSL): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_DIR)$(LIBFT) -o $(FT_SSL)

%.o: %.c $(INCLUDES)$(MAIN_HEAEDER) $(LIBFT_DIR)$(LIBFT_HEADER)
	$(CC) -c $(CFLAGS) $< -I $(INCLUDES) -I $(LIBFT_DIR) -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	make clean -C $(LIBFT_DIR)
	rm -f $(OBJS)

fclean:
	make fclean -C $(LIBFT_DIR)
	make clean
	rm -f $(FT_SSL)

re: fclean all
