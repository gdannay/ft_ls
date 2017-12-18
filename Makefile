# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gdannay <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/15 10:22:09 by gdannay           #+#    #+#              #
#    Updated: 2017/12/18 13:17:44 by gdannay          ###   ########.fr        #
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
			./srcs/manage_list.c

OBJS	=	$(SRCS:.c=.o)

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror -I./includes/

LDFLAGS	=	-L./libft -lft -L./ft_printf -lftprintf

all		:	$(NAME)

$(NAME)	:	$(OBJS)
			make -C libft
			make -C ft_printf
			$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)
			
%.o		:	%.c
			$(CC) -o $@ -c $< $(CFLAGS)

clean	:	
			make clean -C libft
			make clean -C ft_printf
			rm -rf $(OBJS)

fclean	:	
			make fclean -C libft
			make fclean -C ft_printf
			rm -rf $(OBJS)
			rm -rf $(NAME)

re		:	fclean all
