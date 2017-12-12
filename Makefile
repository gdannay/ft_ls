NAME	=	ft_ls

SRCS	=	./srcs/ft_ls.c

OBJS	=	$(SRCS:.c=.o)

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror -I./includes/ -I./libft/

all		:	$(NAME)

$(NAME)	:	$(OBJS)
			make -C libft
			$(CC) $(OBJS) -L libft -lft -o $(NAME)

%.o		:	%.c
			$(CC) -o $@ -c $< $(CFLAGS)

clean	:	
			make clean -C libft
			rm -rf $(OBJS)

fclean	:	
			@echo "make fclean -C libft"
			rm -rf $(OBJS)
			rm -rf $(NAME)

re		:	fclean all
