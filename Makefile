# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: enennige <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/04 14:06:38 by enennige          #+#    #+#              #
#    Updated: 2018/06/16 19:18:20 by enennige         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
NAME = lemin
CFLAGS = -Wall -Wextra -Werror
SRC_PATH = srcs/
SRC_NAME = main.c read_input.c build_anthill.c identify_linetype.c solve.c
SRC_NAME += build_roomlist.c build_adjlist.c search.c choose_routes.c
SRC_NAME += anthill_util.c print_turns.c
SRCS = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJS = $(patsubst %.c, %.o, $(SRC_NAME))
LIB_NAME = libft
LIB_OPT = -L ./$(LIB_NAME)/ -lft
LIB_HEADER = -I ./$(LIB_NAME)/includes/
HEADER = includes/
INCLUDES = -I $(HEADER) $(LIB_HEADER)

# TEST FRAMEWORK
TS_NAME = check.out
TEST_HEADER = $$HOME/.brew/include/
TEST_LIBRARY = $$HOME/.brew/lib/
TEST = tests
TS = $(patsubst %.a, %.check, $(NAME))
TEST_CHECK = $(addprefix $(TEST)/, $(TS))
TEST_SRC = $(addsuffix .c, $(TEST_CHECK))
TEST_FLAGS = -I$(TEST_HEADER) -L$(TEST_LIBRARY) -lcheck $(LIB_OPT)

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

make_test: clean_test $(NAME)
	checkmk $(TEST_CHECK) > $(TEST_SRC)
	$(CC) $(CFLAGS) $(TEST_FLAGS) $(TEST_SRC) -o $(TS_NAME)

run_test: make_test
	./$(TS_NAME); make clean_test

clean_test:
	/bin/rm -f $(TEST_SRC)
	/bin/rm -f $(TS_NAME)
	/bin/rm -rf $(TS_NAME).dSYM

single_test: $(TEST)/single.c
	$(CC) $(CFLAGS) $(INCLUDES) $(TEST)/single.c -o single.test $(LIB_OPT)
	./single.test
	/bin/rm single.test

re: fclean all
