# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: enennige <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/04 14:06:38 by enennige          #+#    #+#              #
#    Updated: 2018/06/16 22:22:27 by jpollore         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
NAME = lem-in
CFLAGS = -Wall -Wextra -Werror
SRC_PATH = srcs/
SRC_NAME = main.c read_input.c build_anthill.c identify_linetype.c discover.c
SRC_NAME += build_roomlist.c build_adjlist.c search.c choose_routes.c
SRC_NAME += anthill_util.c print_turns.c routes.c
SRCS = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJS = $(patsubst %.c, %.o, $(SRC_NAME))
LIB_NAME = libft
LIB_OPT = -L ./$(LIB_NAME)/ -lft
LIB_HEADER = -I ./$(LIB_NAME)/includes/
HEADER = includes/
INCLUDES = -I $(HEADER) $(LIB_HEADER)

ifeq ($(CDEBUG), 1)
	CFLAGS += -g
endif

all: $(NAME)

$(NAME):
	make -C $(LIB_NAME)/
	$(CC) $(CFLAGS) $(INCLUDES) -c $(SRCS)
	$(CC) $(CFLAGS) $(OBJS) $(LIB_OPT) -o $(NAME)

clean:
	make clean -C $(LIB_NAME)/
	rm -rf obj/$(OBJS)

fclean: clean
	make fclean -C $(LIB_NAME)/
	rm -f $(NAME)

re_example:
	rm -f $(NAME)
	rm -f $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -c $(SRCS)
	$(CC) $(CFLAGS) $(OBJS) $(LIB_OPT) -o $(NAME)

re: fclean all
