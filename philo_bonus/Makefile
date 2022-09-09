# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sharnvon <sharnvon@student.42bangkok.com>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/08 00:28:26 by sharnvon          #+#    #+#              #
#    Updated: 2022/09/08 21:34:43 by sharnvon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
PTHREAD = -pthread
RM = rm -rf
NORM = norminette
NFLAG_C = -R CheckForbiddenSourceHeader
NFLAG_H = -R CheckDefine


NAME = philo_bonus
LIB = philosopher_bonus.a
HEAD = philosopher_bonus.h
SRCS = philosopher_bonus.c \
	   philosopher_thread_bonus.c \
	   philosopher_util1_bonus.c \
	   philosopher_util2_bonus.c \
	   philosopher_initialise.c
OBJS = $(SRCS:.c=.o)

RESET = \033[0m
RED = \033[0;31m
GREEN =\033[0;36m
BLUE = \033[0;34m


all: $(OBJS)
	@echo "  $(RED)-->$(RESET) $(GREEN)Object files was made..$(RESET) $(RED)<--$(RESET)"
	ar -rc $(LIB) $(OBJS)
	@echo "  $(RED)-->$(RESET) $(GREEN)Library file was made....$(RESET)$(RED)<--$(RESET)"
	$(CC) $(CFLAGS) $(PTHREAD) $(LIB) -o $(NAME)
	@echo "  $(RED)-->$(RESET) $(GREEN)Program \"philo_bonus\" complied :)$(RESET) $(RED)<--$(RESET)"
.PHONY: all

$(NAME): all

bonus: all
.PHONY: bonus
	
norminette:
	$(NORM) $(NFLAG_C) $(SRCS)
	$(NORM) $(NFLAG_H) $(HEAD)
	@echo "  $(RED)-->$(GREEN) Norminette check == OKAY :)$(RESET) $(RED)<--$(RESET)"
.PHONY: norminette

clean:
	$(RM) $(OBJS)
	@echo "  $(RED)-->$(RESET) $(GREEN)Object files was removed$(RESET) $(RED)<--$(RESET)"
.PHONY: clean

fclean: clean
	$(RM) $(NAME) $(LIB)
	@echo "  $(RED)-->$(RESET) $(GREEN)Program \"philo_bonus\" and library file were removed$(RESET) $(RED)<--$(RESET)"
.PHONY: fclean

re: fclean all
.PHONY: re
