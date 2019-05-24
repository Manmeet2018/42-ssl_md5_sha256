CC = gcc
FLAGS = -Wall -Wextra -Werror
NAME = ft_ssl

SRC = ft_ssl.c
SRC += ft_md5.c
SRC += memory_helper.c
SRC += util_parser.c
SRC += util_stdin_parser.c
SRC += ft_sha256.c
SRC += ft_writer.c

OBJ = $(SRC:.c=.o)
LIB = ./libft/libft.a
INC = -I ./includes/

CRED = \x1b[31;01m
CYEL =  \033[0;33m
CGRE =  \033[0;32m
CBLUE =  \033[34m
CNO = \033[0m

.PHONY: all clean fclean re lib

all: $(NAME)

$(NAME): lib
	@$(CC) $(FLAGS) $(SRC) $(LIB) -o $(NAME)
	@echo "\033[K$(CYEL)[FT_SSL] :$(CNO) $(CRED)Complied ft_ssl$(CNO)";

lib:
	@$(MAKE) -C ./libft/
	
clean:
	@echo "$(CYEL)[FT_SSL] :$(CNO) $(CGRE)Cleaning ft_ssl objects$(CE)";
	@rm -f $(OBJ)
	@$(MAKE) -C ./libft/ clean
	@echo "$(CYEL)[FT_SSL] : $(CGRE)Cleaned Successfully$(CNO)";

fclean:	clean
	@echo "\033[K$(CYEL)[FT_SSL] :$(CNO) $(CGRE)Cleaning all binairies ...$(CNO)";
	@rm -f $(NAME)
	@$(MAKE) -C ./libft/ fclean
	@echo "\033[K$(CYEL)[FT_SSL] :$(CNO) $(CBLUE) Cleaned successfully binairies ...$(CNO)";
re: fclean all

.PHONY: all clean fclean re