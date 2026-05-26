NAME = bsq

SRCS_DIR = srcs
INCLUDES_DIR = includes

SRCS = \
	$(SRCS_DIR)/main.c \
	$(SRCS_DIR)/types/bsq_map_core.c \
	$(SRCS_DIR)/types/bsq_map_1.c \
	$(SRCS_DIR)/types/bsq_map_print.c \
	$(SRCS_DIR)/types/linked_list.c \
	$(SRCS_DIR)/str_utils.c \
	$(SRCS_DIR)/print_utils.c \
	$(SRCS_DIR)/file_reader_1.c \
	$(SRCS_DIR)/file_reader_2.c \
    $(SRCS_DIR)/parser_map.c \
	$(SRCS_DIR)/bsq_solver.c


OBJS = $(SRCS:.c=.o)
DEPS = $(OBJS:.o=.d)

CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -MP

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I$(INCLUDES_DIR) -c -o $@ $<

clean:
	rm -f $(OBJS) $(DEPS)

fclean: clean
	rm -f $(NAME)

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re
