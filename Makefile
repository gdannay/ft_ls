# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gdannay <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/15 10:22:09 by gdannay           #+#    #+#              #
#    Updated: 2018/01/05 11:13:16 by gdannay          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	ft_ls

SRCS	=	./srcs/ft_ls.c			\
			./srcs/get_infos.c		\
			./srcs/manage_args.c	\
			./srcs/manage_path.c	\
			./srcs/display.c		\
			./srcs/manage_error.c	\
			./srcs/manage_lflag.c	\
			./srcs/manage_list.c	\
			./srcs/display_bigr.c	\
			./srcs/checks.c			\
			./srcs/cmp.c

OBJS	=	$(SRCS:.c=.o)

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror -I./ -I./includes

LDFLAGS	=	libft/libft.a

all		:	$(NAME)

$(NAME)	:	$(OBJS)
			make -C libft
			$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)
			
%.o		:	%.c
			$(CC) -o $@ -c $< $(CFLAGS)

clean	:	
			make clean -C libft
			rm -rf $(OBJS)

fclean	:	
			make fclean -C libft
			rm -rf $(OBJS)
			rm -rf $(NAME)

re		:	fclean all
