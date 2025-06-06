NAME = minishell

# Directory
INC = -I ./include/
OBJ_DIR = obj/

# Complier
CC = cc
CFLAG = -Wall -Werror -Wextra
RM = rm -rf

SRCBASE = main
SRC = $(addsuffix .c, $(addprefix srcs/, $(SRCBASE)))

OBJ = $(SRC:srcs/%.c=$(OBJ_DIR)%.o)

start:
	@make all

# Ensure directories exist
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Build executable
all: $(NAME)
	@echo "\033[32m[Program is ready for use]\033[0m"

# Rule to compile object files
$(OBJ_DIR)%.o: srcs/%.c
	@$(CC) $(CFLAG) -c $< -o $@

$(NAME): $(OBJ_DIR) $(OBJ)
	@$(CC) $(CFLAG) $(INC) $(OBJ) -o $(NAME)
	
clean:
	@$(RM) $(OBJ_DIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: start all clean fclean re
