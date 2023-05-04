# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zouaraqa <zouaraqa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/01 09:42:48 by zouaraqa          #+#    #+#              #
#    Updated: 2023/05/03 13:27:44 by zouaraqa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
NAME = pipex
FLAGS = -Wall -Wextra -Werror
RM = rm -rf
SRC =	pipex.c \
		utils1.c \
		utils2.c \
		utils3.c \
		path.c \
		childs.c \
		herdoc.c \
		split_it.c \
		checking.c \
		ft_putstr_fd.c \
		set_pipes.c \
		check_errors.c \
		get_next_line_bonus.c \
		get_next_line_utils_bonus.c

OBJ = $(SRC:.c=.o)

%.o : %.c
	@$(CC) $(FLAGS) -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJ)
	@$(CC) $(FLAGS) $^ -o $@

bonus : all

clean :
	@$(RM) $(OBJ)

fclean : clean
	@$(RM) $(NAME)  

re : fclean all