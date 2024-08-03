NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
LDFLAGS = -lreadline

LIBFTDIR = ./libft/
SRCDIR = ./srcs/
INCDIR = ./include/
OBJDIR = ./obj/

PARSING_SRC = parsing/parsing.c parsing/analyze_redirections.c parsing/string_modif.c parsing/syntax_errors.c
EXEC_SRC = pipex/exec.c pipex/fds.c pipex/pids.c pipex/parsed_utils.c pipex/fds_utils.c pipex/here_doc.c
INIT_SRC = init/init.c init/env.c init/env_init.c init/env_utils.c init/env_prepare.c
BUILTINS_SRC = builtins/builtins.c builtins/builtin_utils.c builtins/echo_builtin.c \
	builtins/cd_builtin.c builtins/pwd_builtin.c builtins/export_builtin.c builtins/export_builtin_utils.c \
	builtins/unset_builtin.c builtins/env_builtin.c builtins/exit_builtin.c
UTILS_SRC = utils/free.c utils/write.c utils/error.c

BASE_SRC = $(PARSING_SRC) $(EXEC_SRC) $(INIT_SRC) $(BUILTINS_SRC) $(UTILS_SRC)

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