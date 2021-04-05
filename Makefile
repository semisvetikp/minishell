NAME    =   minishell
H		=	minishell.h
OBJ_DIR = 	obj
SRCS_DIR = 	srcs

LIBFT   =   libft.a
SRC     :=  main.c list.c functions.c functions2.c ft_cd.c daughter.c handling_error.c\
			parser.c export.c pipe.c redirect.c utils.c valid.c pars_redirect.c pars_redirect2.c\
			parse_utils_1.c quotes.c valid_redirect.c parse_utils_2.c second_valid.c \
			coder.c replace_env.c termcap.c term_utils.c signal_main_u.c main_utils.c \
			main_utils_2.c term_utils_2.c daughter2.c

CC      =   gcc -Ilibft -Iincludes
FLAGS	=	-Wall -Wextra -Werror

HEAD	=  includes

HEADERS = $(addprefix $(HEAD)/, $(H))
SRCS = $(addprefix $(SRCS_DIR)/, $(SRC))
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJ)
		$(MAKE) -C ./libft/
		mv ./libft/libft.a .
		$(CC) -o $(NAME) $(OBJ) libft.a -ltermcap

$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c $(HEAD)/$(H)
		@mkdir -p $(OBJ_DIR)
		$(CC) $(FLAGS) -c $< -o $@

clean:
	-rm -f $(OBJ)
	rm -f ./libft/*.o

fclean:     clean
	make -C ./libft fclean
	-rm -f $(NAME)
	rm -f ./libft.a

re:         fclean all
.PHONY:     all clean fclean re