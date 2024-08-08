NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
LDFLAGS = -lreadline

LIBFTDIR = ./libft/
SRCDIR = ./srcs/
INCDIR = ./include/
OBJDIR = ./obj/

PARSER_SRC = parser/cmd_utils.c parser/parser.c
INIT_SRC = init/init.c init/env.c init/env_init.c init/env_utils.c init/env_prepare.c
LEXER_SRC = lexer/lexer.c
BUILTINS_SRC = builtins/builtins.c builtins/builtin_utils.c builtins/echo_builtin.c \
	builtins/cd_builtin.c builtins/pwd_builtin.c builtins/export_builtin.c builtins/export_builtin_utils.c \
	builtins/unset_builtin.c builtins/env_builtin.c builtins/exit_builtin.c
# EXECUTOR_SRC = executor/command.c executor/executor.c
EXECUTOR_SRC = exec/exec.c exec/fds_utils.c exec/fds.c exec/here_doc.c exec/parsed_utils.c exec/pids.c exec/command.c
UTILS_SRC = utils/free.c utils/write.c utils/error.c utils/node.c

BASE_SRC = $(PARSER_SRC) $(EXECUTOR_SRC) $(INIT_SRC) $(LEXER_SRC) $(BUILTINS_SRC) $(UTILS_SRC)

SRC =  $(BASE_SRC) main.c
OBJS = $(SRC:%.c=$(OBJDIR)%.o)

LIBFT = -L$(LIBFTDIR) -lft

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)

$(LIBFT):
	make -C $(LIBFTDIR)

$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INCDIR) -I$(LIBFTDIR) -c $< -o $@

clean:
	rm -rf $(OBJDIR)
	make clean -C $(LIBFTDIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFTDIR)

re: fclean all

.PHONY: all clean fclean re