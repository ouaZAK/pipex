CC = cc
NAME = pipex
FLAGS = -Wall -Wextra -Werror
RM = rm -rf
SRC =	pipex.c \
		utils1.c \
		utils2.c \
		utils3.c \
		path.c \
		which_cmd.c \
		putstr_fd.c \
		split_it.c \

OBJ = $(SRC:.c=.o)

%.o : %.c
	@$(CC) $(FLAGS) -c $< -o $@

all : $(NAME)

$(NAME) : $(SRC)
	@$(CC) $(FLAGS) $^ -o $@

clean :
	@$(RM) $(OBJ)

fclean : clean
	@$(RM) $(NAME)

re : fclean all