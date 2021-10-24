# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: brattles <brattles@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/19 22:39:05 by brattles          #+#    #+#              #
#    Updated: 2021/10/22 12:33:19 by brattles         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= philo

CC			:= gcc
WFLAGS		:= -Wall -Wextra -Werror

INC_DIR		:= includes
OBJ_DIR		:= build

FUNCTIONS	= philo.c \
			  ft_parse.c \
			  ft_lifecycle.c \
			  ft_panic.c \
			  ft_utl1.c \
  			  ft_clean.c

OBJ			:= $(FUNCTIONS:%.c=$(OBJ_DIR)/%.o)
DEP			:= $(OBJ:%.o=%.d)

CFLAGS		:= $(WFLAGS) -pthread -g -MMD

INC			:= -I$(INC_DIR)

vpath %.c src

.PHONY:	all clean fclean re debug

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(INC) -o $(NAME)

-include $(DEP)
$(OBJ_DIR)/%.o: %.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all
