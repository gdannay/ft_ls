NAME	=	ft_ls

SRCS	=	./srcs/ft_ls.c

OBJS	=	$(SRCS:.c=.o)

CC		=	gcc

CFLAGS	=	-Wall -Werror -Wextra -I./includes/ -I./libft/

all		:	$(NAME)

$(NAME)	:	$(OBJS)
			make -C libft
			$(CC) $(OBJS) -L libft -lft -o $(NAME)

%.o		:	%.c
			$(CC) -o $@ ć $< $(CFLAGS)

clean	:	
			make clean -C libft
			rm -rf $(OBJS)

fclean	:	clean
			make fclean -C libft
			rm -rf $(NAME)

re		:	fclean all
