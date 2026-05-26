STRIKE = malloc_strike.so

CC = cc
CFLAGS = -Wall -Wextra -Werror
STRIKE_FLAGS = -shared -fPIC

SRC = malloc_strike.c

all: $(STRIKE)

$(STRIKE): $(SRC)
	$(CC) $(CFLAGS) $(STRIKE_FLAGS) -o $(STRIKE) $(SRC) -ldl

clean:
	rm -f $(STRIKE)

re: clean all

.PHONY: all clean re
