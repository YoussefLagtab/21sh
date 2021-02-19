# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/08 10:36:53 by ylagtab           #+#    #+#              #
#    Updated: 2021/02/19 09:23:42 by ylagtab          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#	variables																   #
# **************************************************************************** #

# name
NAME = 21sh
LIBFT = libft/libft.a

# compilation variables
CFLAGS = -Wall -Wextra -Werror -g
CC = gcc

# objects																	   #
21sh_INC = src/twenty_one.h src/parser/parser.h src/expansion/expansion.h \
	src/typedefs.h src/errors/errors.h src/redirections/redirections.h
21sh = main.o \
	parser/parser.o parser/tokenization.o parser/tokenization_helpers.o \
	parser/construct_commands.o parser/syntax_analys.o parser/util.o \
	expansion/expansion.o expansion/expand_word.o expansion/tilde_expansion.o \
	expansion/env_var_expansion.o expansion/tokens_to_fileds.o \
	execution/exec_simple_command.o \
	errors/errors.o \
	redirections/perform_redirections.o redirections/redirect_output.o \
	redirections/redirect_input.o redirections/remove_redirections_tokens.o \
	redirections/fd_aggregation.o \
	built_in/cd.o built_in/cd_utils.o built_in/env.o built_in/env_tools.o \
	built_in/env_ops.o built_in/run_built_in.o built_in/echo.o built_in/exit.o

21sh_OBJS = $(addprefix $(OBJS_DIR)/, ${21sh})

# objects directory
OBJS_DIR = objs

# Colors
BLACK	= \033[30m
RED		= \033[31m
GREEN	= \033[32m
YELLOW	= \033[93m
BLUE	= \033[34m
MAGENTA	= \033[35m
CYAN	= \033[36m
WHITE	= \033[37m
RESET	= \033[0m

# **************************************************************************** #
#	rules																	   #
# **************************************************************************** #
all: $(NAME)

$(NAME): $(21sh_OBJS) $(LIBFT)
	@$(CC) -o $(NAME) $(21sh_OBJS) $(LIBFT)
	@echo "$(GREEN)program$(RESET) $(NAME): $(GREEN)UPDATED!$(RESET)";

$(LIBFT): force
	@make -C libft/

force:

$(21sh_OBJS): $(OBJS_DIR)/%.o : src/%.c $(21sh_INC) | $(OBJS_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ -I src/
	@echo "$(YELLOW)OBJ$(RESET) $<: $(YELLOW)UPDATED!$(RESET)";

$(OBJS_DIR):
	@if [ ! -d $(OBJS_DIR) ]; then \
		echo "$(CYAN)DIR$(RESET) $(OBJS_DIR)/: $(CYAN)CREATED!$(RESET)"; \
		mkdir $(OBJS_DIR); \
	fi;

clean:
	@make fclean -C libft/
	@if [ -d $(OBJS_DIR) ]; then \
		echo "$(RED)OBJ$(RESET) minishell objs: $(RED)REMOVED!$(RESET)"; \
		rm -rf $(OBJS_DIR); \
	fi;

fclean: clean
	@make fclean -C libft/
	@if [ -f $(NAME) ]; then \
		echo "$(RED)program$(RESET) $(NAME): $(RED)REMOVED!$(RESET)"; \
		rm -f $(NAME); \
	fi;

re:
	@make fclean
	@make all

.PHONY: all clean fclean re libft
