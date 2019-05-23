SRC = ft_ssl.c ft_writer.c ft_md5.c memory_helper.c util_parser.c \
util_stdin_parser.c ft_sha256.c

NAME = ft_ssl

OBJDIR = objects/
SRCDIR = sources/
OBJ = $(addprefix $(OBJDIR), $(SRC:.c=.o))

LIB = libft/libft.a
FLAG = -Wall -Wextra -Werror
CC = gcc
CRED = \x1b[31;01m
CYEL =  \033[0;33m
CGRE =  \033[0;32m
CBLUE =  \033[34m
CNO = \033[0m
INC = -I ./includes/

all: lib $(NAME)

lib:
	-@make -C libft nohd
	@mkdir -p $(OBJDIR)

$(NAME): $(OBJ)
	@gcc -o $(NAME) $(OBJ) $(FLAG) $(INC) $(LIB);
	@echo "\033[K$(CYEL)[FT_SSL] :$(CNO) $(CRED)Compiling ft_ssl$(CNO)";

$(OBJ): $(OBJDIR)%.o: $(SRCDIR)%.c
	@echo "\033[K$(CYEL)[FT_SSL] :$(CNO) $(CRED)Compiling $<$(CNO)";
	@gcc $(FLAG) -c $< -o $@ $(INC)

clean: 
	@echo "$(CYEL)[FT_SSL] :$(CNO) $(CGRE)Cleaning ft_ssl objects$(CE)";
	-@make -C libft nohdclean;
	@/bin/rm -rf $(OBJ);
	@echo "$(CYEL)[FT_SSL] : $(CGRE)Cleaned Successfully$(CNO)";

fclean:
	@echo "\033[K$(CYEL)[FT_SSL] :$(CNO) $(CGRE)Cleaning all binairies ...$(CNO)";
	-@make -C libft nohdfclean;
	@/bin/rm -f $(NAME);
	@echo "\033[K$(CYEL)[FT_SSL] :$(CNO) $(CBLUE) Cleaned successfully binairies ...$(CNO)";
re: fclean all

.PHONY: all clean fclean re
