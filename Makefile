# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybahri <ybahri@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/02 01:00:28 by ybahri            #+#    #+#              #
#    Updated: 2025/07/24 11:46:56 by ybahri           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CC_FLAGS = -Wall -Wextra -Werror
OBJDIR = obj
HEADER = philo.h
SRCDIR = .
INFILES =	main.c \
			init.c \
			parsing.c \
			security.c \
			utils.c \
			getters_setters.c \
			write_status.c \
			dinner.c \
			monitor.c \
			sync_utils.c \

OBJFILES = $(INFILES:%.c=$(OBJDIR)/%.o)

NAME = philo

all: setup $(NAME)

$(NAME): $(OBJFILES) $(HEADER)
	$(CC) $(CC_FLAGS) $(OBJFILES) -o $(NAME) -pthread

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CC_FLAGS) -c $< -o $@ -pthread

setup:
	@mkdir -p $(OBJDIR)

clean:
	rm -f $(OBJFILES)
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean setup re
