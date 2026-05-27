NAME = bsq

SRCS_DIR = srcs
INCLUDES_DIR = includes

SRCS = \
	$(SRCS_DIR)/main.c \
	$(SRCS_DIR)/types/linked_list.c \
	$(SRCS_DIR)/str_utils.c \
	$(SRCS_DIR)/print_utils.c \
	$(SRCS_DIR)/file_stream.c \
	$(SRCS_DIR)/file_stream_reader_1.c \
	$(SRCS_DIR)/file_stream_reader_2.c \
	$(SRCS_DIR)/stream_header_parser.c \
	$(SRCS_DIR)/stream_row_parser_1.c \
	$(SRCS_DIR)/stream_row_parser_2.c \
	$(SRCS_DIR)/bsq_solver_1.c \
	$(SRCS_DIR)/bsq_solver_2.c \
	$(SRCS_DIR)/bsq_solver_print.c


OBJS = $(SRCS:.c=.o)
DEPS = $(OBJS:.o=.d)

CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -MP -g

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
