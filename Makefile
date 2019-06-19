# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ggwin-go <ggwin-go@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/02 16:04:28 by dwisoky           #+#    #+#              #
#    Updated: 2019/06/19 11:43:38 by ggwin-go         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh
FLAGS = -Wall -Wextra -Werror
SRCS = main.c exec.c init_exec.c exec_open.c init_attr.c set_fd.c exec_print_error.c exec_redir_right.c exec_fill_fifo.c
OBJS = $(SRCS:.c=.o)
INCLUDES = -I includes -I libft/includes

all:	$(NAME)

$(NAME):	$(OBJS)
				@echo "\x1b[39;01mCompilation...\x1b[39;01m"
				@make --directory ./libft
				@gcc $(FLAGS) $(OBJS) -o $(NAME) -L ./libft -lft $(INCLUDES)
				@echo "\x1b[37;01mYour 21sh is ready\x1b[37;01m"

$(OBJS):	%.o: %.c
				@gcc $(FLAGS) -c -g $< $(INCLUDES) -I libft -o $@
clean:
				@echo "\033[34mDeliting o-files\033[34m"
				@/bin/rm -f $(OBJS)
				@make clean --directory ./libft

fclean:	clean
				@echo "\033[34mDeliting binary\033[34m"
				@/bin/rm -f $(NAME)
				@make fclean --directory ./libft

re:	fclean all

