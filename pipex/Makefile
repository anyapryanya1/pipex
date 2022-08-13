NAME	=	pipex

SRCS	=	pipex.c ft_split.c ft_strjoin.c ft_strnstr.c ft_strlen.c

HEADER	=	pipex.h

OBJS	=	$(SRCS:%.c=%.o)

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror -I$(HEADER)

.PHONY	:	all clean fclean re

all		:	$(NAME)

$(NAME)	:	$(OBJS) $(HEADER)
			$(CC) $(CFLAGS) $(INC) $(OBJS) -o $(NAME)

%.o 	:	%.c $(HEADER)
			$(CC) $(CFLAGS) -c $< -o $@

clean	:
			@rm -f $(OBJS)

fclean	:	clean
			@$(RM) $(NAME)

re		:	fclean all