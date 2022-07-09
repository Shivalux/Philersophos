# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sharnvon <sharnvon@student.42bangkok.com>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/08 00:28:26 by sharnvon          #+#    #+#              #
#    Updated: 2022/07/08 14:36:32 by sharnvon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
NORM = norminette
NFLAG_C = -R CheckForbiddenSourceHeader
NFLAG_H = -R CheckDefine


NAME = philo
LIB = philospher.a
HEAD = philosopher.h
MAIN = philosopher.c
SRCS =
OBJS = $(SRC:.c=.o)

RESET = 
RED =
GREEN =
BLUE = 

all: $(OBJS)
	@echo "$(RED)-->$(RESET) object files was made $(RED)<--$(RESET)"
	ar -rc $(LIB) $(OBJS)
	@echo "/t$(RED)-->$(RESET) $(GREEN)library file was made$(RESET) :) $(RED)<--$(RESET)"
	$(CC) $(CFLAGS) $(MAIN) $(LIB)
	@echo "/t/t$(RED)-->$(RESET) $(GREEN)progarm "philo" complete$(RESET) $(RED)<--$(RESET)"

.PHONY: all

norminette:
	$(NORM) $(NFLAG_C) $(SRCS)
	$(NORM) $(NFLAG_H) $(HEAD)
	@echo "$(GREEN)--> norminette = OKAY :) <--$(RESET)"
.PHONY: norminette

clean:
	$(RM) $(OBJS)
	@echo "--> object files was removed <--"
.PHONY: clean

fclean: clean
	$(RM) $(NAME) $(LIB)
	@echo "--> program "philo" and library files were removed <--"
.PHONY: fclean

re: fclaen all
.PHONY: re
