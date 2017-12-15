# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gdannay <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/15 10:22:09 by gdannay           #+#    #+#              #
#    Updated: 2017/12/15 15:19:58 by gdannay          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	ft_ls

SRCS	=	./srcs/ft_ls.c			\
			./srcs/get_infos.c		\
			./srcs/manage_args.c	\
			./srcs/manage_path.c

OBJS	=	$(SRCS:.c=.o)

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror -I./libft/ -I./includes/

all		:	$(NAME)

$(NAME)	:	$(OBJS)
			make -C libft
			$(CC) $(OBJS) -L libft -lft -L. -lftprintf -o $(NAME)

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
