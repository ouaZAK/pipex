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
		putstr_fd.c \
		set_pipes.c \
		check_errors.c \
		get_next_line.c \
		get_next_line_utils.c

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