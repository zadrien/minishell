# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/02 18:16:06 by zadrien           #+#    #+#              #
#    Updated: 2017/11/06 12:42:31 by zadrien          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY:			all clean fclean name re

CC=				gcc

NAME=			minishell

CFLAGS=			-Wall -Werror -Wextra

CPATH=			srcs/

OPATH=			obj/

HPATH=			includes/ libft/

INC=			$(addprefix -I , $(HPATH))

CFILES= 		main.c	\
				main2.c	\
				binary_finder1.c	\
				binary_finder2.c	\
				cd1.c	\
				cd2.c	\
				echo.c	\
				env.c	\
				exit.c	\
				listing_env.c	\
				primary_functions.c	\
				primary_functions2.c	\
				setenv.c	\
				sh_level.c	\
				unsetenv.c	\


OFILES=			$(CFILES:.c=.o)

HFILES=			includes/minishell.h \
				libft/libft.h	\

OBJ=			$(addprefix $(OPATH), $(OFILES))


all: $(NAME)

$(NAME): $(OBJ)
	make -C libft
	$(CC) $(CFLAGS) $(OBJ) libft/libft.a -o $(NAME)

$(OPATH)%.o: $(CPATH)%.c $(HFILES)
	@mkdir -p $(OPATH)/
	$(CC) $(CFLAGS)  $(INC) $< -c -o $@

clean:
	make -C libft clean
	rm -rf $(OBJ)

fclean: clean
	make -C libft fclean
	rm -rf $(NAME)
	rm -rf $(OPATH)

re: fclean all

norme:
	@norminette srcs/**/**.[ch]
	@norminette libft/*.[ch]
