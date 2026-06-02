CC          = cc
CFLAGS      = -Wall -Wextra -Werror -I. -I42_libft -fsanitize=address -O0 -g3
RM          = rm -f

NAME        = minishell

PARSING_SRC = parsing/lexer_utils.c \
              parsing/lexer.c \
              parsing/syntax_check.c \
              parsing/syntax_check_utils.c \
              parsing/env_init.c \
              parsing/free.c \
              parsing/cmd_builder.c \
              parsing/redirections.c \
              parsing/heredoc.c \
              parsing/expander_utils.c \
              parsing/expander_core.c \
              parsing/parse_core.c \
              parsing/exec_mock.c \
              parsing/signals.c \
              main.c

EXECUTION_SRC = execution/builtin.c \
                execution/builtin2.c \
                execution/builtin3.c \
                execution/builtin4.c \
                execution/builtin5.c \
                execution/builtin6.c \
                execution/builtin_checkers.c \
                execution/env_utils.c \
                execution/fd_utils.c \
                execution/env.c \
                execution/exec.c \
                execution/exec2.c \
                execution/exec_utils.c \
                execution/path.c \
                execution/ft_echo.c \
                execution/pipe.c \
                execution/pipe_utils.c

UTILS         = utils/free.c \
                utils/utils.c 

SRCS        = $(PARSING_SRC) $(EXECUTION_SRC) $(UTILS)

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