# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mderome <mderome@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/02 10:28:07 by mderome           #+#    #+#              #
#    Updated: 2022/01/18 12:20:13 by mderome          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

HEADER_PATH = ./include/
SRC_PATH = ./srcs/
SRC =	main.c		\
		atoi.c		\
		init_arg.c	\

SRC_BASENAME = $(addprefix $(SRC_PATH), $(SRC))
CC =	gcc
CFLAGS =  -pthread -I $(HEADER_PATH) #-Wall -Wextra -Werror

.c.o :
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

OBJ = $(SRC_BASENAME:.c=.o)

all :	$(NAME)

$(NAME) : 	$(OBJ) $(HEADER_PATH)
			$(CC) -o $(NAME) $(CFLAGS) $(OBJ)

clean :
	rm -f $(OBJ)

fclean :	clean
			rm -rf $(NAME)

re : fclean all

