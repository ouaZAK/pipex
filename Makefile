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
		split_it.c \
		putstr_fd.c \
		set_pipes.c \
		parent_and_childs.c \
		get_next_line_bonus.c \
		get_next_line_utils_bonus.c 

OBJ = $(SRC:.c=.o)


%.o : %.c
	$(CC) $(FLAGS) -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(FLAGS) $^ -o $@

bonus : all

clean :
	@$(RM) $(OBJ)

fclean : clean
	@$(RM) $(NAME)  

re : fclean all