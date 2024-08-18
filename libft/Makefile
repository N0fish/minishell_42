# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: algultse <algultse@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/06 16:46:39 by algultse          #+#    #+#              #
#    Updated: 2024/08/09 23:45:40 by algultse         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc -c
INCLUDE = -I./
FLAGS = -Wall -Wextra -Werror
AR = ar rcs
OBJDIR = ./obj/

SRC = ft_atoi.c ft_bzero.c ft_isascii.c ft_isalnum.c ft_calloc.c \
		ft_isalpha.c ft_isdigit.c ft_isprint.c ft_memchr.c ft_memcpy.c \
		ft_memmove.c ft_memset.c ft_strchr.c ft_strdup.c ft_strlcat.c \
		ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
		ft_tolower.c ft_toupper.c ft_memcmp.c ft_substr.c ft_strjoin.c \
		ft_split.c ft_strtrim.c ft_itoa.c ft_strmapi.c ft_striteri.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		ft_ternary.c ft_atoi_long.c ft_atoi_long_long_int.c ft_strcmp.c \
		get_next_line.c ft_printf.c ft_printf_utils.c \
		ft_malloc.c ft_malloc_utils.c ft_split_m.c ft_strjoin_m.c \
		ft_strdup_m.c ft_substr_m.c ft_itoa_m.c ft_itoa_long_long_int_m.c \
		ft_array_len.c ft_strtok.c ft_strcpy.c ft_free_char_array.c \
		ft_strncpy.c ft_strcat.c

OBJ = $(SRC:%.c=$(OBJDIR)%.o)

all : $(NAME)

$(NAME) : $(OBJ)
		$(AR) $(NAME) $(OBJ)

$(OBJDIR)%.o: %.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -f $(OBJ)
	rm -rf $(OBJDIR)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY: all clean fclean re