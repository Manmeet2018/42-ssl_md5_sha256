# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maparmar <maparmar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/15 20:49:48 by maparmar          #+#    #+#              #
#    Updated: 2019/05/23 15:59:40 by maparmar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Werror -Wextra -I $(INCLUDES)
INCLUDES = libft.h
LIB = libft.a
CC = gcc
AR = ar rc
RM = rm -rf
RANLIB = ranlib
CG = \033[92m
CY =  \033[93m
CE = \033[0m
CB = \033[34m
CR = \x1b[31;01m
FILES = ft_atoi.c \
		ft_bzero.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_memalloc.c \
		ft_memccpy.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memdel.c \
		ft_memmove.c \
		ft_memset.c \
		ft_strcat.c \
		ft_strchr.c \
		ft_strclr.c \
		ft_strcmp.c \
		ft_strcpy.c \
		ft_strdel.c \
		ft_strdup.c \
		ft_striter.c \
		ft_strlcat.c \
		ft_strlen.c \
		ft_strncat.c \
		ft_strncmp.c \
		ft_strncpy.c \
		ft_strnew.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strstr.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_striteri.c \
		ft_strmap.c \
		ft_strmapi.c \
		ft_strequ.c \
		ft_strnequ.c \
		ft_strsub.c \
		ft_strjoin.c \
		ft_iswhitespace.c \
		ft_strwhitespace.c \
		ft_otherwhitespace.c \
		ft_strtrim.c \
		ft_count.c \
		ft_strsplit.c \
		ft_intlen.c \
		ft_itoa.c \
		ft_putchar.c \
		ft_putstr.c \
		ft_putendl.c \
		ft_putnbr.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_lstnew.c \
		ft_lstdelone.c \
		ft_lstdel.c \
		ft_lstadd.c \
		ft_lstiter.c \
		ft_lstmap.c

OBJ = $(FILES:.c=.o)

%.o: %.c
	@echo "\033[K$(CY)[LIBFT] :$(CE) $(CR)Compiling $<$(CE)\033[1A";
	@$(CC) $(CFLAGS) -c $< -o $@

nohd: $(OBJ)
	@echo "\033[K$(CY)[LIBFT] :$(CE) $(CR)Creating Library$(CE)\033[1A";
	@$(AR) $(LIB) $(OBJ)
	@$(RANLIB) $(LIB)

nohdclean:
	@echo "\033[K$(CY)[LIBFT] :$(CE) $(CG)Cleaning object files...$(CE)\033[1A";
	@$(RM) $(OBJ)

nohdfclean: nohdclean
	@echo "\033[K$(CY)[LIBFT] :$(CE) $(CG)Cleaning Library...$(CE)\033[1A";
	@$(RM) $(LIB)

all: $(NAME)

$(NAME):
	gcc $(CFLAGS) -c $(FILES)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

clean:
	@$(RM) $(OBJ)
	@echo "\033[K$(CY)[LIBFT] :$(CG) $(CR)objects cleaned $(CE)\033[1A";

fclean: clean
	@echo "\033[K$(CY)[LIBFT] :$(CG) $(CR)Library deleted $(CE)\033[1A";
	@$(RM) $(NAME)
	

re: fclean all

.PHONY: clean fclean all re
