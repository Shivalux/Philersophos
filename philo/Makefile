# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sharnvon <sharnvon@student.42bangkok.com>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/08 00:28:26 by sharnvon          #+#    #+#              #
#    Updated: 2022/09/03 20:33:45 by sharnvon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
PTHREAD = -pthread
RM = rm -rf
NORM = norminette
NFLAG_C = -R CheckForbiddenSourceHeader
NFLAG_H = -R CheckDefine


NAME = philo
LIB = philospher.a
HEAD = philosopher.h
SRCS = philosopher.c \
	   philosopher_thread.c \
	   philosopher_util.c
OBJS = $(SRCS:.c=.o)

BOLD = \e[1m
/BOLD = \e[0m
RESET = \033[0m
RED = \033[0;31m
GREEN =\033[0;36m
BLUE = \033[0;34m


all: $(OBJS)
	@echo "  $(RED)-->$(RESET) $(GREEN)$(BOLD)Project files was made..$(/BOLD)$(RESET) $(RED)<--$(RESET)"
	ar -rc $(LIB) $(OBJS)
	@echo "  $(RED)-->$(RESET) $(GREEN)library file was made....$(RESET)$(RED)<--$(RESET)"
	$(CC) $(CFLAGS) $(PTHREAD) $(LIB) -o $(NAME)
	@echo "  $(RED)-->$(RESET) $(GREEN)program \"philo\" complied :)$(RESET) $(RED)<--$(RESET)"

.PHONY: all

norminette:
	$(NORM) $(NFLAG_C) $(SRCS)
	$(NORM) $(NFLAG_H) $(HEAD)
	@echo "  $(RED)-->$(GREEN) norminette check == OKAY :)$(RESET) $(RED)<--$(RESET)"
.PHONY: norminette

clean:
	$(RM) $(OBJS)
	@echo "  $(RED)-->$(RESET) $(GREEN)object files was removed$(RESET) $(RED)<--$(RESET)"
.PHONY: clean

fclean: clean
	$(RM) $(NAME) $(LIB)
	@echo "  $(RED)-->$(RESET) $(GREEN)program \"philo\" and library file were removed$(RESET) $(RED)<--$(RESET)"
.PHONY: fclean

re: fclean all
.PHONY: re
