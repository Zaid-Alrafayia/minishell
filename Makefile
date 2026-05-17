CC          = cc
CFLAGS      = -Wall -Wextra -Werror -I. -I42_libft -I42_gnl
RM          = rm -f

NAME        = minishell


PARSING_SRC = parsing/cmd_builder.c \
              parsing/env_init.c \
              parsing/exec_mock.c \
              parsing/expander.c \
              parsing/free.c \
              parsing/lexer_utils.c \
              parsing/lexer.c \
              parsing/main.c \
              parsing/parse_core.c \
              parsing/syntax_check.c \
              parsing/redirections.c

EXECUTION_SRC = execution/builtin.c \
                execution/builtin2.c \
                execution/builtin_checkers.c \
                execution/env.c \
                execution/exec.c \
                execution/path.c

SRCS        = $(PARSING_SRC) $(EXECUTION_SRC)

OBJS        = $(SRCS:.c=.o)

LIBFT_DIR   = 42_libft
LIBFT_A     = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(LIBFT_A):
	make -C $(LIBFT_DIR) bonus

$(NAME): $(OBJS) $(LIBFT_A)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) -lreadline -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make -C $(LIBFT_DIR) clean
	$(RM) $(OBJS)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re