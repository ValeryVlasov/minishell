NAME = minishell

SRC =	main.c\
		./parser/delete_quotes.c ./parser/element_trim_line.c ./parser/first_trim_line.c \
		./parser/init_struct_mini.c ./parser/noda_env.c ./parser/parser.c ./parser/signals.c\
		./parser/expend_path.c ./parser/syntax_error.c ./parser/noda_word.c \
		utils/mem_delete.c utils/utils.c utils/errors.c\
		file/checks.c file/heredoc.c file/file_handl.c\
		env/shell_lvl.c env/env.c\
		cmd_handl/counting.c cmd_handl/handling_main_cmd.c\
		cmd_handl/handling_cmd_utils.c cmd_handl/bin.c cmd_handl/cmd_init.c\
		builtins/check_built.c builtins/cd.c builtins/echo.c builtins/env.c builtins/exit.c builtins/pwd.c builtins/unset.c builtins/export.c builtins/export_utils.c\
		gnl/get_next_line.c gnl/get_next_line_utils.c ./parser/find_syntax_word.c ./parser/help_path.c

SRC_LIB	=	libft/ft_lstadd_back.c libft/ft_lstadd_front.c libft/ft_lstclear.c libft/ft_lstdelone.c libft/ft_lstiter.c libft/ft_lstlast.c libft/ft_lstmap.c libft/ft_lstnew.c libft/ft_lstsize.c\
			libft/ft_atoi.c libft/ft_bzero.c libft/ft_calloc.c libft/ft_isalnum.c libft/ft_isalpha.c libft/ft_isascii.c libft/ft_isdigit.c libft/ft_isprint.c libft/ft_isspace.c libft/ft_itoa.c libft/ft_memccpy.c libft/ft_memchr.c libft/ft_memcmp.c libft/ft_memcpy.c libft/ft_memmove.c libft/ft_memset.c libft/ft_putchar_fd.c libft/ft_putendl_fd.c libft/ft_putnbr_fd.c libft/ft_putstr_fd.c libft/ft_split.c libft/ft_strchr.c libft/ft_strdup.c libft/ft_strjoin.c libft/ft_strlcat.c libft/ft_strlcpy.c libft/ft_strmapi.c libft/ft_strcmp.c libft/ft_strncmp.c libft/ft_strnstr.c libft/ft_strrchr.c libft/ft_strrev.c libft/ft_strtrim.c libft/ft_substr.c libft/ft_tolower.c libft/ft_toupper.c libft/ft_strlen.c
OBJ		=	$(SRC:.c=.o)
LIBDIR	=	./libft
RLDIR	=	/Users/$(USER)/.brew/opt/readline/include/readline
LIB		=	$(LIBDIR)/libft.a
CC		=	gcc
CFLAGS	=	 -g -I$(RLDIR) -Wall -Wextra -Werror
LFLAGS	=	-L /Users/$(USER)/.brew/opt/readline/lib -lreadline -lhistory -L $(LIBDIR) -lft
HEADER	=	minishell.h

.PHONY	:	all clean fclean re libft minilibs sbor_minishell

all		:	$(NAME)

$(LIB)	:
			make -s -C $(LIBDIR)

$(NAME)	:	$(OBJ)  Makefile
			$(CC) $(CFLAGS) $(LFLAGS) $(OBJ) -o $(NAME)

%.o		:	%.c $(HEADER) $(LIB)
			$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

clean	:
			rm -f $(OBJ)
			make clean -C $(LIBDIR)

fclean	:	clean
			make fclean -C $(LIBDIR)
			rm -f $(NAME)

re		:	fclean all
