# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eeravci <enes.nev@gmail.com>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/22 14:27:28 by eeravci           #+#    #+#              #
#    Updated: 2025/01/22 14:27:30 by eeravci          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Project files
NAME = libftprintf.a
SRC = ft_printf.c ft_printhex.c ft_printnumber.c \
      ft_printpercent.c ft_printptr.c ft_printstring.c \
      ft_printunsigned.c
OBJ = $(SRC:.c=.o)

# Default rule
all: $(NAME)

# Create the library
$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

# Compile .c files to .o
%.o: %.c ft_printf.h
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	rm -f $(OBJ)

# Clean object files and library
fclean: clean
	rm -f $(NAME)

# Rebuild everything
re: fclean all
