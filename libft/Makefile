# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eeravci <eeravci@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/11 18:11:39 by ksuebtha          #+#    #+#              #
#    Updated: 2025/06/26 20:13:58 by eeravci          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CFLAGS = -Wall -Wextra -Werror
CC = cc
SRC = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
		ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
		ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
		ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
		ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
		ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		get_next_line.c get_next_line_utils.c \
		ft_printf.c ft_putchar_pf.c ft_putstr_pf.c ft_putptr_pf.c \
		ft_putnbr_pf.c ft_convert_pf.c ft_putuint_pf.c \
		ft_strndup.c ft_strcmp.c ft_atol.c
		
OBJ = ${SRC:.c=.o}

#target
# create the library

all: ${NAME}

${NAME}: ${OBJ}
	@ar rcs ${NAME} ${OBJ}
	@echo "library ${NAME} created successfully"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f ${OBJ}
	@echo "All objects files cleaned successfully"

fclean: clean
	@rm -f ${NAME}
	@echo "All objects and library ${NAME} cleaned successfully"

re: fclean all

.PHONY: all clean fclean re
	