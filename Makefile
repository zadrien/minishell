# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/26 20:45:05 by zadrien           #+#    #+#              #
#    Updated: 2017/03/17 19:37:05 by zadrien          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: make all clean fclean re

NAME = minishell

LIB = -L libft/ -lft

LIBFT = libft/libft.a

C_DIR = srcs/

SRCS = main.c main2.c env.c echo.c exit.c unsetenv.c setenv.c cd1.c cd2.c	\
		binary_finder1.c binary_finder2.c listing_env.c primary_functions.c	\
		sh_level.c primary_functions2.c	\

SRC = $(addprefix $(C_DIR), $(SRCS))

OBJ = $(SRCS:.c=.o)

INC = -I includes -I libft/

all : $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@gcc -Wall -Wextra -Werror $^ -o $@ $(LIB)

$(LIBFT):
	@make -C libft/
	@echo "Compilation Minishell: DONE"

$(OBJ) : $(SRC)
	@echo "Compilation Minishell: In progress"
	@gcc -c -Wall -Wextra -Werror $^ $(INC)

clean :
	@make clean -C libft/
	@echo "Suppression Objet LIBFT : OK"
	@rm -f $(OBJ)
	@echo "Suppression Objet SRCS : OK"

fclean : clean
	@rm -f $(LIBFT)
	@echo "Suppression libft.a : OK"
	@rm -f $(NAME)
	@echo "Suppression (executable) minishell : OK"

re : fclean all
